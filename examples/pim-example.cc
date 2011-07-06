	/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
	/*
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
	*/

	//
	// Simple example of OLSR routing over some point-to-point links
	//
	// Network topology
	//
	//   n0
	//     \ 5 Mb/s, 2ms
	//      \          1.5Mb/s, 10ms        3Mb/s, 4ms
	//       n2 -------------------------n3---------n4
	//      /
	//     / 5 Mb/s, 2ms
	//   n1
	//
	// - all links are point-to-point links with indicated one-way BW/delay
	// - CBR/UDP flows from n0 to n4, and from n3 to n1
	// - UDP packet size of 210 bytes, with per-packet interval 0.00375 sec.
	//   (i.e., DataRate of 448,000 bps)
	// - DropTail queues
	// - Tracing of queues and packet receptions to file "simple-point-to-point-olsr.tr"

	#include <iostream>
	#include <fstream>
	#include <cassert>

	#include "ns3/core-module.h"
	#include "ns3/network-module.h"
	#include "ns3/internet-module.h"
	#include "ns3/csma-helper.h"
	#include "ns3/point-to-point-module.h"
	#include "ns3/applications-module.h"
	#include "ns3/olsr-helper.h"
	#include "ns3/pimdm-helper.h"
	#include "ns3/pimdm-routing.h"
	#include "ns3/ipv4-static-routing-helper.h"
	#include "ns3/ipv4-list-routing-helper.h"
//	#include "ns3/animation-interface.h"


	using namespace ns3;

	NS_LOG_COMPONENT_DEFINE ("SimplePointToPointOlsrExample");

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
	LogComponentEnable ("OlsrRoutingProtocol", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
	LogComponentEnable ("PIMDMMulticastRouting", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
	LogComponentEnable ("CsmaNetDevice", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
	LogComponentEnable ("CsmaChannel", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
	LogComponentEnable ("CsmaHelper", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
	LogComponentEnable ("Socket", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
	LogComponentEnable ("DefaultSimulatorImpl", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));

	#endif

	// Set up some default values for the simulation.  Use the

	Config::SetDefault ("ns3::OnOffApplication::PacketSize", UintegerValue (210));
	Config::SetDefault ("ns3::OnOffApplication::DataRate", StringValue ("448kb/s"));

	//DefaultValue::Bind ("DropTailQueue::m_maxPackets", 30);

	// Allow the user to override any of the defaults and the above
	// DefaultValue::Bind ()s at run-time, via command-line arguments
	CommandLine cmd;
	cmd.Parse (argc, argv);

	// Here, we will explicitly create four nodes.  In more sophisticated
	// topologies, we could configure a node factory.
	NS_LOG_INFO ("Create nodes.");

	NodeContainer csmaNodes02;
	csmaNodes02.Create (2);
	NodeContainer csmaNodes12;
	csmaNodes12.Create (1);
	csmaNodes12.Add(csmaNodes02.Get(1));
	NodeContainer csmaNodes23;
	csmaNodes23.Create (1);
	csmaNodes23.Add(csmaNodes02.Get(1));
	NodeContainer csmaNodes34;
	csmaNodes34.Create (1);
	csmaNodes34.Add(csmaNodes23.Get(0));

	NS_LOG_INFO ("Create channels.");

	CsmaHelper csma02;
	csma02.SetChannelAttribute ("DataRate", StringValue ("5Mbps"));
	csma02.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (2000)));

	CsmaHelper csma12;
	csma12.SetChannelAttribute ("DataRate", StringValue ("5Mbps"));
	csma12.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (2000)));

	CsmaHelper csma23;
	csma23.SetChannelAttribute ("DataRate", StringValue ("1.5Mbps"));
	csma23.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (10000)));

	CsmaHelper csma34;
	csma34.SetChannelAttribute ("DataRate", StringValue ("3Mbps"));
	csma34.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (4000)));

	Config::Set("NodeList/0/DeviceList/0/$ns3::CsmaNetDevice/Address", Mac48AddressValue("08:00:2e:00:02:00"));
	Config::Set("NodeList/2/DeviceList/0/$ns3::CsmaNetDevice/Address", Mac48AddressValue("08:00:2e:00:02:02"));
	Config::Set("NodeList/1/DeviceList/0/$ns3::CsmaNetDevice/Address", Mac48AddressValue("08:00:2e:00:12:01"));
	Config::Set("NodeList/2/DeviceList/1/$ns3::CsmaNetDevice/Address", Mac48AddressValue("08:00:2e:00:12:02"));
	Config::Set("NodeList/3/DeviceList/0/$ns3::CsmaNetDevice/Address", Mac48AddressValue("08:00:2e:00:23:02"));
	Config::Set("NodeList/2/DeviceList/2/$ns3::CsmaNetDevice/Address", Mac48AddressValue("08:00:2e:00:23:03"));
	Config::Set("NodeList/3/DeviceList/1/$ns3::CsmaNetDevice/Address", Mac48AddressValue("08:00:2e:00:34:03"));
	Config::Set("NodeList/4/DeviceList/0/$ns3::CsmaNetDevice/Address", Mac48AddressValue("08:00:2e:00:34:04"));

	NS_LOG_INFO ("Build Topology.");

	NetDeviceContainer csmaDevices02 = csma02.Install (csmaNodes02);
	NetDeviceContainer csmaDevices12 = csma12.Install (csmaNodes12);
	NetDeviceContainer csmaDevices23 = csma23.Install (csmaNodes23);
	NetDeviceContainer csmaDevices34 = csma34.Install (csmaNodes34);

	NodeContainer all;
	all.Add(csmaNodes02.Get(0));
	all.Add(csmaNodes12.Get(0));
	all.Add(csmaNodes23.Get(1));
	all.Add(csmaNodes34);
	InternetStackHelper stack;
	stack.Install(all);

	Ipv4AddressHelper ip02;
	ip02.SetBase ("10.1.0.0", "255.255.255.0");
	Ipv4InterfaceContainer ip02i = ip02.Assign (csmaDevices02);

	Ipv4AddressHelper ip12;
	ip12.SetBase ("10.1.1.0", "255.255.255.0");
	Ipv4InterfaceContainer ip12i = ip12.Assign (csmaDevices12);

	Ipv4AddressHelper ip23;
	ip23.SetBase ("10.1.3.0", "255.255.255.0");
	Ipv4InterfaceContainer ip23i = ip23.Assign (csmaDevices23);

	Ipv4AddressHelper ip34;
	ip34.SetBase ("10.1.4.0", "255.255.255.0");
	Ipv4InterfaceContainer ip34i = ip34.Assign (csmaDevices34);

