/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2011 University of Trento, Italy
 *                    University of California, Los Angeles, U.S.A.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Authors: Alessandro Russo <russo@disi.unitn.it>
 *          University of Trento, Italy
 *          University of California, Los Angeles U.S.A.
 *
 * Example on installing pimdm module in nodes.
 */

#include <iostream>
#include <fstream>
#include <cassert>

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/olsr-helper.h"
#include "ns3/pimdm-helper.h"
#include "ns3/ipv4-static-routing-helper.h"
#include "ns3/ipv4-list-routing-helper.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("PimDmExample1");

int
main (int argc, char *argv[])
{
  LogComponentEnable("PimDmExample1",
        LogLevel(LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
  LogComponentEnable("OlsrRoutingProtocol",
      LogLevel(LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
  LogComponentEnable("PIMDMMulticastRouting",
      LogLevel(LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
  LogComponentEnable("Socket", LogLevel(LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
  LogComponentEnable("DefaultSimulatorImpl",
      LogLevel(LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));

  // Set up some default values for the simulation.  Use the 
  Config::SetDefault("ns3::OnOffApplication::PacketSize", UintegerValue(210));
  Config::SetDefault("ns3::OnOffApplication::DataRate", StringValue("448kb/s"));

  // Allow the user to override any of the defaults and the above
  // DefaultValue::Bind ()s at run-time, via command-line arguments
  CommandLine cmd;
  cmd.Parse(argc, argv);

  NS_LOG_INFO ("Create nodes.");
  NodeContainer c;
  c.Create(5);
  NodeContainer n02 = NodeContainer(c.Get(0), c.Get(2));
  NodeContainer n12 = NodeContainer(c.Get(1), c.Get(2));
  NodeContainer n32 = NodeContainer(c.Get(3), c.Get(2));
  NodeContainer n34 = NodeContainer(c.Get(3), c.Get(4));
  NodeContainer n14 = NodeContainer(c.Get(1), c.Get(4));

  // Enable OLSR
  NS_LOG_INFO ("Enabling OLSR Routing.");
  OlsrHelper olsr;

  NS_LOG_INFO ("Enabling PIM-DM Routing.");
  PimDmHelper pimdm;

  Ipv4StaticRoutingHelper staticRouting;

  Ipv4ListRoutingHelper list;
  list.Add(staticRouting, 0);
  list.Add(olsr, 10);
  list.Add(pimdm, 11);

  InternetStackHelper internet;
  internet.SetRoutingHelper(list);
  internet.Install(c);

  // We create the channels first without any IP addressing information
  NS_LOG_INFO ("Create channels.");
  PointToPointHelper p2p;
  p2p.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
  p2p.SetChannelAttribute("Delay", StringValue("2ms"));
  NetDeviceContainer nd02 = p2p.Install(n02);
  NetDeviceContainer nd12 = p2p.Install(n12);
  NetDeviceContainer nd32 = p2p.Install(n32);
  NetDeviceContainer nd34 = p2p.Install(n34);
  NetDeviceContainer nd14 = p2p.Install(n14);

  // Later, we add IP addresses.  
  NS_LOG_INFO ("Assign IP Addresses.");
  Ipv4AddressHelper ipv4;
  ipv4.SetBase("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer i02 = ipv4.Assign(nd02);

  ipv4.SetBase("10.1.2.0", "255.255.255.0");
  Ipv4InterfaceContainer i12 = ipv4.Assign(nd12);

  ipv4.SetBase("10.1.3.0", "255.255.255.0");
  Ipv4InterfaceContainer i32 = ipv4.Assign(nd32);

  ipv4.SetBase("10.1.4.0", "255.255.255.0");
  Ipv4InterfaceContainer i34 = ipv4.Assign(nd34);

  ipv4.SetBase("10.1.5.0", "255.255.255.0");
  Ipv4InterfaceContainer i14 = ipv4.Assign(nd14);

  NS_LOG_INFO ("Create Applications.");
  uint16_t port = 9;
  Ptr<ConstantRandomVariable> onv = CreateObject<ConstantRandomVariable>();
  onv->SetAttribute("Constant", DoubleValue(1));
  Ptr<ConstantRandomVariable> offv = CreateObject<ConstantRandomVariable>();
  offv->SetAttribute("Constant", DoubleValue(0));

  OnOffHelper onoff("ns3::UdpSocketFactory", InetSocketAddress(i34.GetAddress(0), port));
  onoff.SetAttribute("OnTime", PointerValue(onv));
  onoff.SetAttribute("OffTime", PointerValue(offv));

  // Create a flow from n3 to n4, starting at time 1
  ApplicationContainer apps = onoff.Install(c.Get(0));
  apps.Start(Seconds(1.0));
  apps.Stop(Seconds(100.0));

  // Create a packet sink to receive these packets
  PacketSinkHelper sink("ns3::UdpSocketFactory", InetSocketAddress(Ipv4Address::GetAny(), port));
  apps = sink.Install(c.Get(4));
  apps.Start(Seconds(1.0));
  apps.Stop(Seconds(10.0));

  // Create a flow from n1 to n2, starting at time 10
  onoff.SetAttribute("Remote", AddressValue(InetSocketAddress(i12.GetAddress(0), port)));
  apps = onoff.Install(c.Get(1));
  apps.Start(Seconds(10));
  apps.Stop(Seconds(100.0));

  // Create a packet sink to receive these packets
  apps = sink.Install(c.Get(2));
  apps.Start(Seconds(5));
  apps.Stop(Seconds(10.0));

  AsciiTraceHelper ascii;
  p2p.EnableAsciiAll(ascii.CreateFileStream("simple-point-to-point-olsr.tr"));
  p2p.EnablePcapAll("simple-point-to-point-olsr");

  Simulator::Stop(Seconds(110));

  NS_LOG_INFO ("Run Simulation.");
  Simulator::Run();
  Simulator::Destroy();
  NS_LOG_INFO ("Done.");

  return 0;
}
