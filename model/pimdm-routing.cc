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

/// \brief	This file implements the PIM-DM node state.
#define NS_LOG_APPEND_CONTEXT                                   \
  if (GetObject<Node> ()) { std::clog << "[node " << GetObject<Node> ()->GetId () << "] "; }

#include "pimdm-routing.h"
#include "ns3/socket-factory.h"
#include "ns3/udp-socket-factory.h"
#include "ns3/simulator.h"
#include "ns3/log.h"
#include "ns3/names.h"
#include "ns3/random-variable.h"
#include "ns3/inet-socket-address.h"
#include "ns3/ipv4-routing-protocol.h"
#include "ns3/ipv4-routing-table-entry.h"
#include "ns3/ipv4-route.h"
#include "ns3/boolean.h"
#include "ns3/uinteger.h"
#include "ns3/enum.h"
#include "limits.h"
#include "ns3/trace-source-accessor.h"
#include "ns3/ipv4-header.h"
#include "ns3/log.h"

namespace ns3{
namespace pimdm{
NS_LOG_COMPONENT_DEFINE ("PIMDMMulticastRouting");

NS_OBJECT_ENSURE_REGISTERED (MulticastRoutingProtocol);

MulticastRoutingProtocol::MulticastRoutingProtocol() :
		m_routingTableAssociation(0), m_ipv4 (0), m_lo(0)
	{}

MulticastRoutingProtocol::~MulticastRoutingProtocol()
	{}

TypeId
MulticastRoutingProtocol::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::pimdm::MulticastRoutingProtocol")
    .SetParent<Ipv4RoutingProtocol> ()
    .AddConstructor<MulticastRoutingProtocol> ()
    .AddAttribute ("HelloInterval", "HELLO messages interval.",
                   TimeValue (Seconds (Hello_Period)),
                   MakeTimeAccessor (&MulticastRoutingProtocol::m_helloTime),
                   MakeTimeChecker ())
//    .AddAttribute ("StateRefreshCapability", "State refresh capability.",
//					  BooleanValue (true),
//					  MakeBooleanAccessor(&MulticastRoutingProtocol::SetStateRefreshCapable),
//					  MakeBooleanChecker())
//    .AddAttribute ("LANDelayEnabled", "LAN delay enabled.",
//					  BooleanValue (true),
//					  MakeBooleanAccessor(&MulticastRoutingProtocol::SetLANDelayEnabled),
//					  MakeBooleanChecker())
	.AddAttribute ("HelloHoldTime", "HoldTime used in hello messages",
			 	 	UintegerValue (Hold_Time_Default),
			        MakeUintegerAccessor (&MulticastRoutingProtocol::SetHelloHoldTime),
			        MakeUintegerChecker<uint16_t> ())
//	.AddAttribute ("OverrideInterval", "Override interval",
//					 TimeValue (Seconds (1)),
//					 MakeTimeAccessor (&MulticastRoutingProtocol::m_overrideInterval),
//					 MakeTimeChecker ())
	.AddTraceSource ("Rx", "Receive PIM packet.",
					 MakeTraceSourceAccessor (&MulticastRoutingProtocol::m_rxPacketTrace))
	.AddTraceSource ("Tx", "Send PIM packet.",
					 MakeTraceSourceAccessor (&MulticastRoutingProtocol::m_txPacketTrace))
    .AddTraceSource ("RoutingTableChanged", "The PIM-DM routing table has changed.",
		     MakeTraceSourceAccessor (&MulticastRoutingProtocol::m_routingTableChanged))

