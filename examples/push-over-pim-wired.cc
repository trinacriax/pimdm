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
#ifndef NS3_LOG_ENABLE
	#define NS3_LOG_ENABLE
#endif

#include <iostream>
#include <fstream>
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

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/applications-module.h"
#include "ns3/csma-helper.h"
#include "ns3/flow-monitor-helper.h"
#include "ns3/string.h"


using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("PushPimWired");

static bool g_verbose = true;

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

//static void PhyTxDrop (Ptr<const Packet> p)
//{
//std::cout <<"Sending Packet "<< p->GetSize() << " bytes " << std::endl;
//}

static void NodeStatusChanged(std::string source, Ptr<const mbn::RoutingProtocol> nodez) {
	std::cout << Simulator::Now()<< " Node Status Changed: " << source << ", new status: "
			<< nodez->GetLocalNodeStatus()<< std::endl;
}

static void RegisterClientOnNode (Ipv4Address source, Ipv4Address group, int node, int clientIface){
	std::stringstream ss;
	ss<< source<< "," << group << "," << clientIface;
	std::stringstream command;//create a stringstream
	command<< "NodeList/" << node << "/$ns3::pimdm::MulticastRoutingProtocol/RegisterAsMember";
	Config::Set(command.str(), StringValue(ss.str()));
	NS_LOG_DEBUG(command.str()<<"::"<<ss.str());
}

static void UnRegisterClientOnNode (Ipv4Address source, Ipv4Address group, int node, int clientIface){
	std::stringstream ss;
	ss<< source<< "," << group << "," << clientIface;
	std::stringstream command;//create a stringstream
	command<< "NodeList/" << node << "/$ns3::pimdm::MulticastRoutingProtocol/UnRegisterAsMember";
	Config::Set(command.str(), StringValue(ss.str()));
	NS_LOG_DEBUG(command.str()<<"::"<<ss.str());
}

int
main (int argc, char *argv[])
{
// Users may find it convenient to turn on explicit debugging
// for selected modules; the below lines suggest how to do this
#if 1
//	LogComponentEnable ("SimpleGlobalRoutingExample", LOG_LEVEL_INFO);
	LogComponentEnable ("PushPimWired", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
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
	/// Write per-device PCAP traces if true
	bool pcap = true;
	/// Print routes if true
	bool printRoutes = true;
	/// Number of PIM nodes
	uint32_t sizePim = 10;
	/// Number of client nodes
	uint32_t maxClient = 5;
	/// Animator filename
	uint32_t sizeSource = 1;
	/// grid cols number
	uint16_t cols = (uint16_t)sqrt(sizePim);
	//Routing protocol 1) OLSR, 2) AODV, 3) MBN-AODV
	int32_t routing = 1;
	//Seed for random numbers
	uint32_t run = 1;
	/// Animator filename
	std::string animFile = "push-over-pim-wired.tr";
	std::string flowFile = "results.xml";
	/// Simulation time, seconds
	double totalTime = 400;
	/// Video start
	double sourceStart = 40;
	/// Flow Monitor
	bool enableFlowMonitor = true;

	CommandLine cmd;
	cmd.AddValue("pcap", "Write PCAP traces.", pcap);
	cmd.AddValue("run", "Run sim.", run);
	cmd.AddValue("printRoutes", "Print routing table dumps.", printRoutes);
	cmd.AddValue("sizePim", "Number of PIM nodes.", sizePim);
	cmd.AddValue("maxClient", "Max number of clients for each PIM router.", maxClient);
	cmd.AddValue("sizeSource", "Number of PIM nodes.", sizeSource);
	cmd.AddValue("cols", "Number of cols in the grid.", cols);
	cmd.AddValue("routing", "Routing protocol to use.", routing);
	cmd.AddValue("time", "Simulation time, s.", totalTime);
	cmd.AddValue("animFile", "File Name for Animation Output", animFile);
	cmd.AddValue ("EnableMonitor", "Enable Flow Monitor", enableFlowMonitor);

	cmd.Parse(argc, argv);
	// Here, we will explicitly create four nodes.  In more sophisticated
	// topologies, we could configure a node factory.

	/// Video stop
	double sourceStop = totalTime-10;
	/// Client start
	double clientStart = sourceStart;
	/// Client stop
	double clientStop = totalTime;

	SeedManager::SetRun(run);
	SeedManager::SetSeed(8453*run);

	NS_LOG_INFO ("Create nodes.");
	NodeContainer source;
	source.Create(sizeSource);
	NodeContainer routers;
	routers.Create (sizePim);// here routes from node 0 to 3
	NodeContainer all_clients;

	NodeContainer allNodes;
	allNodes.Add(source);
	allNodes.Add(routers);

	for (uint32_t i = 0; i < allNodes.GetN(); ++i) {// Name nodes
		std::ostringstream os;
		os << "node-" <<i;
		Names::Add(os.str(), allNodes.Get(i));
	}
	NS_LOG_INFO ("Build Topology.");

	CsmaHelper csma;
	csma.SetChannelAttribute ("DataRate", DataRateValue (DataRate (5000000)));
	csma.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (2)));
