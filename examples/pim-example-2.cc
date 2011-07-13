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
	#include <string>

	#include "ns3/core-module.h"
	#include "ns3/network-module.h"
	#include "ns3/internet-module.h"
	#include "ns3/point-to-point-module.h"
	#include "ns3/applications-module.h"
	#include "ns3/flow-monitor-helper.h"
	#include "ns3/olsr-helper.h"
	#include "ns3/pimdm-helper.h"
	#include "ns3/pimdm-routing.h"

	using namespace ns3;

	NS_LOG_COMPONENT_DEFINE ("PimExample2");

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
	LogComponentEnable ("PacketSink", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
	LogComponentEnable ("OlsrRoutingProtocol", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
	LogComponentEnable ("PIMDMMulticastRouting", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
	LogComponentEnable ("Ipv4L3Protocol", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
	LogComponentEnable ("Ipv4ListRouting", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
	LogComponentEnable ("CsmaNetDevice", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
	LogComponentEnable ("CsmaChannel", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
	LogComponentEnable ("CsmaHelper", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
	LogComponentEnable ("Socket", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
	LogComponentEnable ("Ipv4EndPointDemux", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
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
	  bool enableFlowMonitor = false;
	  cmd.AddValue ("EnableMonitor", "Enable Flow Monitor", enableFlowMonitor);
	  cmd.Parse (argc, argv);

	  // Here, we will explicitly create four nodes.  In more sophisticated
	  // topologies, we could configure a node factory.
	  NS_LOG_INFO ("Create nodes.");
	  NodeContainer c;
	  c.Create (3);
	  NodeContainer n0n2 = NodeContainer (c.Get (0), c.Get (2));
	  NodeContainer n1n2 = NodeContainer (c.Get (1), c.Get (2));

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

	  // We create the channels first without any IP addressing information
	  NS_LOG_INFO ("Create channels.");
	  PointToPointHelper p2p;
	  p2p.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
	  p2p.SetChannelAttribute ("Delay", StringValue ("2ms"));
	  NetDeviceContainer d0d2 = p2p.Install (n0n2);

	  NetDeviceContainer d1d2 = p2p.Install (n1n2);

//	  p2p.SetDeviceAttribute ("DataRate", StringValue ("1500kbps"));
//	  p2p.SetChannelAttribute ("Delay", StringValue ("10ms"));

	  // Later, we add IP addresses.
	  NS_LOG_INFO ("Assign IP Addresses.");
	  Ipv4AddressHelper ipv4;
	  ipv4.SetBase ("10.1.0.0", "255.255.255.0");
	  Ipv4InterfaceContainer i0i2 = ipv4.Assign (d0d2);

	  ipv4.SetBase ("10.1.1.0", "255.255.255.0");
	  Ipv4InterfaceContainer i1i2 = ipv4.Assign (d1d2);

	  NS_LOG_INFO ("Configure multicasting.");

	Ipv4Address multicastSource ("10.1.0.1");
	Ipv4Address multicastGroup1 (ALL_PIM_ROUTERS4);
//	Ipv4Address multicastGroup2 ("225.1.2.4");

//	// Now, we will set up multicast routing.  We need to do three things:
//	// 1) Configure a (static) multicast route on node n2
//	// 2) Set up a default multicast route on the sender n0
//	// 3) Have node n4 join the multicast group
//	// We have a helper that can help us with static multicast
//	Ipv4StaticRoutingHelper multicast;
//
//	// 1) Configure a (static) multicast route on node n2 (multicastRouter)
//	Ptr<Node> mr0 = c.Get (0);  // The node in question
//	Ptr<NetDevice> inputIf = n0n2.Get (0);  // The input NetDevice
//	NetDeviceContainer outputDevices;  // A container of output NetDevices
//	outputDevices.Add (n0n2.Get (1));  // (we only need one NetDevice here)
//
//	multicast.AddMulticastRoute (mr0, multicastSource,
//							   multicastGroup1, inputIf, outputDevices);
//
//	// 2) Set up a default multicast route on the sender n0
//	Ptr<Node> sender = c.Get (0);
//	Ptr<NetDevice> senderIf = nd0.Get (0);
//	multicast.SetDefaultMulticastRoute (sender, senderIf);

	Config::Set("NodeList/*/$ns3::pimdm::MulticastRoutingProtocol/MulticastGroup", Ipv4AddressValue(multicastGroup1));
//	Config::Set("NodeList/*/$ns3::pimdm::MulticastRoutingProtocol/MulticastGroup", Ipv4AddressValue(multicastGroup2));


	NS_LOG_INFO ("Create Applications.");
	  uint16_t port = PIM_PORT_NUMBER;   // Discard port (RFC 863)
	  OnOffHelper onoff ("ns3::UdpSocketFactory",
	                     Address (InetSocketAddress (multicastGroup1, port)));
	  onoff.SetAttribute ("OnTime", RandomVariableValue (ConstantVariable (1)));
	  onoff.SetAttribute ("OffTime", RandomVariableValue (ConstantVariable (0)));
	  ApplicationContainer apps = onoff.Install (c.Get (0));
	  apps.Start (Seconds (1.0));
	  apps.Stop (Seconds (10.0));

	  // Create a packet sink to receive these packets
	  PacketSinkHelper sink ("ns3::UdpSocketFactory",
	                         Address (InetSocketAddress (Ipv4Address::GetAny (), port)));
	  apps = sink.Install (c.Get (1));
	  apps.Start (Seconds (1.0));
	  apps.Stop (Seconds (30.0));


	  AsciiTraceHelper ascii;
	  p2p.EnableAsciiAll (ascii.CreateFileStream ("simple-global-routing.tr"));
	  p2p.EnablePcapAll ("simple-global-routing");


//	  // Flow Monitor
	  Ptr<FlowMonitor> flowmon;
	  if (enableFlowMonitor)
	    {
//	      FlowMonitorHelper flowmonHelper;
//	      flowmon = flowmonHelper.InstallAll ();
	    }

	  NS_LOG_INFO ("Run Simulation.");
	  Simulator::Stop (Seconds (31));
	  Simulator::Run ();
	  NS_LOG_INFO ("Done.");

	  if (enableFlowMonitor)
	    {
//	      flowmon->SerializeToXmlFile ("simple-global-routing.flowmon", false, false);
	    }

	  Simulator::Destroy ();
	  return 0;
	}