    ;
  return tid;
}

/* TODO
 * The Generation ID is regenerated whenever PIM forwarding is started or restarted on the interface.

*/

Ptr<Ipv4Route> MulticastRoutingProtocol::RouteOutput (Ptr<Packet> p, const Ipv4Header &header,
									  Ptr<NetDevice> oif, Socket::SocketErrno &sockerr){
	return NULL;
}

bool MulticastRoutingProtocol::RouteInput  (Ptr<const Packet> p,
  const Ipv4Header &header, Ptr<const NetDevice> idev,
  UnicastForwardCallback ucb, MulticastForwardCallback mcb,
  LocalDeliverCallback lcb, ErrorCallback ecb)
{
	return false;
}

void
MulticastRoutingProtocol::NotifyInterfaceUp (uint32_t i)
{NS_LOG_FUNCTION(this);NS_LOG_DEBUG("Interface Up: "<<i);}
void
MulticastRoutingProtocol::NotifyInterfaceDown (uint32_t i)
{NS_LOG_FUNCTION(this);NS_LOG_DEBUG("Interface Down "<<i);
//TODO When a PIM router takes an interface down or changes IP address, a Hello message with a zero Hold Time SHOULD be
//sent immediately (with the old IP address if the IP address is changed) to cause any PIM neighbors to remove the old information immediately.
}
void
MulticastRoutingProtocol::NotifyAddAddress (uint32_t interface, Ipv4InterfaceAddress address){
	NS_LOG_FUNCTION(this);
	NS_LOG_DEBUG("+ Address("<<interface<<") = "<< address);
	Ipv4Address loopback ("127.0.0.1");
	Ipv4Address addr = m_ipv4->GetAddress (interface, 0).GetLocal ();
	if (addr != loopback){
		InsertNeighborhoodStatus(interface);
		m_IfacePimEnabled.insert(std::pair<uint32_t, bool>(interface, true));
		NeighborhoodStatus *ns = FindNeighborhoodStatus(interface);
		ns->propagationDelay = Seconds(UniformVariable().GetValue(Propagation_Delay*.3,Propagation_Delay));
		ns->overrideInterval = Seconds(UniformVariable().GetValue(Override_Interval*.3,Override_Interval));
		ns->stateRefreshInterval = Seconds(UniformVariable().GetValue(RefreshInterval*.3,RefreshInterval));
		ns->pruneHoldtime = Seconds(UniformVariable().GetValue(PruneHoldTime*.3,PruneHoldTime));
		ns->LANDelayEnabled = true;
		ns->stateRefreshCapable = true;
	}
	//TODO When a PIM router takes an interface down or changes IP address, a Hello message with a zero Hold Time SHOULD be
	//sent immediately (with the old IP address if the IP address is changed) to cause any PIM neighbors to remove the old information immediately.
}
void
MulticastRoutingProtocol::NotifyRemoveAddress (uint32_t interface, Ipv4InterfaceAddress address)
{NS_LOG_FUNCTION(this);NS_LOG_DEBUG("- Address("<<interface<<") = "<< address);}

void
MulticastRoutingProtocol::SetIpv4 (Ptr<Ipv4> ipv4)
{
  NS_ASSERT (ipv4 != 0);
  NS_ASSERT (m_ipv4 == 0);
  NS_LOG_DEBUG ("Created MulticastRoutingProtocol");
  Ipv4Address loopback ("127.0.0.1");
  m_ipv4 = ipv4;
}

Ipv4Address
MulticastRoutingProtocol::GetLocalAddress (uint32_t interface)
{
//  NS_LOG_DEBUG ("Get Local Address "<<interface);
  if(interface<m_ipv4->GetNInterfaces ()){
  	return  m_ipv4->GetAddress (interface, 0).GetLocal ();
  }else{
	Ipv4Address loopback ("127.0.0.1");
	return loopback;
  }
}

void MulticastRoutingProtocol::DoDispose ()
	{
	m_ipv4 = 0;
	m_routingTableAssociation = 0;

	for (std::map< Ptr<Socket>, Ipv4InterfaceAddress >::iterator iter = m_socketAddresses.begin ();
	   iter != m_socketAddresses.end (); iter++)
	{
	  iter->first->Close ();
	}
	m_socketAddresses.clear ();

	Ipv4RoutingProtocol::DoDispose ();
	}

void
MulticastRoutingProtocol::PrintRoutingTable (Ptr<OutputStreamWrapper> stream) const
{
  std::ostream* os = stream->GetStream ();
  *os << "Source\t\tNextHop\t\tPreference\tMetric\n";

  for (std::map<Ipv4Address, RoutingMulticastTable>::const_iterator iter = m_mrib.begin ();
    iter != m_mrib.end (); iter++)
    {
      *os << iter->first << "\t\t";
      *os << iter->second.nextAddr << "\t\t";
//      if (Names::FindName (m_ipv4->GetNetDevice (iter->second.nextAddr)) != "")
//            {
//              *os << Names::FindName (m_ipv4->GetNetDevice (iter->second.nextAddr)) << "\t\t";
//            }
//          else
//            {
//              *os << iter->second.nextAddr<< "\t\t";
//            }
      *os << iter->second.metricPreference << "\t";
      *os << iter->second.route_metric << "\t";
      *os << "\n";
    }
}

void MulticastRoutingProtocol::DoStart (){
	if (m_mainAddress == Ipv4Address ())
	    {
	      Ipv4Address loopback ("127.0.0.1");
	      for (uint32_t i = 0; i < m_ipv4->GetNInterfaces (); i++)
	        {
	          // Use primary address, if multiple
	          Ipv4Address addr = m_ipv4->GetAddress (i, 0).GetLocal ();
	          if (addr != loopback)
	            {
	              m_mainAddress = addr;
	              SetMainInterface(i);
//	              If a Hello message is received from an active neighbor with a
//	                different Generation ID (GenID), the neighbor has restarted and may
//	                not contain the correct (S,G) state.
	              m_generationID = UniformVariable().GetInteger(1,INT_MAX);///force value > 0
	              NS_LOG_DEBUG("Address("<<i<< ") = "<<addr<< ", Generation Id = "<< m_generationID);
	              break;
	            }
	        }

	      NS_ASSERT (m_mainAddress != Ipv4Address ());
	    }
	  m_startTime = Simulator::Now();
	  Ipv4Address loopback ("127.0.0.1");

	  for (uint32_t i = 0; i < m_ipv4->GetNInterfaces (); i++)
	    {
	      Ipv4Address addr = m_ipv4->GetAddress (i, 0).GetLocal ();
	      if (addr == loopback)
	        continue;
	      Timer *helloTimer = &m_IfaceNeighbors.find(i)->second.hello_timer;
	      Time rndHello = Seconds(UniformVariable().GetValue(0,Triggered_Hello_Delay));
	      Simulator::Schedule (rndHello, &MulticastRoutingProtocol::HelloTimerExpire, this, i);
	      helloTimer->SetDelay(m_helloTime);
	      helloTimer->SetFunction(&MulticastRoutingProtocol::HelloTimerExpire,this);
	      helloTimer->SetArguments(i);

		  NS_LOG_DEBUG ("Starting PIM_DM on Interface = "<<i<<", Address ("<<i<<") = "<<addr<<", Hello "<< rndHello.GetSeconds());

	      // Create a socket to listen only on this interface
	      Ptr<Socket> socket = Socket::CreateSocket (GetObject<Node> (),
	                                                 UdpSocketFactory::GetTypeId());
	      socket->SetAllowBroadcast (true);
	      InetSocketAddress inetAddr (m_ipv4->GetAddress (i, 0).GetLocal (), PIM_PORT_NUMBER);
	      socket->SetRecvCallback (MakeCallback (&MulticastRoutingProtocol::RecvPimDm,  this));
	      if (socket->Bind (inetAddr))
	        {
	          NS_FATAL_ERROR ("Failed to bind() PIMDM socket");
	        }
	      socket->BindToNetDevice (m_ipv4->GetNetDevice (i));
	      m_socketAddresses[socket] = m_ipv4->GetAddress (i, 0);

	    }
//	  if(canRunOlsr)
//	   {
	  /*
	   * The Hello Timer (HT) MUST be set to random value between 0 and Triggered_Hello_Delay
	   * When PIM is enabled on an interface or when a router first starts.
	   */
	      NS_LOG_DEBUG ("PIMDM on node " << m_mainAddress << " started");
//	   }
}

void
MulticastRoutingProtocol::HelloTimerExpire (uint32_t i){
	Ipv4Address loopback ("127.0.0.1");
//	for (uint32_t i = 0; i < m_ipv4->GetNInterfaces (); i++){
	  Ipv4Address addr = m_ipv4->GetAddress (i, 0).GetLocal ();
	  if (addr == loopback)
		  return;
	  NS_LOG_DEBUG("Interface "<< i<< " [ E "<<m_IfaceNeighbors.find(i)->second.hello_timer.IsExpired() <<
			  ", R " << m_IfaceNeighbors.find(i)->second.hello_timer.IsRunning()<<", S:" << m_IfaceNeighbors.find(i)->second.hello_timer.IsSuspended()<<"].");
	  if(!m_IfaceNeighbors.find(i)->second.hello_timer.IsRunning()){
		  m_IfaceNeighbors.find(i)->second.hello_timer.Schedule();
		  m_IfaceNeighbors.find(i)->second.hello_timer.SetArguments(i);
	  }
	  SendHello (i);
//	}
}

//	 PIM-DM uses Hello messages to detect other PIM routers.  Hello
//	   messages are sent periodically on each PIM enabled interface.  Hello
//	   messages are multicast to the ALL-PIM-ROUTERS group.  When PIM is
//	   enabled on an interface or when a router first starts, the Hello
//	   Timer (HT) MUST be set to random value between 0 and
//	   Triggered_Hello_Delay.  This prevents synchronization of Hello
//	   messages if multiple routers are powered on simultaneously.
//
//	   After the initial Hello message, a Hello message MUST be sent every
//	   Hello_Period.  A single Hello timer MAY be used to trigger sending
//	   Hello messages on all active interfaces.  The Hello Timer SHOULD NOT
//	   be reset except when it expires.




bool
MulticastRoutingProtocol::IsDownstream (uint32_t interface, SourceGroupPair sgpair){
	return (interface != RPF_interface(sgpair.sourceIfaceAddr));
}
bool
MulticastRoutingProtocol::IsUpstream (uint32_t interface, SourceGroupPair sgpair){
	return (interface == RPF_interface(sgpair.sourceIfaceAddr));
}


void
MulticastRoutingProtocol::ForgeHeaderMessage (enum PIMType type, PIMHeader &msg){
	NS_LOG_FUNCTION(this);
	msg.SetVersion(2);
	msg.SetType(type);
	msg.SetReserved(0);
}

void
MulticastRoutingProtocol::ForgePruneMessage (PIMHeader &msg){
	NS_LOG_FUNCTION(this);
	ForgeHeaderMessage(PIM_JP, msg);
	PIMHeader::JoinPruneMessage jpMessage = msg.GetJoinPruneMessage();
	jpMessage.m_joinPruneMessage.m_upstreamNeighborAddr = ForgeEncodedUnicast(Ipv4Address("0.0.0.0"));
	jpMessage.m_joinPruneMessage.m_reserved = 0;
	jpMessage.m_joinPruneMessage.m_numGroups = 0;
	jpMessage.m_joinPruneMessage.m_holdTime = Time(Hold_Time_Default);
}

void
MulticastRoutingProtocol::ForgeAssertMessage (uint32_t interface, PIMHeader &msg, SourceGroupPair &sgp){
	NS_LOG_FUNCTION(this);
	ForgeHeaderMessage(PIM_JP, msg);
	PIMHeader::AssertMessage assertMessage = msg.GetAssertMessage();
	assertMessage.m_sourceAddr =  ForgeEncodedUnicast(sgp.sourceIfaceAddr);
	assertMessage.m_multicastGroupAddr = ForgeEncodedGroup(sgp.groupMulticastAddr);
	assertMessage.m_R = 0;
	assertMessage.m_metricPreference = m_mrib.find(sgp.sourceIfaceAddr)->second.metricPreference;
	assertMessage.m_metric = m_mrib.find(sgp.sourceIfaceAddr)->second.route_metric;
}

void
MulticastRoutingProtocol::ForgeAssertCancelMessage (uint32_t interface, PIMHeader &msg, SourceGroupPair &sgp){
	//An AssertCancel(S,G) message is simply an Assert message for (S,G)
	//with infinite metric.  The Assert winner sends this message when it
	//changes its upstream interface to this interface.  Other routers will
	//see this metric, causing those with forwarding state to send their
	//own Asserts and re-establish an Assert winner.
	//
	//AssertCancel messages are simply an optimization.  The original
	//Assert timeout mechanism will eventually allow a subnet to become
	//consistent; the AssertCancel mechanism simply causes faster
	//convergence.  No special processing is required for an AssertCancel
	//message, as it is simply an Assert message from the current winner
	NS_LOG_FUNCTION(this);
	ForgeHeaderMessage(PIM_JP, msg);
	PIMHeader::AssertMessage assertMessage = msg.GetAssertMessage();
	assertMessage.m_sourceAddr =  ForgeEncodedUnicast(sgp.sourceIfaceAddr);
	assertMessage.m_multicastGroupAddr = ForgeEncodedGroup(sgp.groupMulticastAddr);
	assertMessage.m_R = 0;
	assertMessage.m_metricPreference = 0xffffffff;
	assertMessage.m_metric = 0xffffffff;
}

void
MulticastRoutingProtocol::ForgeStateRefresh (uint32_t interface, SourceGroupPair &sgp, PIMHeader &msg){
	NS_LOG_FUNCTION(this);
	SourceGroupState *sgState = FindSourceGroupState(interface,sgp);
	ForgeHeaderMessage(PIM_STATE_REF, msg);
	PIMHeader::StateRefreshMessage refresh = msg.GetStateRefreshMessage();
	refresh.m_multicastGroupAddr = ForgeEncodedGroup(sgp.groupMulticastAddr);//TODO check whether params are correct or not.
	refresh.m_sourceAddr = ForgeEncodedUnicast(sgp.sourceIfaceAddr);
	Ipv4Address nextHop = m_mrib.find(sgp.sourceIfaceAddr)->second.nextAddr;
	refresh.m_originatorAddr = ForgeEncodedUnicast(Ipv4Address(GetLocalAddress(interface)));
	refresh.m_R = 0;
	refresh.m_metricPreference = m_mrib.find(sgp.sourceIfaceAddr)->second.metricPreference;
	refresh.m_metric = m_mrib.find(sgp.sourceIfaceAddr)->second.route_metric;
	refresh.m_maskLength = IPV4_ADDRESS_SIZE;
	refresh.m_ttl = (sgState->SG_DATA_TTL>0 ? sgState->SG_DATA_TTL : sgState->SG_SR_TTL);
	refresh.m_P = (sgState->PruneState==Prune_Pruned?1:0);
	refresh.m_N = 0;
	refresh.m_O = (!sgState->SG_AT.IsRunning() && (IsUpstream(m_mrib.find(sgp.sourceIfaceAddr)->second.interface,sgp))?1:0);
	refresh.m_reserved = 0;
	refresh.m_interval = RefreshInterval;
}

void
MulticastRoutingProtocol::ForgeHelloMessageHoldTime (uint32_t interface, PIMHeader &msg){
	PIMHeader::HelloMessage helloMessage = msg.GetHelloMessage();//TODO holdtime for the corresponding interface
	PIMHeader::HelloMessage::HelloEntry holdtime = {PIMHeader::HelloMessage::HelloHoldTime, PIM_DM_HELLO_HOLDTIME};
	holdtime.m_optionValue.holdTime.m_holdTime = Seconds(m_helloHoldTime);
	msg.GetHelloMessage().m_optionList.push_back(holdtime);
}

void
MulticastRoutingProtocol::ForgeHelloMessageLANPD (uint32_t interface, PIMHeader &msg){
	PIMHeader::HelloMessage::HelloEntry lanpd = {PIMHeader::HelloMessage::LANPruneDelay, PIM_DM_HELLO_LANPRUNDELAY};
	lanpd.m_optionValue.lanPruneDelay.m_T = 0;
	lanpd.m_optionValue.lanPruneDelay.m_propagationDelay = m_IfaceNeighbors.find(interface)->second.propagationDelay;
	lanpd.m_optionValue.lanPruneDelay.m_overrideInterval = m_IfaceNeighbors.find(interface)->second.overrideInterval;
	msg.GetHelloMessage().m_optionList.push_back(lanpd);
}

void
MulticastRoutingProtocol::ForgeHelloMessageGenID (uint32_t interface, PIMHeader &msg){
	PIMHeader::HelloMessage::HelloEntry genid = {PIMHeader::HelloMessage::GenerationID, PIM_DM_HELLO_GENERATIONID};
	genid.m_optionValue.generationID.m_generatioID = m_generationID;
	msg.GetHelloMessage().m_optionList.push_back(genid);
}

void
MulticastRoutingProtocol::ForgeHelloMessageStateRefresh (uint32_t interface, PIMHeader &msg){
	PIMHeader::HelloMessage::HelloEntry staterefresh = {PIMHeader::HelloMessage::StateRefreshCapable, PIM_DM_HELLO_STATEREFRESH};
	staterefresh.m_optionValue.stateRefreshCapable.m_version = 1;
	staterefresh.m_optionValue.stateRefreshCapable.m_reserved = 0;
	staterefresh.m_optionValue.stateRefreshCapable.m_interval = (uint8_t)(m_IfaceNeighbors.find(interface)->second.stateRefreshInterval).GetSeconds();
	msg.GetHelloMessage().m_optionList.push_back(staterefresh);
}

void
MulticastRoutingProtocol::ForgeHelloMessage (uint32_t interface, PIMHeader &msg){
	NS_LOG_FUNCTION(this);
	ForgeHeaderMessage(PIM_HELLO, msg);
	ForgeHelloMessageHoldTime(interface,msg);
	ForgeHelloMessageLANPD(interface,msg);
	ForgeHelloMessageGenID(interface,msg);
	if(m_IfaceNeighbors.find(interface)->second.stateRefreshCapable){
		ForgeHelloMessageStateRefresh(interface,msg);
	}
}

void
MulticastRoutingProtocol::CreateMulticastGroupEntry (PIMHeader &msg, PIMHeader::MulticastGroupEntry m_entry,  PIMHeader::EncodedGroup group){
	NS_LOG_FUNCTION(this);
	m_entry.m_multicastGroupAddr = group;
	m_entry.m_numberJoinedSources = 0;
	m_entry.m_numberPrunedSources = 0;
}

void
MulticastRoutingProtocol::AddMulticastGroupEntry (PIMHeader &msg, PIMHeader::MulticastGroupEntry &entry){
	NS_LOG_FUNCTION(this);
	PIMHeader::JoinPruneMessage jpMessage = msg.GetJoinPruneMessage();
	jpMessage.m_joinPruneMessage.m_numGroups = 1 + jpMessage.m_joinPruneMessage.m_numGroups;
	jpMessage.m_multicastGroups.push_back(entry);
}

void
MulticastRoutingProtocol::AddMulticastGroupSourceJoin (PIMHeader::MulticastGroupEntry m_entry, PIMHeader::EncodedSource source){
	NS_LOG_FUNCTION(this);
	m_entry.m_numberJoinedSources = 1 + m_entry.m_numberJoinedSources;
	m_entry.m_joinedSourceAddrs.push_back(source);
}

void
MulticastRoutingProtocol::AddMulticastGroupSourcePrune (PIMHeader::MulticastGroupEntry m_entry, PIMHeader::EncodedSource source){
	NS_LOG_FUNCTION(this);
	m_entry.m_numberPrunedSources = 1 + m_entry.m_numberPrunedSources;
	m_entry.m_prunedSourceAddrs.push_back(source);
}

void
MulticastRoutingProtocol::RecvPimDm (Ptr<Socket> socket){
	NS_LOG_FUNCTION(this);
	Ptr<Packet> receivedPacket;
	Address sourceAddress;
	receivedPacket = socket->RecvFrom (sourceAddress);
	InetSocketAddress inetSourceAddr = InetSocketAddress::ConvertFrom (sourceAddress);
	Ipv4Address senderIfaceAddr = inetSourceAddr.GetIpv4 ();
	Ipv4Address receiverIfaceAddr = m_socketAddresses[socket].GetLocal ();
	NS_ASSERT (receiverIfaceAddr != Ipv4Address ());
    Ptr<Ipv4Route> route = 0;
    Ipv4Header hdr;
    hdr.SetDestination(senderIfaceAddr);
    Ptr<NetDevice> oif (0);
    Socket::SocketErrno err = Socket::ERROR_NOTERROR;

	route = m_ipv4->GetRoutingProtocol()->RouteOutput(receivedPacket,hdr, oif,err);

	NS_LOG_DEBUG ("Sender "<< senderIfaceAddr<<", Destination "<< receiverIfaceAddr);
	if(route)
	NS_LOG_DEBUG (" (SRC: "<< route->GetSource()<< ", GW: "<<route->GetGateway()
			<<",DevID: "<< route->GetOutputDevice()->GetIfIndex()<<")");
	NS_ASSERT (inetSourceAddr.GetPort () == PIM_PORT_NUMBER);
	//Within PIM-DM, route and state information associated with an (S,G) entry MUST be maintained as long as any
	//	timer associated with that (S,G) entry is active.  When no timer associated with an (S,G) entry is active,
	//	all information concerning that (S,G) route may be discarded.
	Ptr<Packet> packet = receivedPacket;
	PIMHeader pimdmPacket;
	packet->RemoveHeader(pimdmPacket);
	if(pimdmPacket.GetType()!=PIM_HELLO && !IsValidSG(GetReceivingInterface(receiverIfaceAddr), senderIfaceAddr, receiverIfaceAddr)){
			NS_LOG_DEBUG ("PIM-DM No running timer: discarded");
			return;
	}
	switch (pimdmPacket.GetType()){
	case PIM_HELLO:{
		m_rxPacketTrace (pimdmPacket);
		RecvHello(pimdmPacket.GetHelloMessage(),senderIfaceAddr,receiverIfaceAddr);
		break;
		}
	case PIM_JP:{
		RecvJP(pimdmPacket.GetJoinPruneMessage(),senderIfaceAddr,receiverIfaceAddr);
		break;
		}
	case PIM_ASSERT:{
		RecvAssert(pimdmPacket.GetAssertMessage(),senderIfaceAddr,receiverIfaceAddr);
		break;
		}
	case PIM_GRAFT:{
		RecvGraft(pimdmPacket.GetGraftMessage(),senderIfaceAddr,receiverIfaceAddr);
		break;
		}
	case PIM_GRAFT_ACK:{
		RecvGraftAck(pimdmPacket.GetGraftAckMessage(),senderIfaceAddr,receiverIfaceAddr);
		break;
		}
	case PIM_STATE_REF:{
		RecvStateRefresh(pimdmPacket.GetStateRefreshMessage(),senderIfaceAddr,receiverIfaceAddr);
		break;
		}
	default:{
		RecvData (receivedPacket,senderIfaceAddr,receiverIfaceAddr);
		break;
		}
	}
}


void
MulticastRoutingProtocol::RecvData (Ptr<Packet> packet, Ipv4Address sender, Ipv4Address receiver){
	NS_LOG_FUNCTION(this);
	uint32_t interface = GetReceivingInterface(receiver);
	// Data Packet arrives on RPF_Interface(S) AND olist(S,G) == NULL AND S NOT directly connected
	SourceGroupPair sgp(sender, receiver);
	SourceGroupState *sgState = FindSourceGroupState(interface,sgp);
	if(!sgState){
		SourceGroupState sgs(sgp);
		InsertSourceGroupState(interface,sgs);
		sgState = FindSourceGroupState(interface,sgp);
	}

	if(sgState->upstream->SG_SAT.IsRunning()){
		sgState->upstream->SG_SAT.Cancel();
		sgState->upstream->SG_SAT.Schedule();
	}
	if(RPF_interface(sender) == interface){
		switch (sgState->upstream->GraftPrune){
			//The Upstream(S,G) state machine MUST transition to the Pruned (P)
			// state, send a Prune(S,G) to RPF'(S), and set PLT(S,G) to t_limit seconds.
			case GP_Forwarding:{
				if(olist(sender,receiver).size() == 0 && m_mrib.find(sender)->second.nextAddr != sender){
					sgState->upstream->GraftPrune = GP_Pruned;
					Ipv4Address destination = RPF_prime(sgp);
					SendPruneUnicast(destination, sgp);
					sgState->upstream->SG_PLT.SetDelay(Seconds(t_limit));
					}
					break;
				}
			case GP_Pruned:{
				if(!sgState->upstream->SG_PLT.IsRunning() && m_mrib.find(sender)->second.nextAddr != sender){
					sgState->upstream->SG_PLT.SetDelay(Seconds(t_limit));
					sgState->upstream->SG_PLT.Schedule();
					sgState->upstream->SG_PLT.SetFunction(&MulticastRoutingProtocol::PLTTimerExpire, this);//re-schedule transmission
					sgState->upstream->SG_PLT.SetArguments(sgp);
					SendPruneBroadcast(GetReceivingInterface(RPF_prime(sgp.sourceIfaceAddr)), sgp);
					}
					break;
				}
			case GP_AckPending:{
				//nothing
				break;
			}
			default:{
				NS_LOG_ERROR("RecvData: Graft Prune state not valid"<<sgState->upstream->GraftPrune);
			}
		}
	}
	else{
		switch (sgState->AssertState){
			case  Assert_NoInfo:{
			//An (S,G) data packet arrives on downstream interface I.
			//   An (S,G) data packet arrived on a downstream interface.  It is
			//   optimistically assumed that this router will be the Assert winner
			//   for this (S,G).  The Assert state machine MUST transition to the
			//   "I am Assert Winner" state, send an Assert(S,G) to interface I,
			//   store its own address and metric as the Assert Winner, and set
			//   the Assert_Timer (AT(S,G,I) to Assert_Time, thereby initiating
			//   the Assert negotiation for (S,G).
				if(!IsDownstream(interface,sgp)) break;
				sgState->AssertState = Assert_Winner;
				PIMHeader assert;
				ForgeAssertMessage(interface, assert, sgp);
				UpdateAssertWinner(sgState, sender);
//				sgState->AssertWinner.metric_preference = m_mrib.find(sender)->second.metricPreference;
//				sgState->AssertWinner.route_metric = m_mrib.find(sender)->second.route_metric;
//				sgState->AssertWinner.ip_address = GetLocalAddress(interface);
				Ptr<Packet> packetA = Create<Packet> ();
				SendBroadPacketInterface(packetA,assert,interface);
				if(sgState->SG_AT.IsRunning())
					sgState->SG_AT.Cancel();
				sgState->SG_AT.SetDelay(Seconds(Assert_Time));
				sgState->SG_AT.Schedule();
				break;
				}
			case Assert_Winner:{
				//An (S,G) data packet arrives on downstream interface I.
				//	An (S,G) data packet arrived on a downstream interface.
				//	The Assert state machine remains in the "I am Assert Winner" state.
				//	The router MUST send an Assert(S,G) to interface I and set the Assert Timer (AT(S,G,I) to Assert_Time.
				if(!IsDownstream(interface,sgp))break;
				PIMHeader assert;
				ForgeAssertMessage(interface,assert,sgp);
				sgState->AssertWinner.metric_preference = m_mrib.find(sender)->second.metricPreference;
				sgState->AssertWinner.route_metric = m_mrib.find(sender)->second.route_metric;
				sgState->AssertWinner.ip_address = GetLocalAddress(interface);
				Ptr<Packet> packetA = Create<Packet> ();
				SendBroadPacketInterface(packetA,assert,interface);
				//The Assert winner for (S,G) must act as the local forwarder for
				//  (S,G) on behalf of all downstream members.
				if(sgState->SG_AT.IsRunning())
					sgState->SG_AT.Cancel();
				sgState->SG_AT.SetDelay(Seconds(Assert_Time));
				sgState->SG_AT.Schedule();
				break;
			}
			case Assert_Loser:{
				//nothing
				break;
			}
			default:{
				NS_LOG_ERROR("RecvData: Assert State not valid"<<sgState->AssertState);
			}
		}
	}
	if(sgState->upstream || sender == m_mrib.find(sender)->second.nextAddr){
		if(!sgState->upstream){
			UpstreamState upstream;
			sgState->upstream = &upstream;
		}
	switch (sgState->upstream->origination) {
		case NotOriginator:{
			//Data Packet received from directly connected Source S addressed to group G.
			//	The router MUST transition to an Originator (O) state, set SAT(S,G) to SourceLifetime,
			//	and set SRT(S,G) to StateRefreshInterval.
			//	The router SHOULD record the TTL of the packet for use in State Refresh messages.
			if(m_mrib.find(sender)->second.nextAddr == sender){
				sgState->upstream->origination = Originator;
				if(sgState->upstream->SG_SAT.IsRunning())
					sgState->upstream->SG_SAT.Cancel();
				sgState->upstream->SG_SAT.SetDelay(Seconds(SourceLifetime));
				sgState->upstream->SG_SAT.Schedule();
				if(sgState->upstream->SG_SRT.IsRunning())
					sgState->upstream->SG_SRT.Cancel();
				sgState->upstream->SG_SRT.SetDelay(Seconds(RefreshInterval));
				sgState->upstream->SG_SRT.Schedule();
				Ipv4Header ipv4h;
				packet->RemoveHeader(ipv4h);
				sgState->SG_DATA_TTL = ipv4h.GetTtl();
			}
			break;
		}
		case Originator:{
		//Receive Data Packet from S addressed to G.
		//	The router remains in the Originator (O) state and MUST reset
		//	SAT(S,G) to SourceLifetime.  The router SHOULD increase its
		//	recorded TTL to match the TTL of the packet, if the packet's TTL
		//	is larger than the previously recorded TTL.  A router MAY record
		//	the TTL based on an implementation specific sampling policy to
		//	avoid examining the TTL of every multicast packet it handles.
			if(sgState->upstream->SG_SRT.IsRunning())
				sgState->upstream->SG_SAT.Cancel();
			sgState->upstream->SG_SAT.SetDelay(Seconds(SourceLifetime));
			sgState->upstream->SG_SAT.Schedule();
			Ipv4Header ipv4h;
			packet->RemoveHeader(ipv4h);
			double sample = UniformVariable().GetValue();
			if(sample < TTL_SAMPLE && ipv4h.GetTtl() > sgState->SG_DATA_TTL){//TODO: increase means +1 or equal to packet's TTL?
				sgState->SG_DATA_TTL = ipv4h.GetTtl();
			}
			break;
		}
		default:{
			NS_LOG_ERROR("RecvStateRefresh: Origination state not valid"<<sgState->upstream->origination);
			break;
		}
	}
	}
	//	   Section 4.2. Data Packet Forwarding Rules.
	//	   Upon receipt of a data packet from S addressed to G on interface iif:
	//
	//	   if (iif == RPF_interface(S) AND UpstreamPState(S,G) != Pruned) {
	//	       oiflist = olist(S,G)
	//	   } else {
	//	       oiflist = NULL
	//	   }
	//	   forward packet on all interfaces in oiflist
	//
	//	   This pseudocode employs the following "macro" definition:
	//
	//	   UpstreamPState(S,G) is the state of the Upstream(S,G) state machine in Section 4.4.1.
	std::set<uint32_t> oiflist;
	///   First, an RPF check MUST be performed to determine whether the packet should be accepted based on TIB state
	///      and the interface on which that the packet arrived.
	///   Packets that fail the RPF check MUST NOT be forwarded, and the router will conduct an assert process for the (S,G) pair specified in the packet.
	///   Packets for which a route to the source cannot be found MUST be discarded.

	if(RPF_interface(sender)<0){///   Packets for which a route to the source cannot be found MUST be discarded.
		return;
	}
	if(interface == RPF_interface(sender)){
		if(sgState->PruneState!=Prune_Pruned ){
			/// If the RPF check has been passed, an outgoing interface list is constructed for the packet.
			/// If this list is not empty, then the packet MUST be forwarded to all listed interfaces.
			oiflist = olist(sender,receiver);
			//TODO CHECK
			oiflist.erase(interface);
		}
	}
	else{
		///   Packets that fail the RPF check MUST NOT be forwarded, and the router will conduct an assert process for the (S,G) pair specified in the packet.
		PIMHeader assert;
		ForgeAssertMessage(interface,assert,sgp);
		Ptr<Packet> packetAssert = Create<Packet> ();
		SendBroadPacketInterface(packetAssert,assert,interface);
	}
	if(oiflist.size()){
		// Forward packet on all interfaces in oiflist
		for(std::set<uint32_t>::iterator out = oiflist.begin(); out!=oiflist.end(); out++){
			SendBroadPacketInterface(packet,*out);
		}
	}
	else {
		//  If the list is empty, then the router will conduct a prune process for the (S,G) pair specified in the packet.
		SendPruneBroadcast(interface,sgp);
	}
}

void
MulticastRoutingProtocol::SendStateRefresh (uint32_t interface, PIMHeader &refresh){
	NS_LOG_FUNCTION(this);
	Ptr<Packet> packet = Create<Packet> ();
	SendBroadPacket(packet,refresh);
}

//TODO
void
MulticastRoutingProtocol::SendPruneBroadcast (uint32_t interface, SourceGroupPair &sgp){
	NS_LOG_FUNCTION(this);
	PIMHeader::MulticastGroupEntry mge;
	AddMulticastGroupSourcePrune(mge,ForgeEncodedSource(sgp.sourceIfaceAddr));
	PIMHeader msg;
	Ipv4Address target = RPF_prime(sgp.sourceIfaceAddr,sgp.groupMulticastAddr); //TODO is broadcast or not?
	ForgePruneMessage(msg);
	CreateMulticastGroupEntry(msg,mge,ForgeEncodedGroup(sgp.groupMulticastAddr));
	msg.GetJoinPruneMessage().m_joinPruneMessage.m_upstreamNeighborAddr.m_unicastAddress =target;
	Ptr<Packet> packet = Create<Packet> ();
	NS_LOG_DEBUG("Sending Prune for source \""<<sgp.sourceIfaceAddr <<"\" and group \""<< sgp.groupMulticastAddr<<"\" to UpstreamNeighbor \""<< target<<"\"");
	SendPacket(packet,msg,target);
}



void
MulticastRoutingProtocol::SendStateRefreshPair (uint32_t interface, Ipv4Address target, SourceGroupPair &sgp)
{
	NS_LOG_FUNCTION(this);
	SourceGroupState *sgState = FindSourceGroupState(interface,sgp);
	Ptr<Packet> packet = Create<Packet> ();
	PIMHeader msg;
	ForgeHeaderMessage(PIM_STATE_REF, msg);
	PIMHeader::StateRefreshMessage refresh = msg.GetStateRefreshMessage();
	refresh.m_multicastGroupAddr = ForgeEncodedGroup(sgp.groupMulticastAddr);//TODO check whether params are correct or not.
	refresh.m_sourceAddr = ForgeEncodedUnicast(sgp.sourceIfaceAddr);
	Ipv4Address nextHop = m_mrib.find(sgp.sourceIfaceAddr)->second.nextAddr;
	refresh.m_originatorAddr = ForgeEncodedUnicast(nextHop);
	refresh.m_R = 0;
	refresh.m_metricPreference = m_mrib.find(sgp.sourceIfaceAddr)->second.metricPreference;
	refresh.m_metric = m_mrib.find(sgp.sourceIfaceAddr)->second.route_metric;
	refresh.m_maskLength = IPV4_ADDRESS_SIZE;
	refresh.m_ttl = 7; // TODO ??
	refresh.m_P = (sgState->PruneState==Prune_Pruned?1:0);
	refresh.m_N = 0;
	refresh.m_O = (!sgState->SG_AT.IsRunning() && (IsUpstream(m_mrib.find(sgp.sourceIfaceAddr)->second.interface,sgp))?1:0);
	refresh.m_reserved = 0;
	refresh.m_interval = RefreshInterval;

	SendPacket(packet,msg,target);
	switch (sgState->PruneState) {
		case Prune_NoInfo:{
			// nothing
			break;
		}
		case Prune_PrunePending:{
			// nothing
			break;
		}
		case Prune_Pruned:{
		//Send State Refresh(S,G) out interface I. The router has refreshed the Prune(S,G) state on interface I.
		//	The router MUST reset the Prune Timer (PT(S,G,I)) to the Holdtime from an active Prune received on interface I.
		//	The Holdtime used SHOULD be the largest active one but MAY be the most recently received active Prune Holdtime.
			if(sgState->SG_PT.IsRunning())
				sgState->SG_PT.Cancel();
			sgState->SG_PT.SetDelay(FindNeighborhoodStatus(interface)->pruneHoldtime);
			sgState->SG_PT.Schedule();
			break;
		}
		default:
			NS_LOG_ERROR("SendStateRefreshPair : Prune state not valid"<<sgState->PruneState);
			break;
	}
		switch (sgState->AssertState){
			case  Assert_NoInfo:{
				break;
				}
			case Assert_Winner:{
				//Send State Refresh
				//	The router is sending a State Refresh(S,G) message on interface I.
				//	The router MUST set the Assert Timer (AT(S,G,I)) to three
				//	times the State Refresh Interval contained in the State Refresh(S,G) message.
					sgState->SG_AT.Cancel();
					sgState->SG_AT.SetDelay(Seconds(3*refresh.m_interval));
					sgState->SG_AT.Schedule();
					break;
				}
			case Assert_Loser:{
				//nothing
				break;
			}
			default:{
				NS_LOG_ERROR("RecvData: Assert State not valid"<<sgState->AssertState);
			}
		}
}

void
MulticastRoutingProtocol::SendHello (uint32_t interface){///< Sec. 4.3.1.
	NS_LOG_FUNCTION(this);
	Ptr<Packet> packet = Create<Packet> ();
	PIMHeader msg;
	ForgeHelloMessage(interface, msg);
	SendBroadPacketInterface(packet,msg,interface);//TODO broadcast packet on a specific interface
}

void
MulticastRoutingProtocol::SendNeighHello (uint32_t interface, Ipv4Address destination)
{///< Sec. 4.3.1.
	NS_LOG_FUNCTION(this);
	Ptr<Packet> packet = Create<Packet> ();
	PIMHeader msg;
	ForgeHelloMessage(interface, msg);
	NS_LOG_DEBUG("Send Hello to "<< destination);
	SendPacket(packet,msg,destination);
}

void
MulticastRoutingProtocol::SendGraft (uint32_t interface, SourceGroupPair pair){
	NS_LOG_FUNCTION(this);//TODO To complete
	Ptr<Packet> packet = Create<Packet> ();
	PIMHeader msg;
	ForgeHeaderMessage(PIM_GRAFT, msg);
	// Create the graft packet

	// Send the packet toward the RPF(S)

	SendPacket(packet,msg,pair.sourceIfaceAddr);
	SourceGroupState *sgState = FindSourceGroupState(interface,pair);
	sgState->upstream->SG_GRT.Cancel();//remove old events
	sgState->upstream->SG_GRT.SetFunction(&MulticastRoutingProtocol::SendGraft, this);//re-schedule transmission
	sgState->upstream->SG_GRT.SetArguments(interface, pair);
	sgState->upstream->SG_GRT.SetDelay(Seconds(Graft_Retry_Period));//set the timer

}

void
MulticastRoutingProtocol::SendGraftUnicast (Ipv4Address destination, SourceGroupPair pair){
	NS_LOG_FUNCTION(this);//TODO To complete
	Ptr<Packet> packet = Create<Packet> ();
	PIMHeader msg;
	ForgeHeaderMessage(PIM_GRAFT, msg);
	// Create the graft packet TODO

	// Send the packet toward the RPF(S)
	uint32_t interface = GetReceivingInterface(destination);
	SendPacket(packet,msg,pair.sourceIfaceAddr);
	SourceGroupState *sgState = FindSourceGroupState(interface, pair);
	sgState->upstream->SG_GRT.Cancel();//remove old events
	sgState->upstream->SG_GRT.SetFunction(&MulticastRoutingProtocol::SendGraft, this);//re-schedule transmission
	sgState->upstream->SG_GRT.SetArguments(interface, pair);
	sgState->upstream->SG_GRT.SetDelay(Seconds(Graft_Retry_Period));//set the timer
}

void
MulticastRoutingProtocol::RecvGraft (PIMHeader::GraftMessage &graft, Ipv4Address sender, Ipv4Address receiver){
	NS_LOG_FUNCTION(this);
	uint32_t interface = GetReceivingInterface(sender);
	for(std::vector<PIMHeader::MulticastGroupEntry>::iterator mgroup = graft.m_multicastGroups.begin();
			mgroup!=graft.m_multicastGroups.end(); mgroup++){
		for(std::vector<PIMHeader::EncodedSource>::iterator msource = mgroup->m_joinedSourceAddrs.begin();
					msource != mgroup->m_joinedSourceAddrs.end(); msource++){
			if(interface == RPF_interface(msource->m_sourceAddress)){
				RecvGraftDownstream (graft, sender, receiver, *msource,mgroup->m_multicastGroupAddr);
			}
		}
	}
}

void //TODO split as done in join
MulticastRoutingProtocol::RecvGraftDownstream(PIMHeader::GraftMessage &graft, Ipv4Address sender, Ipv4Address receiver, const PIMHeader::EncodedSource &source, PIMHeader::EncodedGroup &group){
	NS_LOG_FUNCTION(this);
	uint32_t interface = GetReceivingInterface(sender);
	Ipv4Address current = GetLocalAddress(interface);
	SourceGroupPair sgp (source.m_sourceAddress, group.m_groupAddress);
	SourceGroupState *sgState = FindSourceGroupState(interface,source.m_sourceAddress,group.m_groupAddress);
	switch (sgState->PruneState) {
		case Prune_NoInfo:{
		//A Graft(S,G) is received on the interface I with the upstream neighbor field set to the router's
		//	address on I.  The Prune(S,G) Downstream state machine on interface I stays in the NoInfo (NI)
		//	state.  A GraftAck(S,G) MUST be unicast to the originator of the Graft(S,G) message.
			if(graft.m_joinPruneMessage.m_upstreamNeighborAddr.m_unicastAddress == current){
				SendGraftAckUnicast(interface,sgp,sender);
			}
		}
		case Prune_PrunePending:{
		//Receive Graft(S,G): A Graft(S,G) is received on interface I with the upstream neighbor
		//	field set to the router's address on I.  The Prune(S,G) Downstream state machine on
		//	interface I MUST transition to the NoInfo (NI) state and MUST unicast a Graft Ack
		//	message to the Graft originator.  The PrunePending Timer (PPT(S,G,I)) MUST be cancelled.
			if(graft.m_joinPruneMessage.m_upstreamNeighborAddr.m_unicastAddress == current){
				sgState->PruneState = Prune_NoInfo;
				SendGraftAckUnicast(interface,sgp,sender);
				sgState->SG_PPT.Cancel();
			}
			break;
		}
		//Receive Graft(S,G). A Graft(S,G) is received on interface I with the upstream neighbor field
		//	set to the router's address on I.  The Prune(S,G) Downstream state machine on interface I
		//	MUST transition to the NoInfo (NI) state and send a Graft Ack back to the Graft's source.
		//	The Prune Timer (PT(S,G,I)) MUST be cancelled.
		//	TODO: The router MUST evaluate any possible transitions in the Upstream(S,G) state machine.
		case Prune_Pruned:{
			if(graft.m_joinPruneMessage.m_upstreamNeighborAddr.m_unicastAddress == current){
				sgState->PruneState = Prune_NoInfo;
				SendGraftAckUnicast(interface,sgp,sender);
				sgState->SG_PPT.Cancel();
			}
			break;
		}
		default:{
			NS_LOG_ERROR("RecvGraftDownstream: Prune state not valid"<<sgState->PruneState);
			break;
		}
	}
	switch (sgState->AssertState){
		case  Assert_NoInfo:{
			//nothing
			break;
			}
		case Assert_Winner:{
			//nothing
			break;
		}
		case Assert_Loser:{
			//Receive Prune(S,G), Join(S,G), or Graft(S,G).
			//	A Prune(S,G), Join(S,G), or Graft(S,G) message was received on
			//	interface I with its upstream neighbor address set to the
			//	router's address on I.  The router MUST send an Assert(S,G) on
			//	the receiving interface I to initiate an Assert negotiation.  The
			//	Assert state machine remains in the Assert Loser(L) state.  If a
			//	Graft(S,G) was received, the router MUST respond with a GraftAck(S,G).
			if(graft.m_joinPruneMessage.m_upstreamNeighborAddr.m_unicastAddress == current){
				PIMHeader assertR;
				ForgeAssertMessage(interface,assertR,sgp);
				assertR.GetAssertMessage().m_metricPreference = sgState->AssertWinner.metric_preference;
				assertR.GetAssertMessage().m_metric = sgState->AssertWinner.route_metric;
				Ptr<Packet> packet = Create<Packet> ();
				SendBroadPacketInterface(packet,assertR,interface);
				SendGraftAckUnicast(interface,sgp,sender);//TODO check receiver is the previous sender
			}
			//An Assert loser that receives a Prune(S,G), Join(S,G), or
			//  Graft(S,G) directed to it initiates a new Assert negotiation so
			//  that the downstream router can correct its RPF'(S).
			break;
		}
		default:{
			NS_LOG_ERROR("RecvAssert: Assert State not valid"<<sgState->AssertState);
		}
	}
}

void
MulticastRoutingProtocol::SendGraftAck (uint32_t interface, SourceGroupPair pair){
	NS_LOG_FUNCTION(this);
	Ptr<Packet> packet = Create<Packet> ();
	PIMHeader msg;
	ForgeHeaderMessage(PIM_GRAFT_ACK, msg);//TODO
}

void
MulticastRoutingProtocol::SendGraftAckUnicast(uint32_t interface, SourceGroupPair &pair, const Ipv4Address receiver){
	NS_LOG_FUNCTION(this);
	Ptr<Packet> packet = Create<Packet> ();
	PIMHeader msg;
	ForgeHeaderMessage(PIM_GRAFT_ACK, msg);//TODO
}

void
MulticastRoutingProtocol::RecvGraftAck (PIMHeader::GraftAckMessage &graftAck, Ipv4Address sender, Ipv4Address receiver){
	NS_LOG_FUNCTION(this);
	uint32_t interface = GetReceivingInterface(receiver);
	//The transition event "RcvGraftAck(S,G)" implies receiving a Graft Ack message targeted to this router's address on the incoming interface
	//	for the (S,G) entry.  If the destination address is not correct, the state transitions in this state machine must not occur.
	if(GetLocalAddress(interface) != graftAck.m_joinPruneMessage.m_upstreamNeighborAddr.m_unicastAddress) return;
	for(std::vector<struct PIMHeader::MulticastGroupEntry>::iterator groups = graftAck.m_multicastGroups.begin();
			groups != graftAck.m_multicastGroups.end(); groups++){
		graftAck.Print(std::cout);
		for(std::vector<PIMHeader::EncodedSource>::const_iterator iterSource = groups->m_joinedSourceAddrs.begin();
				iterSource!=groups->m_joinedSourceAddrs.end(); iterSource++){
			SourceGroupPair pair (iterSource->m_sourceAddress, groups->m_multicastGroupAddr.m_groupAddress);
			SourceGroupState *sgState = FindSourceGroupState(interface,pair);
			NS_LOG_DEBUG("Removing Timer GRAFT " << sgState->upstream->SG_GRT.GetDelayLeft().GetMilliSeconds());
			pair.sourceIfaceAddr.Print(std::cout);
			pair.groupMulticastAddr.Print(std::cout);
			if(interface == RPF_interface(sender)){
				sgState->upstream->SG_GRT.Cancel(); //TODO check!
				switch (sgState->upstream->GraftPrune){
				//The Upstream(S,G) state machine MUST transition to the Pruned (P)
				// state, send a Prune(S,G) to RPF'(S), and set PLT(S,G) to t_limit seconds.
				case GP_Forwarding:{
					//nothing
					break;
				}
				case GP_Pruned:{
					//nothing
					break;
				}
				case GP_AckPending:{
					if(sender == RPF_prime(pair.sourceIfaceAddr,pair.groupMulticastAddr)){
						sgState->upstream->SG_GRT.Cancel();
						sgState->upstream->GraftPrune = GP_Forwarding;
					}
					break;
				}
				default:{
					NS_LOG_ERROR("RecvGraftAck: Graft Prune state not valid"<<sgState->upstream->GraftPrune);
				}
				}
			}
	}
}
}

void
MulticastRoutingProtocol::NeighborRestart (uint32_t interface){
//TODO
}

void
MulticastRoutingProtocol::SendBroadPacket (Ptr<Packet> packet, const PIMHeader &message)
{
  NS_LOG_FUNCTION(this);
  packet->AddHeader(message);
    // Trace it
//  m_txPacketTrace (packet, message);

  // Send it
  for (std::map<Ptr<Socket> , Ipv4InterfaceAddress>::const_iterator i =
      m_socketAddresses.begin (); i != m_socketAddresses.end (); i++) {
      Ipv4Address bcast = i->second.GetLocal ().GetSubnetDirectedBroadcast (i->second.GetMask ());
      NS_LOG_DEBUG ("Broadcast: " << bcast << ":"<<PIM_PORT_NUMBER);
      i->first->SendTo (packet, 0, InetSocketAddress (bcast, PIM_PORT_NUMBER));
    }
}

void
MulticastRoutingProtocol::SendPacket (Ptr<Packet> packet, const PIMHeader &message, Ipv4Address destination){
//	 A Hello message SHOULD be sent after a random delay between 0 and
//	Triggered_Hello_Delay (see 4.8) before any other messages are sent.
  if(m_stopTx) return;
  packet->AddHeader(message);
  // Trace it
  m_txPacketTrace (message);

  // Send it
  for (std::map<Ptr<Socket> , Ipv4InterfaceAddress>::const_iterator i =
      m_socketAddresses.begin (); i != m_socketAddresses.end (); i++)
    {
	  if(i->second.GetLocal() == GetLocalAddress(GetReceivingInterface(destination))){
		  NS_LOG_DEBUG ("Destination: " << destination << ":"<<PIM_PORT_NUMBER<<", Interface "<<GetReceivingInterface(destination));
		  i->first->SendTo (packet, 0, InetSocketAddress (destination, PIM_PORT_NUMBER));
		}
    }
}

void
MulticastRoutingProtocol::SendBroadPacketInterface (Ptr<Packet> packet, const PIMHeader &message, uint32_t interface){
  packet->AddHeader(message);
  // Trace it
  //  m_txPacketTrace (packet, message);

  // Send it
  for (std::map<Ptr<Socket> , Ipv4InterfaceAddress>::const_iterator i =
      m_socketAddresses.begin (); i != m_socketAddresses.end (); i++)
    {
	  if(GetLocalAddress(interface) == i->second.GetLocal ()){
		  Ipv4Address bcast = i->second.GetLocal ().GetSubnetDirectedBroadcast (i->second.GetMask ());
		  NS_LOG_DEBUG ("Broadcast: " << bcast << ":"<<PIM_PORT_NUMBER<<", Interface "<<interface);
		  i->first->SendTo (packet, 0, InetSocketAddress (bcast, PIM_PORT_NUMBER));
	  }
      }
}

void
MulticastRoutingProtocol::SendBroadPacketInterface (Ptr<Packet> packet, uint32_t interface){
  NS_LOG_DEBUG ("PIMDM node " << GetLocalAddress(interface) << " sending a Data packet");

  // Send it
  for (std::map<Ptr<Socket> , Ipv4InterfaceAddress>::const_iterator i =
      m_socketAddresses.begin (); i != m_socketAddresses.end (); i++)
    {
	  if(GetLocalAddress(interface) == i->second.GetLocal ()){
		  Ipv4Address bcast = i->second.GetLocal ().GetSubnetDirectedBroadcast (i->second.GetMask ());
		  NS_LOG_DEBUG ("Destination: " << bcast << ":"<<PIM_PORT_NUMBER<<", Interface "<<interface);
		  i->first->SendTo (packet, 0, InetSocketAddress (bcast, PIM_PORT_NUMBER));
	  }
  }
}

bool
MulticastRoutingProtocol::IsValidSG(uint32_t interface, const Ipv4Address & source,const Ipv4Address & group){
	SourceGroupState *sgState = FindSourceGroupState(interface,source, group);
	bool valid = false;
	if(sgState){
		valid = valid || sgState->SG_PPT.IsRunning();
		valid = valid || sgState->SG_PT.IsRunning();
		valid = valid || sgState->SG_AT.IsRunning();
				///     Upstream interface-specific
		if(RPF_interface(source) == interface){
			valid = valid || sgState->upstream->SG_GRT.IsRunning();
			valid = valid || sgState->upstream->SG_OT.IsRunning();
			valid = valid || sgState->upstream->SG_PLT.IsRunning();
			valid = valid || sgState->upstream->SG_SAT.IsRunning();
			valid = valid || sgState->upstream->SG_SRT.IsRunning();
		}
	}
	return valid;
}

void
MulticastRoutingProtocol::PLTTimerExpire (SourceGroupPair &sgp){
	NS_LOG_FUNCTION(this);
	SourceGroupState *sgState = FindSourceGroupState(RPF_interface(sgp.sourceIfaceAddr),sgp);
	SendPruneBroadcast(RPF_interface(sgp.sourceIfaceAddr),sgp);
	sgState->upstream->SG_PLT.Schedule();
}

void
MulticastRoutingProtocol::NLTTimerExpire (Ipv4Address neighborIfaceAddr, Ipv4Address receivingIfaceAddr){
	uint32_t interface = GetReceivingInterface(neighborIfaceAddr); // retrieve the interface
	SourceGroupList *sgList= FindSourceGroupList(interface); // get all the S,G pair
	for (SourceGroupList::iterator sgState = sgList->begin(); sgState != sgList->end() ; sgState++){
		if(sgState->SGAW == neighborIfaceAddr){// Find the assert winner
			switch (sgState->AssertState){
				case  Assert_NoInfo:{
					break;
					}
				case Assert_Winner:{
					break;
					}
				case Assert_Loser:{
					//Current Assert Winner's NeighborLiveness Timer Expires
					//	The current Assert winner's NeighborLiveness Timer (NLT(N,I)) has
					//	expired.  The Assert state machine MUST transition to the NoInfo
					//	(NI) state, delete the Assert Winner's address and metric, and
					//	TODO: evaluate any possible transitions to its Upstream(S,G) state machine.
					sgState->AssertState = Assert_NoInfo;
					sgState->AssertWinner.metric_preference = 0xffffffff;
					sgState->AssertWinner.route_metric = 0xffffffff;
					sgState->AssertWinner.ip_address = Ipv4Address("255.255.255.255");
					break;
				}
				default:{
					NS_LOG_ERROR("NLTTimerExpire: Assert State not valid"<<sgState->AssertState);
				}
			}
		}
	}
}

void
MulticastRoutingProtocol::OTTimerExpire (SourceGroupPair &sgp){
	NS_LOG_FUNCTION(this);
	SourceGroupState *sgState = FindSourceGroupState(RPF_interface(sgp.sourceIfaceAddr),sgp);
		switch (sgState->upstream->GraftPrune){
			case GP_Forwarding:{
				//The OverrideTimer (OT(S,G)) expires.  The router MUST send a Join(S,G) to RPF'(S) to override a previously detected prune.
				//	The Upstream(S,G) state machine remains in the Forwarding (F) state.
				if(sgp.sourceIfaceAddr!=m_mrib.find(sgp.sourceIfaceAddr)->second.nextAddr){
					Ipv4Address nextHop = RPF_prime(sgp.sourceIfaceAddr,sgp.groupMulticastAddr);
					SendJoinUnicast(nextHop, sgp); //broadcast
				}
				break;
			}
			case GP_Pruned:{
				break;
			}
			case GP_AckPending:{
				//The OverrideTimer (OT(S,G)) expires.  The router MUST send a Join(S,G) to RPF'(S).
				//	The Upstream(S,G) state machine remains in the AckPending (AP) state.
				Ipv4Address nextHop = RPF_prime(sgp.sourceIfaceAddr,sgp.groupMulticastAddr);
				SendJoinUnicast(nextHop, sgp); //broadcast
				break;
			}
			default:{
				NS_LOG_ERROR("OT_Timer: state not valid"<<sgState->upstream->GraftPrune);
			}
	}
//	sgState->upstream->SG_OT.Schedule();
	sgState->upstream->SG_OT.Cancel();
}


void
MulticastRoutingProtocol::GRTTimerExpire (SourceGroupPair &sgp){
	SourceGroupState *sgState = FindSourceGroupState(RPF_interface(sgp.sourceIfaceAddr),sgp);
	switch (sgState->upstream->GraftPrune){
		case GP_Forwarding:{
			//nothing
			break;
		}
		case GP_Pruned:{
			//nothing
			break;
		}
		case GP_AckPending:{
		//The GraftRetry Timer (GRT(S,G)) expires for this (S,G) entry.
		//	The Upstream(S,G) state machine stays in the AckPending (AP) state.
		//	Another Graft message for (S,G) SHOULD be unicast to RPF'(S) and the GraftRetry Timer (GRT(S,G)) reset to Graft_Retry_Period.
		//	It is RECOMMENDED that the router retry a configured number of times before ceasing retries.
			Ipv4Address target = RPF_prime(sgp.sourceIfaceAddr,sgp.groupMulticastAddr);
			NeighborState dest(target,GetLocalAddress(GetReceivingInterface(target)));
			NeighborState *ns = FindNeighborState(GetReceivingInterface(target),dest);
			if(ns->neighborGraftRetry[0]<ns->neighborGraftRetry[1]){//increase counter retries
				SendGraftUnicast(target,sgp);
				sgState->upstream->SG_GRT.Cancel();
				sgState->upstream->SG_GRT.SetDelay(Seconds(Graft_Retry_Period));
				sgState->upstream->SG_GRT.Schedule();
			}else{
				ns->neighborGraftRetry[0] = 0;//reset counter retries
			}
			break;
		}
		default:{
			NS_LOG_ERROR("GRTTimerExpire: state not valid"<<sgState->upstream->GraftPrune);
		}
	}
}


void
MulticastRoutingProtocol::PPTTimerExpire(SourceGroupPair &sgp){
	uint32_t interface = RPF_interface(sgp.sourceIfaceAddr);
	SourceGroupState *sgState = FindSourceGroupState(interface,sgp);
	switch (sgState->PruneState) {
		case Prune_NoInfo:{
			// nothing
			break;
		}
		case Prune_PrunePending:{
		//PPT(S,G,I) Expires: The PrunePending Timer (PPT(S,G,I)) expires, indicating that no
		//	neighbors have overridden the previous Prune(S,G) message.  The Prune(S,G) Downstream
		//	state machine on interface I MUST transition to the Pruned (P) state.
			sgState->PruneState = Prune_Pruned;
		//	The Prune Timer (PT(S,G,I)) is started and MUST be initialized to the received
		//	Prune_Hold_Time minus J/P_Override_Interval.
			NeighborhoodStatus *nstatus = FindNeighborhoodStatus(RPF_interface(sgp.sourceIfaceAddr));
			Time JP_Override_Interval= nstatus->overrideInterval+nstatus->propagationDelay;
			Time Delay = nstatus->pruneHoldtime - JP_Override_Interval;
			Delay = (Delay.GetSeconds()>=0 ? Delay: Seconds(0));
			if(nstatus->neighbors.size()>1){// Prune echo
			//  A PruneEcho(S,G) MUST be sent on I if I has more than one PIM neighbor.
			//	A PruneEcho(S,G) is simply a Prune(S,G) message
			//	multicast by the upstream router to a LAN, with itself as the Upstream Neighbor.
				PIMHeader msg;
				ForgePruneMessage(msg);
				msg.GetJoinPruneMessage().m_joinPruneMessage.m_upstreamNeighborAddr.m_unicastAddress = GetLocalAddress(interface);
				Ptr<Packet> packet = Create<Packet> ();
				SendBroadPacket(packet,msg);
			//	Its purpose is to add additional reliability so that if a Join that should have
			//	overridden the Prune is lost locally on the LAN, the PruneEcho(S,G) may be received
			//	and trigger a new Join message.
			//	TODO: A PruneEcho(S,G) is OPTIONAL on an interface with only one PIM neighbor.
			//	TODO: In addition, the router MUST evaluate any possible transitions in the Upstream(S,G) state machine.
			}
			break;
		}
		case Prune_Pruned:{
			//nothing
			break;
		}
		default:
			NS_LOG_ERROR("PPTTimerExpire: Prune state not valid"<<sgState->PruneState);
			break;
	}
}



void
MulticastRoutingProtocol::PTTimerExpire(SourceGroupPair &sgp){
	uint32_t interface = RPF_interface(sgp.sourceIfaceAddr);
	SourceGroupState *sgState = FindSourceGroupState(interface,sgp);
	switch (sgState->PruneState) {
		case Prune_NoInfo:{
			// nothing
			break;
		}
		case Prune_PrunePending:{
			// nothing
			break;
		}
		case Prune_Pruned:{
		//PT(S,G,I) Expires. The Prune Timer (PT(S,G,I)) expires, indicating that it is again
		//	time to flood data from S addressed to group G onto interface I.
		//	The Prune(S,G) Downstream state machine on interface I MUST transition to the NoInfo (NI) state.
		//	TODO: The router MUST evaluate any possible transitions in the Upstream(S,G) state machine.
			sgState->PruneState = Prune_NoInfo;
			break;
		}
		default:
			NS_LOG_ERROR("PTTimerExpire: Prune state not valid"<<sgState->PruneState);
			break;
	}
}

void
MulticastRoutingProtocol::SRTTimerExpire (SourceGroupPair &sgp){
	uint32_t interface = RPF_interface(sgp.sourceIfaceAddr);
	SourceGroupState *sgState = FindSourceGroupState(interface,sgp);
	if(sgState->upstream->origination){
	switch (sgState->upstream->origination) {
		case NotOriginator:{
			//nothing
			break;
		}
		case Originator:{
		//SRT(S,G) Expires.
		//	The router remains in the Originator (O) state and MUST reset
		//	SRT(S,G) to StateRefreshInterval.  The router MUST also generate
		//	State Refresh messages for transmission, as described in the
		//	State Refresh Forwarding rules (Section 4.5.1), except for the
		//	TTL.  If the TTL of data packets from S to G are being recorded,
		//	then the TTL of each State Refresh message is set to the highest
		//	recorded TTL.  Otherwise, the TTL is set to the configured State
		//	Refresh TTL.  Let I denote the interface over which a State
		//	Refresh message is being sent.  If the Prune(S,G) Downstream
		//	state machine is in the Pruned (P) state, then the Prune-
		//	Indicator bit MUST be set to 1 in the State Refresh message being
		//	sent over I. Otherwise, the Prune-Indicator bit MUST be set to 0.
			if(sgState->upstream->SG_SRT.IsRunning())
				sgState->upstream->SG_SRT.Cancel();
			sgState->upstream->SG_SRT.SetDelay(Seconds(RefreshInterval));
			sgState->upstream->SG_SRT.Schedule();
			for (uint32_t i = 0; i < m_ipv4->GetNInterfaces (); i++){
				PIMHeader refresh;//TODO Check to which interfaces should be sent
				ForgeStateRefresh(i, sgp, refresh);
				refresh.GetStateRefreshMessage().m_P = (IsDownstream(i,sgp) ? 1 : 0);
				Ptr<Packet> packet = Create<Packet> ();
				SendBroadPacket(packet,refresh);
			}
			break;
		}
		default:{
			NS_LOG_ERROR("SRTTimerExpire: Origination state not valid"<<sgState->upstream->origination);
			break;
		}
	}
	}
}

void
MulticastRoutingProtocol::ATTimerExpire (SourceGroupPair &sgp){
	uint32_t interface = RPF_interface(sgp.sourceIfaceAddr);
	SourceGroupState *sgState = FindSourceGroupState(interface,sgp);
	switch (sgState->AssertState){
		case  Assert_NoInfo:{
			break;
			}
		case Assert_Winner:{
			//AT(S,G,I) Expires
			//	The (S,G) Assert Timer (AT(S,G,I)) expires.  The Assert state
			//	machine MUST transition to the NoInfo (NI) state.
			sgState->AssertState = Assert_NoInfo;
			break;
			}
		case Assert_Loser:{
			//AT(S,G,I) Expires
			//	The (S,G) Assert Timer (AT(S,G,I)) expires.  The Assert state
			//	machine MUST transition to NoInfo (NI) state.  The router MUST
			//	delete the Assert Winner's address and metric.
			sgState->AssertState = Assert_NoInfo;
			sgState->AssertWinner.metric_preference = 0xffffffff;
			sgState->AssertWinner.route_metric = 0xffffffff;
			sgState->AssertWinner.ip_address = Ipv4Address("255.255.255.255");
			if(CouldAssert(sgp.sourceIfaceAddr,sgp.groupMulticastAddr, interface)){
				//	If CouldAssert == TRUE, the router MUST evaluate any possible
				//	transitions to its Upstream(S,G) state machine.
				//TODO
			}
			//nothing
			break;
		}
		default:{
			NS_LOG_ERROR("ATTimerExpire: Assert State not valid"<<sgState->AssertState);
		}
	}
}

void
MulticastRoutingProtocol::SATTimerExpire (SourceGroupPair &sgp){
	uint32_t interface = RPF_interface(sgp.sourceIfaceAddr);
	SourceGroupState *sgState = FindSourceGroupState(interface,sgp);
	if(sgState->upstream){
	switch (sgState->upstream->origination) {
		case NotOriginator:{
			//nothing
			break;
		}
		case Originator:{
		//SAT(S,G) Expires.
		//	The router MUST cancel the SRT(S,G) timer and transition to the NotOriginator (NO) state.
			if(sgState->upstream->SG_SRT.IsRunning())
				sgState->upstream->SG_SRT.Cancel();
			sgState->upstream->origination = NotOriginator;
			break;
		}
		default:{
			NS_LOG_ERROR("SATTimerExpire: Origination state not valid"<<sgState->upstream->origination);
			break;
		}
	}
	}
}


void
MulticastRoutingProtocol::SendJoinUnicast (Ipv4Address destination, SourceGroupPair &sgpair){
	NS_LOG_FUNCTION(this);
//	uint32_t interface = GetReceiveingInterface(destination);
	//TODO
}


void
MulticastRoutingProtocol::SendPruneUnicast(Ipv4Address destination, SourceGroupPair &sgpair){
	NS_LOG_FUNCTION(this);
	//	uint32_t interface = GetReceiveingInterface(destination);
	//TODO
}

void
MulticastRoutingProtocol::olistCheck(SourceGroupPair &sgp, std::set<uint32_t> list){
	NS_LOG_FUNCTION(this);
	if(list.size() == 0)
		olistEmpty(sgp, list);
	else
		olistFull(sgp, list);
	}

void
MulticastRoutingProtocol::olistEmpty(SourceGroupPair &sgp, std::set<uint32_t> list){
	NS_LOG_FUNCTION(this);
	SourceGroupState *sgState = FindSourceGroupState(RPF_interface(sgp.sourceIfaceAddr),sgp);
	switch (sgState->upstream->GraftPrune){
		case GP_Forwarding:{
		// olist(S,G) -> NULL AND S NOT directly connected
       	//   The Upstream(S,G) state machine MUST transition to the Pruned (P)  state,
       	//   send a Prune(S,G) to RPF'(S), and set PLT(S,G) to t_limit seconds.
			if(m_mrib.find(sgp.sourceIfaceAddr)->second.nextAddr != sgp.sourceIfaceAddr){
				sgState ->upstream->GraftPrune = GP_Pruned;
				Ipv4Address target = RPF_prime(sgp.sourceIfaceAddr,sgp.groupMulticastAddr);
				SendPruneBroadcast(RPF_interface(target),sgp);
				sgState->upstream->SG_PLT.Cancel();
				sgState->upstream->SG_PLT.SetDelay(Seconds(t_limit));
				sgState->upstream->SG_PLT.Schedule();
			}
			break;
		}
		case GP_Pruned:{
			//nothing
			break;
		}
		case GP_AckPending:{
		//The set of interfaces defined by the olist(S,G) macro becomes null, indicating that traffic from S addressed to group G should
		//	no longer be forwarded.  The Upstream(S,G) state machine MUST transition to the Pruned (P) state.
		//	A Prune(S,G) MUST be multicast to the RPF_interface(S), with RPF'(S) named in the upstream neighbor field.
		//	The GraftRetry Timer (GRT(S,G)) MUST be cancelled, and PLT(S,G) MUST be set to t_limit seconds.
			sgState->upstream->GraftPrune = GP_Pruned;
			uint32_t interface = RPF_interface(sgp.sourceIfaceAddr);
			PIMHeader::MulticastGroupEntry mge;
			AddMulticastGroupSourcePrune(mge,ForgeEncodedSource(sgp.sourceIfaceAddr));
			PIMHeader msg;
			Ipv4Address destination = RPF_prime(sgp.sourceIfaceAddr,sgp.groupMulticastAddr);
			ForgePruneMessage(msg);
			CreateMulticastGroupEntry(msg,mge,ForgeEncodedGroup(sgp.groupMulticastAddr));
			msg.GetJoinPruneMessage().m_joinPruneMessage.m_upstreamNeighborAddr.m_unicastAddress = destination;
			Ptr<Packet> packet = Create<Packet> ();
			SendBroadPacketInterface(packet,msg,GetReceivingInterface(destination));
			sgState->upstream->SG_GRT.Cancel();
			sgState->upstream->SG_PLT.SetDelay(Seconds(t_limit));

			break;
		}
		default:{
			NS_LOG_ERROR("OList is empty: state not valid"<<sgState->upstream->GraftPrune);
		}
		}
	}

void
MulticastRoutingProtocol::olistFull(SourceGroupPair &sgp, std::set<uint32_t> list){
	NS_LOG_FUNCTION(this);
	SourceGroupState *sgState = FindSourceGroupState(RPF_interface(sgp.sourceIfaceAddr),sgp);
	switch (sgState->upstream->GraftPrune){
		case GP_Forwarding:{
			//nothing
			break;
		}
		case GP_Pruned:{
		// olist(S,G)->non-NULL AND S NOT directly connected
        //   The set of interfaces defined by the olist(S,G) macro becomes non-empty,
        //   indicating that traffic from S addressed to group G  must be forwarded.
        //   The Upstream(S,G) state machine MUST cancel PLT(S,G), transition to the AckPending (AP) state and unicast a Graft message to RPF'(S).
        //   The Graft Retry Timer (GRT(S,G)) MUST be set to Graft_Retry_Period.
			if(m_mrib.find(sgp.sourceIfaceAddr)->second.nextAddr != sgp.sourceIfaceAddr){
				sgState->upstream->SG_PLT.Cancel();
				sgState->upstream->GraftPrune = GP_AckPending;
				Ipv4Address target = RPF_prime(sgp.sourceIfaceAddr,sgp.groupMulticastAddr);
				SendGraftUnicast(target, sgp);
				sgState->upstream->SG_GRT.Cancel();
				sgState->upstream->SG_GRT.SetDelay(Seconds(Graft_Retry_Period));
				sgState->upstream->SG_GRT.Schedule();
			}
			break;
		}
		case GP_AckPending:{
			//nothing
			break;
		}
		default:{
			NS_LOG_ERROR("OList is full: state not valid"<<sgState->upstream->GraftPrune);
		}
		}
	}


void
MulticastRoutingProtocol::SourceDirectlyConnected(SourceGroupPair &sgp){
	NS_LOG_FUNCTION(this);
	SourceGroupState *sgState = FindSourceGroupState(RPF_interface(sgp.sourceIfaceAddr),sgp);
	switch (sgState->upstream->GraftPrune){
		case GP_Forwarding:{
			//nothing
			break;
		}
		case GP_Pruned:{
			//nothing
			break;
		}
		case GP_AckPending:{
		//Unicast routing has changed so that S is directly connected.
		//	The GraftRetry Timer MUST be canceled, and the Upstream(S,G) state machine MUST transition to the Forwarding(F) state.
			sgState->upstream->SG_GRT.Cancel();
			sgState->upstream->GraftPrune = GP_Forwarding;
			break;
		}
		default:{
			NS_LOG_ERROR("SourceDirectlyConnected: state not valid"<<sgState->upstream->GraftPrune);
		}
	}
	if(sgState->upstream){
	switch (sgState->upstream->origination) {
		case NotOriginator:{
			sgState->upstream->origination = Originator;
			sgState->upstream->SG_SRT.SetDelay(Seconds(RefreshInterval));
			sgState->upstream->SG_SRT.Schedule();
			sgState->upstream->SG_SAT.SetDelay(Seconds(SourceLifetime));
			sgState->upstream->SG_SAT.Schedule();
			break;
		}
		case Originator:{
			//nothing
			break;
		}
		default:{
			NS_LOG_ERROR("SourceDirectlyConnected: Origination state not valid"<<sgState->upstream->origination);
			break;
		}
	}
	}
}

void
MulticastRoutingProtocol::SourceNoDirectlyConnected(SourceGroupPair &sgp){
	NS_LOG_FUNCTION(this);
	SourceGroupState *sgState = FindSourceGroupState(RPF_interface(sgp.sourceIfaceAddr),sgp);
	if(sgState->upstream){
	switch (sgState->upstream->origination) {
		case NotOriginator:{
			//nothing
			break;
		}
		case Originator:{
			sgState->upstream->origination = NotOriginator;
			if(sgState->upstream->SG_SRT.IsRunning())
				sgState->upstream->SG_SRT.Cancel();
			sgState->upstream->SG_SAT.Cancel();
			break;
		}
		default:{
			NS_LOG_ERROR("SourceNoDirectlyConnected: Origination state not valid"<<sgState->upstream->origination);
			break;
		}
	}}
}

void
MulticastRoutingProtocol::RPF_Changes(SourceGroupPair &sgp, uint32_t oldInterface, uint32_t newInterface){
	ChangeSourceGroupState(oldInterface,newInterface,*FindSourceGroupState(oldInterface,sgp));
	SourceGroupState *sgState = FindSourceGroupState(newInterface,sgp);
	switch (sgState->PruneState) {
		case Prune_NoInfo:{
			// nothing
			break;
		}
		case Prune_PrunePending:{
		//RPF_Interface(S) becomes interface I. The upstream interface for S has changed.
		//	The Prune(S,G) Downstream state machine on interface I MUST transition to the
		//	NoInfo (NI) state.  The PrunePending Timer (PPT(S,G,I)) MUST be cancelled.
			sgState->PruneState = Prune_NoInfo;
			sgState->SG_PPT.Cancel();
			break;
		}
		case Prune_Pruned:{
		//RPF_Interface(S) becomes interface I. The upstream interface for S has changed.
		//	The Prune(S,G) Downstream state machine on interface I MUST transition to the NoInfo (NI) state.
		//	The PruneTimer (PT(S,G,I)) MUST be cancelled.
			sgState->PruneState = Prune_NoInfo;
			sgState->SG_PT.Cancel();
			break;
		}
		default:
			NS_LOG_ERROR("PPTTimerExpire: Prune state not valid"<<sgState->PruneState);
			break;
	}
}

bool
MulticastRoutingProtocol::CouldAssertCheck (Ipv4Address source, Ipv4Address group, uint32_t interface, bool couldAssert) {
	SourceGroupPair sgp(source,group);
	SourceGroupState *sgState = FindSourceGroupState(interface,sgp);
	switch (sgState->AssertState){
		case  Assert_NoInfo:{
			break;
			}
		case Assert_Winner:{
			if(couldAssert) break;
			//CouldAssert(S,G,I) -> FALSE
			//	This router's RPF interface changed, making CouldAssert(S,G,I) false.
			//	This router can no longer perform the actions of the Assert winner,
			//	so the Assert state machine MUST transition to NoInfo (NI) state,
			sgState->AssertState = Assert_NoInfo;
			//	send an AssertCancel(S,G) to interface I,
			PIMHeader assertR;
			ForgeAssertCancelMessage(interface,assertR, sgp);
			Ptr<Packet> packet = Create<Packet> ();
			SendBroadPacketInterface(packet,assertR,interface);
			//  cancel the Assert Timer (AT(S,G,I)),
			if(sgState->SG_AT.IsRunning())
				sgState->SG_AT.Cancel();
			//  and remove itself as the Assert Winner.
			UpdateAssertWinner(sgState, 0xffffffff, 0xffffffff, Ipv4Address("255.255.255.255"));
			break;
			//An Assert winner for (S,G) sends a cancelling assert when it is
			//about to stop forwarding on an (S,G) entry.  Example: If a router
			//is being taken down, then a canceling assert is sent.
			}
		case Assert_Loser:{
			if(couldAssert){
				//CouldAssert -> TRUE
				//	CouldAssert has become TRUE because interface I used to be the
				//	RPF interface for S, and now it is not.  The Assert state machine
				//	MUST transition to NoInfo (NI) state, cancel AT(S,G,I), and
				//	delete information concerning the Assert Winner on I.
				sgState->AssertState = Assert_NoInfo;
				if(sgState->SG_AT.IsRunning())
					sgState->SG_AT.Cancel();
				UpdateAssertWinner(sgState, 0xffffffff, 0xffffffff, Ipv4Address("255.255.255.255"));
			}else{
				//CouldAssert -> FALSE
				//	CouldAssert has become FALSE because interface I has become the
				//	RPF interface for S.  The Assert state machine MUST transition to
				//	NoInfo (NI) state, cancel AT(S,G,I), and delete information
				//	concerning the Assert Winner on I.
				sgState->AssertState = Assert_NoInfo;
				if(sgState->SG_AT.IsRunning())
					sgState->SG_AT.Cancel();
				UpdateAssertWinner(sgState, 0xffffffff, 0xffffffff, Ipv4Address("255.255.255.255"));
			}
			break;
		}
		default:{
			NS_LOG_ERROR("RPF_Changes: Assert State not valid"<<sgState->AssertState);
		}
	}
}

void
MulticastRoutingProtocol::RPF_primeChanges(SourceGroupPair &sgp){
	std::set<uint32_t> outlist = olist(sgp.sourceIfaceAddr,sgp.groupMulticastAddr);
	SourceGroupState *sgState = FindSourceGroupState(RPF_interface(sgp.sourceIfaceAddr),sgp);
	switch (sgState->upstream->GraftPrune){
		case GP_Forwarding:{
		//RPF'(S) Changes AND olist(S,G) is NULL
		//	Unicast routing or Assert state causes RPF'(S) to change, including changes to RPF_Interface(S).
		//	The Upstream(S,G) state machine MUST transition to the Pruned (P) state.
			if(outlist.size()==0){
				sgState->upstream->GraftPrune = GP_Pruned;
			}
		//RPF'(S) Changes AND olist(S,G) is non-NULL AND S NOT directly connected
		//	Unicast routing or Assert state causes RPF'(S) to change, including changes to RPF_Interface(S).
		//	The Upstream(S,G) state machine MUST transition to the AckPending (AP) state,
		//	unicast a Graft to the new RPF'(S), and set the GraftRetry Timer (GRT(S,G)) to Graft_Retry_Period.
			if(outlist.size()>0 && sgp.sourceIfaceAddr != m_mrib.find(sgp.sourceIfaceAddr)->second.nextAddr){
				sgState->upstream->GraftPrune = GP_AckPending;
				Ipv4Address destination = RPF_prime(sgp.sourceIfaceAddr,sgp.groupMulticastAddr);
				SendGraftUnicast(destination,sgp);
				sgState->upstream->SG_GRT.Cancel();
				sgState->upstream->SG_GRT.SetDelay(Seconds(Graft_Retry_Period));
				sgState->upstream->SG_GRT.Schedule();
			}
			break;
		}
		case GP_Pruned:{
			if(outlist.size()==0 && sgp.sourceIfaceAddr != m_mrib.find(sgp.sourceIfaceAddr)->second.nextAddr){
			//RPF'(S) Changes AND olist(S,G) == NULL AND S NOT directly connected
			//	Unicast routing or Assert state causes RPF'(S) to change, including changes to RPF_Interface(S).
			//	The Upstream(S,G) state machine stays in the Pruned (P) state and MUST cancel the PLT(S,G) timer.
				sgState->upstream->SG_PLT.Cancel();
			}
			if(outlist.size()>0 && sgp.sourceIfaceAddr != m_mrib.find(sgp.sourceIfaceAddr)->second.nextAddr){
			//RPF'(S) Changes AND olist(S,G) == non-NULL AND S NOT directly connected
			//	Unicast routing or Assert state causes RPF'(S) to change, including changes to RPF_Interface(S).
			//	The Upstream(S,G) state machine MUST cancel PLT(S,G), transition to the AckPending (AP) state,
			//	send a Graft unicast to the new RPF'(S), and set the GraftRetry Timer (GRT(S,G)) to Graft_Retry_Period.
				sgState->upstream->SG_PLT.Cancel();
				sgState->upstream->GraftPrune = GP_AckPending;
				Ipv4Address destination = RPF_prime(sgp.sourceIfaceAddr,sgp.groupMulticastAddr);
				SendGraftUnicast(destination,sgp);//TODO check
				sgState->upstream->SG_GRT.Cancel();
				sgState->upstream->SG_GRT.SetDelay(Seconds(Graft_Retry_Period));
				sgState->upstream->SG_GRT.Schedule();
			}
			break;
		}
		case GP_AckPending:{
			if(outlist.size()==0 && sgp.sourceIfaceAddr != m_mrib.find(sgp.sourceIfaceAddr)->second.nextAddr){
			//RPF'(S) Changes AND olist(S,G) == NULL AND S NOT directly connected
			//	Unicast routing or Assert state causes RPF'(S) to change, including changes to RPF_Interface(S).
			//	The Upstream(S,G) state machine MUST transition to the Pruned (P) state.
			//	The GraftRetry Timer (GRT(S,G)) MUST be canceled.
				sgState->upstream->GraftPrune = GP_Pruned;
				sgState->upstream->SG_GRT.Cancel();
			}
			if(outlist.size()>0 && sgp.sourceIfaceAddr != m_mrib.find(sgp.sourceIfaceAddr)->second.nextAddr){
				//RPF'(S) Changes AND olist(S,G) does not become NULL AND S NOT directly connected
				//	Unicast routing or Assert state causes RPF'(S) to change, including changes to RPF_Interface(S).
				//	The Upstream(S,G) state machine stays in the AckPending (AP) state.
				//	A Graft MUST be unicast to the new RPF'(S) and the GraftRetry Timer (GRT(S,G)) reset to Graft_Retry_Period.
				Ipv4Address target = RPF_prime(sgp.sourceIfaceAddr,sgp.groupMulticastAddr);
				SendGraftUnicast(target, sgp);//TODO check
				sgState->upstream->SG_GRT.Cancel();
				sgState->upstream->SG_GRT.SetDelay(Seconds(Graft_Retry_Period));
				sgState->upstream->SG_GRT.Schedule();
			}
			break;
		}
		default:{
			NS_LOG_ERROR("RPF prime changed: state not valid"<<sgState->upstream->GraftPrune);
		}
	}
}


void
MulticastRoutingProtocol::RecvJP (PIMHeader::JoinPruneMessage &jp, Ipv4Address sender, Ipv4Address receiver){
	NS_LOG_FUNCTION(this);
	NS_LOG_DEBUG("Node  "<<receiver <<" receives JP from "<<sender);
	uint32_t interface = GetReceivingInterface(receiver);
	uint16_t groups = jp.m_joinPruneMessage.m_numGroups;
	Time HoldTime = jp.m_joinPruneMessage.m_holdTime;
	NS_LOG_DEBUG("Groups = "<<groups<<", HoldTime = "<<HoldTime.GetSeconds());
	for(std::vector<PIMHeader::MulticastGroupEntry>::iterator iter = jp.m_multicastGroups.begin();
			iter != jp.m_multicastGroups.end(); iter++){///<Section 4.4.1.
		NS_LOG_DEBUG("Join = "<<iter->m_numberJoinedSources<<", Prune = "<<iter->m_numberPrunedSources);
		//JOIN sources' addresses
		for(std::vector<PIMHeader::EncodedSource>::iterator iterJoin = iter->m_joinedSourceAddrs.begin();
			iterJoin != iter->m_joinedSourceAddrs.end(); iterJoin++){
			std::set<uint32_t> joinList = olist(iterJoin->m_sourceAddress, iter->m_multicastGroupAddr.m_groupAddress);
			//Interfaces interested in JOIN
			for(std::set<uint32_t>::const_iterator iterList = joinList.begin(); iterList != joinList.end(); iterList++){
				uint32_t out_interface = *iterList;
				SourceGroupPair sgp (iterJoin->m_sourceAddress,iter->m_multicastGroupAddr.m_groupAddress);
				SourceGroupState *sgState = FindSourceGroupState(interface,sgp);
				sgState->upstream->SG_OT.Cancel();
				sgState->upstream->SG_OT.SetDelay(Seconds(Graft_Retry_Period));
				sgState->upstream->SG_OT.SetFunction(&MulticastRoutingProtocol::OTTimerExpire,this);
				sgState->upstream->SG_OT.SetArguments(sgp);
				// Upstream state machine
				RecvJoin(jp, sender, receiver, out_interface, *iterJoin, iter->m_multicastGroupAddr);
			}
		}
		//PRUNE
		for(std::vector<PIMHeader::EncodedSource>::iterator iterPrune = iter->m_prunedSourceAddrs.begin();
					iterPrune != iter->m_prunedSourceAddrs.end(); iterPrune++){
			//This timer is set when a Prune(S,G) is received on the upstream interface where olist(S,G) != NULL.
			//	When the timer expires, a Join(S,G) message is sent on the upstream interface.  This timer
			//	is normally set to t_override (see 4.8).
			std::set<uint32_t> pruneList = olist(iterPrune->m_sourceAddress, iter->m_multicastGroupAddr.m_groupAddress);
			for(std::set<uint32_t>::const_iterator iterList = pruneList.begin(); iterList != pruneList.end(); iterList++){
				uint32_t out_interface = *iterList;
				SourceGroupPair sgp (iterPrune->m_sourceAddress,iter->m_multicastGroupAddr.m_groupAddress);
				SourceGroupState *sgState = FindSourceGroupState(interface,sgp);
				sgState->upstream->SG_OT.Cancel();
				sgState->upstream->SG_OT.SetDelay(Seconds(Graft_Retry_Period));
				sgState->upstream->SG_OT.SetFunction(&MulticastRoutingProtocol::OTTimerExpire,this);
				sgState->upstream->SG_OT.SetArguments(jp.m_joinPruneMessage.m_upstreamNeighborAddr.m_unicastAddress,sgp);
				// Upstream state machine
				RecvPrune(jp, sender, receiver, out_interface, *iterPrune, iter->m_multicastGroupAddr);
			}
		}
	}
}

void //TOCHECK
MulticastRoutingProtocol::RecvPrune (PIMHeader::JoinPruneMessage &jp,Ipv4Address &sender, Ipv4Address &receiver, uint32_t &interface, const PIMHeader::EncodedSource &source,PIMHeader::EncodedGroup &group){
	NS_LOG_FUNCTION(this);
	NeighborhoodStatus *nstatus = FindNeighborhoodStatus(interface);
	nstatus->pruneHoldtime = Time(jp.m_joinPruneMessage.m_holdTime);
	// The node is not directly connected to S.
//	if(m_mrib.find(source.m_sourceAddress)->second.nextAddr != source.m_sourceAddress){ // TODO: is the condition just for Forwarding or even for the others?
	if(RPF_interface(source.m_sourceAddress)==interface){
		RecvPruneUpstream(jp, sender, receiver, interface, source, group);
	}
	else {
		RecvPruneDownstream(jp, sender, receiver, interface, source, group);
	}
//	}
}

//4.4.  PIM-DM Prune, Join, and Graft Messages
//	This section describes the generation and processing of PIM-DM Join, Prune, and Graft messages.
//	Prune messages are sent toward the upstream neighbor for S to indicate that traffic from S addressed to group G is not desired.
//	In the case of downstream routers A and B, where A wishes to continue receiving data and B does not, A will send
//	a Join in response to B's Prune to override the Prune.  This is the only situation in PIM-DM in which a Join message is used.
//	Finally, a Graft message is used to re-join a previously pruned branch to the delivery tree.
void //TODO: CHECK
MulticastRoutingProtocol::RecvPruneUpstream(PIMHeader::JoinPruneMessage &jp,Ipv4Address &sender, Ipv4Address &receiver, uint32_t &interface, const PIMHeader::EncodedSource &source,PIMHeader::EncodedGroup &group){
	NS_LOG_FUNCTION(this);
	SourceGroupState *sgState = FindSourceGroupState(interface,source.m_sourceAddress, group.m_groupAddress);
	// The node is not directly connected to S.
	switch (sgState->upstream->GraftPrune) {
		case GP_Forwarding:{
		//This event is only relevant if RPF_interface(S) is a shared medium.
		//	This router sees another router on RPF_interface(S) send a Prune(S,G).
		//	As this router is in Forwarding state, it must override the Prune after a short random interval.
		//	If OT(S,G) is not running, the router MUST set OT(S,G) to t_override seconds.
		//	The Upstream(S,G) state machine remains in Forwarding (F) state.
			if(m_mrib.find(source.m_sourceAddress)->second.nextAddr != source.m_sourceAddress && !sgState->upstream->SG_OT.IsRunning()){
				sgState->upstream->SG_OT.SetDelay(Seconds(t_override(interface)));
				sgState->upstream->SG_OT.Schedule();
				}
			break;
		}
		case GP_Pruned:{
		//A Prune(S,G) is seen on RPF_interface(S) to RPF'(S).
		//	The Upstream(S,G) state machine stays in the Pruned (P) state.
		//	The router MAY reset its PLT(S,G) to the value in the Holdtime field of the received message
		//	if it is greater than the current value of the PLT(S,G).
			if(RPF_prime(source.m_sourceAddress) == receiver && jp.m_joinPruneMessage.m_holdTime>sgState->upstream->SG_PLT.GetDelay()){
				sgState->upstream->SG_PLT.Cancel();
				sgState->upstream->SG_PLT.SetDelay(jp.m_joinPruneMessage.m_holdTime);
				sgState->upstream->SG_PLT.Schedule();
			}
			break;
		}
		case GP_AckPending:{
		//This event is only relevant if RPF_interface(S) is a shared medium.
		//	This router sees another router on RPF_interface(S) send a Prune(S,G).
		//	As this router is in AckPending (AP) state, it must override the Prune after a short random interval.
		//	If OT(S,G) is not running, the router MUST set OT(S,G) to t_override seconds.
		//	The Upstream(S,G) state machine remains in AckPending (AP) state.
			if(!sgState->upstream->SG_OT.IsRunning()){
				sgState->upstream->SG_OT.SetDelay(Seconds(t_override(interface)));
				sgState->upstream->SG_OT.Schedule();
			}
			break;
		}
		default:
			NS_LOG_ERROR("RecvPruneUpstream: Graft Prune state not valid"<<sgState->upstream->GraftPrune);
				break;
		}
//	}
}

void //TOCHECK
MulticastRoutingProtocol::RecvPruneDownstream (PIMHeader::JoinPruneMessage &jp,Ipv4Address &sender, Ipv4Address &receiver, uint32_t &interface, const PIMHeader::EncodedSource &source,PIMHeader::EncodedGroup &group){
	SourceGroupState *sgState = FindSourceGroupState(interface,source.m_sourceAddress, group.m_groupAddress);
	Ipv4Address current = GetLocalAddress(interface);
	switch (sgState->PruneState) {
		case Prune_NoInfo:{
			//Receive Prune(S,G): A Prune(S,G) is received on interface I with the upstream neighbor field
			//  set to the router's address on I.  The Prune(S,G) Downstream state machine on interface I
			//  MUST transition to the PrunePending (PP) state.  The PrunePending Timer (PPT(S,G,I))
			//  MUST be set to J/P_Override_Interval if the router has more than one neighbor on I.
			//  If the router has only one neighbor on interface I, then it SHOULD set the PPT(S,G,I) to zero,
		    //  effectively transitioning immediately to the Pruned (P) state.
			if(jp.m_joinPruneMessage.m_upstreamNeighborAddr.m_unicastAddress == current){
				NeighborhoodStatus *nstatus = FindNeighborhoodStatus(interface);
				Time JP_Override_Interval= nstatus->overrideInterval+nstatus->propagationDelay;
				sgState->PruneState = Prune_PrunePending;
				if(nstatus->neighbors.size() == 1){
					sgState->SG_PPT.SetDelay(Seconds(0));
				}
				else if(nstatus->neighbors.size()>1){
					sgState->SG_PPT.SetDelay(JP_Override_Interval);
				}
				if(!sgState->SG_PPT.IsRunning()){
					sgState->SG_PPT.Schedule();
				}
			}
			break;
		}
		case Prune_PrunePending:{
			break;
		}
		case Prune_Pruned:{
		//Receive Prune(S,G). A Prune(S,G) is received on the interface I with the upstream
		//	neighbor field set to the router's address on I.
		//	The Prune(S,G) Downstream state machine on interface I remains in the Pruned (P) state.
		//	The Prune Timer (PT(S,G,I)) SHOULD be reset to the holdtime contained in the Prune(S,G)
		//	message if it is greater than the current value.
			if(jp.m_joinPruneMessage.m_upstreamNeighborAddr.m_unicastAddress == current){
				if(jp.m_joinPruneMessage.m_holdTime >sgState->SG_PT.GetDelay()){
					sgState->SG_PT.Cancel();
					sgState->SG_PT.SetDelay(jp.m_joinPruneMessage.m_holdTime);
					sgState->SG_PT.Schedule();
				}
			}
			break;
		}
		default:
			NS_LOG_ERROR("RecvPruneDownstream: Prune state not valid"<<sgState->PruneState);
			break;
	}
	switch (sgState->AssertState){
		case  Assert_NoInfo:{
			//nothing
			break;
			}
		case Assert_Winner:{
			//nothing
			break;
			}
		case Assert_Loser:{
			//Receive Prune(S,G), Join(S,G), or Graft(S,G).
			//	A Prune(S,G), Join(S,G), or Graft(S,G) message was received on
			//	interface I with its upstream neighbor address set to the
			//	router's address on I.  The router MUST send an Assert(S,G) on
			//	the receiving interface I to initiate an Assert negotiation.  The
			//	Assert state machine remains in the Assert Loser(L) state.  If a
			//	Graft(S,G) was received, the router MUST respond with a GraftAck(S,G).
			if(jp.m_joinPruneMessage.m_upstreamNeighborAddr.m_unicastAddress == current){
				PIMHeader assertR;
				SourceGroupPair sgp(source.m_sourceAddress,group.m_groupAddress);
				ForgeAssertMessage(interface, assertR, sgp);
				assertR.GetAssertMessage().m_metricPreference = sgState->AssertWinner.metric_preference;
				assertR.GetAssertMessage().m_metric = sgState->AssertWinner.route_metric;
				Ptr<Packet> packet = Create<Packet> ();
				SendBroadPacketInterface(packet,assertR,interface);
			}
			//An Assert loser that receives a Prune(S,G), Join(S,G), or
			//  Graft(S,G) directed to it initiates a new Assert negotiation so
			//  that the downstream router can correct its RPF'(S).
			break;
			}
		default:{
			NS_LOG_ERROR("RecvPruneDownstream: Assert State not valid"<<sgState->AssertState);
		}
	}
}

void // TOCHECK
MulticastRoutingProtocol::RecvJoin(PIMHeader::JoinPruneMessage &jp,Ipv4Address &sender, Ipv4Address &receiver, uint32_t &interface, const PIMHeader::EncodedSource &source,PIMHeader::EncodedGroup &group){
	NS_LOG_FUNCTION(this);
	if(RPF_interface(source.m_sourceAddress)==interface){
		RecvJoinUpstream(jp, sender, receiver, interface, source, group);
	}
	else {
		RecvJoinDownstream(jp, sender, receiver, interface, source, group);
	}
}

void // TOCHECK
MulticastRoutingProtocol::RecvJoinUpstream(PIMHeader::JoinPruneMessage &jp,Ipv4Address &sender, Ipv4Address &receiver, uint32_t &interface, const PIMHeader::EncodedSource &source,PIMHeader::EncodedGroup &group){
	SourceGroupState *sgState = FindSourceGroupState(interface,source.m_sourceAddress, group.m_groupAddress);
		switch (sgState->upstream->GraftPrune) {
			case GP_Forwarding:{
			//This event is only relevant if RPF_interface(S) is a shared medium.
			//	This router sees another router on RPF_interface(S) send a Join(S,G) to RPF'(S,G).
			//	If the OT(S,G) is running, then it means that the router had scheduled a Join to override a previously received Prune.
			//	Another router has responded more quickly with a Join, so the local router SHOULD cancel its OT(S,G), if it is running.
			//	The Upstream(S,G) state machine remains in the Forwarding (F) state.
				if(sender == RPF_prime(source.m_sourceAddress, group.m_groupAddress) && sgState->upstream->SG_OT.IsRunning()){
					sgState->upstream->SG_OT.Cancel();
				}
				break;
			}
			case GP_Pruned:{
			//nothing
				break;
			}
			case GP_AckPending:{
			//This event is only relevant if RPF_interface(S) is a shared medium.
			//	This router sees another router on RPF_interface(S) send a Join(S,G) to RPF'(S,G).
			//	If the OT(S,G) is running, then it means that the router had scheduled a Join to override a previously received Prune.
			//	Another router has responded more quickly with a Join, so the local router SHOULD cancel its OT(S,G), if it is running.
			//	The Upstream(S,G) state machine remains in the AckPending (AP) state.
				if(receiver == RPF_prime(source.m_sourceAddress) && sgState->upstream->SG_OT.IsRunning()){
					sgState->upstream->SG_OT.Cancel();
				}
				break;
			}
			default:
				NS_LOG_ERROR("RecvJoinUpstream: Graft Prune state not valid"<<sgState->upstream->GraftPrune);
					break;
	}
}

void // TOCHECK
MulticastRoutingProtocol::RecvJoinDownstream(PIMHeader::JoinPruneMessage &jp,Ipv4Address &sender, Ipv4Address &receiver, uint32_t &interface, const PIMHeader::EncodedSource &source,PIMHeader::EncodedGroup &group){
		SourceGroupState *sgState = FindSourceGroupState(interface,source.m_sourceAddress, group.m_groupAddress);
		Ipv4Address current = GetLocalAddress(interface);
		switch (sgState->PruneState) {
			case Prune_NoInfo:{
				break;
			}
			case Prune_PrunePending:{
				//Receive Join(S,G): A Join(S,G) is received on interface I with the upstream neighbor
				//	field set to the router's address on I.  The Prune(S,G) Downstream state machine
				//	on interface I MUST transition to the NoInfo (NI) state.
				//	The PrunePending Timer (PPT(S,G,I)) MUST be cancelled.
				if(jp.m_joinPruneMessage.m_upstreamNeighborAddr.m_unicastAddress == current){
					sgState->PruneState = Prune_NoInfo;
					sgState->SG_PPT.Cancel();
				}
				break;
			}
			case Prune_Pruned:{
			//Receive Join(S,G). A Join(S,G) is received on the interface I with the upstream
			//	neighbor field set to the router's address on I.  The Prune(S,G) downstream state
			//	machine on interface I MUST transition to the NoInfo (NI) state.
			//	The Prune Timer (PT(S,G,I)) MUST be cancelled.
			//	TODO: The router MUST evaluate any possible transitions in the Upstream(S,G) state machine.
				if(jp.m_joinPruneMessage.m_upstreamNeighborAddr.m_unicastAddress == current){
					sgState->PruneState = Prune_NoInfo;
					sgState->SG_PPT.Cancel();
				}
				break;
			}
			default:{
				NS_LOG_ERROR("RecvPruneDownstream: Prune state not valid"<<sgState->PruneState);
				break;
			}
		}
		switch (sgState->AssertState){
			case  Assert_NoInfo:{
				//nothing
				break;
				}
			case Assert_Winner:{
				//nothing
				break;
			}
			case Assert_Loser:{
				//Receive Prune(S,G), Join(S,G), or Graft(S,G).
				//	A Prune(S,G), Join(S,G), or Graft(S,G) message was received on
				//	interface I with its upstream neighbor address set to the
				//	router's address on I.  The router MUST send an Assert(S,G) on
				//	the receiving interface I to initiate an Assert negotiation.  The
				//	Assert state machine remains in the Assert Loser(L) state.  If a
				//	Graft(S,G) was received, the router MUST respond with a GraftAck(S,G).
				if(jp.m_joinPruneMessage.m_upstreamNeighborAddr.m_unicastAddress == current){
					PIMHeader assertR;
					SourceGroupPair sgp(source.m_sourceAddress,group.m_groupAddress);
					ForgeAssertMessage(interface,assertR,sgp);
					assertR.GetAssertMessage().m_metricPreference = sgState->AssertWinner.metric_preference;
					assertR.GetAssertMessage().m_metric = sgState->AssertWinner.route_metric;
					Ptr<Packet> packet = Create<Packet> ();
					SendBroadPacketInterface(packet,assertR,interface);
				}
				//An Assert loser that receives a Prune(S,G), Join(S,G), or
				//  Graft(S,G) directed to it initiates a new Assert negotiation so
				//  that the downstream router can correct its RPF'(S).
				break;
			}
			default:{
				NS_LOG_ERROR("RecvJoinDownstream: Assert State not valid"<<sgState->AssertState);
			}
		}
	}


void
MulticastRoutingProtocol::RecvAssert (PIMHeader::AssertMessage &assert, Ipv4Address sender, Ipv4Address receiver){
	NS_LOG_FUNCTION(this);
	uint32_t interface = GetReceivingInterface(sender);
	SourceGroupState *sgState = FindSourceGroupState(interface,assert.m_sourceAddr.m_unicastAddress,assert.m_multicastGroupAddr.m_groupAddress);
	switch (sgState->AssertState){
			case  Assert_NoInfo:{
			//Receive Inferior (Assert OR State Refresh) AND CouldAssert(S,G,I)==TRUE.
			//   An Assert or State Refresh is received for (S,G) that is inferior
			//   to our own assert metric on interface I. The Assert state machine
			//   MUST transition to the "I am Assert Winner" state, send an Assert(S,G)
			//   to interface I, store its own address and metric as the Assert Winner,
			//   and set the Assert Timer (AT(S,G,I)) to Assert_Time.
				struct AssertMetric received (assert.m_metricPreference,assert.m_metric, receiver);
				if(my_assert_metric(assert.m_sourceAddr.m_unicastAddress, assert.m_multicastGroupAddr.m_groupAddress, interface) > received
						&& CouldAssert(assert.m_sourceAddr.m_unicastAddress, assert.m_multicastGroupAddr.m_groupAddress, interface)){
					sgState->AssertState = Assert_Winner;
					PIMHeader assertR;
					SourceGroupPair sgp(assert.m_sourceAddr.m_unicastAddress, assert.m_multicastGroupAddr.m_groupAddress);
					ForgeAssertMessage(interface, assertR, sgp);
					UpdateAssertWinner(sgState,assert.m_sourceAddr.m_unicastAddress);
					Ptr<Packet> packet = Create<Packet> ();
					SendBroadPacketInterface(packet,assertR,interface);
					if(sgState->SG_AT.IsRunning())
						sgState->SG_AT.Cancel();
					sgState->SG_AT.SetDelay(Seconds(Assert_Time));
					sgState->SG_AT.Schedule();
				}
				else{
					//Receive Preferred Assert or State Refresh.
					//	The received Assert or State Refresh has a better metric than
					//	this router's, and therefore the Assert state machine MUST
					//	transition to the "I am Assert Loser" state and store the Assert
					//	Winner's address and metric.  If the metric was received in an
					//	Assert, the router MUST set the Assert Timer (AT(S,G,I)) to
					//	Assert_Time.  If the metric was received in a State Refresh, the
					//	router MUST set the Assert Timer (AT(S,G,I)) to three times the
					//	received State Refresh Interval.
					sgState->AssertState = Assert_Loser;
					UpdateAssertWinner(sgState, assert.m_metricPreference, assert.m_metric, sender);
					if(sgState->SG_AT.IsRunning())
						sgState->SG_AT.Cancel();
					sgState->SG_AT.SetDelay(Seconds(Assert_Time));
					sgState->SG_AT.Schedule();
					if(CouldAssert(assert.m_sourceAddr.m_unicastAddress,assert.m_multicastGroupAddr.m_groupAddress,interface)){
						//If CouldAssert(S,G,I) == TRUE,
						//	the router MUST also multicast a Prune(S,G) to the Assert winner
						//	with a Prune Hold Time equal to the Assert Timer and
						//  TODO: evaluate any changes in its Upstream(S,G) state machine.
						PIMHeader::MulticastGroupEntry mge;
						AddMulticastGroupSourcePrune(mge, ForgeEncodedSource(assert.m_sourceAddr.m_unicastAddress));
						PIMHeader prune;
						ForgePruneMessage(prune);
						CreateMulticastGroupEntry(prune,mge,ForgeEncodedGroup(assert.m_multicastGroupAddr.m_groupAddress));
						prune.GetJoinPruneMessage().m_joinPruneMessage.m_upstreamNeighborAddr.m_unicastAddress = sender;
						prune.GetJoinPruneMessage().m_joinPruneMessage.m_holdTime = sgState->SG_AT.GetDelay();
						Ptr<Packet> packet = Create<Packet> ();
						SendPacket(packet, prune, sender);
					}
				}
				break;
				}
			case Assert_Winner:{
				struct AssertMetric received (assert.m_metricPreference,assert.m_metric, receiver);
				if(my_assert_metric(assert.m_sourceAddr.m_unicastAddress,assert.m_multicastGroupAddr.m_groupAddress,RPF_interface(sender)) > received){
				//Receive Inferior Assert or State Refresh
				//	An (S,G) Assert is received containing a metric for S that is
				//	worse than this router's metric for S.  Whoever sent the Assert
				//	is in error.  The router MUST send an Assert(S,G) to interface I
				//	and reset the Assert Timer (AT(S,G,I)) to Assert_Time.
					PIMHeader assertR;
					SourceGroupPair sgp(assert.m_sourceAddr.m_unicastAddress,assert.m_multicastGroupAddr.m_groupAddress);
					ForgeAssertMessage(interface, assertR, sgp);
					assertR.GetAssertMessage().m_metricPreference = sgState->AssertWinner.metric_preference;
					assertR.GetAssertMessage().m_metric = sgState->AssertWinner.route_metric;
					Ptr<Packet> packet = Create<Packet> ();
					SendBroadPacketInterface(packet,assertR,interface);
					sgState->SG_AT.Cancel();
					sgState->SG_AT.SetDelay(Seconds(Assert_Time));
					sgState->SG_AT.Schedule();
				}
				else{
					//Receive Preferred Assert or State Refresh.
					//	An (S,G) Assert or State Refresh is received that has a better
					//	metric than this router's metric for S on interface I. The
					//	Assert state machine MUST transition to "I am Assert Loser" state
					//	and store the new Assert Winner's address and metric.  If the
					//	metric was received in an Assert, the router MUST set the Assert
					//	Timer (AT(S,G,I)) to Assert_Time.  If the metric was received in
					//	a State Refresh, the router MUST set the Assert Timer (AT(S,G,I))
					//	to three times the State Refresh Interval.
					sgState->AssertState = Assert_Loser;
					sgState->AssertWinner.metric_preference = assert.m_metricPreference;
					sgState->AssertWinner.route_metric = assert.m_metric;
					sgState->AssertWinner.ip_address = receiver;
					sgState->SG_AT.SetDelay(Seconds(Assert_Time));
					sgState->SG_AT.Cancel();
					sgState->SG_AT.Schedule();
					//The router MUST also
					//	multicast a Prune(S,G) to the Assert winner, with a Prune Hold
					//	Time equal to the Assert Timer, and evaluate any changes in its
					//	Upstream(S,G) state machine.
					PIMHeader::MulticastGroupEntry mge;
					AddMulticastGroupSourcePrune(mge,ForgeEncodedSource(assert.m_sourceAddr.m_unicastAddress));
					PIMHeader msg;
					Ipv4Address target = receiver;
					ForgePruneMessage(msg);
					CreateMulticastGroupEntry(msg,mge,ForgeEncodedGroup(assert.m_multicastGroupAddr.m_groupAddress));
					msg.GetJoinPruneMessage().m_joinPruneMessage.m_upstreamNeighborAddr.m_unicastAddress = target;//TODO check
					msg.GetJoinPruneMessage().m_joinPruneMessage.m_holdTime = sgState->SG_AT.GetDelay();
					Ptr<Packet> packet = Create<Packet> ();
					SendPacket(packet,msg,target);
					}
				break;
			}
			case Assert_Loser:{
			//Receive Inferior Assert or State Refresh from Current Winner
			//   An Assert or State Refresh is received from the current Assert
			//   winner that is worse than this router's metric for S (typically,
			//   the winner's metric became worse).  The Assert state machine MUST
			//   transition to NoInfo (NI) state and cancel AT(S,G,I).  The router
			//   MUST delete the previous Assert Winner's address and metric and
			//   evaluate any possible transitions to its Upstream(S,G) state
			//   machine.  TODO: Usually this router will eventually re-assert and win
			//   when data packets from S have started flowing again.
				struct AssertMetric received (assert.m_metricPreference,assert.m_metric, receiver);
				if(my_assert_metric(assert.m_sourceAddr.m_unicastAddress,assert.m_multicastGroupAddr.m_groupAddress,RPF_interface(sender)) > received){
					sgState->AssertState = Assert_NoInfo;
					sgState->SG_AT.Cancel();
					sgState->AssertWinner.metric_preference = 0XFFFFFFFF;
					sgState->AssertWinner.route_metric = 0XFFFFFFFF;
					sgState->AssertWinner.ip_address = Ipv4Address("255.255.255.255");
				}
				else{
					//Receive Preferred Assert or State Refresh
					//	An Assert or State Refresh is received that has a metric better
					//	than or equal to that of the current Assert winner.  The Assert
					//	state machine remains in Loser (L) state.  If the metric was
					//	received in an Assert, the router MUST set the Assert Timer
					//	(AT(S,G,I)) to Assert_Time.  If the metric was received in a
					//	State Refresh, the router MUST set the Assert Timer (AT(S,G,I))
					//	to three times the received State Refresh Interval.  If the
					//	metric is better than the current Assert Winner, the router MUST
					//	store the address and metric of the new Assert Winner, and if
					//	CouldAssert(S,G,I) == TRUE, the router MUST multicast a
					//	Prune(S,G) to the new Assert winner.
					sgState->AssertState = Assert_Loser;
					sgState->AssertWinner.metric_preference = assert.m_metricPreference;
					sgState->AssertWinner.route_metric = assert.m_metric;
					sgState->AssertWinner.ip_address = receiver;
					sgState->SG_AT.SetDelay(Seconds(Assert_Time));
					sgState->SG_AT.Cancel();
					sgState->SG_AT.Schedule();
					if(CouldAssert(assert.m_sourceAddr.m_unicastAddress,assert.m_multicastGroupAddr.m_groupAddress,interface)){
						PIMHeader::MulticastGroupEntry mge;
						AddMulticastGroupSourcePrune(mge,ForgeEncodedSource(assert.m_sourceAddr.m_unicastAddress));
						PIMHeader prune;
						Ipv4Address target = receiver;
						ForgePruneMessage(prune);
						CreateMulticastGroupEntry(prune,mge,ForgeEncodedGroup(assert.m_multicastGroupAddr.m_groupAddress));
						prune.GetJoinPruneMessage().m_joinPruneMessage.m_upstreamNeighborAddr.m_unicastAddress = target;//TODO check
						prune.GetJoinPruneMessage().m_joinPruneMessage.m_holdTime = sgState->SG_AT.GetDelay();
						Ptr<Packet> packet = Create<Packet> ();
						SendPacket(packet,prune,target);
					}
				}
				break;
			}
			default:{
				NS_LOG_ERROR("RecvAssert: Assert State not valid"<<sgState->AssertState);
			}
		}
}

void
MulticastRoutingProtocol::RecvStateRefresh(PIMHeader::StateRefreshMessage &refresh, Ipv4Address sender, Ipv4Address receiver){
	NS_LOG_FUNCTION(this);
	NeighborState tmp (sender, receiver);
	uint32_t interface = GetReceivingInterface(receiver);
	NeighborState *ns = FindNeighborState(interface,tmp);
	SourceGroupPair sgp (refresh.m_sourceAddr.m_unicastAddress,refresh.m_multicastGroupAddr.m_groupAddress);
	SourceGroupState *sgState = FindSourceGroupState(interface,sgp);
	uint32_t rpf_prime_interface = RPF_interface(RPF_prime(refresh.m_sourceAddr.m_unicastAddress));
	if(rpf_prime_interface == interface && sgState->upstream){
		switch (sgState->upstream->GraftPrune) {
			case GP_Forwarding:{ //OK
				// The Upstream(S,G) state machine remains in a Forwarding state. If the received State Refresh has the Prune Indicator bit set to
				//	   one, this router must override the upstream router's Prune state after a short random interval.
				Simulator::Schedule (Seconds(UniformVariable().GetValue(0,t_shorter)), &MulticastRoutingProtocol::SetPruneState, this, interface, sgp, Prune_Pruned);
//				Simulator::Schedule (delay, &MulticastRoutingProtocol::SendNeighHello, this, interface, sender);
				//     If OT(S,G) is not running and the Prune Indicator bit equals one, the router MUST set OT(S,G) to t_override seconds.
				if(refresh.m_P == 1 && !sgState->upstream->SG_OT.IsRunning()){
					sgState->upstream->SG_OT.Cancel();
					sgState->upstream->SG_OT.SetDelay(Seconds(t_override(interface)));
					sgState->upstream->SG_OT.Schedule();
				}
				break;
			}
			case GP_Pruned:{//OK
			//The Upstream(S,G) state machine remains in a Pruned state. If the State Refresh has its Prune Indicator bit set to zero and
			//	   PLT(S,G) is not running, a Prune(S,G) MUST be sent to RPF'(S), and the PLT(S,G) MUST be set to t_limit.
			//	   If the State Refresh has its Prune Indicator bit set to one, the router MUST reset PLT(S,G) to t_limit.
				if(refresh.m_P==0 && !sgState->upstream->SG_PLT.IsRunning()){
						SendPruneUnicast(RPF_prime(refresh.m_sourceAddr.m_unicastAddress), sgp);
						sgState->upstream->SG_PLT.SetDelay(Seconds(t_limit));
						sgState->upstream->SG_PLT.Schedule();
					}
				else if(refresh.m_P){
					sgState->upstream->SG_PLT.Cancel();
					sgState->upstream->SG_PLT.SetDelay(Seconds(t_limit));
					sgState->upstream->SG_PLT.Schedule();
				}
				break;
			}
			case GP_AckPending:{ //OK
			//The Upstream(S,G) state machine remains in an AckPending state.
			//   The router must override the upstream router's Prune state after a short random interval.
			//   If OT(S,G) is not running and the Prune Indicator bit equals one, the router MUST set OT(S,G) to t_override seconds.
				if(refresh.m_P){//TODO CHECK the Schedule 4.4.1.3.
					Simulator::Schedule (Seconds(UniformVariable().GetValue(0,t_shorter)), &MulticastRoutingProtocol::SetPruneState, this, interface, sgp, Prune_Pruned);
					if(!sgState->upstream->SG_OT.IsRunning()){
						sgState->upstream->SG_OT.SetDelay(Seconds(t_override(interface)));
						sgState->upstream->SG_OT.Schedule();
					}
				}
				if(refresh.m_P == 0){
					sgState->upstream->SG_GRT.Cancel();
					sgState->upstream->GraftPrune = GP_Forwarding;
				}
				break;
			}
			default:
				NS_LOG_ERROR("RecvStateRefresh: Graft Prune state not valid"<<sgState->upstream->GraftPrune);
					break;
			}
	}
	//TODO: Upon startup, a router MAY use any State Refresh messages received  within Hello_Period of its first Hello message on an interface to establish state information.
	for(uint32_t i = 0; i < m_ipv4->GetNInterfaces();i++){
		SourceGroupState *sgStateB = FindSourceGroupState(i,sgp);
		//	The State Refresh source will be the RPF'(S), and Prune status for all interfaces will be set according to the Prune Indicator bit in the State Refresh message.
		if (i == rpf_prime_interface){
			//	If the Prune Indicator is set, the router SHOULD set the PruneLimitTimer to Prune_Holdtime ...
			if (refresh.m_P){
				sgStateB->upstream->SG_PLT.SetDelay(Seconds(PruneHoldTime));
			}
			continue;
		}
		//	.... and set the PruneTimer on all downstream interfaces to
		//	the State Refresh's Interval times two.  The router SHOULD then propagate the State Refresh as described in Section 4.5.1.
		sgStateB->PruneState = (refresh.m_P ? Prune_Pruned: Prune_NoInfo);
		if(refresh.m_P){
			sgStateB->upstream->SG_PLT.SetDelay(Seconds(PruneHoldTime));
			sgStateB->SG_PT.SetDelay(Seconds(2 * StateRefreshInterval));
		}
	}
	switch (sgState->AssertState){
		case  Assert_NoInfo:{
			//Receive Inferior (Assert OR State Refresh) AND CouldAssert(S,G,I)==TRUE.
			//   An Assert or State Refresh is received for (S,G) that is inferior
			//   to our own assert metric on interface I. The Assert state machine
			//   MUST transition to the "I am Assert Winner" state, send an Assert(S,G)
			//   to interface I, store its own address and metric as the Assert Winner,
			//   and set the Assert Timer (AT(S,G,I)) to Assert_Time.
				struct AssertMetric received (refresh.m_metricPreference,refresh.m_metric, refresh.m_originatorAddr.m_unicastAddress);
				if(my_assert_metric(refresh.m_sourceAddr.m_unicastAddress,refresh.m_multicastGroupAddr.m_groupAddress,interface) > received
						&& CouldAssert(refresh.m_sourceAddr.m_unicastAddress,refresh.m_multicastGroupAddr.m_groupAddress,interface)){
					sgState->AssertState = Assert_Winner;
					PIMHeader assertR;
					ForgeAssertMessage(interface, assertR, sgp);
					sgState->AssertWinner.metric_preference = m_mrib.find(refresh.m_sourceAddr.m_unicastAddress)->second.metricPreference;
					sgState->AssertWinner.route_metric = m_mrib.find(refresh.m_sourceAddr.m_unicastAddress)->second.route_metric;
					sgState->AssertWinner.ip_address = GetLocalAddress(interface);
					Ptr<Packet> packet = Create<Packet> ();
					SendBroadPacketInterface(packet,assertR,interface);
					sgState->SG_AT.SetDelay(Seconds(Assert_Time));
					sgState->SG_AT.Schedule();
				}
				else{
					//Receive Preferred Assert or State Refresh.
					//	The received Assert or State Refresh has a better metric than
					//	this router's, and therefore the Assert state machine MUST
					//	transition to the "I am Assert Loser" state and store the Assert
					//	Winner's address and metric.  If the metric was received in an
					//	Assert, the router MUST set the Assert Timer (AT(S,G,I)) to
					//	Assert_Time.  If the metric was received in a State Refresh, the
					//	router MUST set the Assert Timer (AT(S,G,I)) to three times the
					//	received State Refresh Interval.
					sgState->AssertState = Assert_Loser;
					sgState->AssertWinner.metric_preference = refresh.m_metricPreference;
					sgState->AssertWinner.route_metric = refresh.m_metric;
					sgState->AssertWinner.ip_address = refresh.m_originatorAddr.m_unicastAddress;
					sgState->SG_AT.SetDelay(Seconds(3*refresh.m_interval));
					sgState->SG_AT.Cancel();
					sgState->SG_AT.Schedule();
					if(CouldAssert(refresh.m_sourceAddr.m_unicastAddress,refresh.m_multicastGroupAddr.m_groupAddress,interface)){
						//If CouldAssert(S,G,I) == TRUE,
						//	the router MUST also multicast a Prune(S,G) to the Assert winner
						//	with a Prune Hold Time equal to the Assert Timer and evaluate any
						//	changes in its Upstream(S,G) state machine.
						PIMHeader::MulticastGroupEntry mge;
						AddMulticastGroupSourcePrune(mge,ForgeEncodedSource(refresh.m_sourceAddr.m_unicastAddress));
						PIMHeader msg;
						Ipv4Address target = refresh.m_originatorAddr.m_unicastAddress;
						ForgePruneMessage(msg);
						CreateMulticastGroupEntry(msg,mge,ForgeEncodedGroup(refresh.m_multicastGroupAddr.m_groupAddress));
						msg.GetJoinPruneMessage().m_joinPruneMessage.m_upstreamNeighborAddr.m_unicastAddress = target;//TODO check
						msg.GetJoinPruneMessage().m_joinPruneMessage.m_holdTime = sgState->SG_AT.GetDelay();
						Ptr<Packet> packet = Create<Packet> ();
						SendPacket(packet,msg,target);
					}
				}
				break;
				}
		case Assert_Winner:{
			//Receive Inferior Assert or State Refresh
			//	An (S,G) Assert is received containing a metric for S that is
			//	worse than this router's metric for S.  Whoever sent the Assert
			//	is in error.  The router MUST send an Assert(S,G) to interface I
			//	and reset the Assert Timer (AT(S,G,I)) to Assert_Time.
			struct AssertMetric received (refresh.m_metricPreference,refresh.m_metric, refresh.m_originatorAddr.m_unicastAddress);
			if(my_assert_metric(refresh.m_sourceAddr.m_unicastAddress,refresh.m_multicastGroupAddr.m_groupAddress,interface) > received){
				PIMHeader assertR;
				ForgeAssertMessage(interface, assertR, sgp);
				assertR.GetAssertMessage().m_metricPreference = sgState->AssertWinner.metric_preference;
				assertR.GetAssertMessage().m_metric = sgState->AssertWinner.route_metric;
				Ptr<Packet> packet = Create<Packet> ();
				SendBroadPacketInterface(packet,assertR,interface);
				sgState->SG_AT.Cancel();
				sgState->SG_AT.SetDelay(Seconds(Assert_Time));
				sgState->SG_AT.Schedule();
			}
			else{
				//Receive Preferred Assert or State Refresh.
				//	An (S,G) Assert or State Refresh is received that has a better
				//	metric than this router's metric for S on interface I. The
				//	Assert state machine MUST transition to "I am Assert Loser" state
				//	and store the new Assert Winner's address and metric.  If the
				//	metric was received in an Assert, the router MUST set the Assert
				//	Timer (AT(S,G,I)) to Assert_Time.  If the metric was received in
				//	a State Refresh, the router MUST set the Assert Timer (AT(S,G,I))
				//	to three times the State Refresh Interval.
				sgState->AssertState= Assert_Loser;
				sgState->AssertWinner.metric_preference = refresh.m_metricPreference;
				sgState->AssertWinner.route_metric = refresh.m_metric;
				sgState->AssertWinner.ip_address = refresh.m_originatorAddr.m_unicastAddress;
				sgState->SG_AT.Cancel();
				sgState->SG_AT.SetDelay(Seconds(3*RefreshInterval));
				sgState->SG_AT.Schedule();
				//The router MUST also
				//	multicast a Prune(S,G) to the Assert winner, with a Prune Hold
				//	Time equal to the Assert Timer, and evaluate any changes in its
				//	Upstream(S,G) state machine.
				PIMHeader::MulticastGroupEntry mge;
				AddMulticastGroupSourcePrune(mge,ForgeEncodedSource(refresh.m_sourceAddr.m_unicastAddress));
				PIMHeader prune;
				Ipv4Address target = refresh.m_originatorAddr.m_unicastAddress;
				ForgePruneMessage(prune);
				CreateMulticastGroupEntry(prune,mge,ForgeEncodedGroup(refresh.m_multicastGroupAddr.m_groupAddress));
				prune.GetJoinPruneMessage().m_joinPruneMessage.m_upstreamNeighborAddr.m_unicastAddress = target;//TODO check
				prune.GetJoinPruneMessage().m_joinPruneMessage.m_holdTime = sgState->SG_AT.GetDelay();
				Ptr<Packet> packet = Create<Packet> ();
				SendPacket(packet,prune,target);
			}
			break;
			}
		case Assert_Loser:{
			//Receive Inferior Assert or State Refresh from Current Winner.
			//   An Assert or State Refresh is received from the current Assert
			//   winner that is worse than this router's metric for S (typically,
			//   the winner's metric became worse).  The Assert state machine MUST
			//   transition to NoInfo (NI) state and cancel AT(S,G,I).  The router
			//   MUST delete the previous Assert Winner's address and metric and
			//   evaluate any possible transitions to its Upstream(S,G) state
			//   machine.  Usually this router will eventually re-assert and win
			//   when data packets from S have started flowing again.
			struct AssertMetric received (refresh.m_metricPreference,refresh.m_metric, refresh.m_originatorAddr.m_unicastAddress);
			if(my_assert_metric(refresh.m_sourceAddr.m_unicastAddress,refresh.m_multicastGroupAddr.m_groupAddress,interface) > received){
				sgState->AssertState = Assert_NoInfo;
				sgState->SG_AT.Cancel();
				sgState->AssertWinner.metric_preference = 0XFFFFFFFF;
				sgState->AssertWinner.route_metric = 0XFFFFFFFF;
				sgState->AssertWinner.ip_address = Ipv4Address("255.255.255.255");
			}
			else{
			//Receive Preferred Assert or State Refresh.
			//	An Assert or State Refresh is received that has a metric better
			//	than or equal to that of the current Assert winner.  The Assert
			//	state machine remains in Loser (L) state.  If the metric was
			//	received in an Assert, the router MUST set the Assert Timer
			//	(AT(S,G,I)) to Assert_Time.  If the metric was received in a
			//	State Refresh, the router MUST set the Assert Timer (AT(S,G,I))
			//	to three times the received State Refresh Interval.  If the
			//	metric is better than the current Assert Winner, the router MUST
			//	store the address and metric of the new Assert Winner,
				sgState->SG_AT.SetDelay(Seconds(3*refresh.m_interval));
				sgState->SG_AT.Cancel();
				sgState->SG_AT.Schedule();
				sgState->AssertWinner.metric_preference = refresh.m_metricPreference;
				sgState->AssertWinner.route_metric = refresh.m_metric;
				sgState->AssertWinner.ip_address = refresh.m_originatorAddr.m_unicastAddress;

				if(CouldAssert(refresh.m_sourceAddr.m_unicastAddress,refresh.m_multicastGroupAddr.m_groupAddress,interface)){
					//	and if CouldAssert(S,G,I) == TRUE, the router MUST multicast a
					//	Prune(S,G) to the new Assert winner.
					PIMHeader::MulticastGroupEntry mge;
					AddMulticastGroupSourcePrune(mge, ForgeEncodedSource(refresh.m_sourceAddr.m_unicastAddress));
					PIMHeader prune;
					Ipv4Address target = refresh.m_originatorAddr.m_unicastAddress;
					ForgePruneMessage(prune);
					CreateMulticastGroupEntry(prune,mge,ForgeEncodedGroup(refresh.m_multicastGroupAddr.m_groupAddress));
					prune.GetJoinPruneMessage().m_joinPruneMessage.m_upstreamNeighborAddr.m_unicastAddress = target;//TODO check
					prune.GetJoinPruneMessage().m_joinPruneMessage.m_holdTime = sgState->SG_AT.GetDelay();
					Ptr<Packet> packet = Create<Packet> ();
					SendPacket(packet,prune,target);
				}
			}
			break;
		}
		default:{
			NS_LOG_ERROR("RecvStateRefresh: Assert State not valid"<<sgState->AssertState);
		}
	}
}

void
MulticastRoutingProtocol::ForwardingStateRefresh(PIMHeader::StateRefreshMessage &refresh,Ipv4Address sender, Ipv4Address receiver){
	//4.5.1.  Forwarding of State Refresh Messages.
	//	When a State Refresh message, SRM, is received, it is forwarded according to the following pseudo-code.
	uint32_t iif = GetReceivingInterface(sender);
	if (iif != RPF_interface(refresh.m_sourceAddr.m_unicastAddress))
		return;
	//srcaddr(SRM) returns the source address contained in the network
	//	protocol (e.g., IPv4) header of the State Refresh Message, SRM.
	if (RPF_prime(refresh.m_sourceAddr.m_unicastAddress,refresh.m_multicastGroupAddr.m_groupAddress) != sender)//source=sender here? refresh.m_sourceAddr.m_unicastAddress
		return;
	//StateRefreshRateLimit(S,G) is TRUE if the time elapsed since the last received StateRefresh(S,G)
	//	is less than the configured RefreshLimitInterval.
	if (StateRefreshRateLimit(refresh.m_sourceAddr.m_unicastAddress,refresh.m_multicastGroupAddr.m_groupAddress))
		return;
	std::set<uint32_t> nbrs = pim_nbrs();
	for(std::set<uint32_t>::iterator i_nbrs = nbrs.begin(); i_nbrs != nbrs.end() ; i_nbrs++){
		//TTL(SRM) returns the TTL contained in the State Refresh Message, SRM.
		//	This is different from the TTL contained in the IP header.
		//
		//Threshold(I) returns the minimum TTL that a packet must have before it can be transmitted on interface I.
		if (refresh.m_ttl == 0 || (refresh.m_ttl - 1) < Threshold(I))
			continue;     /* Out of TTL, skip this interface */
		//Boundary(I,G) is TRUE if an administratively scoped boundary for group G is configured on interface I.
		if (boundary(*i_nbrs,refresh.m_multicastGroupAddr.m_groupAddress))
			continue;     /* This interface is scope boundary, skip it */
		if (*i_nbrs == iif)
			continue;     /* This is the incoming interface, skip it */
		if (lost_assert(refresh.m_sourceAddr.m_unicastAddress,refresh.m_multicastGroupAddr.m_groupAddress,*i_nbrs))
			continue;     /* Let the Assert Winner do State Refresh */
		// Create a new message
		PIMHeader refreshFRW;
		refreshFRW.GetStateRefreshMessage() = refresh;
		PIMHeader::StateRefreshMessage SRMP = refreshFRW.GetStateRefreshMessage();
		// Copy SRM to SRMP';   /* Make a copy of SRM to forward */
		std::set<uint32_t> prunez = prunes(refresh.m_sourceAddr.m_unicastAddress,refresh.m_multicastGroupAddr.m_groupAddress);
		// if (I contained in prunes(S,G)) {
		if(prunez.find(*i_nbrs)!=prunez.end()){
			SRMP.m_P = 1;
			// set Prune Indicator bit of SRMP' to 1;
			// StateRefreshCapable(I) is TRUE if all neighbors on an interface use the State Refresh option.
			if (StateRefreshCapable(*i_nbrs)){
				SourceGroupState *sgState = FindSourceGroupState(*i_nbrs,refresh.m_sourceAddr.m_unicastAddress,refresh.m_multicastGroupAddr.m_groupAddress);
				Time pruneHoldTime = FindNeighborhoodStatus(*i_nbrs)->pruneHoldtime;
				//set PT(S,G) to largest active holdtime read from a Prune  message accepted on I;
				sgState->SG_PT.SetDelay(pruneHoldTime);
				//sgState->SG_SR_TTL = (sgState->SG_SR_TTL > refresh.m_ttl? sgState->SG_SR_TTL:refresh.m_ttl);
			}
		} else {// set Prune Indicator bit of SRMP' to 0;
			SRMP.m_P = 0;
		}
		// set srcaddr(SRMP') to my_addr(I): my_addr(I) returns this node's network (e.g., IPv4) address on interface I.
		SRMP.m_originatorAddr.m_unicastAddress = GetLocalAddress(*i_nbrs);
		// set TTL of SRMP' to TTL(SRM) - 1;
		SRMP.m_ttl = refresh.m_ttl-1;
		// set metric of SRMP' to metric of unicast route used to reach S;
		SRMP.m_metric = m_mrib.find(refresh.m_sourceAddr.m_unicastAddress)->second.route_metric;
		// set pref of ' to preference of unicast route used to reach S;
		SRMP.m_metricPreference = m_mrib.find(refresh.m_sourceAddr.m_unicastAddress)->second.metricPreference;
		// set mask of SRMP' to mask of route used to reach S;
		SourceGroupState *sgState = FindSourceGroupState(*i_nbrs,refresh.m_sourceAddr.m_unicastAddress,refresh.m_multicastGroupAddr.m_groupAddress);
		if (sgState->AssertState == Assert_NoInfo) {
			SRMP.m_O = 1;//set Assert Override of SRMP' to 1;
		} else {
			SRMP.m_O = 0;//set Assert Override of SRMP' to 0;
		}
		//transmit SRMP' on I;
		Ptr<Packet> packet;
		//TODO send on interface
		SendBroadPacketInterface(packet,refreshFRW,*i_nbrs);
	}
}

void
MulticastRoutingProtocol::RecvHello(PIMHeader::HelloMessage &hello, Ipv4Address sender, Ipv4Address receiver){
	NS_LOG_DEBUG("Sender "<< sender<< " Receiver "<< receiver);
	uint16_t entry = 0;
	NeighborState tmp(sender,receiver);
	uint32_t interface = GetReceivingInterface(receiver);
	NeighborState *ns = FindNeighborState(interface,tmp);
	if(!ns){// Hello message received from a new neighbor
		InsertNeighborState(interface,tmp);
		ns = FindNeighborState(interface,tmp);
		// If a Hello message is received from a new neighbor, the receiving router SHOULD send its own Hello message
		//    after a random delay between 0 and Triggered_Hello_Delay.
		Time delay = Seconds(UniformVariable().GetValue(0,Triggered_Hello_Delay));
		Simulator::Schedule (delay, &MulticastRoutingProtocol::SendNeighHello, this, interface, sender);
		NS_LOG_DEBUG(sender<< " first Hello, reply at "<<(Simulator::Now()+delay).GetSeconds());
	}
	while(entry < hello.m_optionList.size()){
		switch (hello.m_optionList[entry].m_optionType){
			case PIMHeader::HelloMessage::HelloHoldTime:{///< Sec. 4.3.2.
				Time value = hello.m_optionList[entry].m_optionValue.holdTime.m_holdTime;
				// NLT is running, we should reset it to the new holdtime
				switch ((uint16_t)value.GetSeconds()){///< Sec. 4.3.3.
					case 0xffff://Never timeout
						ns->neighborTimeoutB=false;
						break;
					case 0://Removing old information
						EraseNeighborState(interface,tmp);
						break;
					default:
						if(ns->neigborNLT.IsRunning()){
							ns->neigborNLT.Cancel();
						}
						ns->neigborNLT.SetDelay(hello.m_optionList[entry].m_optionValue.holdTime.m_holdTime);
//						if(!ns->neigborNLT.IsRunning()){
						ns->neigborNLT.Schedule();
						ns->neigborNLT.SetArguments(sender,receiver);
//						}
					}
				break;
				}
			case PIMHeader::HelloMessage::GenerationID:{// Section 4.3.4.
				/// First time node receives neighbor's generation ID
				if(!ns->neighborGenerationID)//its value is always greater than zero
					ns->neighborGenerationID = hello.m_optionList[entry].m_optionValue.generationID.m_generatioID;
				/// Generation ID changed
				else if(ns->neighborGenerationID != hello.m_optionList[entry].m_optionValue.generationID.m_generatioID){///< Sec. 4.3.4.
					// Generation ID changed The Generation ID is regenerated whenever PIM
					//   forwarding is started or restarted on the interface.
					// TODO: NeighborRestart
					EraseNeighborState(interface,*ns);
					InsertNeighborState(interface,tmp);
					// When a new or rebooting neighbor is detected, a responding Hello is sent
					//   within rand(0,Triggered_Hello_Delay).
					Time delay = Seconds(UniformVariable().GetValue(0,Triggered_Hello_Delay));
					//  A Hello message SHOULD be sent after a random delay between 0 and Triggered_Hello_Delay (see 4.8) before any other messages are sent.
					Simulator::Schedule (Seconds(0), &MulticastRoutingProtocol::SetStopTx, this);
					Simulator::Schedule (Seconds(delay.GetMicroSeconds()-1), &MulticastRoutingProtocol::UnsetStopTx, this);
					Simulator::Schedule (delay, &MulticastRoutingProtocol::SendNeighHello, this,interface,sender);
					delay = Seconds(delay.GetSeconds()+0.1);
					SourceGroupList sgList = m_IfaceSourceGroup.find(interface)->second;
					for(std::list<SourceGroupState>::iterator sgElement = sgList.begin(); sgElement!=sgList.end(); sgElement++){
//						for (uint32_t i = 0; i < m_ipv4->GetNInterfaces (); i++){
							// if the neighbor is downstream, the router MAY replay the last State Refresh message for any (S,G)
							//   pairs for which it is the Assert Winner indicating Prune and Assert status to the downstream router.
							if(IsDownstream(interface,sgElement->SGPair) && sgElement->AssertState == Assert_Winner){
								//   These State Refresh messages SHOULD be sent out immediately after the Hello message.
								Simulator::Schedule (Seconds(delay.GetMicroSeconds()+1), &MulticastRoutingProtocol::SendStateRefreshPair, this, interface, sender, sgElement->SGPair);
								break;
							}
							// If the neighbor is the upstream neighbor for an (S,G) entry, the router MAY cancel its
							//     Prune Limit Timer to permit sending a prune and reestablishing a Pruned state in the upstream router.
							else if (IsUpstream(interface,sgElement->SGPair) && sgElement->PruneState == Prune_Pruned){
								sgElement->SG_PT.Cancel();
								sgElement->SG_PT.SetDelay(Seconds(2*RefreshInterval));//TODO I am not sure of that: I have to understand the prune better
								Simulator::Schedule (Seconds(0), &MulticastRoutingProtocol::SendPruneBroadcast, this, interface, sgElement->SGPair);
							}
//							else NS_LOG_ERROR("Interface "<< i << " skipped\n");
//						}
					}
				}
				break;
			}
			case PIMHeader::HelloMessage::LANPruneDelay:{
				NeighborhoodStatus *nStatus = FindNeighborhoodStatus(interface);
				//If all routers on a LAN support the LAN Prune Delay option, then the PIM routers on that LAN will use the values received to adjust their
				//	J/P_Override_Interval on that interface and the interface is LAN Delay Enabled.
				if(nStatus->LANDelayEnabled){
				//  TODO Briefly, to avoid synchronization of Prune Override (Join) messages when multiple downstream routers share a multi-access link,
				//	sending of these messages is delayed by a small random amount of time.  The period of randomization is configurable and has a default value of 3 seconds.
					ns->neighborT = hello.m_optionList[entry].m_optionValue.lanPruneDelay.m_T;
					if(ns->neighborPropagationDelay != Time(hello.m_optionList[entry].m_optionValue.lanPruneDelay.m_propagationDelay)){
						// When all routers on a link use the LAN Prune Delay Option, all routers on the
						//   LAN MUST set Propagation Delay to the largest LAN Delay on the LAN.
						ns->neighborPropagationDelay = Time(hello.m_optionList[entry].m_optionValue.lanPruneDelay.m_propagationDelay);
						nStatus->propagationDelay = Max(ns->neighborPropagationDelay,nStatus->propagationDelay);
					}
					if(ns->neighborOverrideInterval != Time(hello.m_optionList[entry].m_optionValue.lanPruneDelay.m_overrideInterval)){
						// When all routers on a LAN use the LAN Prune Delay Option, all routers on the
						//   LAN MUST set their Override_Interval to the largest Override value on the LAN.
						ns->neighborOverrideInterval = Time(hello.m_optionList[entry].m_optionValue.lanPruneDelay.m_overrideInterval);
						nStatus->overrideInterval = Max(ns->neighborOverrideInterval,nStatus->overrideInterval);
					}
					// TODO check such values!
				}
				break;
			}
			case PIMHeader::HelloMessage::StateRefreshCapable:{
				ns->neighborVersion = hello.m_optionList[entry].m_optionValue.stateRefreshCapable.m_version;
				ns->neighborInterval = hello.m_optionList[entry].m_optionValue.stateRefreshCapable.m_interval;
//				ns->neighborReserved = hello.m_optionList[entry].m_optionValue.stateRefreshCapable.m_reserved;
				break;
			}
			default:{
				NS_LOG_DEBUG ("PIM Hello message type " << (int)hello.m_optionList[entry-1].m_optionType <<
                        " not implemented");
				NS_ASSERT(false);
				break;
				}
		};
		entry++;
 	}
	NeighborTimeout(interface);//TODO just one interface or all?
}


struct IsExpired
{
  bool operator() (const NeighborState & ns) const
  {
    return (ns.neighborTimeoutB && ns.neighborTimeout < Simulator::Now());
  }
};

void
MulticastRoutingProtocol::NeighborTimeout(uint32_t interface){
//	NS_LOG_FUNCTION(this);
	NeighborhoodStatus *nl = FindNeighborhoodStatus(interface);
	uint32_t size = nl->neighbors.size();
	IsExpired pred;
	nl->neighbors.erase (std::remove_if (nl->neighbors.begin (), nl->neighbors.end (), pred), nl->neighbors.end ());
	NS_LOG_DEBUG("Clean neighbors list on interface "<< interface<<": "<< size << " -> "<< nl->neighbors.size());
}

void
MulticastRoutingProtocol::SetMainInterface (uint32_t interface){
	NS_LOG_FUNCTION(this);
	m_mainAddress = m_ipv4->GetAddress (interface, 0).GetLocal ();
	}

void
MulticastRoutingProtocol::SetInterfaceExclusions (std::set<uint32_t> exceptions){
	NS_LOG_FUNCTION(this);
	m_interfaceExclusions = exceptions;
	}

bool
MulticastRoutingProtocol::UsesNonPimDmOutgoingInterface (const Ipv4RoutingTableEntry &route){
	NS_LOG_FUNCTION(this);
	std::set<uint32_t>::const_iterator ci = m_interfaceExclusions.find (route.GetInterface ());
	// The outgoing interface is a non-OLSR interface if a match is found
	// before reaching the end of the list of excluded interfaces
	return (ci != m_interfaceExclusions.end ());
}

void MulticastRoutingProtocol::InsertNeighborState(uint32_t interface, const NeighborState &ns) {
	if (!FindNeighborState(interface, ns)) {
		FindNeighborhoodStatus(interface)->neighbors.push_back(ns);
		NeighborState *neighbor = FindNeighborState(interface, ns);
		neighbor->neigborNLT.Cancel();
		neighbor->neigborNLT.SetFunction(&MulticastRoutingProtocol::NLTTimerExpire,this);
		neighbor->neighborCreation = Simulator::Now();
		//TODO Neighbor timeout disabled
		//neighbor->neighborTimeout = Simulator::Now() + Seconds(Hello_Period+Propagation_Delay);
		//neighbor->neighborTimeoutB = true;
	}
}

}
}// namespace ns3