//	csma.SetDeviceAttribute ("EncapsulationM8ode", StringValue ("Llc"));

	// Defines connections between routers and clients

	NS_LOG_DEBUG("Building Clients Topology by Matrix");
	std::list<NetDeviceContainer> rcDevices;
	int32_t routersC [10][5]= {
		//IFACE  0,1,2,3,4,5,6,7,8,9,
		/*1*/	{0,-1,0,0,0},
		/*2*/	{0,-1,0,0,0},
		/*3*/	{0,-1,0,0,0},
		/*4*/	{0,-1,0,0,0},
		/*5*/	{0,1,0,0,0},
		/*6*/	{0,-1,0,0,0},
		/*7*/	{0,-1,0,0,0},
		/*8*/	{0,-1,0,0,0},
		/*9*/	{0,-1,0,0,0},
		/*10*/	{0,-1,0,0,0}
		};
	std::stringstream topo;
	for (uint32_t n = 0; n < routers.GetN() ; n++){
		topo << "Router " << routers.Get(n)->GetId() <<" Clients on interface :";
		NetDeviceContainer ndc;
		for (uint32_t c = 0; c < 5 ; c++){
			if (routersC[n][c] == 0 ) continue;
			uint32_t n_clients = UniformVariable().GetInteger(1,maxClient);
			topo<< c <<" (" << n_clients << ")" << ",";
			NodeContainer clients;
			clients.Create(n_clients); // create clients
			NodeContainer nc;
			nc.Add(routers.Get(n));
			nc.Add(clients);
			all_clients.Add(clients); // add all clients
			ndc = csma.Install (nc);  // create the lan covering router and its clients
			rcDevices.push_back(ndc); // add the NetDeviceContainer in the Routers-Clients device
		}
		NS_LOG_DEBUG(topo.str()<< " Devices "<< routers.Get(n)->GetNDevices());
		topo.str("");
	}

	NS_LOG_DEBUG("Building Routers Topology by Matrix");
	int32_t routersM [10][10]= {
		//   1,2,3,4,5,6,7,8,9,10
	/*1*/	{0,1,1,0,0,0,0,0,0,0},
	/*2*/	{0,0,1,1,1,0,0,0,0,0},
	/*3*/	{0,0,0,1,0,0,0,0,0,1},
	/*4*/	{0,0,0,0,1,0,0,0,0,0},
	/*5*/	{0,0,0,0,0,1,0,0,0,0},
	/*6*/	{0,0,0,0,0,0,1,0,1,0},
	/*7*/	{0,0,0,0,0,0,0,1,0,0},
	/*8*/	{0,0,0,0,0,0,0,0,1,0},
	/*9*/	{0,0,0,0,0,0,0,0,0,1},
	/*10*/	{0,0,0,0,0,0,0,0,0,0}
	};

	std::list<NetDeviceContainer> rrDevices;
	for (uint32_t n = 0; n < routers.GetN(); n++){
		topo << "Node " << routers.Get(n)->GetId() << "(D="<<routers.Get(n)->GetNDevices()<<"): ";
		NetDeviceContainer ndc;
		for (uint32_t m = n+1; m < routers.GetN() ; m++){
			if(routersM[n][m] == 0) continue;
			topo << routers.Get(m)->GetId() << ",";
			NodeContainer dx;
			dx.Add(routers.Get(n));
			dx.Add(routers.Get(m));
			ndc = csma.Install (dx);
			rrDevices.push_back(ndc);
		}
		NS_LOG_DEBUG(topo.str()<< " Devices "<< routers.Get(n)->GetNDevices());
		topo.str("");
	}
