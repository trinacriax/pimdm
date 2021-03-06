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


#ifndef NS3_LOG_ENABLE
	#define NS3_LOG_ENABLE
#endif


#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <sstream>

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

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("PushPimWifi");

static bool g_verbose = false;

uint32_t
GetNodeID (std::string context){
	uint32_t p3 = 0;
	if(g_verbose){
		uint32_t p2 = context.find("/");
		uint32_t p1 = context.find("/",p2+1);
		p2 = context.find("/",p1+1);
		std::string str = context.substr(p1+1, (p2-p1)-1);
		p3 = atoi(str.c_str());
//		std::cout<<"P1 = "<<p1<< " P2 = "<< p2<< "?"<<p3<< " ID "<< context.substr(p1, (p2-p1))<<" -- " << context<<"\n";
	}
	return p3;
}

static void AppRx (Ptr<const Packet> p, const Address &ad)
{
std::cout <<"Received Packet "<< p->GetSize() << " bytes from "<<InetSocketAddress::ConvertFrom (ad).GetIpv4()<< std::endl;
}

static void AppTx (Ptr<const Packet> p)
{
std::cout <<"Sending Packet "<< p->GetSize() << " bytes " << std::endl;
}

static void PhyTxDrop (Ptr<const Packet> p)
{
std::cout <<"Phy Drop Packet "<< p->GetSize() << " bytes " << std::endl;
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
//	LogComponentEnable ("PIMDMMulticastRouting", LogLevel(LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE| LOG_PREFIX_FUNC));
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
	uint32_t sizePim = 8;
	/// Animator filename
	uint32_t sizeSource = 1;
	/// grid cols number
	uint16_t cols = (uint16_t)sqrt(sizePim);
	//Routing protocol 1) OLSR, 2) AODV
	int32_t routing = 1;
	//Seed for random numbers
	uint32_t seed = 4001254589;
	//Step in the grid X
	double deltaX = 30;
	//Step in the grid Y
	double deltaY = 30;
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
//	bool enableFlowMonitor = false;
	/// Run
	uint32_t run = 2;

	CommandLine cmd;
	cmd.AddValue("pcap", "Write PCAP traces.", pcap);
	cmd.AddValue("seed", "Seed Random.", seed);
	cmd.AddValue("printRoutes", "Print routing table dumps.", printRoutes);
	cmd.AddValue("sizePim", "Number of PIM nodes.", sizePim);
//	cmd.AddValue("sizeClient", "Number of PIM nodes.", sizeClient);
	cmd.AddValue("sizeSource", "Number of PIM nodes.", sizeSource);
	cmd.AddValue("routing", "Routing protocol to use.", routing);
	cmd.AddValue("time", "Simulation time, s.", totalTime);
	cmd.AddValue("deltaY", "Grid step Y", deltaY);
	cmd.AddValue("deltaX", "Grid step X", deltaX);
	cmd.AddValue("cols", "Grid width ", cols);
	cmd.AddValue("animFile", "File Name for Animation Output", animFile);
	cmd.AddValue("run", "Run to execute.", run);

	cmd.Parse(argc, argv);
	// Here, we will explicitly create four nodes.  In more sophisticated
	// topologies, we could configure a node factory.

//	SeedManager::SetSeed(seed);
	SeedManager::SetRun(run);
	NS_LOG_INFO ("Create nodes.");
	NodeContainer source;
	source.Create(sizeSource);
	NodeContainer routers;
	routers.Create (sizePim);// here routes from node 0 to 3

	NodeContainer allNodes;
	allNodes.Add(source);
	allNodes.Add(routers);

	for (uint32_t i = 0; i < allNodes.GetN(); ++i) {// Name nodes
			std::ostringstream os;
			os << "node-" <<i;
			Names::Add(os.str(), allNodes.Get(i));
		}
		NS_LOG_INFO ("Build Topology.");

//	WifiModeValue phyMode = WifiModeValue(WifiPhy::GetOfdmRate54Mbps());
//
//    Config::SetDefault ("ns3::WifiRemoteStationManager::RtsCtsThreshold", StringValue ("2200"));
//    Config::SetDefault ("ns3::WifiRemoteStationManager::NonUnicastMode", phyMode);

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

	WifiHelper wifi = WifiHelper::Default ();

	/************  802.11b   ************/
	// Typical indoor range is 30 m (100 ft) at 11 Mbit/s and 90 m (300 ft) at 1 Mbit/s
	wifi.SetStandard (WIFI_PHY_STANDARD_80211b);
	wifi.SetRemoteStationManager ("ns3::ConstantRateWifiManager",
		"DataMode", WifiModeValue (WifiPhy::GetDsssRate1Mbps())
		,"ControlMode",WifiModeValue (WifiPhy::GetDsssRate5_5Mbps())
//		,"NonUnicastMode", WifiModeValue (WifiPhy::GetDsssRate1Mbps())
		);

	/************  802.11g   ************/
//	wifi.SetStandard (WIFI_PHY_STANDARD_80211g);
//	wifi.SetRemoteStationManager ("ns3::ConstantRateWifiManager",
//		"DataMode", WifiModeValue (WifiPhy::GetErpOfdmRate54Mbps())
//		,"ControlMode",WifiModeValue (WifiPhy::GetErpOfdmRate54Mbps())
////		,"NonUnicastMode", WifiModeValue (WifiPhy::GetErpOfdmRate24Mbps())
//		);

	// Set it to adhoc mode
	mac.SetType ("ns3::AdhocWifiMac");

	NetDeviceContainer sourceNetDev = wifi.Install(phy, mac, source);
	NetDeviceContainer routersNetDev = wifi.Install(phy, mac, routers);

	// INSTALL INTERNET STACK
	// Enable AODV
	NS_LOG_INFO ("Enabling AODV Routing.");
	OlsrHelper olsr;
	AodvHelper aodv;

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
		}
	listRouters.Add (pimdm, 11);

	InternetStackHelper internetRouters;
	internetRouters.SetRoutingHelper (listRouters);
	internetRouters.Install (routers);

	Ipv4ListRoutingHelper listSource;
	switch(routing){
		case 1:{
			listSource.Add (olsr, 10);
			break;
		}
		case 2:{
			listSource.Add (aodv, 10);
			break;
		}
	}
	listSource.Add (staticRouting, 11);

	InternetStackHelper internetClients;
	internetClients.SetRoutingHelper (listSource);
	internetClients.Install (source);

	// Later, we add IP addresses.
	NS_LOG_INFO ("Assign IP Addresses.");
	Ipv4AddressHelper ipv4;
	Ipv4Address base = Ipv4Address("10.1.1.0");
	Ipv4Mask mask = Ipv4Mask("255.255.255.0");
	ipv4.SetBase (base, mask);
	Ipv4InterfaceContainer ipSource = ipv4.Assign (sourceNetDev);
	Ipv4Address multicastSource (base.Get()+1);
	Ipv4InterfaceContainer ipRouter = ipv4.Assign (routersNetDev);

	NS_LOG_INFO ("Configure multicasting.");

	Ipv4Address multicastGroup ("225.1.2.4");

	// 1) Configure a (static) multicast route on ASNGW (multicastRouter)
	Ptr<Node> multicastRouter = routers.Get (0); // The node in question
	Ptr<NetDevice> inputIf = routersNetDev.Get (0); // The input NetDevice

	Ipv4StaticRoutingHelper multicast;
	multicast.AddMulticastRoute (multicastRouter, multicastSource, multicastGroup, inputIf, routersNetDev.Get(0));

	// 2) Set up a default multicast route on the sender n0
	Ptr<Node> sender = source.Get (0);
	Ptr<NetDevice> senderIf = sourceNetDev.Get (0);
	multicast.SetDefaultMulticastRoute (sender, senderIf);

	std::stringstream ss;
	// source,group,interface
	ss<< multicastSource<< "," << multicastGroup;// << "," << "1";
	for (uint32_t n = 0;  n < routers.GetN() ; n++){
		std::stringstream command;//create a stringstream
		command<< "NodeList/" << routers.Get(n)->GetId() << "/$ns3::pimdm::MulticastRoutingProtocol/RegisterSG";
		Config::Set(command.str(), StringValue(ss.str()));
	}
	for (uint32_t n = 0;  n < routers.GetN() ; n++){
		std::stringstream command;//create a stringstream
		ss.str("");
		ss<< multicastSource<< "," << multicastGroup << "," << "1";
		command<< "NodeList/" << routers.Get(n)->GetId() << "/$ns3::pimdm::MulticastRoutingProtocol/RegisterAsMember";
		Config::Set(command.str(), StringValue(ss.str()));
	}

	switch(routing){
		case 1:{
			break;
		}
		case 2:{
			break;
		}
	}

	NS_LOG_INFO ("Create Source");
	InetSocketAddress dst = InetSocketAddress (multicastGroup, PUSH_PORT);
	Config::SetDefault ("ns3::UdpSocket::IpMulticastTtl", UintegerValue (1));
	VideoHelper videoSource = VideoHelper ("ns3::UdpSocketFactory", dst);
	videoSource.SetAttribute ("OffTime", RandomVariableValue (ConstantVariable (2.0)));
	videoSource.SetAttribute ("OnTime", RandomVariableValue (ConstantVariable (1.0)));
	videoSource.SetAttribute ("DataRate", StringValue ("10kb/s"));
	videoSource.SetAttribute ("PacketSize", UintegerValue (1200));
	videoSource.SetAttribute ("PeerType", EnumValue (SOURCE));
	videoSource.SetAttribute ("Local", AddressValue (ipSource.GetAddress(0)));
	videoSource.SetAttribute ("PeerPolicy", EnumValue (PS_RANDOM));
	videoSource.SetAttribute ("ChunkPolicy", EnumValue (CS_LATEST));


	ApplicationContainer apps = videoSource.Install (source.Get (0));
	apps.Start (Seconds (sourceStart));
	apps.Stop (Seconds (sourceStop));

	for(uint32_t n = 0; n < routers.GetN() ; n++){
		InetSocketAddress dstR = InetSocketAddress (multicastGroup, PUSH_PORT);
		Config::SetDefault ("ns3::UdpSocket::IpMulticastTtl", UintegerValue (1));
		VideoHelper videoNodes = VideoHelper ("ns3::UdpSocketFactory", dstR);
		videoNodes.SetAttribute ("OffTime", RandomVariableValue (ConstantVariable (2.0)));
		videoNodes.SetAttribute ("OnTime", RandomVariableValue (ConstantVariable (1.0)));
//		videoNodes.SetAttribute ("DataRate", StringValue ("10kb/s"));
//		videoNodes.SetAttribute ("PacketSize", UintegerValue (1200));
		videoNodes.SetAttribute ("PeerType", EnumValue (PEER));
		videoNodes.SetAttribute ("Local", AddressValue(ipRouter.GetAddress(n)));
		videoNodes.SetAttribute ("PeerPolicy", EnumValue (PS_RANDOM));
		videoNodes.SetAttribute ("ChunkPolicy", EnumValue (CS_LATEST));

		ApplicationContainer appR = videoNodes.Install (routers.Get(n));
		appR.Start (Seconds (clientStart));
		appR.Stop (Seconds (clientStop));
	}

