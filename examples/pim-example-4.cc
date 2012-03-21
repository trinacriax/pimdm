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

/*
//
// Network topology
//
//           s0    c5
//           |     |
//           0 --- 5     c7
//          / \   /     /
//         /   \ /     /
// c1 --- 1     3 --- 7
//         \   / \     \
//          \ /   \     \
//           2 --- 4 --- 6
//           |     |     |
//        c2-|    c4    c6
//        c3-|
//
// - all links are point-to-point links with indicated one-way BW/delay
// - CBR/UDP flows from n0 to n4, and from n3 to n1
// - UDP packet size of 210 bytes, with per-packet interval 0.00375 sec.
//   (i.e., DataRate of 448,000 bps)
// - DropTail queues
// - Tracing of queues and packet receptions to file "simple-point-to-point-olsr.tr"
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

NS_LOG_COMPONENT_DEFINE ("PimDmExample4");

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
	LogComponentEnable ("PimDmExample4",LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
	LogComponentEnable ("PacketSink", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
	LogComponentEnable ("OnOffApplication", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
	LogComponentEnable ("PIMDMMulticastRouting",LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
//	LogComponentEnable ("SimpleGlobalRoutingExample", LOG_LEVEL_INFO);
//	LogComponentEnable ("MacLow", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
//	LogComponentEnable ("YansWifiChannel", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
//	LogComponentEnable ("UdpSocketImpl", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
//	LogComponentEnable ("OnOffApplication", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
//	LogComponentEnable ("OlsrRoutingProtocol", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
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
	CommandLine cmd;
	bool enableFlowMonitor = false;
	cmd.AddValue ("EnableMonitor", "Enable Flow Monitor", enableFlowMonitor);
	cmd.Parse (argc, argv);
	int32_t simTime, senderStart, receiverStart;
	simTime = 200;
	senderStart = 50;
	receiverStart = 50;

	NodeContainer source;
	source.Create(1);// source # 15

	// Here, we will explicitly create four nodes.  In more sophisticated
	// topologies, we could configure a node factory.
	NS_LOG_INFO ("Create nodes.");
	NodeContainer pimRouters;
	pimRouters.Create (8);// here routes from node 0 to 7
	NodeContainer n0n1 = NodeContainer (pimRouters.Get (0), pimRouters.Get (1));
	NodeContainer n0n3 = NodeContainer (pimRouters.Get (0), pimRouters.Get (3));
	NodeContainer n1n2 = NodeContainer (pimRouters.Get (1), pimRouters.Get (2));
	NodeContainer n2n3 = NodeContainer (pimRouters.Get (2), pimRouters.Get (3));
	NodeContainer n0n5 = NodeContainer (pimRouters.Get (0), pimRouters.Get (5));
	NodeContainer n3n5 = NodeContainer (pimRouters.Get (3), pimRouters.Get (5));
	NodeContainer n2n4 = NodeContainer (pimRouters.Get (2), pimRouters.Get (4));
	NodeContainer n3n4 = NodeContainer (pimRouters.Get (3), pimRouters.Get (4));
	NodeContainer n3n7 = NodeContainer (pimRouters.Get (3), pimRouters.Get (7));
	NodeContainer n4n6 = NodeContainer (pimRouters.Get (4), pimRouters.Get (6));
	NodeContainer n6n7 = NodeContainer (pimRouters.Get (6), pimRouters.Get (7));

	NodeContainer s0n0 = NodeContainer (source.Get (0),pimRouters.Get(0));

	NodeContainer pimClients;
	pimClients.Create (7);// here clients: 8 - 14
	NodeContainer c1 = NodeContainer (pimRouters.Get(1), pimClients.Get (0));
	NodeContainer c2 = NodeContainer (pimRouters.Get(2), pimClients.Get (1), pimClients.Get (2));
	NodeContainer c4 = NodeContainer (pimRouters.Get(4), pimClients.Get (3));
	NodeContainer c5 = NodeContainer (pimRouters.Get(5), pimClients.Get (4));
	NodeContainer c6 = NodeContainer (pimRouters.Get(6), pimClients.Get (5));
	NodeContainer c7 = NodeContainer (pimRouters.Get(7), pimClients.Get (6));

	// connect all our nodes to a shared channel.
	NS_LOG_INFO("Build Topology.");
	CsmaHelper csma;
	csma.SetChannelAttribute("DataRate", DataRateValue(DataRate(5000000)));
	csma.SetChannelAttribute("Delay", TimeValue(MilliSeconds(2)));
	csma.SetDeviceAttribute("EncapsulationMode", StringValue("Llc"));

	NS_LOG_INFO("Build Topology: clients on interface 1");
	NetDeviceContainer d1c1 = csma.Install (c1);
	NetDeviceContainer d2c2 = csma.Install (c2);
	NetDeviceContainer d4c4 = csma.Install (c4);
	NetDeviceContainer d5c5 = csma.Install (c5);
	NetDeviceContainer d6c6 = csma.Install (c6);
	NetDeviceContainer d7c7 = csma.Install (c7);

	NS_LOG_INFO("Build Topology: routers on other interfaces");
	NetDeviceContainer d0d1 = csma.Install (n0n1);
	NetDeviceContainer d0d3 = csma.Install (n0n3);
	NetDeviceContainer d1d2 = csma.Install (n1n2);
	NetDeviceContainer d2d3 = csma.Install (n2n3);
	NetDeviceContainer d0d5 = csma.Install (n0n5);
	NetDeviceContainer d3d5 = csma.Install (n3n5);
	NetDeviceContainer d2d4 = csma.Install (n2n4);
	NetDeviceContainer d3d4 = csma.Install (n3n4);
	NetDeviceContainer d3d7 = csma.Install (n3n7);
	NetDeviceContainer d4d6 = csma.Install (n4n6);
	NetDeviceContainer d6d7 = csma.Install (n6n7);

	NetDeviceContainer d0s0 = csma.Install (s0n0);

	// Enable OLSR unicast routing protocol
	NS_LOG_INFO("Enabling OLSR Routing.");
	OlsrHelper olsr;
	NS_LOG_INFO("Enabling PIM-DM Routing.");
	PimDmHelper pimdm;

	Ipv4StaticRoutingHelper staticRouting;
	Ipv4ListRoutingHelper list;
	list.Add(staticRouting, 0);
	list.Add(olsr, 10);
	list.Add(pimdm, 11);

	InternetStackHelper internet;
	internet.SetRoutingHelper(list);
	internet.Install(pimRouters);

	Ipv4ListRoutingHelper list2;
	list2.Add(staticRouting, 0);
	list2.Add(olsr, 10);

	InternetStackHelper internet2;
	internet2.SetRoutingHelper(list2);
	internet2.Install(pimClients);
	internet2.Install(source);

	// Later, we add IP addresses.
	NS_LOG_INFO ("Assign IP Addresses.");
	Ipv4AddressHelper ipv4;

	///clients

	ipv4.SetBase ("10.1.1.0", "255.255.255.0");
	Ipv4InterfaceContainer i1i1 = ipv4.Assign (d1c1);

	ipv4.SetBase ("10.2.2.0", "255.255.255.0");
	Ipv4InterfaceContainer i2i2 = ipv4.Assign (d2c2);

	ipv4.SetBase ("10.4.4.0", "255.255.255.0");
	Ipv4InterfaceContainer i4i4 = ipv4.Assign (d4c4);

	ipv4.SetBase ("10.5.5.0", "255.255.255.0");
	Ipv4InterfaceContainer i5i5 = ipv4.Assign (d5c5);

	ipv4.SetBase ("10.6.6.0", "255.255.255.0");
	Ipv4InterfaceContainer i6i6 = ipv4.Assign (d6c6);

	ipv4.SetBase ("10.7.7.0", "255.255.255.0");
	Ipv4InterfaceContainer i7i7 = ipv4.Assign (d7c7);

	//routers

	ipv4.SetBase ("10.0.1.0", "255.255.255.0");
	Ipv4InterfaceContainer i0i2 = ipv4.Assign (d0d1);

	ipv4.SetBase ("10.0.2.0", "255.255.255.0");
	Ipv4InterfaceContainer i0i3 = ipv4.Assign (d0d3);

	ipv4.SetBase ("10.0.3.0", "255.255.255.0");
	Ipv4InterfaceContainer i1i2 = ipv4.Assign (d1d2);

	ipv4.SetBase ("10.0.4.0", "255.255.255.0");
	Ipv4InterfaceContainer i2i3 = ipv4.Assign (d2d3);

	ipv4.SetBase ("10.0.5.0", "255.255.255.0");
	Ipv4InterfaceContainer i0i5 = ipv4.Assign (d0d5);

	ipv4.SetBase ("10.0.6.0", "255.255.255.0");
	Ipv4InterfaceContainer i3i5 = ipv4.Assign (d3d5);

	ipv4.SetBase ("10.0.7.0", "255.255.255.0");
	Ipv4InterfaceContainer i2i4 = ipv4.Assign (d2d4);

	ipv4.SetBase ("10.0.8.0", "255.255.255.0");
	Ipv4InterfaceContainer i3i4 = ipv4.Assign (d3d4);

	ipv4.SetBase ("10.0.9.0", "255.255.255.0");
	Ipv4InterfaceContainer i3i7 = ipv4.Assign (d3d7);

	ipv4.SetBase ("10.0.10.0", "255.255.255.0");
	Ipv4InterfaceContainer i4i6 = ipv4.Assign (d4d6);

	ipv4.SetBase ("10.0.11.0", "255.255.255.0");
	Ipv4InterfaceContainer i6i7 = ipv4.Assign (d6d7);

	// source

	ipv4.SetBase ("10.0.0.0", "255.255.255.0");
	Ipv4InterfaceContainer i0i0 = ipv4.Assign (d0s0);

	NS_LOG_INFO ("Configure multicasting.");
	Ipv4Address multicastSource ("10.0.0.1");
	Ipv4Address multicastSourceR ("10.0.0.2");
	Ipv4Address multicastGroup ("225.1.2.4");

	Ptr<Ipv4> ipv4A = source.Get(0)->GetObject<Ipv4>();
	Ptr<Ipv4StaticRouting> staticRoutingA = staticRouting.GetStaticRouting(ipv4A);
	staticRoutingA->AddHostRouteTo(multicastGroup, multicastSourceR, 1); //just one entry to set first hop from the source

	NS_LOG_INFO("Registering clients");
	std::stringstream ss;
	// source,group,interface
	ss << multicastSource << "," << multicastGroup;
	Config::Set("NodeList/[1-8]/$ns3::pimdm::MulticastRoutingProtocol/RegisterSG", StringValue(ss.str()));
	ss << "," << "1";
	Config::Set("NodeList/[1-8]/$ns3::pimdm::MulticastRoutingProtocol/RegisterAsMember", StringValue(ss.str()));

	NS_LOG_INFO("Create Source");
	InetSocketAddress dst = InetSocketAddress(multicastGroup, 703);//703 is the port
	Config::SetDefault("ns3::UdpSocket::IpMulticastTtl", UintegerValue(1));
	OnOffHelper onoff = OnOffHelper("ns3::UdpSocketFactory", dst);
	onoff.SetAttribute("OnTime", RandomVariableValue(ConstantVariable(1.0)));
	onoff.SetAttribute("OffTime", RandomVariableValue(ConstantVariable(0.0)));
	onoff.SetAttribute("DataRate", DataRateValue(DataRate(15000)));
	onoff.SetAttribute("PacketSize", UintegerValue(1200));

	ApplicationContainer apps = onoff.Install(source.Get(0));
	apps.Start(Seconds(senderStart));
	apps.Stop(Seconds(simTime*.9));

	NS_LOG_INFO("Create Sink.");
	PacketSinkHelper sink = PacketSinkHelper("ns3::UdpSocketFactory", dst);
	apps = sink.Install(pimClients);
	apps.Start(Seconds(receiverStart));
	apps.Stop(Seconds(simTime));
	Config::ConnectWithoutContext("/NodeList/[9-15]/ApplicationList/0/$ns3::PacketSink/Rx", MakeCallback(&SinkRx));


	NS_LOG_INFO ("Run Simulation.");
	Simulator::Stop (Seconds (simTime));
	Simulator::Run ();
	NS_LOG_INFO ("Done.");


	//	  if (enableFlowMonitor)
	//	    {
	//	      flowmon->SerializeToXmlFile ("simple-global-routing.flowmon", false, false);
	//	    }

	Simulator::Destroy ();
	return 0;
}
