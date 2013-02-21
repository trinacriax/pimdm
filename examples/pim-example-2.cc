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
 * Source:  http://www.ietf.org/rfc/rfc3973.txt
 *
 * Authors: Alessandro Russo <russo@disi.unitn.it>
 *          University of Trento, Italy
 *          University of California, Los Angeles U.S.A.
 */

#include <iostream>
#include <fstream>
#include <cassert>
#include <string>

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/applications-module.h"
#include "ns3/mobility-module.h"
#include "ns3/csma-helper.h"
#include "ns3/olsr-helper.h"
#include "ns3/pimdm-helper.h"
#include "ns3/pimdm-routing.h"
#include "ns3/igmpx-helper.h"
#include "ns3/string.h"
#include <sstream>

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("PimDmExample2");

static void
SinkRx (Ptr<const Packet> p, const Address &ad)
{
  std::cout << "Received Packet " << p->GetSize() << " bytes from " << InetSocketAddress::ConvertFrom(ad).GetIpv4()
      << std::endl;
}

int
main (int argc, char *argv[])
{
  LogComponentEnable("PimDmExample2", LogLevel(LOG_LEVEL_ALL | LOG_LEVEL_DEBUG | LOG_LEVEL_INFO | LOG_PREFIX_TIME | LOG_PREFIX_NODE | LOG_PREFIX_FUNC));
//	LogComponentEnable ("UdpSocketImpl", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
//	LogComponentEnable ("OnOffApplication", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
  LogComponentEnable("PacketSink", LogLevel(LOG_LEVEL_ALL | LOG_LEVEL_DEBUG | LOG_LEVEL_INFO | LOG_PREFIX_TIME | LOG_PREFIX_NODE | LOG_PREFIX_FUNC));
//	LogComponentEnable ("OlsrRoutingProtocol", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
  LogComponentEnable("PIMDMMulticastRouting", LogLevel(LOG_LEVEL_ALL | LOG_LEVEL_DEBUG | LOG_LEVEL_INFO | LOG_PREFIX_TIME | LOG_PREFIX_NODE | LOG_PREFIX_FUNC));
//	LogComponentEnable ("Ipv4L3Protocol", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
//	LogComponentEnable ("Ipv4ListRouting", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
//	LogComponentEnable ("CsmaNetDevice", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
//	LogComponentEnable ("CsmaChannel", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
//	LogComponentEnable ("CsmaHelper", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
//	LogComponentEnable ("Socket", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
//	LogComponentEnable ("Node", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
//	LogComponentEnable ("Ipv4EndPointDemux", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
//	LogComponentEnable ("Ipv4RawSocketImpl", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
//	LogComponentEnable ("UdpL4Protocol", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
//	LogComponentEnable ("Packet", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));

  CommandLine cmd;
  bool enableFlowMonitor = false;
  cmd.AddValue("EnableMonitor", "Enable Flow Monitor", enableFlowMonitor);
  cmd.Parse(argc, argv);

  NS_LOG_INFO ("Create nodes.");
  NodeContainer routers;
  routers.Create(5);	// here 5 routers
  NodeContainer n0n1 = NodeContainer(routers.Get(0), routers.Get(1));
  NodeContainer n1n2 = NodeContainer(routers.Get(1), routers.Get(2));
  NodeContainer n1n3 = NodeContainer(routers.Get(1), routers.Get(3));
  NodeContainer n2n4 = NodeContainer(routers.Get(2), routers.Get(4));
  NodeContainer n3n4 = NodeContainer(routers.Get(3), routers.Get(4));
  NodeContainer clients;
  clients.Create(4);	// here 4 clients, id 5-8, 8 is the source
  NodeContainer c0r1 = NodeContainer(clients.Get(0), routers.Get(1));
  NodeContainer c1r2 = NodeContainer(clients.Get(1), routers.Get(2));
  NodeContainer c2r3 = NodeContainer(clients.Get(2), routers.Get(3));
  NodeContainer c3r0 = NodeContainer(clients.Get(3), routers.Get(0));

  NS_LOG_INFO ("Build Topology.");
  CsmaHelper csma;
  csma.SetChannelAttribute("DataRate", DataRateValue(DataRate(5000000)));
  csma.SetChannelAttribute("Delay", TimeValue(MilliSeconds(2)));

  NetDeviceContainer d0d1 = csma.Install(n0n1);
  NetDeviceContainer d1d2 = csma.Install(n1n2);
  NetDeviceContainer d1d3 = csma.Install(n1n3);
  NetDeviceContainer d2d4 = csma.Install(n2n4);
  NetDeviceContainer d3d4 = csma.Install(n3n4);

  NetDeviceContainer d1c1 = csma.Install(c0r1);
  NetDeviceContainer d2c2 = csma.Install(c1r2);
  NetDeviceContainer d3c3 = csma.Install(c2r3);
  NetDeviceContainer d0c4 = csma.Install(c3r0);

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
  internet.Install(routers);

  Ipv4ListRoutingHelper list2;
  list2.Add(staticRouting, 0);
  list2.Add(olsr, 10);
  InternetStackHelper internet2;
  internet2.SetRoutingHelper(list2);
  internet2.Install(clients);

  // Later, we add IP addresses.
  NS_LOG_INFO ("Assign IP Addresses.");
  Ipv4AddressHelper ipv4;
  ipv4.SetBase("10.0.1.0", "255.255.255.0");
  Ipv4InterfaceContainer i0i1 = ipv4.Assign(d0d1);

  ipv4.SetBase("10.1.2.0", "255.255.255.0");
  Ipv4InterfaceContainer i1i2 = ipv4.Assign(d1d2);

  ipv4.SetBase("10.1.3.0", "255.255.255.0");
  Ipv4InterfaceContainer i1i3 = ipv4.Assign(d1d3);

  ipv4.SetBase("10.2.4.0", "255.255.255.0");
  Ipv4InterfaceContainer i2i4 = ipv4.Assign(d2d4);

  ipv4.SetBase("10.3.4.0", "255.255.255.0");
  Ipv4InterfaceContainer i3i4 = ipv4.Assign(d3d4);

  ipv4.SetBase("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer i1i1 = ipv4.Assign(d1c1);

  ipv4.SetBase("10.2.2.0", "255.255.255.0");
  Ipv4InterfaceContainer i2i2 = ipv4.Assign(d2c2);

  ipv4.SetBase("10.3.3.0", "255.255.255.0");
  Ipv4InterfaceContainer i3i3 = ipv4.Assign(d3c3);

  ipv4.SetBase("10.4.4.0", "255.255.255.0");
  Ipv4InterfaceContainer i4i4 = ipv4.Assign(d0c4);

  NS_LOG_INFO ("Configure multicasting.");
  Ipv4Address multicastSource = i4i4.GetAddress(0);
  Ipv4Address multicastGroup ("225.1.2.4");

  /* 1) Configure a (static) multicast route */
  Ptr<Node> sourceNode = clients.Get (3); // The node in question
  Ptr<NetDevice> inputIf = d0c4.Get (0); // The input NetDevice

  Ipv4StaticRoutingHelper multicast;
  multicast.AddMulticastRoute (sourceNode, multicastSource, multicastGroup, inputIf, d0c4.Get(0));

  /* 2) Set up a default multicast route on the sender n0 */
  Ptr<Node> sender = clients.Get (3);
  Ptr<NetDevice> senderIf = d0c4.Get (0);
  multicast.SetDefaultMulticastRoute (sender, senderIf);

  NS_LOG_INFO ("Define multicast groups");
  std::stringstream peerRoleReg;
  peerRoleReg << multicastSource << "," << multicastGroup;
  for (uint32_t n = 0; n < routers.GetN(); n++)
    {
      std::stringstream command; //create a stringstream
      command << "NodeList/" << routers.Get(n)->GetId() << "/$ns3::pimdm::MulticastRoutingProtocol/RegisterSG";
      Config::Set(command.str(), StringValue(peerRoleReg.str()));
      command.str("");
      command << "NodeList/" << routers.Get(n)->GetId() << "/$ns3::igmpx::IGMPXRoutingProtocol/PeerRole";
      Config::Set(command.str(), EnumValue(igmpx::ROUTER));
    }
// CLIENTS IGMPX
  peerRoleReg.str("");
  peerRoleReg << multicastSource << "," << multicastGroup << "," << "1";
  for (uint32_t n = 0; n < clients.GetN(); n++)
    { //Clients are RN nodes
      std::stringstream command;
      command << "/NodeList/" << clients.Get(n)->GetId() << "/$ns3::igmpx::IGMPXRoutingProtocol/PeerRole";
      Config::Set(command.str(), EnumValue(igmpx::CLIENT));
      command.str("");
      command << "/NodeList/" << clients.Get(n)->GetId() << "/$ns3::igmpx::IGMPXRoutingProtocol/RegisterAsMember";
    }

  // Set source position and mobility
  NS_LOG_INFO ("Topology Source");
  Ptr<ListPositionAllocator> positionAllocS = CreateObject<ListPositionAllocator>();
  positionAllocS->Add(Vector(-10, 0.0, 0.0)); // Source

  MobilityHelper mobilityS;
  mobilityS.SetPositionAllocator(positionAllocS);
  mobilityS.SetMobilityModel("ns3::ConstantPositionMobilityModel");
  mobilityS.Install(routers.Get(0));

  NS_LOG_INFO ("Topology Routers");
  MobilityHelper mobilityR;
  mobilityR.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  mobilityR.SetPositionAllocator ("ns3::GridPositionAllocator",
    "MinX", DoubleValue (0.0),
    "MinY", DoubleValue (0.0),
    "DeltaX", DoubleValue (10),
    "DeltaY", DoubleValue (10),
    "GridWidth", UintegerValue (2),
    "LayoutType", StringValue ("RowFirst"));
  mobilityR.Install(routers);

  MobilityHelper mobilityC;
  mobilityC.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  mobilityC.SetPositionAllocator ("ns3::GridPositionAllocator",
    "MinX", DoubleValue (0.0),
    "MinY", DoubleValue (0.0),
    "DeltaX", DoubleValue (12),
    "DeltaY", DoubleValue (12),
    "GridWidth", UintegerValue (2),
    "LayoutType", StringValue ("RowFirst"));
  mobilityC.Install(clients);

//  NS_LOG_INFO ("Application: create source");
//  InetSocketAddress dst = InetSocketAddress (multicastGroup, PUSH_PORT);
//  Config::SetDefault ("ns3::UdpSocket::IpMulticastTtl", UintegerValue (1));
//  VideoHelper video = VideoHelper ("ns3::UdpSocketFactory", dst);
//  video.SetAttribute ("DataRate", DataRateValue (DataRate (1000000)));
//  video.SetAttribute ("Source", Ipv4AddressValue (multicastSource));
//  video.SetAttribute ("PacketSize", UintegerValue (1200));
//  video.SetAttribute ("PeerType", EnumValue (SOURCE));
//  video.SetAttribute ("Local", AddressValue (i0i1.GetAddress(0)));
//  video.SetAttribute ("PeerPolicy", EnumValue (PS_RANDOM));
//  video.SetAttribute ("ChunkPolicy", EnumValue (CS_NEW_CHUNK));
//  ApplicationContainer apps = video.Install (routers.Get (0));
//  apps.Start (Seconds (10));
//  apps.Stop (Seconds (100));

  NS_LOG_INFO ("Create Source Application");
  Ptr<ConstantRandomVariable> onv = CreateObject<ConstantRandomVariable>();
  onv->SetAttribute("Constant", DoubleValue(1));
  Ptr<ConstantRandomVariable> offv = CreateObject<ConstantRandomVariable>();
  offv->SetAttribute("Constant", DoubleValue(0));
  InetSocketAddress dst = InetSocketAddress(multicastGroup, PIM_PORT_NUMBER);
  Config::SetDefault("ns3::UdpSocket::IpMulticastTtl", UintegerValue(1));
  OnOffHelper onoff = OnOffHelper("ns3::UdpSocketFactory", dst);
  onoff.SetAttribute("OnTime", PointerValue(onv));
  onoff.SetAttribute("OffTime", PointerValue(offv));
  onoff.SetAttribute("DataRate", DataRateValue (DataRate (1000000)));
  onoff.SetAttribute("PacketSize", UintegerValue(1200));

  ApplicationContainer apps = onoff.Install(sourceNode);
  apps.Start(Seconds(20.0));
  apps.Stop(Seconds(80.0));

  NS_LOG_INFO ("Create Sink.");
  PacketSinkHelper sink = PacketSinkHelper("ns3::UdpSocketFactory", dst);
  apps = sink.Install(clients);
  apps.Start(Seconds(20.0));
  apps.Stop(Seconds(80.0));
  Config::ConnectWithoutContext("/NodeList/[5-8]/ApplicationList/0/$ns3::PacketSink/Rx", MakeCallback(&SinkRx));

//	AsciiTraceHelper ascii;
//	csma.EnableAsciiAll (ascii.CreateFileStream ("simple-global-routing.tr"));
//	csma.EnablePcapAll ("link12", false);

  //	  // Flow Monitor
  //	  Ptr<FlowMonitor> flowmon;
  //	  if (enableFlowMonitor)
  //	    {
  //	      FlowMonitorHelper flowmonHelper;
  //	      flowmon = flowmonHelper.InstallAll ();
  //	    }

  // then, print what the packet sink receives.
  //	  Config::ConnectWithoutContext ("/NodeList/1/ApplicationList/0/$ns3::PacketSink/Rx", MakeCallback (&SinkRx));
//	Packet::EnablePrinting ();

  NS_LOG_INFO ("Run Simulation.");
  Simulator::Stop(Seconds(100));
  Simulator::Run();
  NS_LOG_INFO ("Done.");

  //	  if (enableFlowMonitor)
  //	    {
  //	      flowmon->SerializeToXmlFile ("simple-global-routing.flowmon", false, false);
  //	    }

  Simulator::Destroy();
  return 0;
}