//TODO
//* If a Hello message is received from a new neighbor, the receiving router SHOULD send its own Hello message after a random delay between 0 and Triggered_Hello_Delay.
//* Upon startup, a router MAY use any State Refresh messages received within Hello_Period of its first Hello message on an interface to establish state information.  The State Refresh source will be the
//		RPF'(S), and Prune status for all interfaces will be set according to the Prune Indicator bit in the State Refresh message.  If the Prune
// 		Indicator is set, the router SHOULD set the PruneLimitTimer to Prune_Holdtime and set the PruneTimer on all downstream interfaces to
//		the State Refresh's Interval times two.  The router SHOULD then propagate the State Refresh as described in Section 4.5.1.
//* The LAN Delay inserted by a router in the LAN Prune Delay option expresses the expected message propagation delay on the link and
//		SHOULD be configurable by the system administrator.
//* When a packet is send, we should guarantee the packet will not send on an PIM-DM excluded interface
//* When a PIM router takes an interface down or changes IP address, a Hello message with a zero Hold Time SHOULD be sent immediately (with the old IP address if the IP address is
//		changed) to cause any PIM neighbors to remove the old information immediately.
//* A Hello message SHOULD be sent after a random delay between 0 and Triggered_Hello_Delay (see 4.8) before any other messages are sent. -> TO CHECK
//* Check whether it works or not: Seconds(delay.GetMicroSeconds()+1)
//* How to define RPF_primeChanges and Source directly connected?
//* How to and when update m_mrib??
