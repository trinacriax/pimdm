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

#ifndef NS3_LOG_ENABLE
	#define NS3_LOG_ENABLE
#endif


#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <sstream>

#include "ns3/mbn-aodv-module.h"
#include "ns3/mbn-aodv-helper.h"

#include "ns3/aodv-helper.h"
#include "ns3/olsr-helper.h"

#include "ns3/pimdm-helper.h"
#include "ns3/pimdm-routing.h"

#include "ns3/video-helper.h"
#include "ns3/video-push-module.h"

#include "ns3/string.h"
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/mobility-module.h"
#include "ns3/tools-module.h"
#include "ns3/wifi-module.h"
#include "ns3/applications-module.h"
#include "ns3/propagation-delay-model.h"
#include "ns3/propagation-loss-model.h"
#include "ns3/yans-error-rate-model.h"
#include "ns3/csma-helper.h"


using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("PushPimWifi");

static bool g_verbose = false;

int
GetNodeID (std::string context){
	int p3 = 0;
	if(g_verbose){
		int p2 = context.find("/");
		int p1 = context.find("/",p2+1);
		p2 = context.find("/",p1+1);
		std::string str = context.substr(p1+1, (p2-p1)-1);
		p3 = atoi(str.c_str());
//		std::cout<<"P1 = "<<p1<< " P2 = "<< p2<< "?"<<p3<< " ID "<< context.substr(p1, (p2-p1))<<" -- " << context<<"\n";
	}
	return p3;
}

//static void SinkRx (Ptr<const Packet> p, const Address &ad)
//{
//std::cout <<"Received Packet "<< p->GetSize() << " bytes from "<<InetSocketAddress::ConvertFrom (ad).GetIpv4()<< std::endl;
//}

static void AppTx (Ptr<const Packet> p)
{
std::cout <<"Sending Packet "<< p->GetSize() << " bytes " << std::endl;
}

static void PhyTxDrop (Ptr<const Packet> p)
{
std::cout <<"Phy Drop Packet "<< p->GetSize() << " bytes " << std::endl;
}

static void NodeStatusChanged(std::string source, Ptr<const mbn::RoutingProtocol> nodez) {
	std::cout << Simulator::Now()<< " Node Status Changed: " << source << ", new status: "
			<< nodez->GetLocalNodeStatus()<< std::endl;
}

void
DevTxTrace (std::string context, Ptr<const Packet> p)
{
 if (g_verbose)
   {
     std::cout<< "  Node "<< GetNodeID(context) << " TX p: " << *p << std::endl;
   }
}
void
DevRxTrace (std::string context, Ptr<const Packet> p)
{
 if (g_verbose)
   {
     std::cout<< "  Node "<< GetNodeID(context) << " RX p: " << *p << std::endl;
   }
}
void
PhyRxOkTrace (std::string context, Ptr<const Packet> packet, double
snr, WifiMode mode, enum WifiPreamble preamble)
{
 if (g_verbose)
   {
     std::cout<< "  Node "<< GetNodeID(context) << " PHYRXOK mode=" << mode << " snr=" << snr << " " <<
*packet << std::endl;
   }
}
void
PhyRxErrorTrace (std::string context, Ptr<const Packet> packet, double
snr)
{
 if (g_verbose)
   {
     std::cout<< "  Node "<< GetNodeID(context) << " PHYRXERROR snr=" << snr << " " << *packet <<
std::endl;
   }
}
void
PhyTxTrace (std::string context, Ptr<const Packet> packet, WifiMode
mode, WifiPreamble preamble, uint8_t txPower)
{
 if (g_verbose)
   {
	 std::cout<< "  Node "<< GetNodeID(context) << " PHYTX mode=" << mode << " " << *packet <<
std::endl;
   }
}

void
PhyStateTrace (std::string context, Time start, Time duration, enum
WifiPhy::State state)
{
 if (g_verbose)
   {
	 std::cout<< "  Node "<< GetNodeID(context) << " state=" << state << " start=" << start << " duration=" << duration << std::endl;
   }
}