if(g_verbose){
	Config::ConnectWithoutContext("/NodeList/*/ApplicationList/0/$ns3::VideoPushApplication/Rx", MakeCallback (&AppRx));
	Config::ConnectWithoutContext("/NodeList/0/ApplicationList/0/$ns3::VideoPushApplication/Tx",MakeCallback (&AppTx));
	Config::ConnectWithoutContext("/NodeList/*/DeviceList/*/$ns3::WifiNetDevice/Phy/$ns3::YansWifiPhy/PhyTxDrop",MakeCallback (&PhyTxDrop));
	Config::Connect ("/NodeList/*/DeviceList/*/Mac/MacTx", MakeCallback (&DevTxTrace));
	Config::Connect ("/NodeList/*/DeviceList/*/Mac/MacRx",	MakeCallback (&DevRxTrace));
	Config::Connect ("/NodeList/*/DeviceList/*/Phy/State/RxOk",	MakeCallback (&PhyRxOkTrace));
	Config::Connect ("/NodeList/*/DeviceList/*/Phy/State/RxError",	MakeCallback (&PhyRxErrorTrace));
	Config::Connect ("/NodeList/*/DeviceList/*/Phy/State/Tx",	MakeCallback (&PhyTxTrace));
	Config::Connect ("/NodeList/*/DeviceList/*/Phy/State/State", MakeCallback (&PhyStateTrace));
}

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

	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	 	 	 	 	 	 Mobility Nodes
    * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

	MobilityHelper mobilityNodes;
	mobilityNodes.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
	mobilityNodes.SetPositionAllocator ("ns3::GridPositionAllocator",
	  "MinX", DoubleValue (0.0),
	  "MinY", DoubleValue (0.0),
	  "DeltaX", DoubleValue (deltaX),
	  "DeltaY", DoubleValue (deltaY),
	  "GridWidth", UintegerValue (cols),
	  "LayoutType", StringValue ("RowFirst"));

//  mobilityNodes.SetPositionAllocator ("ns3::RandomDiscPositionAllocator",
//								 "X", StringValue ("100.0"),
//								 "Y", StringValue ("100.0"),
//								 "Rho", StringValue ("Uniform:0:30"));

//  mobilityNodes.SetMobilityModel ("ns3::RandomWalk2dMobilityModel",
//                             "Mode", StringValue ("Time"),
//                             "Time", StringValue ("2s"),
//                             "Speed", StringValue ("Constant:1.0"),
//                             "Bounds", StringValue ("0|200|0|200"));
	mobilityNodes.Install(routers);

	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	 	 	 	 	 	 Mobility Source
    * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

	Ptr<ListPositionAllocator> positionAllocS = CreateObject<ListPositionAllocator> ();
	positionAllocS->Add(Vector(-70.0, -70.0, 0.0));// Source
	MobilityHelper mobilityS;
	mobilityS.SetPositionAllocator(positionAllocS);
	mobilityS.SetMobilityModel("ns3::ConstantPositionMobilityModel");
	mobilityS.Install(source);

	for(uint32_t i = 0; i < allNodes.GetN(); i++){
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