//	/* GRID TOPOLOGY*/
//	std::list<NetDeviceContainer> rrDevices;
//	for (uint32_t n = 0; n < sizePim; n++){
//		NetDeviceContainer ndc;
//		if(n + 1 < sizePim && !((n+1)%cols == 0)){
//			NodeContainer dx;
//			uint16_t p = n+1;
//			dx.Add(routers.Get(n));
//			dx.Add(routers.Get(p));
//			ndc = csma.Install (dx);
//			NS_LOG_DEBUG("Node "<< n << " <--> "<< p << " :: " << ndc.GetN());
//			rrDevices.push_back(ndc);
//		}
//		if(n + cols < sizePim){
//			NodeContainer dw;
//			uint16_t p = n+cols;
//			dw.Add(routers.Get(n));
//			dw.Add(routers.Get(p));
//			ndc = csma.Install (dw);
//			NS_LOG_DEBUG("Node "<< n << " <--> "<< p << " :: " << ndc.GetN());
//			rrDevices.push_back(ndc);
//		}
//	}

	// Source 0 -> Node 0
	NodeContainer s0r0;
	s0r0.Add(source.Get(0));
	s0r0.Add(routers.Get(0));
	NetDeviceContainer ds0dr0 = csma.Install (s0r0);
	NS_LOG_DEBUG("Node " << routers.Get(0)->GetId() << " Devices "<<routers.Get(0)->GetNDevices());

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

	Ipv4ListRoutingHelper listClients;
	listClients.Add (staticRouting, 11);

	switch(routing){
			case 1:{
				listRouters.Add (olsr, 10);
				listClients.Add (olsr, 10);
				break;
			}
			case 2:{
				listRouters.Add (aodv, 10);
				listClients.Add (aodv, 10);
				break;
			}
			case 3:{
				listRouters.Add (mbnaodv, 10);
				listClients.Add (mbnaodv, 10);
				break;
			}
		}
	listRouters.Add (pimdm, 11);

	InternetStackHelper internetRouters;
	internetRouters.SetRoutingHelper (listRouters);
	internetRouters.Install (routers);

	InternetStackHelper internetClients;
	internetClients.SetRoutingHelper (listClients);
	internetClients.Install (all_clients);
	internetClients.Install (source);

	// Later, we add IP addresses.
	NS_LOG_INFO ("Assign IP Addresses.");
	Ipv4AddressHelper ipv4;

	Ipv4Address base = Ipv4Address("10.1.2.0");
	ipv4.SetBase ("10.1.2.0", "255.255.255.0");
	Ipv4InterfaceContainer ipClients;
	while(!rcDevices.empty()){
		Ipv4InterfaceContainer iprc = ipv4.Assign (rcDevices.front());
		for (int k = 1; k < iprc.GetN(); k++)
			ipClients.Add(iprc.Get(k));
		rcDevices.pop_front();
		base = Ipv4Address(base.Get()+256);
		ipv4.SetBase (base, "255.255.255.0");
		//evitare il loop
	}

	base = Ipv4Address(base.Get()+(256*10));
	ipv4.SetBase (base, "255.255.255.0");
	while(!rrDevices.empty()){
		NS_LOG_DEBUG("IP Base "<<base);
		Ipv4InterfaceContainer iprr = ipv4.Assign (rrDevices.front());
		rrDevices.pop_front();
		base = Ipv4Address(base.Get()+256);
		ipv4.SetBase (base, "255.255.255.0");
	}

	ipv4.SetBase ("10.1.1.0", "255.255.255.0");
	Ipv4InterfaceContainer ips0r0 = ipv4.Assign (ds0dr0);

	NS_LOG_INFO ("Configure multicasting.");
	Ipv4Address multicastSource ("10.1.1.1");
	Ipv4Address multicastGroup ("225.1.2.4");

	// 1) Configure a (static) multicast route on ASNGW (multicastRouter)
	Ipv4StaticRoutingHelper multicast;
	//	Add a multicast route to a node and net device using explicit Ptr<Node> and Ptr<NetDevice>
	//    Source IP: multicastSource; Group IP: multicastGroup;
	//    Route to Node: routers.Get (0)
	//    Dest. Node input interface: ds0dr0.Get(1)
	//
	multicast.AddMulticastRoute (routers.Get (0), multicastSource, multicastGroup, ds0dr0.Get(1), ds0dr0.Get(1));

	// 2) Set up a default multicast route on the sender n0
	Ptr<Node> sender = source.Get (0);
	Ptr<NetDevice> senderIf = ds0dr0.Get (0);
	multicast.SetDefaultMulticastRoute (sender, senderIf);

	std::stringstream ss;
	// source,group,interface
	ss<< multicastSource<< "," << multicastGroup;
	for (int n = 0;  n < routers.GetN() ; n++){
		std::stringstream command;//create a stringstream
		command<< "NodeList/" << routers.Get(n)->GetId() << "/$ns3::pimdm::MulticastRoutingProtocol/RegisterSG";
		Config::Set(command.str(), StringValue(ss.str()));
	}
	for (int n = 0;  n < routers.GetN() ; n++){
		for (uint32_t c = 0; c < 5 ; c++){
			if (routersC[n][c] == 0 ) continue;
			if (routersC[n][c] == -1 ) {
				NS_LOG_DEBUG("Delayed on " << routers.Get(n)->GetId()<< " Client over "<< c);
				continue;
			}
			ss.str("");
			ss<< multicastSource<< "," << multicastGroup << "," << c;
			std::stringstream command;//create a stringstream
			command<< "NodeList/" << routers.Get(n)->GetId() << "/$ns3::pimdm::MulticastRoutingProtocol/RegisterAsMember";
			Config::Set(command.str(), StringValue(ss.str()));
		}
	}
	switch(routing){
			case 1:{
				break;
			}
			case 2:{
				break;
			}
			case 3:{
				Config::Set("/NodeList/*/$ns3::mbn::RoutingProtocol/localWeightFunction",EnumValue(mbn::W_NODE_RND));
				Config::Connect("/NodeList/*/$ns3::mbn::RoutingProtocol/NodeStatusChanged",MakeCallback(&NodeStatusChanged));

				for (int n = 0;  n < all_clients.GetN() ; n++){//Clients are RN nodes
					std::stringstream command;
					command<< "/NodeList/"<<all_clients.Get(n)->GetId()<<"/$ns3::mbn::RoutingProtocol/localNodeStatus";
					Config::Set(command.str(), EnumValue(mbn::RN_NODE));
				}
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


	// Configure Source
	NS_LOG_INFO ("Create Source");
	InetSocketAddress dst = InetSocketAddress (multicastGroup, PIM_PORT_NUMBER);
	Config::SetDefault ("ns3::UdpSocket::IpMulticastTtl", UintegerValue (1));
	VideoHelper video = VideoHelper ("ns3::UdpSocketFactory", dst);
	video.SetAttribute ("OffTime", RandomVariableValue (ConstantVariable (2.0)));
	video.SetAttribute ("OnTime", RandomVariableValue (ConstantVariable (1.0)));
	video.SetAttribute ("DataRate", StringValue ("10kb/s"));
	video.SetAttribute ("PacketSize", UintegerValue (1200));
	video.SetAttribute ("PeerType", EnumValue (SOURCE));
	video.SetAttribute ("Local", AddressValue (ips0r0.GetAddress(0)));
	video.SetAttribute ("PeerPolicy", EnumValue (RANDOM));
	video.SetAttribute ("ChunkPolicy", EnumValue (LATEST));

	ApplicationContainer apps = video.Install (source.Get (0));
	apps.Start (Seconds (sourceStart));
	apps.Stop (Seconds (sourceStop));

	for(int n = 0; n < all_clients.GetN() ; n++){
		InetSocketAddress dstC = InetSocketAddress (multicastGroup, PIM_PORT_NUMBER);
		Config::SetDefault ("ns3::UdpSocket::IpMulticastTtl", UintegerValue (1));
		VideoHelper videoC = VideoHelper ("ns3::UdpSocketFactory", dstC);
		videoC.SetAttribute ("OffTime", RandomVariableValue (ConstantVariable (2.0)));
		videoC.SetAttribute ("OnTime", RandomVariableValue (ConstantVariable (1.0)));
//		videoC.SetAttribute ("DataRate", StringValue ("10kb/s"));
//		videoC.SetAttribute ("PacketSize", UintegerValue (1200));
		videoC.SetAttribute ("PeerType", EnumValue (PEER));
		videoC.SetAttribute ("LocalPort", UintegerValue (PIM_PORT_NUMBER));
		videoC.SetAttribute ("Local", AddressValue (ipClients.GetAddress(n)));
		videoC.SetAttribute ("PeerPolicy", EnumValue (RANDOM));
		videoC.SetAttribute ("ChunkPolicy", EnumValue (LATEST));

		ApplicationContainer appC = videoC.Install (all_clients.Get(n));
		appC.Start (Seconds (clientStart));
		appC.Stop (Seconds (clientStop));
	}

	Config::ConnectWithoutContext("/NodeList/0/ApplicationList/0/$ns3::VideoPushApplication/Tx",MakeCallback (&AppTx));

	Simulator::Schedule(Seconds(210), &RegisterClientOnNode, multicastSource, multicastGroup , 10, 1);
	Simulator::Schedule(Seconds(150), &UnRegisterClientOnNode, multicastSource, multicastGroup , 5, 1);
//	AsciiTraceHelper ascii;
//	csma.EnableAsciiAll (ascii.CreateFileStream (animFile));
//	csma.EnablePcapAll ("link12", false);

	// Flow Monitor
	Ptr<FlowMonitor> flowmon;
	if (enableFlowMonitor)
	{
	  FlowMonitorHelper flowmonHelper;
	  flowmon = flowmonHelper.InstallAll ();
	  flowmon->SetAttribute("DelayBinWidth", DoubleValue(0.001));
	  flowmon->SetAttribute("JitterBinWidth",DoubleValue(0.001));
	  flowmon->SetAttribute("PacketSizeBinWidth", DoubleValue(20));
	}

	NS_LOG_INFO ("Run Simulation.");
	Simulator::Stop (Seconds (totalTime));
	Simulator::Run ();
	NS_LOG_INFO ("Done.");


	if (enableFlowMonitor)
	{
	  flowmon->SerializeToXmlFile (flowFile, true, true);
	}

	Simulator::Destroy ();
	return 0;
}
