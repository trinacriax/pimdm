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
//
//
//       C4 C5   C6 C7
//       -----   -----
//         |       |
//         R2 --- R3
//         |       |
//  S0 --- R0 --- R1
//         |       |
//       -----   -----
//       C0 C1   C2 C3
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
#include "ns3/applications-module.h"
#include "ns3/csma-helper.h"
#include "ns3/olsr-helper.h"
#include "ns3/pimdm-helper.h"
#include "ns3/ipv4-static-routing-helper.h"
#include "ns3/ipv4-list-routing-helper.h"
#include "ns3/string.h"
#include "ns3/csma-channel.h"

#include <sstream>

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("PimDmExample1");

static void SinkRx (Ptr<const Packet> p, const Address &ad)
{
std::cout <<"Received Packet "<< p->GetSize() << " bytes from "<<InetSocketAddress::ConvertFrom (ad).GetIpv4()<< std::endl;
}

int main(int argc, char *argv[]) {
	// Users may find it convenient to turn on explicit debugging
	// for selected modules; the below lines suggest how to do this
#if 1
	LogComponentEnable ("PimDmExample1",LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
	LogComponentEnable ("PacketSink", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
	LogComponentEnable ("OnOffApplication", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
	LogComponentEnable ("PIMDMMulticastRouting",LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
//	LogComponentEnable ("AodvRoutingProtocol", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
//	LogComponentEnable ("OlsrRoutingProtocol", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
//	LogComponentEnable ("UdpL4Protocol", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
//	LogComponentEnable ("Ipv4ListRouting", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
//	LogComponentEnable ("UdpSocketImpl", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
//	LogComponentEnable ("Ipv4L3Protocol", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
//	LogComponentEnable ("Ipv4RawSocketImpl", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
//	LogComponentEnable ("Ipv4EndPointDemux", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
//	LogComponentEnable ("Socket", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
//	LogComponentEnable ("Ipv4Interface", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
//	LogComponentEnable ("CsmaNetDevice", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
//	LogComponentEnable ("CsmaChannel", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
//	LogComponentEnable ("CsmaHelper", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
//	LogComponentEnable ("Node", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
//	LogComponentEnable ("InterferenceHelper", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
//	LogComponentEnable ("ArpL3Protocol", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
//	LogComponentEnable ("ArpCache", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
//	LogComponentEnable ("Packet", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
//	LogComponentEnable ("DefaultSimulatorImpl", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
#endif

	CommandLine cmd;
	cmd.Parse(argc, argv);

	// Here, we will explicitly create four nodes.  In more sophisticated
	// topologies, we could configure a node factory.
	NS_LOG_INFO("Create nodes.");

	int32_t simTime, senderStart, receiverStart;
	simTime = 200;
	senderStart = 50;
	receiverStart = 50;
	NodeContainer source;
	source.Create(1); // source

	NodeContainer pimRouters;
	pimRouters.Create(4);
	// node 0 is the sender
	NodeContainer n0n1 = NodeContainer(pimRouters.Get(0), pimRouters.Get(1));
	NodeContainer n0n2 = NodeContainer(pimRouters.Get(0), pimRouters.Get(2));
	NodeContainer n1n3 = NodeContainer(pimRouters.Get(1), pimRouters.Get(3));
	NodeContainer n2n3 = NodeContainer(pimRouters.Get(2), pimRouters.Get(3));

	NodeContainer s0n0 = NodeContainer(source.Get(0), pimRouters.Get(0));

	NodeContainer pimClients;
	pimClients.Create(8); // here clients: 5-8
	NodeContainer c1 = NodeContainer(pimRouters.Get(0), pimClients.Get(0), pimClients.Get(1));
	NodeContainer c2 = NodeContainer(pimRouters.Get(1), pimClients.Get(2), pimClients.Get(3));
	NodeContainer c3 = NodeContainer(pimRouters.Get(2), pimClients.Get(4), pimClients.Get(5));
	NodeContainer c4 = NodeContainer(pimRouters.Get(3), pimClients.Get(6), pimClients.Get(7));

	// connect all our nodes to a shared channel.
	NS_LOG_INFO("Build Topology.");
	CsmaHelper csma;
	csma.SetChannelAttribute("DataRate", DataRateValue(DataRate(5000000)));
	csma.SetChannelAttribute("Delay", TimeValue(MilliSeconds(2)));
	csma.SetDeviceAttribute("EncapsulationMode", StringValue("Llc"));

	NS_LOG_INFO("Build Topology: clients on interface 1");
	NetDeviceContainer d1c1 = csma.Install(c1);
	NetDeviceContainer d2c2 = csma.Install(c2);
	NetDeviceContainer d3c3 = csma.Install(c3);
	NetDeviceContainer d4c4 = csma.Install(c4);

	NS_LOG_INFO("Build Topology: routers on other interfaces");
	NetDeviceContainer d0d1 = csma.Install(n0n1);
	NetDeviceContainer d0d2 = csma.Install(n0n2);
	NetDeviceContainer d1d3 = csma.Install(n1n3);
	NetDeviceContainer d2d3 = csma.Install(n2n3);

	NetDeviceContainer d0s0 = csma.Install(s0n0);

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
	NS_LOG_INFO("Assign IP Addresses: clients.");
	Ipv4AddressHelper ipv4;

	ipv4.SetBase("10.2.0.0", "255.255.255.0");
	Ipv4InterfaceContainer i0c = ipv4.Assign(d1c1);

	ipv4.SetBase("10.2.1.0", "255.255.255.0");
	Ipv4InterfaceContainer i1c = ipv4.Assign(d2c2);

	ipv4.SetBase("10.2.2.0", "255.255.255.0");
	Ipv4InterfaceContainer i2c = ipv4.Assign(d3c3);

	ipv4.SetBase("10.2.3.0", "255.255.255.0");
	Ipv4InterfaceContainer i3c = ipv4.Assign(d4c4);

	NS_LOG_INFO("Assign IP Addresses: routers.");
	ipv4.SetBase("10.2.4.0", "255.255.255.0");
	Ipv4InterfaceContainer i01 = ipv4.Assign(d0d1);

	ipv4.SetBase("10.2.5.0", "255.255.255.0");
	Ipv4InterfaceContainer i02 = ipv4.Assign(d0d2);

	ipv4.SetBase("10.2.6.0", "255.255.255.0");
	Ipv4InterfaceContainer i13 = ipv4.Assign(d1d3);

	ipv4.SetBase("10.2.7.0", "255.255.255.0");
	Ipv4InterfaceContainer i23 = ipv4.Assign(d2d3);

	ipv4.SetBase("10.0.0.0", "255.255.255.0");
	Ipv4InterfaceContainer i00 = ipv4.Assign(d0s0);

	NS_LOG_INFO("Configure multicasting.");
	Ipv4Address multicastSource("10.0.0.1");
	Ipv4Address multicastSourceR("10.0.0.2");
	Ipv4Address multicastGroup("225.1.2.4");

	Ptr<Ipv4> ipv4A = source.Get(0)->GetObject<Ipv4>();
	Ptr<Ipv4StaticRouting> staticRoutingA = staticRouting.GetStaticRouting(ipv4A);
	staticRoutingA->AddHostRouteTo(multicastGroup, multicastSourceR, 1); //just one entry to set first hop from the source

	NS_LOG_INFO("Registering clients");
	std::stringstream ss;
	// source,group,interface
	ss << multicastSource << "," << multicastGroup;
	Config::Set("NodeList/[1-4]/$ns3::pimdm::MulticastRoutingProtocol/RegisterSG", StringValue(ss.str()));
	ss << "," << "1";
	Config::Set("NodeList/[1-4]/$ns3::pimdm::MulticastRoutingProtocol/RegisterAsMember", StringValue(ss.str()));

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
	apps.Stop(Seconds(70.0));

	NS_LOG_INFO("Create Sink.");
	PacketSinkHelper sink = PacketSinkHelper("ns3::UdpSocketFactory", dst);
	apps = sink.Install(pimClients);
	apps.Start(Seconds(receiverStart));
	apps.Stop(Seconds(80.0));
	Config::ConnectWithoutContext("/NodeList/[5-12]/ApplicationList/0/$ns3::PacketSink/Rx", MakeCallback(&SinkRx));

	Simulator::Stop(Seconds(simTime));

	NS_LOG_INFO("Run Simulation.");
	Simulator::Run();
	Simulator::Destroy();
	NS_LOG_INFO("Done.");

	return 0;
}
