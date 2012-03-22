/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2011 University of Trento, Italy
 * 					  University of California, Los Angeles, U.S.A.
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
#include "ns3/csma-helper.h"
#include "ns3/olsr-helper.h"
#include "ns3/pimdm-helper.h"
#include "ns3/pimdm-routing.h"
#include "ns3/string.h"
#include <sstream>

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("PimExample2");

static void SinkRx (Ptr<const Packet> p, const Address &ad)
{
std::cout <<"Received Packet "<< p->GetSize() << " bytes from "<<InetSocketAddress::ConvertFrom (ad).GetIpv4()<< std::endl;
}

int
main (int argc, char *argv[])
{
// Users may find it convenient to turn on explicit debugging
// for selected modules; the below lines suggest how to do this
#if 1
//	LogComponentEnable ("SimpleGlobalRoutingExample", LOG_LEVEL_INFO);
//	LogComponentEnable ("MacLow", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
//	LogComponentEnable ("YansWifiChannel", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
//	LogComponentEnable ("UdpSocketImpl", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
//	LogComponentEnable ("OnOffApplication", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
	LogComponentEnable ("PacketSink", LogLevel(LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
//	LogComponentEnable ("OlsrRoutingProtocol", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
	LogComponentEnable ("PIMDMMulticastRouting", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
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

	//	LogComponentEnable ("DefaultSimulatorImpl", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
#endif

	// Set up some default values for the simulation.  Use the
	Config::SetDefault ("ns3::OnOffApplication::PacketSize", UintegerValue (210));
	Config::SetDefault ("ns3::OnOffApplication::DataRate", StringValue ("448kb/s"));

	//DefaultValue::Bind ("DropTailQueue::m_maxPackets", 30);

	// Allow the user to override any of the defaults and the above
	// DefaultValue::Bind ()s at run-time, via command-line arguments
	CommandLine cmd;
	bool enableFlowMonitor = false;
	cmd.AddValue ("EnableMonitor", "Enable Flow Monitor", enableFlowMonitor);
	cmd.Parse (argc, argv);

	// Here, we will explicitly create four nodes.  In more sophisticated
	// topologies, we could configure a node factory.
	NS_LOG_INFO ("Create nodes.");
	NodeContainer routers;
	routers.Create (4);// here routes from node 0 to 3
	NodeContainer n0n1 = NodeContainer (routers.Get (0), routers.Get (1));
	NodeContainer n0n3 = NodeContainer (routers.Get (0), routers.Get (3));
	NodeContainer n1n2 = NodeContainer (routers.Get (1), routers.Get (2));
	NodeContainer n2n3 = NodeContainer (routers.Get (2), routers.Get (3));
	NodeContainer client;
	client.Create (4);// here clients from node 4 to 7, 7 is the source
	NodeContainer c1 = NodeContainer (client.Get (0), routers.Get(1));
	NodeContainer c2 = NodeContainer (client.Get (1), routers.Get(2));
	NodeContainer c3 = NodeContainer (client.Get (2), routers.Get(3));
	NodeContainer c4 = NodeContainer (client.Get (3), routers.Get(0));


	// connect all our nodes to a shared channel.
	NS_LOG_INFO ("Build Topology.");
	CsmaHelper csma;
	csma.SetChannelAttribute ("DataRate", DataRateValue (DataRate (5000000)));
	csma.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (2)));
	csma.SetDeviceAttribute ("EncapsulationMode", StringValue ("Llc"));
	NetDeviceContainer d0d1 = csma.Install (n0n1);
	NetDeviceContainer d0d3 = csma.Install (n0n3);
	NetDeviceContainer d1d2 = csma.Install (n1n2);
	NetDeviceContainer d2d3 = csma.Install (n2n3);

	NetDeviceContainer d1c1 = csma.Install (c1);
	NetDeviceContainer d2c2 = csma.Install (c2);
	NetDeviceContainer d3c3 = csma.Install (c3);
	NetDeviceContainer d0c4 = csma.Install (c4);

	// Enable OLSR
	NS_LOG_INFO ("Enabling OLSR Routing.");
	OlsrHelper olsr;
	NS_LOG_INFO ("Enabling PIM-DM Routing.");
	PimDmHelper pimdm;

	Ipv4StaticRoutingHelper staticRouting;
	Ipv4ListRoutingHelper list;
	list.Add (staticRouting, 0);
	list.Add (olsr, 10);
	list.Add (pimdm, 11);

	InternetStackHelper internet;
	internet.SetRoutingHelper (list);
	internet.Install (routers);

	Ipv4ListRoutingHelper list2;
	list2.Add (staticRouting, 0);
	list2.Add (olsr, 10);
	InternetStackHelper internet2;
	internet2.SetRoutingHelper (list2);
	internet2.Install (client);

	// Later, we add IP addresses.
	NS_LOG_INFO ("Assign IP Addresses.");
	Ipv4AddressHelper ipv4;
	ipv4.SetBase ("10.0.2.0", "255.255.255.0");
	Ipv4InterfaceContainer i0i2 = ipv4.Assign (d0d1);

	ipv4.SetBase ("10.0.3.0", "255.255.255.0");
	Ipv4InterfaceContainer i0i3 = ipv4.Assign (d0d3);

	ipv4.SetBase ("10.1.2.0", "255.255.255.0");
	Ipv4InterfaceContainer i1i2 = ipv4.Assign (d1d2);

	ipv4.SetBase ("10.2.3.0", "255.255.255.0");
	Ipv4InterfaceContainer i2i3 = ipv4.Assign (d2d3);


	ipv4.SetBase ("10.1.1.0", "255.255.255.0");
	Ipv4InterfaceContainer i1i1 = ipv4.Assign (d1c1);

	ipv4.SetBase ("10.2.2.0", "255.255.255.0");
	Ipv4InterfaceContainer i2i2 = ipv4.Assign (d2c2);

	ipv4.SetBase ("10.3.3.0", "255.255.255.0");
	Ipv4InterfaceContainer i3i3 = ipv4.Assign (d3c3);

	ipv4.SetBase ("10.4.4.0", "255.255.255.0");
	Ipv4InterfaceContainer i4i4 = ipv4.Assign (d0c4);

	NS_LOG_INFO ("Configure multicasting.");
	Ipv4Address multicastSource ("10.4.4.1");
	Ipv4Address multicastSourceR ("10.4.4.2");
	Ipv4Address multicastGroup ("225.1.2.4");

	Ptr<Ipv4> ipv4A = client.Get(3)->GetObject<Ipv4> ();
	Ptr<Ipv4StaticRouting> staticRoutingA = staticRouting.GetStaticRouting (ipv4A);
	staticRoutingA->AddHostRouteTo (multicastGroup, multicastSourceR, 1);//just one entry to set first hop from the source

	std::stringstream ss;
	// source,group,interface
	ss<< multicastSource<< "," << multicastGroup << "," << "3";
	Config::Set("NodeList/[0-3]/$ns3::pimdm::MulticastRoutingProtocol/RegisterMember", StringValue(ss.str()));

	NS_LOG_INFO ("Create Source");
	InetSocketAddress dst = InetSocketAddress (multicastGroup, PIM_PORT_NUMBER);
	Config::SetDefault ("ns3::UdpSocket::IpMulticastTtl", UintegerValue (1));
	OnOffHelper onoff = OnOffHelper ("ns3::UdpSocketFactory", dst);
	onoff.SetAttribute ("OnTime", RandomVariableValue (ConstantVariable (1.0)));
	onoff.SetAttribute ("OffTime", RandomVariableValue (ConstantVariable (0.0)));
	onoff.SetAttribute ("DataRate", DataRateValue (DataRate (15000)));
	onoff.SetAttribute ("PacketSize", UintegerValue (1200));

	ApplicationContainer apps = onoff.Install (client.Get (3));
	apps.Start (Seconds (12.0));
	apps.Stop (Seconds (28.0));

	NS_LOG_INFO ("Create Sink.");
	PacketSinkHelper sink = PacketSinkHelper ("ns3::UdpSocketFactory", dst);
	apps = sink.Install (client);
	apps.Start (Seconds (4.0));
	apps.Stop (Seconds (30.0));
	Config::ConnectWithoutContext ("/NodeList/[4-6]/ApplicationList/0/$ns3::PacketSink/Rx", MakeCallback (&SinkRx));

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
	Simulator::Stop (Seconds (30));
	Simulator::Run ();
	NS_LOG_INFO ("Done.");


	//	  if (enableFlowMonitor)
	//	    {
	//	      flowmon->SerializeToXmlFile ("simple-global-routing.flowmon", false, false);
	//	    }

	Simulator::Destroy ();
	return 0;
}