int
main (int argc, char *argv[])
{
// Users may find it convenient to turn on explicit debugging
// for selected modules; the below lines suggest how to do this
#if 1
//	LogComponentEnable ("SimpleGlobalRoutingExample", LOG_LEVEL_INFO);
	LogComponentEnable ("PushPimWifi", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
	LogComponentEnable ("VideoPushApplication", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
//	LogComponentEnable ("PacketSink", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
	LogComponentEnable ("PIMDMMulticastRouting", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
//	LogComponentEnable ("AodvRoutingProtocol", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
//	LogComponentEnable ("OlsrRoutingProtocol", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
//	LogComponentEnable ("MbnAodvRoutingProtocol", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
//	LogComponentEnable ("MbnAodvNeighbors", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
//	LogComponentEnable ("MbnRoutingTable", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
//	LogComponentEnable ("UdpL4Protocol", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
//	LogComponentEnable ("Ipv4ListRouting", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
//	LogComponentEnable ("UdpSocketImpl", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
//	LogComponentEnable ("Ipv4L3Protocol", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
//	LogComponentEnable ("Ipv4RawSocketImpl", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
//	LogComponentEnable ("Ipv4EndPointDemux", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
//	LogComponentEnable ("Socket", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
//	LogComponentEnable ("Ipv4Interface", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
//	LogComponentEnable ("MacLow", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
//	LogComponentEnable ("MacRxMiddle", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
//	LogComponentEnable ("YansWifiPhy", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
//	LogComponentEnable ("InterferenceHelper", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
//	LogComponentEnable ("ArpL3Protocol", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
//	LogComponentEnable ("ArpCache", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
//	LogComponentEnable ("YansWifiChannel", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
//	LogComponentEnable("YansWifiPhy", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_FUNC | LOG_PREFIX_NODE | LOG_PREFIX_TIME));
//	LogComponentEnable ("Node", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
//	LogComponentEnable ("InterferenceHelper", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
//	LogComponentEnable ("ArpL3Protocol", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
//	LogComponentEnable ("ArpCache", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
//	LogComponentEnable ("Packet", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
//	LogComponentEnable ("DefaultSimulatorImpl", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
#endif
	/// Write per-device PCAP traces if true
	bool pcap = true;
	/// Print routes if true
	bool printRoutes = true;
	/// Number of PIM nodes
	uint32_t sizePim = 16;
//	/// Number of client nodes
	uint32_t sizeClient = 2;
	/// Animator filename
	uint32_t sizeSource = 1;
	/// grid cols number
	uint16_t cols = (uint16_t)sqrt(sizePim);
	//Routing protocol 1) OLSR, 2) AODV, 3) MBN-AODV
	int32_t routing = 1;
	//Seed for random numbers
	uint32_t seed = 4001254589;
	//Seed Run
	uint32_t run = 2;
	//Step in the grid X
	double deltaX = 80;
	//Step in the grid Y
	double deltaY = 80;
	//Nodes in a row
	/// Animator filename
	std::string animFile = "push-over-pim-wireles.tr";
	/// Simulation time, seconds
	double totalTime = 82;
	/// Video start
	double sourceStart = 30;
	/// Video stop
	double sourceStop = totalTime-10;
	/// Client start
	double clientStart = sourceStart;
	/// Client stop
	double clientStop = totalTime;
	/// Flow Monitor
	bool enableFlowMonitor = false;

//
//	double onOffStart = 14;
//	double onOffStop = totalTime-5;
//	double sinkStart = onOffStart;
//	double sinkStop = totalTime-1;

	CommandLine cmd;
	cmd.AddValue("seed", "Seed Random.", seed);
	cmd.AddValue("run", "Seed Run.", run);

	cmd.AddValue("sizePim", "Number of PIM nodes.", sizePim);
	cmd.AddValue("sizeClient", "Number of PIM nodes.", sizeClient);
	cmd.AddValue("sizeSource", "Number of PIM nodes.", sizeSource);
	cmd.AddValue("routing", "Routing protocol to use.", routing);
	cmd.AddValue("time", "Simulation time, s.", totalTime);
	cmd.AddValue("deltaY", "Grid step Y", deltaY);
	cmd.AddValue("deltaX", "Grid step X", deltaX);
	cmd.AddValue("cols", "Grid width ", cols);

	cmd.AddValue("printRoutes", "Print routing table dumps.", printRoutes);
	cmd.AddValue("pcap", "Write PCAP traces.", pcap);
	cmd.AddValue("animFile", "File Name for Animation Output", animFile);

	cmd.Parse(argc, argv);
	// Here, we will explicitly create four nodes.  In more sophisticated
	// topologies, we could configure a node factory.

	SeedManager::SetSeed(seed);
	SeedManager::SetRun(run);
	NS_LOG_INFO ("Create nodes.");
	NodeContainer source;
	source.Create(sizeSource);
	NodeContainer routers;
	routers.Create (sizePim);// here routes from node 0 to 3
	NodeContainer clients;
	clients.Create (sizeClient);// here clients from node 4 to 7, 7 is the source

	NodeContainer allNodes;
	allNodes.Add(source);
	allNodes.Add(routers);
	allNodes.Add(clients);

	for (uint32_t i = 0; i < allNodes.GetN(); ++i) { // Name nodes
		std::ostringstream os;
		os << "node-" << i;
		Names::Add(os.str(), allNodes.Get(i));
	}
	NS_LOG_INFO("Build Topology.");

//	WifiModeValue phyMode = WifiModeValue(WifiPhy::GetOfdmRate54Mbps());
//
//    Config::SetDefault ("ns3::WifiRemoteStationManager::RtsCtsThreshold", StringValue ("2200"));
//    Config::SetDefault ("ns3::WifiRemoteStationManager::NonUnicastMode", phyMode);

	/* WIFI STANDARD */

	WifiHelper wifi = WifiHelper::Default ();
	wifi.SetStandard (WIFI_PHY_STANDARD_80211b);
//	wifi.SetStandard (WIFI_PHY_STANDARD_80211g);

	Ptr<YansWifiChannel> channel = CreateObject<YansWifiChannel> ();
	Ptr<ConstantSpeedPropagationDelayModel> delayModel = CreateObject<ConstantSpeedPropagationDelayModel> ();
	channel->SetPropagationDelayModel (delayModel);
	Ptr<LogDistancePropagationLossModel> lossModel = CreateObject<LogDistancePropagationLossModel> ();
	channel->SetPropagationLossModel (lossModel);

	YansWifiPhyHelper phy = YansWifiPhyHelper::Default ();
	phy.SetChannel (channel);
	Ptr<ErrorRateModel> error = CreateObject<YansErrorRateModel> ();
	phy.SetErrorRateModel("ns3::YansErrorRateModel");
	phy.Set("TxGain",DoubleValue(0.0));
	phy.Set("RxGain",DoubleValue(1.0));

	 // Add a non-QoS upper mac, and disable rate control
	NqosWifiMacHelper mac = NqosWifiMacHelper::Default ();

	//802.11b
	wifi.SetRemoteStationManager ("ns3::ConstantRateWifiManager",
		"DataMode", WifiModeValue (WifiPhy::GetDsssRate1Mbps()),
		"ControlMode",WifiModeValue (WifiPhy::GetDsssRate1Mbps()),
		"NonUnicastMode", WifiModeValue (WifiPhy::GetDsssRate1Mbps())
		);

	//802.11g
//	wifi.SetRemoteStationManager ("ns3::ConstantRateWifiManager",
//		"DataMode", WifiModeValue (WifiPhy::GetErpOfdmRate6Mbps()),
//		"ControlMode",WifiModeValue (WifiPhy::GetErpOfdmRate6Mbps()),
//		"NonUnicastMode", WifiModeValue (WifiPhy::GetErpOfdmRate6Mbps())
//		);


	// Set it to adhoc mode
	mac.SetType ("ns3::AdhocWifiMac");

	//add csma
	CsmaHelper csma;
	csma.SetChannelAttribute ("DataRate", DataRateValue (DataRate (5000000)));
	csma.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (2)));

//	NetDeviceContainer sourceNetDev = wifi.Install(phy, mac, source);
	NetDeviceContainer routersNetDev = wifi.Install(phy, mac, routers);
	NetDeviceContainer clientsNetDev = wifi.Install(phy, mac, clients);

	NodeContainer s0r0;
	s0r0.Add(source.Get(0));
	s0r0.Add(routers.Get(0));
	NetDeviceContainer ds0dr0 = csma.Install (s0r0);

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

	Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

	InternetStackHelper internetClients;
	internetClients.SetRoutingHelper (listClients);
	internetClients.Install (clients);
	internetClients.Install (source);

	// Later, we add IP addresses.
	NS_LOG_INFO ("Assign IP Addresses.");
	Ipv4AddressHelper ipv4;
	Ipv4Address base = Ipv4Address("10.1.2.0");
	Ipv4Mask mask = Ipv4Mask("255.255.255.0");
	ipv4.SetBase (base, mask);
//	Ipv4InterfaceContainer ipSource = ipv4.Assign (sourceNetDev);
	Ipv4InterfaceContainer ipRouter = ipv4.Assign (routersNetDev);
	Ipv4InterfaceContainer ipClient = ipv4.Assign (clientsNetDev);

	base = Ipv4Address("10.1.1.0");
	ipv4.SetBase (base, mask);
	Ipv4InterfaceContainer ipSource = ipv4.Assign (ds0dr0);
	Ipv4Address multicastSource = ipSource.GetAddress(0);

  	NS_LOG_INFO ("Configure multicasting.");

	Ipv4Address multicastGroup ("225.1.2.4");

	/* 1) Configure a (static) multicast route on ASNGW (multicastRouter) */
	Ptr<Node> multicastRouter = routers.Get (0); // The node in question
	Ptr<NetDevice> inputIf = routersNetDev.Get (0); // The input NetDevice

	Ipv4StaticRoutingHelper multicast;
	multicast.AddMulticastRoute (multicastRouter, multicastSource, multicastGroup, inputIf, routersNetDev.Get(0));

	/* 2) Set up a default multicast route on the sender n0 */
	Ptr<Node> sender = source.Get (0);
//	Ptr<NetDevice> senderIf = sourceNetDev.Get (0);
	Ptr<NetDevice> senderIf = ds0dr0.Get (0);
	multicast.SetDefaultMulticastRoute (sender, senderIf);

	std::stringstream ss;
	/* source, group, interface*/
	ss<< multicastSource<< "," << multicastGroup;// << "," << "1";
	for (int n = 0;  n < routers.GetN() ; n++){
		std::stringstream command;//create a stringstream
		command<< "NodeList/" << routers.Get(n)->GetId() << "/$ns3::pimdm::MulticastRoutingProtocol/RegisterSG";
		Config::Set(command.str(), StringValue(ss.str()));
	}
	for (int n = 0;  n < routers.GetN() ; n++){
		std::stringstream command;//create a stringstream
		ss.str("");
		ss<< multicastSource<< "," << multicastGroup << "," << "1";
		command<< "NodeList/" << routers.Get(n)->GetId() << "/$ns3::pimdm::MulticastRoutingProtocol/RegisterAsMember";
		Config::Set(command.str(), StringValue(ss.str()));
	}

	switch(routing){
		case 1:{
			for (int n = 0;  n < clients.GetN() ; n++){//Clients are RN nodes
				std::stringstream command;
				command<< "/NodeList/"<<clients.Get(n)->GetId()<<"/$ns3::olsr::RoutingProtocol/Willingness";
				Config::Set(command.str(), EnumValue(0));
			}
			break;
		}
		case 2:{
			break;
		}
		case 3:{
			Config::Set("/NodeList/*/$ns3::mbn::RoutingProtocol/localWeightFunction",EnumValue(mbn::W_NODE_RND));
//			if(g_verbose){
				Config::Connect("/NodeList/*/$ns3::mbn::RoutingProtocol/NodeStatusChanged",MakeCallback(&NodeStatusChanged));
//			}

//			for (int n = 0;  n < clients.GetN() ; n++){//Clients are RN nodes
//				std::stringstream command;
//				command<< "/NodeList/"<<clients.Get(n)->GetId()<<"/$ns3::mbn::RoutingProtocol/localNodeStatus";
//				Config::Set(command.str(), EnumValue(mbn::RN_NODE));
//			}
			for (int n = 0;  n < source.GetN() ; n++){//SOURCE is BN so it can Tx
				std::stringstream command;
				command<< "/NodeList/"<<source.Get(n)->GetId()<<"/$ns3::mbn::RoutingProtocol/localNodeStatus";
				Config::Set(command.str(), EnumValue(mbn::BN_NODE));
			}

			for (int n = 0;  n < routers.GetN() ; n++){//ROUTERS are BCN nodes
				std::stringstream command;//create a stringstream
				command<< "/NodeList/"<<routers.Get(n)->GetId()<<"/$ns3::mbn::RoutingProtocol/localNodeStatus";
				Config::Set(command.str(), EnumValue(mbn::BCN_NODE));
			}
//				for(int i = 0; i < routers.GetN(); i++){
//					std::stringstream ss;
//					ss << "/NodeList/"<<i<<"/$ns3::mbn::RoutingProtocol/localWeight";
//					uint32_t weight = (uint32_t)UintegerValue(UniformVariable().GetValue()*100.0);
//					Config::Set(ss.str(),UintegerValue(weight));
//					ss.str("");
//				}
			Config::Set("/NodeList/*/$ns3::mbn::RoutingProtocol/localWeight",UintegerValue(6));
			Config::Set("/NodeList/0/$ns3::mbn::RoutingProtocol/localWeight",UintegerValue(9));
			std::cout << "Starting simulation for " << totalTime << " s ...\n";
			break;
		}
	}

	NS_LOG_INFO ("Create Source");
	InetSocketAddress dst = InetSocketAddress (multicastGroup, PUSH_PORT);
	Config::SetDefault ("ns3::UdpSocket::IpMulticastTtl", UintegerValue (1));
	VideoHelper video = VideoHelper ("ns3::UdpSocketFactory", dst);
	video.SetAttribute ("OffTime", RandomVariableValue (ConstantVariable (2.0)));
	video.SetAttribute ("OnTime", RandomVariableValue (ConstantVariable (1.0)));
	video.SetAttribute ("DataRate", StringValue ("10kb/s"));
	video.SetAttribute ("PacketSize", UintegerValue (1200));
	video.SetAttribute ("PeerType", EnumValue (SOURCE));
	video.SetAttribute ("Local", AddressValue (ipSource.GetAddress(0)));
	video.SetAttribute ("PeerPolicy", EnumValue (RANDOM));
	video.SetAttribute ("ChunkPolicy", EnumValue (LATEST));


	ApplicationContainer apps = video.Install (source.Get (0));
	apps.Start (Seconds (sourceStart));
	apps.Stop (Seconds (sourceStop));

	for(uint32_t n = 0; n < clients.GetN() ; n++){
		InetSocketAddress dstC = InetSocketAddress (multicastGroup, PUSH_PORT);
		Config::SetDefault ("ns3::UdpSocket::IpMulticastTtl", UintegerValue (1));
		VideoHelper videoC = VideoHelper ("ns3::UdpSocketFactory", dstC);
		videoC.SetAttribute ("OffTime", RandomVariableValue (ConstantVariable (2.0)));
		videoC.SetAttribute ("OnTime", RandomVariableValue (ConstantVariable (1.0)));
//		videoC.SetAttribute ("DataRate", StringValue ("10kb/s"));
//		videoC.SetAttribute ("PacketSize", UintegerValue (1200));
		videoC.SetAttribute ("PeerType", EnumValue (PEER));
		videoC.SetAttribute ("LocalPort", UintegerValue (PUSH_PORT));
		videoC.SetAttribute ("Local", AddressValue(ipClient.GetAddress(n)));
		videoC.SetAttribute ("PeerPolicy", EnumValue (RANDOM));
		videoC.SetAttribute ("ChunkPolicy", EnumValue (LATEST));

		ApplicationContainer appC = videoC.Install (clients.Get(n));
		appC.Start (Seconds (clientStart));
		appC.Stop (Seconds (clientStop));
	}


	/* ROUTERS ARE ALSO CLIENTS */
//	for(uint32_t n = 0; n < routers.GetN() ; n++){
//		InetSocketAddress dstR = InetSocketAddress (multicastGroup, PUSH_PORT);
//		Config::SetDefault ("ns3::UdpSocket::IpMulticastTtl", UintegerValue (1));
//		VideoHelper videoR = VideoHelper ("ns3::UdpSocketFactory", dstR);
//		videoR.SetAttribute ("OffTime", RandomVariableValue (ConstantVariable (2.0)));
//		videoR.SetAttribute ("OnTime", RandomVariableValue (ConstantVariable (1.0)));
////		videoC.SetAttribute ("DataRate", StringValue ("10kb/s"));
////		videoC.SetAttribute ("PacketSize", UintegerValue (1200));
//		videoR.SetAttribute ("PeerType", EnumValue (PEER));
//		videoR.SetAttribute ("Local", AddressValue(ipRouter.GetAddress(n)));
//		videoR.SetAttribute ("PeerPolicy", EnumValue (RANDOM));
//		videoR.SetAttribute ("ChunkPolicy", EnumValue (LATEST));
//
////		Ipv4StaticRoutingHelper multicast;
////		multicast.AddMulticastRoute (routers.Get(n), multicastSource, multicastGroup, routersNetDev.Get (n), routersNetDev.Get (n));
//
//		ApplicationContainer appR = videoR.Install (routers.Get(n));
//		appR.Start (Seconds (clientStart));
//		appR.Stop (Seconds (clientStop));
//	}

//	NS_LOG_INFO ("Create Sink.");
//	PacketSinkHelper sink = PacketSinkHelper ("ns3::UdpSocketFactory", dst);
//	apps = sink.Install (clients);
//	apps.Start (Seconds (sinkStart));
//	apps.Stop (Seconds (sinkStop));


	//sink callback
//	for(int i = source.GetN()+routers.GetN(); i < (source.GetN()+routers.GetN()+clients.GetN()); i++){
//		std::stringstream ss;
//		ss << "/NodeList/"<<i<<"/ApplicationList/0/$ns3::PacketSink/Rx";
//		Config::ConnectWithoutContext(ss.str(),MakeCallback (&SinkRx));
//		ss.str("");
//	}

if(g_verbose){
	Config::ConnectWithoutContext("/NodeList/0/ApplicationList/0/$ns3::VideoPushApplication/Tx",MakeCallback (&AppTx));
	Config::ConnectWithoutContext("/NodeList/*/DeviceList/*/$ns3::WifiNetDevice/Phy/$ns3::YansWifiPhy/PhyTxDrop",MakeCallback (&PhyTxDrop));
	Config::Connect ("/NodeList/*/DeviceList/*/Mac/MacTx", MakeCallback (&DevTxTrace));
	Config::Connect ("/NodeList/*/DeviceList/*/Mac/MacRx",	MakeCallback (&DevRxTrace));
	Config::Connect ("/NodeList/*/DeviceList/*/Phy/State/RxOk",	MakeCallback (&PhyRxOkTrace));
	Config::Connect ("/NodeList/*/DeviceList/*/Phy/State/RxError",	MakeCallback (&PhyRxErrorTrace));
	Config::Connect ("/NodeList/*/DeviceList/*/Phy/State/Tx",	MakeCallback (&PhyTxTrace));
	Config::Connect ("/NodeList/*/DeviceList/*/Phy/State/State", MakeCallback (&PhyStateTrace));
}
//	Config::ConnectWithoutContext ("/NodeList/[5-8]/ApplicationList/0/$ns3::PacketSink/Rx", MakeCallback (&SinkRx));
//
//	MobilityHelper mobilityR;
//	Ptr<ListPositionAllocator> positionAllocR = CreateObject<ListPositionAllocator> ();
//	positionAllocR->Add(Vector(250.0, 310.0, 0.0));// 0
//	positionAllocR->Add(Vector(190.0, 250.0, 0.0));// 1
//	positionAllocR->Add(Vector(250.0, 190.0, 0.0));// 2
//	positionAllocR->Add(Vector(320.0, 250.0, 0.0));// 3
//	mobilityR.SetPositionAllocator(positionAllocR);
//	mobilityR.SetMobilityModel("ns3::ConstantPositionMobilityModel");
//	mobilityR.Install(routers);
//
//	Ptr<ListPositionAllocator> positionAllocS = CreateObject<ListPositionAllocator> ();
//	positionAllocS->Add(Vector(250.0, 380.0, 0.0));// Source
//	MobilityHelper mobilityS;
//	mobilityS.SetPositionAllocator(positionAllocS);
//	mobilityS.SetMobilityModel("ns3::ConstantPositionMobilityModel");
//	mobilityS.Install(source);

//	MobilityHelper mobilityC;
//	Ptr<ListPositionAllocator> positionAllocC = CreateObject<ListPositionAllocator> ();
//	positionAllocC->Add(Vector(130.0, 250.0, 0.0));// 1C
//	positionAllocC->Add(Vector(250.0, 120.0, 0.0));// 2C
//	positionAllocC->Add(Vector(380.0, 250.0, 0.0));// 3C
//	mobilityC.SetPositionAllocator(positionAllocC);
//	mobilityC.SetMobilityModel("ns3::ConstantPositionMobilityModel");
//	mobilityC.Install(client);



	MobilityHelper mobilityR;
	mobilityR.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
	mobilityR.SetPositionAllocator ("ns3::GridPositionAllocator",
	  "MinX", DoubleValue (0.0),
	  "MinY", DoubleValue (0.0),
	  "DeltaX", DoubleValue (deltaX),
	  "DeltaY", DoubleValue (deltaY),
	  "GridWidth", UintegerValue (cols),
	  "LayoutType", StringValue ("RowFirst"));
//  mobility.SetPositionAllocator ("ns3::RandomDiscPositionAllocator",
//								 "X", StringValue ("100.0"),
//								 "Y", StringValue ("100.0"),
//								 "Rho", StringValue ("Uniform:0:30"));
//  mobility.SetMobilityModel ("ns3::RandomWalk2dMobilityModel",
//                             "Mode", StringValue ("Time"),
//                             "Time", StringValue ("2s"),
//                             "Speed", StringValue ("Constant:1.0"),
//                             "Bounds", StringValue ("0|200|0|200"));

	mobilityR.Install(routers);

	int deltaXmin, deltaXmax, deltaYmin, deltaYmax;
	deltaXmin = 0;
	deltaXmax = floor (deltaX * cols);
	deltaYmin = 0;
	deltaYmax = deltaY * floor (sizePim / cols);

	NS_LOG_DEBUG ("Arranging clients between ["<<deltaXmin<<","<< deltaYmin<<"] - [" <<deltaXmax<<","<<deltaYmax<<"]");

	MobilityHelper mobilityC;
	mobilityC.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
//	mobilityC.SetPositionAllocator ("ns3::RandomRectanglePositionAllocator",
//	  "MinX", DoubleValue (50.0),
//	  "MinY", DoubleValue (50.0),
//	  "DeltaX", DoubleValue (deltaX),
//	  "DeltaY", DoubleValue (deltaY),
//	  "GridWidth", UintegerValue (cols),
//	  "LayoutType", StringValue ("RowFirst"));
	mobilityC.SetPositionAllocator("ns3::RandomBoxPositionAllocator",
		"X",RandomVariableValue(UniformVariable(deltaXmin,deltaXmax)),
		"Y",RandomVariableValue(UniformVariable(deltaYmin,deltaYmax)),
		"Z",RandomVariableValue(ConstantVariable(0)));

	//	mobilityC.SetMobilityModel("ns3::RandomDirection2dMobilityModel",
//	"Bounds", RectangleValue (Rectangle (deltaXmin,deltaXmax,deltaYmin,deltaYmax)),
//	"Speed", RandomVariableValue (ConstantVariable(5)));

	mobilityC.Install(clients);

	Ptr<ListPositionAllocator> positionAllocS = CreateObject<ListPositionAllocator> ();
	positionAllocS->Add(Vector(-70.0, -70.0, 0.0));// Source
	MobilityHelper mobilityS;
	mobilityS.SetPositionAllocator(positionAllocS);
	mobilityS.SetMobilityModel("ns3::ConstantPositionMobilityModel");
	mobilityS.Install(source);

	for(int i = 0; i < allNodes.GetN(); i++){
		  Ptr<MobilityModel> mobility = allNodes.Get(i)->GetObject<MobilityModel> ();
	      Vector pos = mobility->GetPosition (); // Get position
	      NS_LOG_DEBUG("Position Node ["<<i<<"] = ("<< pos.x << ", " << pos.y<<", "<<pos.z<<")");
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