//	Ptr<Ipv4> ipv4 = node->GetObject<Ipv4> ();
//	int32_t interface = ipv4->GetInterfaceForDevice (device);
//	if (interface == -1){
//	  interface = ipv4->AddInterface (device);
//	}
//	Ipv4InterfaceAddress ipv4Addr = Ipv4InterfaceAddress (NewAddress (), m_mask);
//	ipv4->AddAddress (interface, ipv4Addr);
//	ipv4->SetMetric (interface, 1);
//	ipv4->SetUp (interface);

	NS_LOG_INFO ("Configure multicasting.");

	Ipv4Address multicastSource ("10.1.0.1");
	Ipv4Address multicastGroup ("225.1.2.4");

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

	// Create the OnOff application to send UDP datagrams of size
	// 210 bytes at a rate of 448 Kb/s from n0 to n4
	NS_LOG_INFO ("Create Applications.");
	uint16_t muticastPort = PIM_PORT_NUMBER;   // Discard port (RFC 863)

	OnOffHelper onoff ("ns3::UdpSocketFactory",
	                   InetSocketAddress (multicastGroup, muticastPort));
	onoff.SetAttribute ("OnTime", RandomVariableValue (ConstantVariable (1)));
	onoff.SetAttribute ("OffTime", RandomVariableValue (ConstantVariable (0)));

	ApplicationContainer apps = onoff.Install (all.Get (0));
	apps.Start (Seconds (1.0));
	apps.Stop (Seconds (10.0));

	// Create a packet sink to receive these packets
	PacketSinkHelper sink ("ns3::UdpSocketFactory",
	InetSocketAddress (multicastGroup, muticastPort));

	apps = sink.Install (all.Get (4));
	apps.Start (Seconds (1.0));
	apps.Stop (Seconds (10.0));

	AsciiTraceHelper ascii;
	csma02.EnableAsciiAll (ascii.CreateFileStream ("csma02.tr"));
	csma02.EnablePcapAll ("csma02.pcap");

//	AnimationInterface anim;
//	anim.SetOutputFile("p2p-multicast.tr");
//	anim.StartAnimation();

	Simulator::Stop (Seconds (100));

	NS_LOG_INFO ("Run Simulation.");
	Simulator::Run ();
	Simulator::Destroy ();
	NS_LOG_INFO ("Done.");

	return 0;
}
