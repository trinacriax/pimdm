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
//
// Network topology
//
//           7
//           |
//           0
//          / \
//         /   \
//  4 --- 1     3 --- 6
//         \   /
//          \ /
//           2
//           |
//           5
//

#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <sstream>

#include "ns3/core-module.h"
#include "ns3/mbn-aodv-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/applications-module.h"
#include "ns3/wifi-module.h"
#include "ns3/mbn-aodv-helper.h"
#include "ns3/aodv-helper.h"
#include "ns3/olsr-helper.h"
#include "ns3/pimdm-helper.h"
#include "ns3/pimdm-routing.h"
#include "ns3/mobility-module.h"
#include "ns3/string.h"


using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("PimExample2Mob");

static void SinkRx (Ptr<const Packet> p, const Address &ad)
{
std::cout <<"Received Packet "<< p->GetSize() << " bytes from "<<InetSocketAddress::ConvertFrom (ad).GetIpv4()<< std::endl;
}


static void NodeStatusChanged(std::string source, Ptr<const mbn::RoutingProtocol> nodez) {
	std::cout << "Node Status Changed: " << source << ", new status: "
			<< nodez->GetLocalNodeStatus()<< std::endl;
}

int
main (int argc, char *argv[])
{
// Users may find it convenient to turn on explicit debugging
// for selected modules; the below lines suggest how to do this
#if 1
//	LogComponentEnable ("SimpleGlobalRoutingExample", LOG_LEVEL_INFO);
	LogComponentEnable ("PimExample2Mob", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
//	LogComponentEnable ("MacLow", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
//	LogComponentEnable ("MacRxMiddle", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
//	LogComponentEnable ("YansWifiPhy", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
//	LogComponentEnable ("InterferenceHelper", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
//	LogComponentEnable ("YansWifiChannel", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
//	LogComponentEnable ("UdpSocketImpl", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
	LogComponentEnable ("OnOffApplication", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
	LogComponentEnable ("PacketSink", LogLevel(LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
//	LogComponentEnable ("AodvRoutingProtocol", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
	LogComponentEnable ("MbnAodvRoutingProtocol", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
	LogComponentEnable ("PIMDMMulticastRouting", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
//	LogComponentEnable ("Ipv4L3Protocol", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
//	LogComponentEnable ("Ipv4ListRouting", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
//	LogComponentEnable ("Socket", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
//	LogComponentEnable ("Node", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
//	LogComponentEnable ("Ipv4EndPointDemux", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
//	LogComponentEnable ("Ipv4RawSocketImpl", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
//	LogComponentEnable ("UdpL4Protocol", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
//	LogComponentEnable ("Packet", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
//	LogComponentEnable ("DefaultSimulatorImpl", LogLevel( LOG_LEVEL_ALL | LOG_DEBUG | LOG_LOGIC | LOG_PREFIX_FUNC | LOG_PREFIX_TIME));
#endif
	/// Number of nodes
	uint32_t size = 6;
	/// Animator filename
	std::string animFile = "pimdm.tr";
	/// Distance between nodes, meters
	double step = 100;
	/// Simulation time, seconds
	double totalTime = 60;
	/// Write per-device PCAP traces if true
	bool pcap = true;
	/// Print routes if true
	bool printRoutes = true;

	SeedManager::SetSeed(1234);
	CommandLine cmd;

	cmd.AddValue("pcap", "Write PCAP traces.", pcap);
	cmd.AddValue("printRoutes", "Print routing table dumps.", printRoutes);
	cmd.AddValue("size", "Number of nodes.", size);
	cmd.AddValue("time", "Simulation time, s.", totalTime);
	cmd.AddValue("step", "Grid step, m", step);
	cmd.AddValue("animFile", "File Name for Animation Output", animFile);

	cmd.Parse(argc, argv);

	// Here, we will explicitly create four nodes.  In more sophisticated
	// topologies, we could configure a node factory.
	NS_LOG_INFO ("Create nodes.");
	NodeContainer routers;
	routers.Create (4);// here routes from node 0 to 3
	NodeContainer source;
	source.Create(1);
	NodeContainer client;
	client.Create (3);// here clients from node 4 to 7, 7 is the source

	NodeContainer all;
	all.Add(routers);
	all.Add(source);
	all.Add(client);

	for (uint32_t i = 0; i < all.GetN(); ++i) {// Name nodes
		std::ostringstream os;
		os << "node-" <<i;
		Names::Add(os.str(), all.Get(i));
	}

	NS_LOG_INFO ("Build Topology.");
	NqosWifiMacHelper wifiMac = NqosWifiMacHelper::Default();
	wifiMac.SetType ("ns3::AdhocWifiMac");

	YansWifiPhyHelper wifiPhy = YansWifiPhyHelper::Default();
	YansWifiChannelHelper wifiChannel = YansWifiChannelHelper::Default();
	wifiPhy.SetChannel(wifiChannel.Create());

	WifiHelper wifi = WifiHelper::Default ();
	wifi.SetRemoteStationManager ("ns3::AarfWifiManager");
	wifi.SetRemoteStationManager ("ns3::ConstantRateWifiManager", "DataMode", StringValue ("OfdmRate6Mbps"), "RtsCtsThreshold", UintegerValue (0));

	NetDeviceContainer allNetDev = wifi.Install(wifiPhy, wifiMac, all);

	int32_t routing = 3; //1) OLSR, 2) AODV, 3) MBN-AODV

	// INSTALL INTERNET STACK
	// Enable AODV
	NS_LOG_INFO ("Enabling AODV Routing.");
	OlsrHelper olsr;
	AodvHelper aodv;
	MbnAodvHelper mbnaodv;

	NS_LOG_INFO ("Enabling PIM-DM Routing.");
	PimDmHelper pimdm;

	Ipv4StaticRoutingHelper staticRouting;
	Ipv4ListRoutingHelper listRouters;
	listRouters.Add (staticRouting, 0);
	switch(routing){
			case 1:{
				listRouters.Add (olsr, 10);
				break;
			}
			case 2:{
				listRouters.Add (aodv, 10);
				break;
			}
			case 3:{
				listRouters.Add (mbnaodv, 10);
				break;
			}
		}
	listRouters.Add (pimdm, 11);

	InternetStackHelper internetRouters;
	internetRouters.SetRoutingHelper (listRouters);
	internetRouters.Install (routers);

	Ipv4ListRoutingHelper listClients;
	switch(routing){
		case 1:{
			listClients.Add (olsr, 10);
			break;
		}
		case 2:{
			listClients.Add (aodv, 10);
			break;
		}
		case 3:{
			listClients.Add (mbnaodv, 10);
			break;
		}
	}
	listClients.Add (staticRouting, 11);

	InternetStackHelper internetClients;
	internetClients.SetRoutingHelper (listClients);
	internetClients.Install (client);
	internetClients.Install (source);

	// Later, we add IP addresses.
	NS_LOG_INFO ("Assign IP Addresses.");
	Ipv4AddressHelper ipv4;
	ipv4.SetBase ("10.1.1.0", "255.255.255.0");
	Ipv4InterfaceContainer ipAll = ipv4.Assign (allNetDev);

	NS_LOG_INFO ("Configure multicasting.");
	Ipv4Address multicastSource ("10.1.1.5");
	Ipv4Address multicastGroup ("225.1.2.4");

	// 1) Configure a (static) multicast route on ASNGW (multicastRouter)
	Ptr<Node> multicastRouter = routers.Get (0); // The node in question
	Ptr<NetDevice> inputIf = allNetDev.Get (0); // The input NetDevice

	Ipv4StaticRoutingHelper multicast;
	multicast.AddMulticastRoute (multicastRouter, multicastSource, multicastGroup, inputIf, allNetDev.Get(0));

	// 2) Set up a default multicast route on the sender n0
	Ptr<Node> sender = source.Get (0);
	Ptr<NetDevice> senderIf = allNetDev.Get (4);
	multicast.SetDefaultMulticastRoute (sender, senderIf);

	std::stringstream ss;
	// source,group,interface
	ss<< multicastSource<< "," << multicastGroup << "," << "1";
	Config::Set("NodeList/[0-3]/$ns3::pimdm::MulticastRoutingProtocol/RegisterMember", StringValue(ss.str()));

	switch(routing){
			case 1:{
				break;
			}
			case 2:{
				break;
			}
			case 3:{
				Config::Set("/NodeList/[0-3]/$ns3::mbn::RoutingProtocol/localWeightFunction",EnumValue(mbn::W_NODE_RND));
				Config::Connect("/NodeList/*/$ns3::mbn::RoutingProtocol/NodeStatusChanged",MakeCallback(&NodeStatusChanged));
				Config::Set("/NodeList/0/$ns3::mbn::RoutingProtocol/localWeight",UintegerValue(10));
				Config::Set("/NodeList/1/$ns3::mbn::RoutingProtocol/localWeight",UintegerValue(6));
				Config::Set("/NodeList/2/$ns3::mbn::RoutingProtocol/localWeight",UintegerValue(7));
				Config::Set("/NodeList/3/$ns3::mbn::RoutingProtocol/localWeight",UintegerValue(7));
				std::cout << "Starting simulation for " << totalTime << " s ...\n";
				break;
			}
		}

	NS_LOG_INFO ("Create Source");
	InetSocketAddress dst = InetSocketAddress (multicastGroup, PIM_PORT_NUMBER);
	Config::SetDefault ("ns3::UdpSocket::IpMulticastTtl", UintegerValue (1));
	OnOffHelper onoff = OnOffHelper ("ns3::UdpSocketFactory", dst);
	onoff.SetAttribute ("OnTime", RandomVariableValue (ConstantVariable (1.0)));
	onoff.SetAttribute ("OffTime", RandomVariableValue (ConstantVariable (0.0)));
	onoff.SetAttribute ("DataRate", DataRateValue (DataRate (15000)));
	onoff.SetAttribute ("PacketSize", UintegerValue (1200));

	ApplicationContainer apps = onoff.Install (source.Get (0));
	apps.Start (Seconds (12.0));
	apps.Stop (Seconds (28.0));

	NS_LOG_INFO ("Create Sink.");
	PacketSinkHelper sink = PacketSinkHelper ("ns3::UdpSocketFactory", dst);
	apps = sink.Install (client);
	apps.Start (Seconds (4.0));
	apps.Stop (Seconds (32.0));
	Config::ConnectWithoutContext ("/NodeList/[5-7]/ApplicationList/0/$ns3::PacketSink/Rx", MakeCallback (&SinkRx));

	MobilityHelper mobilityR;
	Ptr<ListPositionAllocator> positionAllocR = CreateObject<ListPositionAllocator> ();
	positionAllocR->Add(Vector(250.0, 310.0, 0.0));// 0
	positionAllocR->Add(Vector(190.0, 250.0, 0.0));// 1
	positionAllocR->Add(Vector(250.0, 190.0, 0.0));// 2
	positionAllocR->Add(Vector(320.0, 250.0, 0.0));// 3
	mobilityR.SetPositionAllocator(positionAllocR);
	mobilityR.SetMobilityModel("ns3::ConstantPositionMobilityModel");
	mobilityR.Install(routers);

	Ptr<ListPositionAllocator> positionAllocS = CreateObject<ListPositionAllocator> ();
	positionAllocS->Add(Vector(250.0, 380.0, 0.0));// Source
	MobilityHelper mobilityS;
	mobilityS.SetPositionAllocator(positionAllocS);
	mobilityS.SetMobilityModel("ns3::ConstantPositionMobilityModel");
	mobilityS.Install(source);

	MobilityHelper mobilityC;
	Ptr<ListPositionAllocator> positionAllocC = CreateObject<ListPositionAllocator> ();
	positionAllocC->Add(Vector(130.0, 250.0, 0.0));// 1C
	positionAllocC->Add(Vector(250.0, 120.0, 0.0));// 2C
	positionAllocC->Add(Vector(380.0, 250.0, 0.0));// 3C
	mobilityC.SetPositionAllocator(positionAllocC);
	mobilityC.SetMobilityModel("ns3::ConstantPositionMobilityModel");
	mobilityC.Install(client);

	for(int i = 0; i < all.GetN(); i++){
		Ptr<MobilityModel> mobility2 = all.Get(i)->GetObject<MobilityModel> ();
	      Vector pos2 = mobility2->GetPosition (); // Get position
	      NS_LOG_INFO("Node ["<<i<<"] = ("<< pos2.x << ", " << pos2.y<<", "<<pos2.z<<")");
	}


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
	Simulator::Stop (Seconds (totalTime));
	Simulator::Run ();
	NS_LOG_INFO ("Done.");


	//	  if (enableFlowMonitor)
	//	    {
	//	      flowmon->SerializeToXmlFile ("simple-global-routing.flowmon", false, false);
	//	    }

	Simulator::Destroy ();
	return 0;
}
