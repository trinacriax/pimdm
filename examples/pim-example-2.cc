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
	//      \          1.5Mb/s, 10ms        1.5Mb/s, 10ms
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
	LogComponentEnable ("OnOffApplication", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
	LogComponentEnable ("OlsrRoutingProtocol", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
	LogComponentEnable ("PIMDMMulticastRouting", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
	LogComponentEnable ("Ipv4ListRouting", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
	LogComponentEnable ("CsmaNetDevice", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
	LogComponentEnable ("CsmaChannel", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
	LogComponentEnable ("CsmaHelper", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
	LogComponentEnable ("Socket", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
	LogComponentEnable ("UdpSocketImpl", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
	LogComponentEnable ("Packet", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
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
	NodeContainer c;
	c.Create (5);
	NodeContainer n02 = NodeContainer (c.Get(0), c.Get (2));
	NodeContainer n12 = NodeContainer (c.Get(1), c.Get (2));
	NodeContainer n32 = NodeContainer (c.Get(3), c.Get (2));
	NodeContainer n34 = NodeContainer (c.Get(3), c.Get (4));

	NS_LOG_INFO ("Build Topology.");

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
	internet.Install (c);

	NS_LOG_INFO ("Create channels.");

	CsmaHelper csmaLinkA;
	csmaLinkA.SetChannelAttribute ("DataRate", StringValue ("5Mbps"));
	csmaLinkA.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (2000)));
	NetDeviceContainer csmaDevices02 = csmaLinkA.Install (n02);
	NetDeviceContainer csmaDevices12 = csmaLinkA.Install (n12);
//	CsmaHelper csma12;
//	csma12.SetChannelAttribute ("DataRate", StringValue ("5Mbps"));
//	csma12.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (2000)));
//	NetDeviceContainer csmaDevices12 = csma12.Install (n12);

	CsmaHelper csmaLinkB;
	csmaLinkB.SetChannelAttribute ("DataRate", StringValue ("1.5Mbps"));
	csmaLinkB.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (10000)));
	NetDeviceContainer csmaDevices23 = csmaLinkB.Install (n32);
	NetDeviceContainer csmaDevices34 = csmaLinkB.Install (n34);
//	CsmaHelper csma34;
//	csma34.SetChannelAttribute ("DataRate", StringValue ("3Mbps"));
//	csma34.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (4000)));
//	NetDeviceContainer csmaDevices34 = csma34.Install (n34);

//	Config::Set("NodeList/0/DeviceList/0/$ns3::CsmaNetDevice/Address", Mac48AddressValue("08:00:2e:00:02:00"));
//	Config::Set("NodeList/2/DeviceList/0/$ns3::CsmaNetDevice/Address", Mac48AddressValue("08:00:2e:00:02:02"));
//	Config::Set("NodeList/1/DeviceList/0/$ns3::CsmaNetDevice/Address", Mac48AddressValue("08:00:2e:00:12:01"));
//	Config::Set("NodeList/2/DeviceList/1/$ns3::CsmaNetDevice/Address", Mac48AddressValue("08:00:2e:00:12:02"));
//	Config::Set("NodeList/3/DeviceList/0/$ns3::CsmaNetDevice/Address", Mac48AddressValue("08:00:2e:00:23:02"));
//	Config::Set("NodeList/2/DeviceList/2/$ns3::CsmaNetDevice/Address", Mac48AddressValue("08:00:2e:00:23:03"));
//	Config::Set("NodeList/3/DeviceList/1/$ns3::CsmaNetDevice/Address", Mac48AddressValue("08:00:2e:00:34:03"));
//	Config::Set("NodeList/4/DeviceList/0/$ns3::CsmaNetDevice/Address", Mac48AddressValue("08:00:2e:00:34:04"));


	Ipv4Address multicastSource ("10.1.0.1");
	Ipv4Address multicastGroup1 ("225.1.1.4");
	Ipv4Address multicastGroup2 ("225.1.2.4");
	Config::Set("NodeList/*/$ns3::pimdm::MulticastRoutingProtocol/MulticastGroup", Ipv4AddressValue(multicastGroup1));
	Config::Set("NodeList/*/$ns3::pimdm::MulticastRoutingProtocol/MulticastGroup", Ipv4AddressValue(multicastGroup2));

	NS_LOG_INFO ("Assign IP Addresses.");

	uint16_t sampleMetric = 1;
	Ipv4AddressHelper ip02;
	ip02.SetBase ("10.1.0.0", "255.255.255.0");
	Ipv4InterfaceContainer ip02i = ip02.Assign (csmaDevices02);
	ip02i.SetMetric(0, sampleMetric);
	ip02i.SetMetric(1, sampleMetric);

	Ipv4AddressHelper ip12;
	ip12.SetBase ("10.1.1.0", "255.255.255.0");
	Ipv4InterfaceContainer ip12i = ip12.Assign (csmaDevices12);
	ip12i.SetMetric(0, sampleMetric);
	ip12i.SetMetric(1, sampleMetric);

	Ipv4AddressHelper ip23;
	ip23.SetBase ("10.1.3.0", "255.255.255.0");
	Ipv4InterfaceContainer ip23i = ip23.Assign (csmaDevices23);
	ip23i.SetMetric(0, sampleMetric);
	ip23i.SetMetric(1, sampleMetric);

	Ipv4AddressHelper ip34;
	ip34.SetBase ("10.1.4.0", "255.255.255.0");
	Ipv4InterfaceContainer ip34i = ip34.Assign (csmaDevices34);
	ip34i.SetMetric(0, sampleMetric);
	ip34i.SetMetric(1, sampleMetric);

	uint16_t o2 = 1;


//	Ptr<Ipv4ListRouting> ipv4 = c.Get(0)->GetObject<Ipv4ListRouting> ();
//	uint32_t num = ipv4->GetNRoutingProtocols();
//	int32_t interface = ipv4->GetInterfaceForDevice (device);
//	if (interface == -1){
//	  interface = ipv4->AddInterface (device);
//	}
//	for(uint32_t i = 0; i < num; i++){
//		Ptr<Ipv4RoutingProtocol> tmp = ipv4->GetRoutingProtocol(1,o2);
//	}

//	Ipv4InterfaceAddress ipv4Addr = Ipv4InterfaceAddress (NewAddress (), m_mask);
//	ipv4->AddAddress (interface, ipv4Addr);
//	ipv4->SetMetric (interface, 1);
//	ipv4->SetUp (interface);

	NS_LOG_INFO ("Configure multicasting.");

	// Create the OnOff application to send UDP datagrams of size
	// 210 bytes at a rate of 448 Kb/s from n0 to n4
//	NS_LOG_INFO ("Create Applications.");
//	uint16_t muticastPort = PIM_PORT_NUMBER;   // Discard port (RFC 863)
//	Address sinkLocalAddress(InetSocketAddress(multicastGroup1, muticastPort));
//
//	PacketSinkHelper sink ("ns3::UdpSocketFactory",sinkLocalAddress);
//	ApplicationContainer sinkApps = sink.Install (c.Get (4));
//	sinkApps.Start (Seconds (1.0));
//	sinkApps.Stop (Seconds (10.0));
//
//	OnOffHelper onoff ("ns3::UdpSocketFactory",sinkLocalAddress);
//	onoff.SetAttribute ("OnTime", RandomVariableValue (ConstantVariable (1)));
//	onoff.SetAttribute ("OffTime", RandomVariableValue (ConstantVariable (0)));
//	onoff.SetAttribute ("DataRate", StringValue ("300bps"));
//	onoff.SetAttribute ("PacketSize", UintegerValue (50));
//
//	ApplicationContainer apps = onoff.Install (c.Get (0));
//	apps.Start (Seconds (1.0));
//	apps.Stop (Seconds (10.0));
	// Create a flow from n3 to n1, starting at time 1.1 seconds
	  OnOffHelper onoff ("ns3::UdpSocketFactory",
	                     Address (InetSocketAddress (multicastGroup1, PIM_PORT_NUMBER)));
	  onoff.SetAttribute ("OnTime", RandomVariableValue (ConstantVariable (1)));
	  onoff.SetAttribute ("OffTime", RandomVariableValue (ConstantVariable (0)));

	  ApplicationContainer apps = onoff.Install (c.Get (3));
	  apps.Start (Seconds (1.1));
	  apps.Stop (Seconds (10.0));

	  // Create a packet sink to receive these packets
	  PacketSinkHelper sink ("ns3::UdpSocketFactory",
	                         Address (InetSocketAddress (Ipv4Address::GetAny (), PIM_PORT_NUMBER)));
	  apps = sink.Install (c.Get (0));
	  apps.Start (Seconds (1.1));
	  apps.Stop (Seconds (10.0));

	// Create a packet sink to receive these packets




	AsciiTraceHelper ascii;
	csmaLinkA.EnableAsciiAll (ascii.CreateFileStream ("csma02.tr"));
	csmaLinkA.EnablePcapAll ("csma02.pcap");

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
