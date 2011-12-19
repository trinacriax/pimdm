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
#include "pimdm-routing.h"
#include "ns3/socket-factory.h"
#include "ns3/ipv4-raw-socket-factory.h"
#include "ns3/udp-socket-factory.h"
#include "ns3/udp-socket.h"
#include "ns3/simulator.h"
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
#include "ns3/ipv4-routing-table-entry.h"
#include "ns3/udp-header.h"
#include "ns3/udp-l4-protocol.h"

namespace ns3{
namespace pimdm{
NS_LOG_COMPONENT_DEFINE ("PIMDMMulticastRouting");

NS_OBJECT_ENSURE_REGISTERED (MulticastRoutingProtocol);

MulticastRoutingProtocol::MulticastRoutingProtocol() :
		m_routingTableAssociation(0), m_ipv4 (0), m_lo(0)
{
	m_RoutingTable = Create<Ipv4StaticRouting> ();
	m_IfaceNeighbors.clear();
	m_IfacePimEnabled.clear();
	m_IfaceSourceGroup.clear();
	m_LocalReceiver.clear();
	m_mrib.clear();
}

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
	.AddAttribute ("HelloHoldTime", "HoldTime used in hello messages.",
			 	 	UintegerValue (Hold_Time_Default),
			        MakeUintegerAccessor (&MulticastRoutingProtocol::SetHelloHoldTime),
			        MakeUintegerChecker<uint16_t> ())
	.AddAttribute ("RegisterSG", "Register a new source-group pair, like a new IGMP entry.",
					StringValue("0,0"),
					MakeStringAccessor(&MulticastRoutingProtocol::register_SG),
					MakeStringChecker())
	.AddAttribute ("RegisterAsMember", "Register as a member of the group. Tuple (group, source, interface).",
					StringValue("0,0,0"),
					MakeStringAccessor(&MulticastRoutingProtocol::register_member),
					MakeStringChecker())
	.AddAttribute ("UnRegisterAsMember", "UnRegister as a member of the group. Tuple (group, source, interface).",
					StringValue("0,0,0"),
					MakeStringAccessor(&MulticastRoutingProtocol::unregister_member),
					MakeStringChecker())
	.AddAttribute ("RPFCheckInterval", "RPF check interval.",
					TimeValue (Seconds (RPF_CHECK)),
					MakeTimeAccessor (&MulticastRoutingProtocol::m_rpfCheck),
					MakeTimeChecker ())
	.AddAttribute ("LanPruneDelay", "LAN prune delay set by administrator.",
					TimeValue (Seconds (Propagation_Delay)),
					MakeTimeAccessor (&MulticastRoutingProtocol::m_LanDelay),
					MakeTimeChecker ())
	.AddTraceSource ("RxPIM", "Trace PIM packet received.",
					MakeTraceSourceAccessor (&MulticastRoutingProtocol::m_rxPacketTrace))
	.AddTraceSource ("TxPIM", "Trace PIM packet sent.",
					MakeTraceSourceAccessor (&MulticastRoutingProtocol::m_txPacketTrace))
    .AddTraceSource ("RxData", "Trace data packet received.",
					MakeTraceSourceAccessor (&MulticastRoutingProtocol::m_rxDataPacketTrace))
    .AddTraceSource ("TxData", "Trace data packet sent.",
					MakeTraceSourceAccessor (&MulticastRoutingProtocol::m_txDataPacketTrace))
	.AddTraceSource ("RoutingTableChanged", "The PIM-DM routing table has changed.",
	   	     	 	MakeTraceSourceAccessor (&MulticastRoutingProtocol::m_routingTableChanged))

    ;
  return tid;
}


uint16_t
MulticastRoutingProtocol::GetRouteMetric(int32_t interface, Ipv4Address source)
{// The cost metric of the unicast route to the source.  The metric is in units applicable to the unicast routing protocol used.
  Ptr<Ipv4RoutingProtocol> rp_Gw = (m_ipv4->GetRoutingProtocol ());
  Ptr<Ipv4ListRouting> lrp_Gw = DynamicCast<Ipv4ListRouting> (rp_Gw);
  Ptr<olsr::RoutingProtocol> olsr_Gw;
  Ptr<aodv::RoutingProtocol> aodv_Gw;
  Ptr<mbn::RoutingProtocol> mbnaodv_Gw;
//  Ptr<dsdv::RoutingProtocol> dsdv_Gw;
  for (int32_t i = 0; i < lrp_Gw->GetNRoutingProtocols ();  i++)
	{
	  int16_t priority;
	  Ptr<Ipv4RoutingProtocol> temp = lrp_Gw->GetRoutingProtocol (i, priority);
	  if (DynamicCast<olsr::RoutingProtocol> (temp))
		{
		  olsr_Gw = DynamicCast<olsr::RoutingProtocol> (temp);
		  std::vector<olsr::RoutingTableEntry> olsr_table = olsr_Gw->GetRoutingTableEntries();
		  for(std::vector<olsr::RoutingTableEntry>::const_iterator iter = olsr_table.begin(); iter!=olsr_table.end(); iter++){
			  if(iter->destAddr!=Ipv4Address::GetLoopback() && iter->destAddr == source)return iter->distance;
		  }
		}
	  else if (DynamicCast<aodv::RoutingProtocol> (temp))
	  		{
	  		  aodv_Gw = DynamicCast<aodv::RoutingProtocol> (temp);
//	  		  aodv::RoutingTableEntry aodv_rte;
//	  		  aodv_Gw->m_routingTable.LookupRoute(source,aodv_rte);
//	  		  return aodv_rte.GetHop();
	  		}
	  else if (DynamicCast<mbn::RoutingProtocol> (temp))
	  		{
		  	  mbnaodv_Gw = DynamicCast<mbn::RoutingProtocol> (temp);
//		  	  mbnaodv_Gw->GetLocalNodeStatus();
//	  		  aodv::RoutingTableEntry aodv_rte;
//	  		  aodv_Gw->m_routingTable.LookupRoute(source,aodv_rte);
//	  		  return aodv_rte.GetHop();
	  		}
//	  else if (DynamicCast<dsdv::RoutingProtocol> (temp))
//	  		{
//		  	  dsdv_Gw = DynamicCast<dsdv::RoutingProtocol> (temp);
//		  	  dsdv::RoutingTableEntry dsdv_rte;
//			  dsdv_Gw->m_routingTable.LookupRoute(source,dsdv_rte);
//			  return dsdv_rte.GetHop();
//	  		}
	}
  return 1;
}

uint16_t
MulticastRoutingProtocol::GetMetricPreference(int32_t interface)
{//TODO: The preference value assigned to the unicast routing protocol that provided the route to the source
	return 1;
}

void
MulticastRoutingProtocol::unregister_member (std::string csv){
	NS_LOG_FUNCTION(this);
	Ipv4Address group, source;
	int32_t interface;
	std::vector<std::string> tokens;
	Tokenize(csv, tokens, ",");
	if(tokens.size()!= 3) return;
	source = Ipv4Address(tokens.at(0).c_str());
	group = Ipv4Address(tokens.at(1).c_str());
	interface = atoi(tokens.at(2).c_str());
	tokens.clear();
	if(source == group && interface == 0) return;//skip initialization
	NS_LOG_LOGIC("UnRegister interface with members for ("<<source<<","<<group<<") over interface "<< interface);
	SourceGroupPair sgp (source,group);
	if(m_LocalReceiver.find(sgp)->second.find(interface) != m_LocalReceiver.find(sgp)->second.end() && interface >0 && interface<m_ipv4->GetNInterfaces()){
		m_LocalReceiver.find(sgp)->second.erase(interface);
		NS_LOG_DEBUG("Removing interface " << interface<< " from ("<<source<<","<<group<<")");
	}
	if(m_LocalReceiver.find(sgp)!=m_LocalReceiver.end() && m_LocalReceiver.find(sgp)->second.size() == 0){
		m_LocalReceiver.erase(sgp);
		NS_LOG_DEBUG("Removing Source-Group ("<<source<<","<<group<<") to the map");
	}
	else NS_LOG_DEBUG("No clients on interface " << interface<< " for ("<<source<<","<<group<<")");
	int32_t sources = m_mrib.find(group)->second.mgroup.size();
	UpstreamStateMachine(sgp);
}

void
MulticastRoutingProtocol::register_member (std::string csv){
	/***************** TODO: TO REMOVE WITH IGMP *****************/
	NS_LOG_FUNCTION(this);
	Ipv4Address group, source;
	int32_t interface;
	std::vector<std::string> tokens;
	Tokenize(csv, tokens, ",");
	if(tokens.size()!= 3) return;
	source = Ipv4Address(tokens.at(0).c_str());
	group = Ipv4Address(tokens.at(1).c_str());
	interface = atoi(tokens.at(2).c_str());
	tokens.clear();
	if(source == group && interface == 0) return;//skip initialization
	NS_LOG_LOGIC("Register interface with members for ("<<source<<","<<group<<") over interface "<< interface);
	SourceGroupPair sgp (source,group);
	if(m_LocalReceiver.find(sgp)==m_LocalReceiver.end()){//add a new receiver on a specific (source,group) on a given interface
		std::set<int32_t> iface;
		m_LocalReceiver.insert(std::pair<SourceGroupPair, std::set<int32_t> >(sgp,iface));
		NS_LOG_DEBUG("Adding Source-Group ("<<source<<","<<group<<") to the map");
	}
	if(m_LocalReceiver.find(sgp)->second.find(interface) == m_LocalReceiver.find(sgp)->second.end() && interface >0 && interface<m_ipv4->GetNInterfaces()){
		m_LocalReceiver.find(sgp)->second.insert(interface);
		NS_LOG_DEBUG("Adding interface " << interface<< " to ("<<source<<","<<group<<")");
	}
	else NS_LOG_DEBUG("Interface " << interface<< " already registered for ("<<source<<","<<group<<")");
	int32_t sources = m_mrib.find(group)->second.mgroup.size();
	NS_LOG_DEBUG("Group "<<group<<", #Sources: "<< sources << " #Clients "<< m_LocalReceiver.find(sgp)->second.size());
}

void
MulticastRoutingProtocol::register_SG (std::string csv){
	/***************** TODO: TO REMOVE WITH IGMP *****************/
	NS_LOG_FUNCTION(this);
	Ipv4Address group, source;
	std::vector<std::string> tokens;
	Tokenize(csv, tokens, ",");
	if(tokens.size()!= 2) return;
	source = Ipv4Address(tokens.at(0).c_str());
	group = Ipv4Address(tokens.at(1).c_str());
	tokens.clear();
	if(source == group) return;//skip initialization
	NS_LOG_LOGIC("Registering SourceGroup pair ("<<source<<","<<group<<")");
	SourceGroupPair sgp (source,group);
	AddEntry(group,source,Ipv4Address::GetLoopback(),-1);//We got an entry from IGMP for this source-group
	int32_t sources = m_mrib.find(group)->second.mgroup.size();
	NS_LOG_DEBUG("Main Addr = "<<  m_mainAddress << ": Group "<<group<<" #Source: "<< sources);
	if(group == ALL_PIM_ROUTERS4 || sources > 1) return;//Socket already registered for this group
	for(int32_t i = 0; i < m_ipv4->GetNInterfaces(); i++){
		if(IsLoopInterface(i))
			continue;
	///Registering endpoint for that address... by creating a socket to listen only on this interface
	Ptr<Socket> socketG = Socket::CreateSocket (GetObject<Node> (), Ipv4RawSocketFactory::GetTypeId());
	socketG->SetAttribute("Protocol", UintegerValue(UdpL4Protocol::PROT_NUMBER));
	socketG->SetAttribute("IpHeaderInclude", BooleanValue(true));
	socketG->SetAllowBroadcast (true);
//	InetSocketAddress inetAddr (group, PIM_PORT_NUMBER);
	InetSocketAddress inetAddr (group);
	socketG->SetRecvCallback (MakeCallback (&MulticastRoutingProtocol::RecvMessage, this));
	if (socketG->Bind (inetAddr)){
		NS_FATAL_ERROR ("Failed to bind() PIMDM socket for group "<<group);
	}
	socketG->BindToNetDevice (m_ipv4->GetNetDevice (i));
	m_socketAddresses[socketG] = m_ipv4->GetAddress (i, 0); //PROBLEM; does not broadcast on local IP, takes the other group-interface
	NS_LOG_DEBUG("Registering Group Socket = "<<socketG<< " Device = "<<socketG->GetBoundNetDevice()<< ", SocketAddr = "<<m_ipv4->GetAddress (i, 0).GetLocal() <<", I = "<<i);
	Ipv4InterfaceAddress mgroup(group, Ipv4Mask::GetOnes());	// WIFI OK
	m_socketAddresses[socketG] = mgroup;						// WIFI OK
	NS_LOG_DEBUG("Group Socket "<<socketG << " Addr: "<<group<<":AnyPort");
	}
}

///
/// \brief Clears the routing table and frees the memory assigned to each one of its entries.
///
void
MulticastRoutingProtocol::Clear ()
{
  NS_LOG_FUNCTION_NOARGS ();
  m_mrib.clear ();
}

///
/// \brief Deletes the entry whose destination address is given.
/// \param dest	address of the destination node.
///
void
MulticastRoutingProtocol::RemoveEntry (Ipv4Address const &group)
{
	NS_LOG_FUNCTION(this);
	m_mrib.erase (group);
}

void
MulticastRoutingProtocol::RemoveEntry (const Ipv4Address &group, const Ipv4Address &source)
{
//	NS_LOG_FUNCTION(this);
	if(m_mrib.find (group) != m_mrib.end() &&
			m_mrib.find (group)->second.mgroup.find(source) != m_mrib.find (group)->second.mgroup.end())
		m_mrib.find (group)->second.mgroup.erase(source);
}

///
/// \brief Lookup for a multicast group entry.
///
/// Look for a multicast entry if exists.
///
/// \param group		multicast group address.
/// \param interface	interface for that group.
/// \param groupEntry	RouteEntry for the multicast group.
bool
MulticastRoutingProtocol::Lookup (const Ipv4Address group, RoutingMulticastTable &outEntry) const
{
//	NS_LOG_FUNCTION(this << group);
	// Get the iterator at "dest" position
	std::map<Ipv4Address, RoutingMulticastTable>::const_iterator it = m_mrib.find (group);
	// If there is no route to "dest", return NULL
	if (it == m_mrib.end ())
		return false;
	outEntry = it->second;
	return true;
}


///
/// \brief Lookup for a multicast group-interface entry.
///
/// Look fopr a multicast entry if exists.
///
/// \param group		multicast group address.
/// \param interface	interface for that group.
/// \param groupEntry		RouteEntry for the multicast group.
/// \param ifaceEntry			InterfaceSpecific Entry for the multicast group.
bool
MulticastRoutingProtocol::Lookup (const Ipv4Address group, const Ipv4Address source, RoutingMulticastTable &outEntry, MulticastEntry &me) const
{
//	NS_LOG_FUNCTION(this << group<< source);
	// Get the iterator at "dest" position
	std::map<Ipv4Address, RoutingMulticastTable>::const_iterator gg = m_mrib.find (group);
	// If there is no route to "dest", return NULL
	if (gg == m_mrib.end ())
		return false;
	outEntry = gg->second;
	std::map<Ipv4Address, MulticastEntry>::const_iterator gs = gg->second.mgroup.find(source);
	if (gs == gg->second.mgroup.end())
		return false;
	me = gs->second;
	return true;
}

///
/// \brief Update a multicast entry, associating a new source, next hop towards the source.
///
/// Update a multicast entry if exists.
///
/// \param group		multicast group address.
/// \param interface	interface for that group.
/// \param source		new multicast source.
/// \param next			new next hop towards the source.
///
bool
MulticastRoutingProtocol::UpdateEntry(Ipv4Address const group, Ipv4Address const source, Ipv4Address const next, int32_t const interface)
{
//	NS_LOG_FUNCTION(this << group<< interface);
	// Get the iterator at "dest" position
	// If there is no route to "dest", return NULL
	MulticastEntry *mentry = &m_mrib[group].mgroup[source];
	if (m_mrib.find (group) == m_mrib.end ())
		return false;
	m_mrib[group].mgroup[source].sourceAddr = source;
	m_mrib[group].mgroup[source].nextAddr = next;
	m_mrib[group].mgroup[source].interface = interface;
	return true;
}

///
/// \brief Adds a new entry into the routing table.
///
/// If an entry for the given destination existed, it is deleted and freed.
///
/// \param dest		address of the group address.
/// \param dist		distance to the source node.
/// \param next		address of the next hop node.
/// \param iface	address of the local interface.
///
void
MulticastRoutingProtocol::AddEntry (const Ipv4Address group, const Ipv4Address source, const Ipv4Address next, const int32_t interface)
{
//  NS_LOG_FUNCTION (this << "Group: "<< group << " Source: "<< source <<" Next: "<< next << " RPF_I: "<< interface << " MainAddress: "<< m_mainAddress);
  // Creates a new rt entry with specified values
  RoutingMulticastTable &entry = m_mrib[group];//DEBUG
  m_mrib[group].groupAddr = group;
  MulticastEntry *me = &m_mrib[group].mgroup[source];//DEBUG
  m_mrib[group].mgroup[source].sourceAddr = source;
  m_mrib[group].mgroup[source].interface = interface;
  m_mrib[group].mgroup[source].nextAddr = next;
}

///
/// \brief Query routing cache for an existing route, for an outbound packet.
///
/// Get....
///
/// \param p		packet to send.
/// \param header	packet header.
/// \param oif		outbound interface designated.
/// \param sockerr	error type.
///
Ptr<Ipv4Route>
MulticastRoutingProtocol::RouteOutput (Ptr<Packet> p, const Ipv4Header &header,
		Ptr<NetDevice> oif, Socket::SocketErrno &sockerr)
{
	NS_LOG_FUNCTION (this << m_ipv4->GetObject<Node> ()->GetId () << header.GetDestination () << oif);
	Ptr<Ipv4Route> rtentry;
	sockerr = Socket::ERROR_NOROUTETOHOST;
	if (m_socketAddresses.empty ())
	{
	  NS_LOG_LOGIC ("No PIMDM interfaces");
	  return rtentry;
	}
	RoutingMulticastTable entry1;
	bool found = Lookup(header.GetDestination(), entry1);
	if(header.GetDestination().IsMulticast()) {//entry in the routing table found
		int32_t interfaceIdx = -1;
		if(oif!=NULL)//we are sending on a specific device, so we "want" to use that interface
			interfaceIdx = m_ipv4->GetInterfaceForDevice (oif);//
		else if(IsMyOwnAddress(header.GetSource()))//since we deal with multicast packet, and the interface is null...this might be the source
			interfaceIdx = m_ipv4->GetInterfaceForAddress(header.GetSource());
		else if(Lookup(header.GetDestination(), entry1))//we don't know anything :( looking for the first entry for this group;
			interfaceIdx = entry1.mgroup.begin()->second.interface;
		if ((oif && m_ipv4->GetInterfaceForDevice (oif) != static_cast<int> (interfaceIdx)) || interfaceIdx <0){
		  // We do not attempt to perform a constrained routing search
		  // if the caller specifies the oif; we just enforce
		  // that the found route matches the requested outbound interface
		  NS_LOG_DEBUG ("PIM-DM node " << m_mainAddress
									 << ": RouteOutput for dest=" << header.GetDestination ()
									 << " Route interface " << interfaceIdx
									 << " does not match requested output interface "
									 << m_ipv4->GetInterfaceForDevice (oif));
		  sockerr = Socket::ERROR_NOROUTETOHOST;
		  return rtentry;
		}
		sockerr = Socket::ERROR_NOTERROR;
		rtentry = Create<Ipv4Route> ();
		rtentry->SetDestination (header.GetDestination ());
		// the source address is the interface address that matches
		// the destination address (when multiple are present on the
		// outgoing interface, one is selected via scoping rules)
		NS_ASSERT (m_ipv4);
		int32_t numOifAddresses = m_ipv4->GetNAddresses (interfaceIdx);
		NS_ASSERT (numOifAddresses > 0);
		Ipv4InterfaceAddress ifAddr;
		if (numOifAddresses == 1) {
		  ifAddr = m_ipv4->GetAddress (interfaceIdx, 0);
		} else {
		  NS_FATAL_ERROR ("TODO Not implemented yet:  IP aliasing");
		}
		rtentry->SetSource (ifAddr.GetLocal ());
		rtentry->SetOutputDevice (m_ipv4->GetNetDevice (interfaceIdx));
		Ipv4Address gateway = header.GetDestination();
		rtentry->SetGateway(gateway);
		NS_LOG_DEBUG ("PIM-DM node " << m_mainAddress << ": RouteOutput for dest= " << header.GetDestination () << " gateway= "<< rtentry->GetGateway () << ", interface = " << interfaceIdx<<" device = "<<gateway);
		found = true;
	}
	if (!found)
	{
	  NS_LOG_DEBUG ("PIM-DM node " << m_mainAddress
			  << ": RouteOutput for dest=" << header.GetDestination ()
			  << " No route to host");
	}
	return rtentry;
}

bool MulticastRoutingProtocol::RouteInput  (Ptr<const Packet> p,
  const Ipv4Header &header, Ptr<const NetDevice> idev,
  UnicastForwardCallback ucb, MulticastForwardCallback mcb,
  LocalDeliverCallback lcb, ErrorCallback ecb)
{
	  NS_LOG_FUNCTION (this << m_ipv4->GetObject<Node> ()->GetId () << header.GetDestination ());

	  Ipv4Address dst = header.GetDestination ();
	  Ipv4Address origin = header.GetSource ();

	  // Consume self-originated packets
	  if (IsMyOwnAddress (origin) == true) //peer doesn't know that route
	    {
	      return false;
	    }

	  // Local delivery
	  NS_ASSERT (m_ipv4->GetInterfaceForDevice (idev) >= 0);
	  int32_t iif = m_ipv4->GetInterfaceForDevice (idev);
	  if (m_ipv4->IsDestinationAddress (dst, iif))
	    {
	      if (!lcb.IsNull ())
	        {
	          NS_LOG_LOGIC ("Local delivery to " << dst);
	          lcb (p, header, iif);
	          return true;
	        }
	      else
	        {
	          // The local delivery callback is null.  This may be a multicast
	          // or broadcast packet, so return false so that another
	          // multicast routing protocol can handle it.  It should be possible
	          // to extend this to explicitly check whether it is a unicast
	          // packet, and invoke the error callback if so

	    	  //TODO implement here the callback
	          return false;
	        }
	    }
	  if(m_RoutingTable->RouteInput (p, header, idev, ucb, mcb, lcb, ecb))
	         {
	           return true;
	         }
	       else
	         {
	 #ifdef NS3_LOG_ENABLE
	           NS_LOG_DEBUG ("PIMDM node " << m_mainAddress
	                                      << ": RouteInput for dest=" << header.GetDestination ()
	                                      << " --> NOT FOUND; ** Dumping routing table...");

	           for (std::map<Ipv4Address, RoutingMulticastTable>::const_iterator iter = m_mrib.begin ();
	                iter != m_mrib.end (); iter++)
	             {
	        	   for (std::map <Ipv4Address,MulticastEntry>::const_iterator miter = iter->second.mgroup.begin();
	        	   	                miter !=  iter->second.mgroup.end(); miter++)
	        	   	             {
								   NS_LOG_DEBUG ("Group = " << iter->first
										   << " --> Source = " << miter->second.sourceAddr<<", Gateway = " << miter->second.nextAddr
										   << ", Interface = " << miter->second.interface);
	        	   	             }
	             }

	           NS_LOG_DEBUG ("** Routing table dump end.");
	 #endif // NS3_LOG_ENABLE
	         }
	return false;
}

///
/// \brief Check whether the given address is a node's address or not.
///
/// True if the address belongs to the node, false otherwise.
///
/// \param address	IP address to check.
///
bool
MulticastRoutingProtocol::IsMyOwnAddress (const Ipv4Address & address) const
{
  for (std::map<Ptr<Socket>, Ipv4InterfaceAddress>::const_iterator j =
         m_socketAddresses.begin (); j != m_socketAddresses.end (); ++j)
    {
      Ipv4InterfaceAddress iface = j->second;
      if (address == iface.GetLocal ())
        {
          return true;
        }
    }
  return false;
}

void
MulticastRoutingProtocol::NotifyInterfaceUp (uint32_t i)
{
	NS_LOG_FUNCTION(this<<i);
	if (m_mainAddress == Ipv4Address ()) {
		Ipv4Address addr = m_ipv4->GetAddress (i, 0).GetLocal ();
		if (addr != Ipv4Address::GetLoopback()) {
			m_mainAddress = addr;
		}
	}
	NS_ASSERT (m_mainAddress != Ipv4Address ());
	EnablePimInterface(i);
}

void
MulticastRoutingProtocol::NotifyInterfaceDown (uint32_t i)
{
	NS_LOG_FUNCTION(this << i);
	DisablePimInterface(i);
}

void
MulticastRoutingProtocol::NotifyAddAddress (uint32_t j, Ipv4InterfaceAddress address)
{
	NS_LOG_FUNCTION(this << GetObject<Node> ()->GetId());
	int32_t i = (int32_t)j;
	Ipv4Address addr = m_ipv4->GetAddress (i, 0).GetLocal ();
	if (addr == Ipv4Address::GetLoopback())
		return;
	// Create socket to listen on ALL_PIM_ROUTERS4 group
	Ptr<Socket> socketP = Socket::CreateSocket (GetObject<Node> (), Ipv4RawSocketFactory::GetTypeId());
	socketP->SetAttribute("Protocol", UintegerValue(PIM_IP_PROTOCOL_NUM));
	socketP->SetAttribute("IpHeaderInclude", BooleanValue(true));
	socketP->SetAllowBroadcast (false);
	InetSocketAddress inetAddrP (ALL_PIM_ROUTERS4, PIM_PORT_NUMBER);
	socketP->SetRecvCallback (MakeCallback (&MulticastRoutingProtocol::RecvMessage, this));
	// Add ALL_PIM_ROUTERS4 multicast group, where the source is the node it self.
	AddEntry(ALL_PIM_ROUTERS4, addr, Ipv4Address::GetLoopback(), i);
	if (socketP->Bind (inetAddrP)){
		NS_FATAL_ERROR ("Failed to bind() PIMDM socket");
	}
	socketP->BindToNetDevice (m_ipv4->GetNetDevice (i));
	Ipv4InterfaceAddress mpim(Ipv4Address(ALL_PIM_ROUTERS4), Ipv4Mask::GetOnes());
	m_socketAddresses[socketP] = mpim;
	NS_LOG_DEBUG("Registering PIM Socket = "<<socketP << " Device = "<<m_ipv4->GetNetDevice (i)<< ", LocalAddr = "<<mpim.GetLocal()<<" Destination = "<<  ALL_PIM_ROUTERS4<<", I = "<<i<<" IfaceAddr "<<m_ipv4->GetAddress (i, 0).GetLocal());

	// Create a socket to listen only on this Interface/Address
	Ptr<Socket> socket = Socket::CreateSocket (GetObject<Node> (), Ipv4RawSocketFactory::GetTypeId());
	socket->SetAttribute("Protocol", UintegerValue(PIM_IP_PROTOCOL_NUM));
	socket->SetAttribute("IpHeaderInclude", BooleanValue(true));
	socket->SetAllowBroadcast (true);
	InetSocketAddress inetAddr (addr , PIM_PORT_NUMBER);
	socket->SetRecvCallback (MakeCallback (&MulticastRoutingProtocol::RecvMessage, this));
	if (socket->Bind (inetAddr)){
		NS_FATAL_ERROR ("Failed to bind() PIMDM socket "<< addr<<":"<<PIM_PORT_NUMBER);
	}
	socket->BindToNetDevice (m_ipv4->GetNetDevice (i));
	m_socketAddresses[socket] = m_ipv4->GetAddress (i, 0);
	NS_LOG_DEBUG("Socket "<<socket << " Device "<<m_ipv4->GetNetDevice (i)<<" Iface "<<i
			<< " Addr "<< addr
			<<" Broad "<< addr.GetSubnetDirectedBroadcast (m_ipv4->GetAddress (i, 0).GetMask ())
	);

	NeighborhoodStatus *ns = FindNeighborhoodStatus(i);
	NS_ASSERT(ns == NULL);
	InsertNeighborhoodStatus(i);
	ns = FindNeighborhoodStatus(i);
	ns->propagationDelay = Seconds(UniformVariable().GetValue(m_LanDelay.GetSeconds()*.3, m_LanDelay.GetSeconds()));
	ns->overrideInterval = Seconds(UniformVariable().GetValue(Override_Interval*.3, Override_Interval));
	ns->stateRefreshInterval = Seconds(UniformVariable().GetValue(RefreshInterval*.3, RefreshInterval));
	ns->pruneHoldtime = Seconds(UniformVariable().GetValue(PruneHoldTime*.3, PruneHoldTime));
	ns->LANDelayEnabled = true;
	ns->stateRefreshCapable = true;
	NS_LOG_DEBUG ("Neighborhood ("<<i<<"): PD " << ns->propagationDelay.GetSeconds() <<"s OI "<< ns->overrideInterval.GetSeconds() <<
			"s SRI "<< ns->stateRefreshInterval.GetSeconds()<<"s PHT "<< ns->pruneHoldtime.GetSeconds()<<"s LDE "<<ns->LANDelayEnabled<<
			"s SRC "<< ns->stateRefreshCapable);
	Time rndHello = TransmissionDelay(0, Triggered_Hello_Delay);
	Simulator::Schedule (rndHello, &MulticastRoutingProtocol::HelloTimerExpire, this, i);
	ns->hello_timer.SetDelay(m_helloTime);
	NS_LOG_DEBUG ("SourceGroup List("<<i<<") HT "<<m_helloTime.GetSeconds()<<"s Starting "<< rndHello.GetSeconds()<<"s");
}

void
MulticastRoutingProtocol::NotifyRemoveAddress (uint32_t interface, Ipv4InterfaceAddress address)
{NS_LOG_FUNCTION(this);NS_LOG_DEBUG("- Address("<<interface<<") = "<< address);}

void
MulticastRoutingProtocol::SetIpv4 (Ptr<Ipv4> ipv4)
{
  NS_ASSERT (ipv4 != 0);
  NS_ASSERT (m_ipv4 == 0);
  NS_LOG_DEBUG ("Created pimdm::MulticastRoutingProtocol");
  m_ipv4 = ipv4;
  m_RoutingTable->SetIpv4 (ipv4);
}

Ipv4Address
MulticastRoutingProtocol::GetLocalAddress (int32_t interface)
{
  NS_ASSERT(interface<m_ipv4->GetNInterfaces () && interface >= 0);
  return m_ipv4->GetAddress (interface, 0).GetLocal ();
}

void MulticastRoutingProtocol::DoDispose ()
	{
	m_ipv4 = 0;
	m_RoutingTable = 0;
	m_routingTableAssociation = 0;

	for (std::map< Ptr<Socket>, Ipv4InterfaceAddress >::iterator iter = m_socketAddresses.begin ();
	   iter != m_socketAddresses.end (); iter++)
	{
	  iter->first->Close ();
	}
	m_socketAddresses.clear ();
	m_IfaceNeighbors.clear();
	m_IfacePimEnabled.clear();
	m_IfaceSourceGroup.clear();
	m_mrib.clear();
	Ipv4RoutingProtocol::DoDispose ();
	}

void
MulticastRoutingProtocol::PrintRoutingTable (Ptr<OutputStreamWrapper> stream) const
{
  std::ostream* os = stream->GetStream ();
  *os << "Group\t Source\t NextHop\t Interface\n";

  for (std::map<Ipv4Address, RoutingMulticastTable>::const_iterator iter = m_mrib.begin ();
    iter != m_mrib.end (); iter++)
    {
      *os << iter->first << "\t\n";
      for(std::map <Ipv4Address, MulticastEntry>::const_iterator iface = iter->second.mgroup.begin();
    		  iface != iter->second.mgroup.end() ; iface++)
      {
    	  *os << "\t"<< iface->first << "\t\t";
		  *os << "\t"<< iface->second.sourceAddr<< "\t\n";
    	  *os << "\t"<< iface->second.nextAddr<< "\t\n";
    	  *os << "\t"<< iface->second.interface<< "\t\t";
      }
    }
	*os << "\nStatic Routing Table:\n";
	m_RoutingTable->PrintRoutingTable (stream);
}

void MulticastRoutingProtocol::DoStart ()
{
	if(m_generationID==0)
		m_generationID = UniformVariable().GetInteger(1, INT_MAX);///force value > 0
	m_latestPacketID = 0;
	m_startTime = Simulator::Now();
	if(m_rpfChecker.IsRunning()) //TODO can be removed
		m_rpfChecker.Cancel();
	m_rpfChecker.SetDelay(m_rpfCheck);
	m_rpfChecker.SetFunction(&MulticastRoutingProtocol::RPFCheckAll, this);
	m_rpfChecker.Schedule();
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
void
MulticastRoutingProtocol::HelloTimerExpire (int32_t i)
{
	  NS_LOG_FUNCTION(this << i);
	  if (IsLoopInterface(i)) return;
	  Ipv4Address addr = m_ipv4->GetAddress (i, 0).GetLocal ();
	  Timer &nHelloTimer = m_IfaceNeighbors.find(i)->second.hello_timer;
	  NS_LOG_DEBUG("Interface "<< i<< " [ E "<< nHelloTimer.IsExpired() <<
			  ", R " <<nHelloTimer.IsRunning()<<", S:" << nHelloTimer.IsSuspended()<<"].");
	  if(!nHelloTimer.IsRunning()){
		  nHelloTimer.SetFunction(&MulticastRoutingProtocol::HelloTimerExpire, this);
		  nHelloTimer.SetArguments(i);
		  nHelloTimer.Schedule();
	  }
	  SendHello (i);
}

bool
MulticastRoutingProtocol::IsDownstream (int32_t interface, Ipv4Address neighbor, SourceGroupPair sgpair)
{return IsDownstream(interface, neighbor,sgpair.sourceMulticastAddr, sgpair.groupMulticastAddr);}

bool
MulticastRoutingProtocol::IsDownstream (int32_t interface, Ipv4Address neighbor, Ipv4Address source, Ipv4Address group)
{return !(IsUpstream(interface, neighbor, source, group));}

bool
MulticastRoutingProtocol::IsUpstream (int32_t interface, Ipv4Address neighbor, SourceGroupPair sgpair)
{return IsUpstream(interface, neighbor, sgpair.sourceMulticastAddr, sgpair.groupMulticastAddr);}

bool
MulticastRoutingProtocol::IsUpstream (int32_t interface, Ipv4Address neighbor, Ipv4Address source, Ipv4Address group)
{
	NS_ASSERT(interface>0 && interface<m_ipv4->GetNInterfaces());
	WiredEquivalentInterface rpfPair = RPF_interface(source, group);
	return (interface == rpfPair.first && rpfPair.second == neighbor);
}

Ptr<Ipv4Route>
MulticastRoutingProtocol::GetRoute(Ipv4Address destination) {
	Ptr<Packet> receivedPacket = Create<Packet> (1000);
	Ipv4Header hdr;
	hdr.SetDestination(destination);
	hdr.SetSource(m_mainAddress);
	Ptr<NetDevice> oif = 0;//m_ipv4->GetNetDevice(m_ipv4->GetInterfaceForAddress(Ipv4Address::GetLoopback()));
	Socket::SocketErrno err = Socket::ERROR_NOROUTETOHOST;
	Ptr<Ipv4Route> route = m_ipv4->GetRoutingProtocol()->RouteOutput(receivedPacket, hdr, oif, err);
	return route;
}

WiredEquivalentInterface
MulticastRoutingProtocol::RPF_interface(Ipv4Address target) {
	Ptr<Ipv4Route> route = GetRoute(target);
	int32_t rpfInterface = (route) ? m_ipv4->GetInterfaceForDevice(route->GetOutputDevice()):-1;
	Ipv4Address rpfNeighbor = (route) ? route->GetGateway() : Ipv4Address::GetLoopback();
	return WiredEquivalentInterface (rpfInterface, rpfNeighbor);
}

WiredEquivalentInterface
MulticastRoutingProtocol::RPF_interface(Ipv4Address source, Ipv4Address group) {
	RoutingMulticastTable mt;
	MulticastEntry me;
	if(Lookup(group, source, mt, me))
		return WiredEquivalentInterface (me.interface, me.nextAddr);
	else
		return WiredEquivalentInterface (-1, Ipv4Address::GetLoopback());
}

Ipv4Address
MulticastRoutingProtocol::GetNextHop(Ipv4Address destination)
{
	WiredEquivalentInterface wei = RPF_interface(destination);
	return wei.second;
}

void
MulticastRoutingProtocol::CreateMulticastGroupEntry (PIMHeader::MulticastGroupEntry &m_entry, PIMHeader::EncodedGroup group)
{
	NS_LOG_FUNCTION(this);
	m_entry.m_multicastGroupAddr = group;
	m_entry.m_numberJoinedSources = 0;
	m_entry.m_numberPrunedSources = 0;
}

void
MulticastRoutingProtocol::AddMulticastGroupEntry (PIMHeader &msg, PIMHeader::MulticastGroupEntry &entry)
{
	NS_LOG_FUNCTION(this);
	switch(msg.GetType()){
		case PIM_JP:
			msg.GetJoinPruneMessage().m_joinPruneMessage.m_numGroups = 1 + msg.GetJoinPruneMessage().m_joinPruneMessage.m_numGroups;
			msg.GetJoinPruneMessage().m_multicastGroups.push_back(entry);
			break;
		case PIM_GRAFT:
			msg.GetGraftMessage().m_joinPruneMessage.m_numGroups = 1 + msg.GetGraftMessage().m_joinPruneMessage.m_numGroups;
			msg.GetGraftMessage().m_multicastGroups.push_back(entry);
			break;
		case PIM_GRAFT_ACK:
			msg.GetGraftAckMessage().m_joinPruneMessage.m_numGroups = 1 + msg.GetGraftAckMessage().m_joinPruneMessage.m_numGroups;
			msg.GetGraftAckMessage().m_multicastGroups.push_back(entry);
			break;
	}
}
void
MulticastRoutingProtocol::AddMulticastGroupSourceJoin (PIMHeader::MulticastGroupEntry &m_entry, PIMHeader::EncodedSource source)
{
	NS_LOG_FUNCTION(this);
	m_entry.m_numberJoinedSources = 1 + m_entry.m_numberJoinedSources;
	m_entry.m_joinedSourceAddrs.push_back(source);
}

void
MulticastRoutingProtocol::AddMulticastGroupSourcePrune (PIMHeader::MulticastGroupEntry &m_entry, PIMHeader::EncodedSource source)
{
	NS_LOG_FUNCTION(this);
	m_entry.m_numberPrunedSources = 1 + m_entry.m_numberPrunedSources;
	m_entry.m_prunedSourceAddrs.push_back(source);
}

void
MulticastRoutingProtocol::ForgeHeaderMessage (enum PIMType type, PIMHeader &msg)
{
	NS_LOG_FUNCTION(this);
	msg.SetVersion(PIM_VERSION_2);
	msg.SetType(type);
	msg.SetReserved(PIM_RESERVED);
}

void
MulticastRoutingProtocol::ForgeHelloMessageHoldTime (int32_t interface, PIMHeader &msg)
{
	PIMHeader::HelloMessage &helloMessage = msg.GetHelloMessage();
	PIMHeader::HelloMessage::HelloEntry holdtime = {PIMHeader::HelloMessage::HelloHoldTime, PIM_DM_HELLO_HOLDTIME};
	holdtime.m_optionValue.holdTime.m_holdTime = Seconds(m_helloHoldTime);
	msg.GetHelloMessage().m_optionList.push_back(holdtime);
}

void
MulticastRoutingProtocol::ForgeHelloMessageLANPD (int32_t interface, PIMHeader &msg)
{
	PIMHeader::HelloMessage::HelloEntry lanpd = {PIMHeader::HelloMessage::LANPruneDelay, PIM_DM_HELLO_LANPRUNDELAY};
	lanpd.m_optionValue.lanPruneDelay.m_T = 0;
	lanpd.m_optionValue.lanPruneDelay.m_propagationDelay = m_IfaceNeighbors.find(interface)->second.propagationDelay;
	lanpd.m_optionValue.lanPruneDelay.m_overrideInterval = m_IfaceNeighbors.find(interface)->second.overrideInterval;
	msg.GetHelloMessage().m_optionList.push_back(lanpd);
}

void
MulticastRoutingProtocol::ForgeHelloMessageGenID (int32_t interface, PIMHeader &msg)
{
	PIMHeader::HelloMessage::HelloEntry genid = {PIMHeader::HelloMessage::GenerationID, PIM_DM_HELLO_GENERATIONID};
	genid.m_optionValue.generationID.m_generatioID = m_generationID;
	msg.GetHelloMessage().m_optionList.push_back(genid);
}

void
MulticastRoutingProtocol::ForgeHelloMessageStateRefresh (int32_t interface, PIMHeader &msg)
{
	PIMHeader::HelloMessage::HelloEntry staterefresh = {PIMHeader::HelloMessage::StateRefreshCapable, PIM_DM_HELLO_STATEREFRESH};
	staterefresh.m_optionValue.stateRefreshCapable.m_version = 1;
	staterefresh.m_optionValue.stateRefreshCapable.m_interval = (uint8_t)(m_IfaceNeighbors.find(interface)->second.stateRefreshInterval).GetSeconds();
	staterefresh.m_optionValue.stateRefreshCapable.m_reserved = 0;
	msg.GetHelloMessage().m_optionList.push_back(staterefresh);
}

void
MulticastRoutingProtocol::ForgeHelloMessage (int32_t interface, PIMHeader &msg)
{
	NS_LOG_FUNCTION(this << interface);
	ForgeHeaderMessage(PIM_HELLO, msg);
	ForgeHelloMessageHoldTime(interface, msg);
	ForgeHelloMessageLANPD(interface, msg);
	ForgeHelloMessageGenID(interface, msg);
	if(m_IfaceNeighbors.find(interface)->second.stateRefreshCapable){
		ForgeHelloMessageStateRefresh(interface, msg);
	}
}

void
MulticastRoutingProtocol::SendHello (int32_t interface)
{///< Sec. 4.3.1. RFC 3973
	NS_LOG_FUNCTION(this << GetLocalAddress(interface)<< interface);
	Ptr<Packet> packet = Create<Packet> ();
	PIMHeader msg;
	ForgeHelloMessage(interface, msg);
	Simulator::Schedule(TransmissionDelay(),&MulticastRoutingProtocol::SendPacketPIMRoutersInterface, this, packet, msg, interface);
}

void
MulticastRoutingProtocol::SendHelloReply (int32_t interface, Ipv4Address destination)
{///< Sec. 4.3.1. RFC 3973
	NS_LOG_FUNCTION(this << GetLocalAddress(interface) << destination << interface);
	Ptr<Packet> packet = Create<Packet> ();
	PIMHeader msg;
	ForgeHelloMessage(interface, msg);
	Simulator::Schedule(TransmissionDelay(),&MulticastRoutingProtocol::SendPacketPIMUnicast, this,packet, msg, destination);
}

void
MulticastRoutingProtocol::ForgeJoinPruneMessage (PIMHeader &msg, Ipv4Address const upstreamNeighbor)
{
	NS_LOG_FUNCTION(this<<upstreamNeighbor);
	ForgeHeaderMessage(PIM_JP, msg);
	PIMHeader::JoinPruneMessage &jpMessage = msg.GetJoinPruneMessage();
	jpMessage.m_joinPruneMessage.m_upstreamNeighborAddr = ForgeEncodedUnicast(Ipv4Address(upstreamNeighbor));
	jpMessage.m_joinPruneMessage.m_reserved = 0;
	jpMessage.m_joinPruneMessage.m_numGroups = 0;
	jpMessage.m_joinPruneMessage.m_holdTime = Seconds(Hold_Time_Default);
}

void
MulticastRoutingProtocol::SendPruneUnicast(Ipv4Address destination, SourceGroupPair &sgp)
{
	NS_LOG_FUNCTION(this<< destination << sgp.sourceMulticastAddr << sgp.groupMulticastAddr);
	WiredEquivalentInterface wei = RPF_interface(destination);//know the interface-nextHop
	if (wei.first< 1 || !isValidGateway(wei.second)){
		return AskRoute(destination);
	} //just send it out, it will find its path
	SourceGroupState *sgState = FindSourceGroupState(RPF_interface(destination).first, destination, sgp, true);
	if(sgState->upstream && sgState->upstream->SG_PLT.IsRunning()){//the prune timer is not active
		NS_LOG_DEBUG("Limiting prune on LAN with PLT");
	}
	else {
		PIMHeader msg;
		ForgeJoinPruneMessage(msg, destination);
		PIMHeader::MulticastGroupEntry mge;
		CreateMulticastGroupEntry(mge, ForgeEncodedGroup(sgp.groupMulticastAddr));
		AddMulticastGroupSourcePrune(mge, ForgeEncodedSource(sgp.sourceMulticastAddr));
		AddMulticastGroupEntry(msg, mge);
		Ptr<Packet> packet = Create<Packet> ();
		Simulator::Schedule(TransmissionDelay(),&MulticastRoutingProtocol::SendPacketPIMUnicast, this, packet, msg, destination);
	}
}

void
MulticastRoutingProtocol::SendJoinUnicast (Ipv4Address destination, SourceGroupPair &sgp)
{
	NS_LOG_FUNCTION(this<< destination<<sgp.sourceMulticastAddr<<sgp.groupMulticastAddr);
	PIMHeader msg;
	ForgeJoinPruneMessage(msg, destination);
	PIMHeader::MulticastGroupEntry mge;
	CreateMulticastGroupEntry(mge, ForgeEncodedGroup(sgp.groupMulticastAddr));
	AddMulticastGroupSourceJoin(mge, ForgeEncodedSource(sgp.sourceMulticastAddr));
	AddMulticastGroupEntry(msg, mge);
//	msg.Print(std::cout);
	Ptr<Packet> packet = Create<Packet> ();
	Simulator::Schedule(TransmissionDelay(),&MulticastRoutingProtocol::SendPacketPIMUnicast, this, packet, msg, destination);
	NS_LOG_LOGIC("SG Pair ("<<sgp.sourceMulticastAddr <<", "<< sgp.groupMulticastAddr<<") via UpstreamNeighbor \""<< destination<<"\"");
}

void
MulticastRoutingProtocol::ForgeAssertMessage (int32_t interface, Ipv4Address destination, PIMHeader &msg, SourceGroupPair &sgp)
{
	NS_LOG_FUNCTION(this << interface << destination<<sgp.sourceMulticastAddr<<sgp.groupMulticastAddr);
	SourceGroupState *sgState = FindSourceGroupState(interface, destination, sgp);
	ForgeHeaderMessage(PIM_ASSERT, msg);
	PIMHeader::AssertMessage &assertMessage = msg.GetAssertMessage();
	assertMessage.m_sourceAddr =  ForgeEncodedUnicast(sgp.sourceMulticastAddr);
	assertMessage.m_multicastGroupAddr = ForgeEncodedGroup(sgp.groupMulticastAddr);
	assertMessage.m_R = 0;
	assertMessage.m_metricPreference = (sgState==NULL) ? GetMetricPreference(interface):sgState->AssertWinner.metricPreference;
	assertMessage.m_metric = (sgState==NULL) ? GetRouteMetric(interface, sgp.sourceMulticastAddr): sgState->AssertWinner.routeMetric;
}

void
MulticastRoutingProtocol::ForgeAssertCancelMessage (int32_t interface, PIMHeader &msg, SourceGroupPair &sgp)
{
	//An AssertCancel(S, G) message is simply an Assert message for (S, G)
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
	ForgeHeaderMessage(PIM_ASSERT, msg);
	PIMHeader::AssertMessage &assertMessage = msg.GetAssertMessage();
	assertMessage.m_sourceAddr =  ForgeEncodedUnicast(sgp.sourceMulticastAddr);
	assertMessage.m_multicastGroupAddr = ForgeEncodedGroup(sgp.groupMulticastAddr);
	assertMessage.m_R = 0;
	assertMessage.m_metricPreference = 0xffffffff;
	assertMessage.m_metric = 0xffffffff;
}

void
MulticastRoutingProtocol::ForgeGraftMessage (int32_t interface, PIMHeader &msg, SourceGroupPair &sgp, Ipv4Address upstreamNeighbor)
{
	NS_LOG_FUNCTION(this);
	ForgeHeaderMessage(PIM_GRAFT, msg);
	PIMHeader::GraftMessage &graft = msg.GetGraftMessage();
	graft.m_joinPruneMessage.m_upstreamNeighborAddr = ForgeEncodedUnicast(upstreamNeighbor);
	graft.m_joinPruneMessage.m_reserved = 0;
	graft.m_joinPruneMessage.m_numGroups = 0;
	graft.m_joinPruneMessage.m_holdTime = Seconds(Hold_Time_Default);
}

void
MulticastRoutingProtocol::SendGraftUnicast (Ipv4Address destination, SourceGroupPair sgp)
{
	NS_LOG_FUNCTION(this);
	Ptr<Packet> packet = Create<Packet> ();
	PIMHeader msg; // Create the graft packet
	ForgeGraftMessage(PIM_GRAFT, msg, sgp, destination);
	PIMHeader::MulticastGroupEntry mge;
	CreateMulticastGroupEntry(mge, ForgeEncodedGroup(sgp.groupMulticastAddr));
	AddMulticastGroupSourceJoin(mge, ForgeEncodedSource(sgp.sourceMulticastAddr));
	AddMulticastGroupEntry(msg, mge);
	NS_LOG_LOGIC("SG Pair ("<<sgp.sourceMulticastAddr <<", "<< sgp.groupMulticastAddr<<") via UpstreamNeighbor \""<< destination<<"\"");
	// Send the packet toward the RPF(S)
	Simulator::Schedule(TransmissionDelay(),&MulticastRoutingProtocol::SendPacketPIMUnicast, this, packet, msg, destination);
}

void
MulticastRoutingProtocol::ForgeGraftAckMessage (PIMHeader &msg, Ipv4Address upstreamNeighbor)
{
	NS_LOG_FUNCTION(this);
	ForgeHeaderMessage(PIM_GRAFT_ACK, msg);
	PIMHeader::GraftAckMessage &jpMessage = msg.GetGraftAckMessage();
	jpMessage.m_joinPruneMessage.m_upstreamNeighborAddr = ForgeEncodedUnicast(upstreamNeighbor);
	jpMessage.m_joinPruneMessage.m_reserved = 0;
	jpMessage.m_joinPruneMessage.m_numGroups = 0;
	jpMessage.m_joinPruneMessage.m_holdTime = Seconds(Hold_Time_Default);
}

void
MulticastRoutingProtocol::SendGraftAckUnicast(SourceGroupPair &sgp, const Ipv4Address destination)
{
	NS_LOG_FUNCTION(this);
	Ptr<Packet> packet = Create<Packet> ();
	PIMHeader::MulticastGroupEntry mge;
	CreateMulticastGroupEntry(mge, ForgeEncodedGroup(sgp.groupMulticastAddr));
	AddMulticastGroupSourceJoin(mge, ForgeEncodedSource(sgp.sourceMulticastAddr));
	PIMHeader msg; // Create the graft packet
	ForgeGraftAckMessage(msg, destination);
	AddMulticastGroupEntry(msg, mge);
	NS_LOG_LOGIC("SG Pair ("<<sgp.sourceMulticastAddr <<", "<< sgp.groupMulticastAddr<<") via UpstreamNeighbor \""<< destination);
	// Send the packet toward the RPF(S)
	Simulator::Schedule(TransmissionDelay(),&MulticastRoutingProtocol::SendPacketPIMUnicast, this, packet, msg, destination);
}

void
MulticastRoutingProtocol::ForgeStateRefresh (int32_t interface, Ipv4Address destination, SourceGroupPair &sgp, PIMHeader &msg)
{
	NS_LOG_FUNCTION(this);
	SourceGroupState *sgState = FindSourceGroupState(interface, destination, sgp);
	ForgeHeaderMessage(PIM_STATE_REF, msg);
	PIMHeader::StateRefreshMessage &refresh = msg.GetStateRefreshMessage();
	refresh.m_multicastGroupAddr = ForgeEncodedGroup(sgp.groupMulticastAddr);
	refresh.m_sourceAddr = ForgeEncodedUnicast(sgp.sourceMulticastAddr);
	Ipv4Address nextHop = RPF_interface(sgp.sourceMulticastAddr).second;
	refresh.m_originatorAddr = ForgeEncodedUnicast(Ipv4Address(GetLocalAddress(interface)));
	//	 The Rendezvous Point Tree bit.  Set to 0 for PIM-DM.  Ignored upon receipt.
	refresh.m_R = 0;
	refresh.m_metricPreference = GetMetricPreference(interface);//(sgp.sourceMulticastAddr));
	refresh.m_metric = GetRouteMetric(interface,sgp.sourceMulticastAddr);
	refresh.m_maskLength = IPV4_ADDRESS_SIZE;
	refresh.m_ttl = (sgState->SG_DATA_TTL>0 ? sgState->SG_DATA_TTL : sgState->SG_SR_TTL);
//    Prune indicator flag.  This MUST be set to 1 if the State Refresh
//		is to be sent on a Pruned interface.  Otherwise, it MUST be set to 0.
	refresh.m_P = (sgState->PruneState==Prune_Pruned?1:0);
//  Prune Now flag.  This SHOULD be set to 1 by the State Refresh
//	    originator on every third State Refresh message and SHOULD be
//	    ignored upon receipt.  This is for compatibility with earlier
//	    versions of state refresh.
	refresh.m_N = 0;
//	 Assert Override flag.  This SHOULD be set to 1 by upstream routers
//	     on a LAN if the Assert Timer (AT(S,G)) is not running and SHOULD be
//	     ignored upon receipt.  This is for compatibility with earlier
//	     versions of state refresh.
	refresh.m_O = (!sgState->SG_AT.IsRunning())?1:0;
	refresh.m_reserved = 0;
	refresh.m_interval = RefreshInterval;
}

void
MulticastRoutingProtocol::SendStateRefreshMessage (int32_t interface, Ipv4Address destination, SourceGroupPair &sgp)
{
	NS_LOG_FUNCTION(this);
	SourceGroupState *sgState = FindSourceGroupState(interface, destination, sgp);
	Ptr<Packet> packet = Create<Packet> ();
	PIMHeader msg;
	ForgeStateRefresh(interface, destination, sgp, msg);
	NeighborhoodStatus *ns = FindNeighborhoodStatus(interface);
	NS_ASSERT_MSG(ns!=NULL, "SendStateRefreshMessage, invalid NeighborhoodStatus on "<< interface);
	Time tmp = ns->stateRefreshInterval;
	PIMHeader::StateRefreshMessage &stateRefresh = msg.GetStateRefreshMessage();
	stateRefresh.m_metricPreference = sgState->AssertWinner.metricPreference;
	stateRefresh.m_metric = sgState->AssertWinner.routeMetric;
	stateRefresh.m_interval = (uint8_t)(tmp.GetSeconds());
	Simulator::Schedule(TransmissionDelay(),&MulticastRoutingProtocol::SendPacketPIMUnicast, this, packet, msg, destination);
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
			//Send State Refresh(S, G) out interface I. The router has refreshed the Prune(S, G) state on interface I.
			//	The router MUST reset the Prune Timer (PT(S, G, I)) to the Holdtime from an active Prune received on interface I.
			//	The Holdtime used SHOULD be the largest active one but MAY be the most recently received active Prune Holdtime.
			if(sgState->SG_PT.IsRunning())
				sgState->SG_PT.Cancel();
			sgState->SG_PT.SetDelay(FindNeighborhoodStatus(interface)->pruneHoldtime);
			sgState->SG_PT.SetFunction(&MulticastRoutingProtocol::PTTimerExpire, this);
			sgState->SG_PT.SetArguments(sgp, interface);
			sgState->SG_PT.Schedule();
			break;
		}
		default:
			NS_LOG_ERROR("SendStateRefreshMessage : Prune state not valid"<<sgState->PruneState);
			break;
	}
	switch (sgState->AssertState){
		case  Assert_NoInfo:{
			break;
			}
		case Assert_Winner:{
			//Send State Refresh
			//	The router is sending a State Refresh(S, G) message on interface I.
			//	The router MUST set the Assert Timer (AT(S, G, I)) to three
			//	times the State Refresh Interval contained in the State Refresh(S, G) message.
			if(sgState->SG_AT.IsRunning())
				sgState->SG_AT.Cancel();
			sgState->SG_AT.SetDelay(Seconds(3*msg.GetStateRefreshMessage().m_interval));
			sgState->SG_AT.SetFunction(&MulticastRoutingProtocol::ATTimerExpire, this);
			sgState->SG_AT.SetArguments(sgp, interface, destination);
			sgState->SG_AT.Schedule();
			break;
			}
		case Assert_Loser:{
			//nothing
			break;
		}
		default:{
			NS_LOG_ERROR("SendStateRefreshMessage: Assert State not valid"<<sgState->AssertState);
			break;
		}
	}
}

void
MulticastRoutingProtocol::RPFCheckAll()
{
	NS_LOG_FUNCTION(this);
	for(std::map<WiredEquivalentInterface, SourceGroupList>::iterator sgList = m_IfaceSourceGroup.begin();
			sgList != m_IfaceSourceGroup.end();  sgList++){
		int32_t interface = sgList->first.first;
		Ipv4Address destination = sgList->first.second;
		NS_LOG_DEBUG("Interface "<<interface<<", Destination "<< destination<< " SGPairs "<<sgList->second.size());
		for(std::list<SourceGroupState>::iterator sgState = sgList->second.begin();
				sgState != sgList->second.end(); sgState++){
			Ptr<Ipv4Route> route;
			NS_ASSERT(interface < m_ipv4->GetNInterfaces());
			Simulator::Schedule(Seconds(0),&MulticastRoutingProtocol::RPFCheck, this, sgState->SGPair);//, interface);//, route);
		}
	}
	m_rpfChecker.Schedule();
}

void
MulticastRoutingProtocol::RPFCheck (SourceGroupPair sgp)
{
	NS_LOG_DEBUG("("<<sgp.sourceMulticastAddr<<","<<sgp.groupMulticastAddr<<")");
	RoutingMulticastTable entry;
	MulticastEntry me;
	WiredEquivalentInterface wei = RPF_interface(sgp.sourceMulticastAddr);
	int32_t interfaceN = wei.first;
	Ipv4Address gatewayN = wei.second;
	bool ret = Lookup(sgp.groupMulticastAddr,sgp.sourceMulticastAddr, entry, me); // there is a entry for this group/source
	ret = ret && (interfaceN != -1 && isValidGateway(gatewayN)); // there is a valid gateway
	ret = ret && entry.mgroup.find(sgp.sourceMulticastAddr) != entry.mgroup.end(); // there is a record for the source
	if(ret) {
		if(me.nextAddr == Ipv4Address::GetLoopback()){//now we know the RPF for the first time, just update it!
			UpdateEntry(sgp.groupMulticastAddr,sgp.sourceMulticastAddr,gatewayN,interfaceN);
			SourceGroupState *sgState = FindSourceGroupState(interfaceN, gatewayN, sgp, true);///we will know the gateway later, so add the entry
			Lookup(sgp.groupMulticastAddr,sgp.sourceMulticastAddr, entry, me);
		}
		if((me.interface != interfaceN || me.nextAddr != gatewayN) && interfaceN>0){//RPF neighbor has changed
			Ipv4Address gatewayO = me.nextAddr;
			int32_t interfaceO = me.interface;
			UpdateEntry (sgp.groupMulticastAddr, sgp.sourceMulticastAddr, gatewayN, interfaceN);//continue from here: problem is that in the second roung it
			RPF_Changes (sgp, interfaceO, gatewayO, interfaceN, gatewayN);
			RPF_primeChanges (sgp, me.interface, me.nextAddr, interfaceN, gatewayN);//check interface old is right
//			if(FindSourceGroupState (interfaceN, gatewayN, sgp)->upstream && !FindSourceGroupState(me.interface , me.nextAddr, sgp)->upstream)//RPF prime change succeed
//				UpdateEntry (sgp.groupMulticastAddr,sgp.sourceMulticastAddr,gatewayN,interfaceN);
//			else
//				NS_LOG_DEBUG ("RPF "<< gatewayN<<" not found: looking for it");
		}
	}
}

void
MulticastRoutingProtocol::RPF_Changes(SourceGroupPair &sgp, int32_t oldInterface, Ipv4Address oldGateway, int32_t newInterface, Ipv4Address newGateway)
{
	NS_LOG_FUNCTION(this<<sgp.sourceMulticastAddr<<sgp.groupMulticastAddr<<oldInterface<<oldGateway<<newInterface<<newGateway);
	bool couldAssert = CouldAssert(sgp.sourceMulticastAddr, sgp.groupMulticastAddr, oldInterface, oldGateway);
	CouldAssertCheck(sgp.sourceMulticastAddr, sgp.groupMulticastAddr, oldInterface, oldGateway, couldAssert);
	SourceGroupState *sgStateO = FindSourceGroupState(oldInterface, oldGateway, sgp);
	if(sgp.sourceMulticastAddr == oldGateway)
		SourceNoDirectlyConnected(sgp, oldInterface, oldGateway);
	SourceGroupState *sgStateN = FindSourceGroupState(newInterface, newGateway, sgp, true); // true remove before of rpf_changes
	if (!sgStateN->upstream)
		sgStateN->upstream = new UpstreamState ();
	couldAssert = CouldAssert(sgp.sourceMulticastAddr, sgp.groupMulticastAddr, newInterface, newGateway);
	CouldAssertCheck(sgp.sourceMulticastAddr, sgp.groupMulticastAddr, newInterface, newGateway, couldAssert);
	if(sgp.sourceMulticastAddr == newGateway)
		SourceDirectlyConnected(sgp);
	switch (sgStateN->PruneState) {
		case Prune_NoInfo:{
			// nothing
			break;
		}
		case Prune_PrunePending:
		//RPF_Interface(S) becomes interface I. The upstream interface for S has changed.
		//	The Prune(S, G) Downstream state machine on interface I MUST transition to the
		//	NoInfo (NI) state.  The PrunePending Timer (PPT(S, G, I)) MUST be cancelled.
		case Prune_Pruned:{
		//RPF_Interface(S) becomes interface I. The upstream interface for S has changed.
		//	The Prune(S, G) Downstream state machine on interface I MUST transition to the NoInfo (NI) state.
		//	The PruneTimer (PT(S, G, I)) MUST be cancelled.
			sgStateN->PruneState = Prune_NoInfo;
			if(sgStateN->SG_PT.IsRunning())
				sgStateN->SG_PT.Cancel();
			break;
		}
		default:
			NS_LOG_ERROR("PTTimerExpire: Prune state not valid"<<sgStateN->PruneState);
			break;
	}
}

void
MulticastRoutingProtocol::RPF_primeChanges(SourceGroupPair &sgp, uint32_t interfaceO, Ipv4Address gatewayO, int32_t interfaceN, Ipv4Address gatewayN)
{
	NS_LOG_FUNCTION(this << sgp.sourceMulticastAddr<<sgp.groupMulticastAddr << interfaceO<<gatewayO << interfaceN<<gatewayN);
	std::set<WiredEquivalentInterface> outlist = olist(sgp.sourceMulticastAddr, sgp.groupMulticastAddr);
	SourceGroupState *sgState = FindSourceGroupState(interfaceO, gatewayO, sgp);
	if(sgState->upstream->SG_GRT.IsRunning()) // remove all pending timers...
		sgState->upstream->SG_GRT.Remove();
	if(sgState->upstream->SG_OT.IsRunning())
		sgState->upstream->SG_OT.Remove();
	if(sgState->upstream->SG_PLT.IsRunning())
		sgState->upstream->SG_PLT.Remove();
	if(sgState->upstream->SG_SAT.IsRunning())
		sgState->upstream->SG_SAT.Remove();
	if(sgState->upstream->SG_SRT.IsRunning())
		sgState->upstream->SG_SRT.Remove();
//	delete sgState->upstream;
	sgState->upstream->origination = NotOriginator;
	sgState->upstream->GraftPrune = GP_Pruned;
	// starting new entries
	sgState = FindSourceGroupState(interfaceN, gatewayN, sgp, true); // find new RPF pair...
	NS_ASSERT(isValidGateway(gatewayN));
	NS_ASSERT(sgState->upstream);
	switch (sgState->upstream->GraftPrune){
		case GP_Forwarding:{
		//RPF'(S) Changes AND olist(S, G) is NULL
		//	Unicast routing or Assert state causes RPF'(S) to change, including changes to RPF_Interface(S).
		//	The Upstream(S, G) state machine MUST transition to the Pruned (P) state.
			if(outlist.size()==0){
				sgState->upstream->GraftPrune = GP_Pruned;
			}
		//RPF'(S) Changes AND olist(S, G) is non-NULL AND S NOT directly connected
		//	Unicast routing or Assert state causes RPF'(S) to change, including changes to RPF_Interface(S).
		//	The Upstream(S, G) state machine MUST transition to the AckPending (AP) state,
		//	unicast a Graft to the new RPF'(S), and set the GraftRetry Timer (GRT(S, G)) to Graft_Retry_Period.
			if(outlist.size()>0 && sgp.sourceMulticastAddr != gatewayN){
				sgState->upstream->GraftPrune = GP_AckPending;
				SendGraftUnicast(gatewayN, sgp);
				NeighborState tmp(gatewayN, GetLocalAddress(interfaceN));
				NeighborState *ns = FindNeighborState(interfaceN, tmp);
				if(!ns){// RPF_Prime changed with a new neighbor we didn't know before...
					InsertNeighborState(interfaceN, tmp);//add it and send a Hello...
					ns = FindNeighborState(interfaceN, tmp);
					NeighborhoodStatus *nst = FindNeighborhoodStatus(interfaceN);
					// If a Hello message is received from a new neighbor, the receiving router SHOULD send its own Hello message
					//    after a random delay between 0 and Triggered_Hello_Delay.
					Time delay = TransmissionDelay(0, Triggered_Hello_Delay);
					Simulator::Schedule (delay, &MulticastRoutingProtocol::SendHelloReply, this, interfaceN, gatewayN);
					NS_LOG_DEBUG("Neighbors = "<< nst->neighbors.size() << ", reply at "<<(Simulator::Now()+delay).GetSeconds());
				}
				if(sgState->upstream->SG_GRT.IsRunning())
					sgState->upstream->SG_GRT.Cancel();
				sgState->upstream->SG_GRT.SetDelay(Seconds(Graft_Retry_Period));
				sgState->upstream->SG_GRT.SetFunction(&MulticastRoutingProtocol::GRTTimerExpire, this);
				sgState->upstream->SG_GRT.SetArguments(sgp, interfaceN, gatewayN);
				sgState->upstream->SG_GRT.Schedule();
			}
			break;
		}
		case GP_Pruned:{
			if(outlist.size()==0 && sgp.sourceMulticastAddr != gatewayN){
			//RPF'(S) Changes AND olist(S, G) == NULL AND S NOT directly connected
			//	Unicast routing or Assert state causes RPF'(S) to change, including changes to RPF_Interface(S).
			//	The Upstream(S, G) state machine stays in the Pruned (P) state and MUST cancel the PLT(S, G) timer.
				sgState->upstream->SG_PLT.Cancel();
			}
			if(outlist.size()>0 && sgp.sourceMulticastAddr != gatewayN){
			//RPF'(S) Changes AND olist(S, G) == non-NULL AND S NOT directly connected
			//	Unicast routing or Assert state causes RPF'(S) to change, including changes to RPF_Interface(S).
			//	The Upstream(S, G) state machine MUST cancel PLT(S, G), transition to the AckPending (AP) state,
			//	send a Graft unicast to the new RPF'(S), and set the GraftRetry Timer (GRT(S, G)) to Graft_Retry_Period.
				sgState->upstream->SG_PLT.Cancel();
				sgState->upstream->GraftPrune = GP_AckPending;
				SendGraftUnicast(gatewayN, sgp);
				if(sgState->upstream->SG_GRT.IsRunning())
					sgState->upstream->SG_GRT.Cancel();
				sgState->upstream->SG_GRT.SetDelay(Seconds(Graft_Retry_Period));
				sgState->upstream->SG_GRT.SetFunction(&MulticastRoutingProtocol::GRTTimerExpire, this);
				sgState->upstream->SG_GRT.SetArguments(sgp, interfaceN, gatewayN);
				sgState->upstream->SG_GRT.Schedule();
			}
			break;
		}
		case GP_AckPending:{
			if(outlist.size()==0 && sgp.sourceMulticastAddr != gatewayN){
			//RPF'(S) Changes AND olist(S, G) == NULL AND S NOT directly connected
			//	Unicast routing or Assert state causes RPF'(S) to change, including changes to RPF_Interface(S).
			//	The Upstream(S, G) state machine MUST transition to the Pruned (P) state.
			//	The GraftRetry Timer (GRT(S, G)) MUST be canceled.
				sgState->upstream->GraftPrune = GP_Pruned;
				if(sgState->upstream->SG_GRT.IsRunning())
					sgState->upstream->SG_GRT.Cancel();
			}
			if(outlist.size()>0 && sgp.sourceMulticastAddr != gatewayN){
				//RPF'(S) Changes AND olist(S, G) does not become NULL AND S NOT directly connected
				//	Unicast routing or Assert state causes RPF'(S) to change, including changes to RPF_Interface(S).
				//	The Upstream(S, G) state machine stays in the AckPending (AP) state.
				//	A Graft MUST be unicast to the new RPF'(S) and the GraftRetry Timer (GRT(S, G)) reset to Graft_Retry_Period.
				SendGraftUnicast(gatewayN, sgp);
				if(sgState->upstream->SG_GRT.IsRunning())
					sgState->upstream->SG_GRT.Cancel();
				sgState->upstream->SG_GRT.SetDelay(Seconds(Graft_Retry_Period));
				sgState->upstream->SG_GRT.SetFunction(&MulticastRoutingProtocol::GRTTimerExpire, this);
				sgState->upstream->SG_GRT.SetArguments(sgp, interfaceN, gatewayN);
				sgState->upstream->SG_GRT.Schedule();
			}
			break;
		}
		default:{
			NS_LOG_ERROR("RPF prime changed: state not valid"<<sgState->upstream->GraftPrune);
			break;
		}
	}
	if(!isValidGateway(gatewayN))
		return AskRoute(sgp.sourceMulticastAddr);//find the gateway before change RPF_prime!
}

void
MulticastRoutingProtocol::RecvMessage (Ptr<Socket> socket)
{
	NS_LOG_FUNCTION(this);
	Ptr<Packet> receivedPacket;
	Address sourceAddress;
	receivedPacket = socket->RecvFrom (sourceAddress);
	InetSocketAddress inetSourceAddr = InetSocketAddress::ConvertFrom (sourceAddress);
	Ipv4Address senderIfaceAddr = inetSourceAddr.GetIpv4 ();
	uint16_t senderIfacePort = inetSourceAddr.GetPort();
	int32_t interface = m_ipv4->GetInterfaceForDevice(socket->GetBoundNetDevice());
	Ipv4Address receiverIfaceAddr = m_ipv4->GetAddress(interface, 0).GetLocal();
	NS_ASSERT (receiverIfaceAddr != Ipv4Address ());
	Ipv4Header ipv4header;
	receivedPacket->RemoveHeader(ipv4header);
	RelayTag rtag;
	bool tag = receivedPacket->RemovePacketTag(rtag);
	Ipv4Address group = ipv4header.GetDestination();
	NS_LOG_LOGIC("Node "<<receiverIfaceAddr<< ": Sender "<< senderIfaceAddr << " Port " << senderIfacePort<< " Group "<< group<<  " Tag "<<tag);
	receivedPacket->AddHeader(ipv4header);
	if (tag || (group.IsMulticast() && group != Ipv4Address(ALL_PIM_ROUTERS4))){//Lookup(ipv4header.GetDestination(),ipv4header.GetSource(),rmt,me)){
		if(tag) receivedPacket->AddPacketTag(rtag);
		this->RecvPIMData (receivedPacket, senderIfaceAddr, senderIfacePort, interface);
		m_rxDataPacketTrace (receivedPacket);
	}
	else if (group == Ipv4Address(ALL_PIM_ROUTERS4) || group == GetLocalAddress(interface)){
		this->RecvPIMDM (receivedPacket, senderIfaceAddr, senderIfacePort, interface);
	}
	else
		NS_LOG_ERROR("Unexpected message "<< receivedPacket);
}



void
MulticastRoutingProtocol::RecvPIMDM (Ptr<Packet> receivedPacket, Ipv4Address senderIfaceAddr, uint16_t senderIfacePort, int32_t interface)
{
	NS_LOG_FUNCTION(this);
	Ptr<Ipv4Route> route = GetRoute (senderIfaceAddr);
	Ipv4Address receiverIfaceAddr = GetLocalAddress(interface);
	NS_ASSERT (receiverIfaceAddr != Ipv4Address ());
	NS_ASSERT (interface);
	Ipv4Header ipv4header;
	receivedPacket->RemoveHeader(ipv4header);
	Ipv4Address group = ipv4header.GetDestination();
	Ipv4Address localAddr = GetLocalAddress(interface);
	NS_LOG_LOGIC("Sender = "<< senderIfaceAddr<<", Group = " << group << ", Destination = "<< receiverIfaceAddr);
	if(route) NS_LOG_DEBUG("\t Route = "<<localAddr<< " <"<<interface<<"> " <<route->GetGateway() <<" <...> "<<senderIfaceAddr);
	if(ipv4header.GetDestination().IsMulticast() && ipv4header.GetDestination() != Ipv4Address(ALL_PIM_ROUTERS4)) {
		NS_LOG_ERROR("Received "<< ipv4header.GetDestination() <<" it should be captured by another callback.");
		return;
	}
	if(!isValidGateway(route->GetGateway()))
		return AskRoute(senderIfaceAddr);
	NS_ASSERT (senderIfacePort != PIM_PORT_NUMBER);
	//Unlike PIM-SM, PIM-DM does not maintain a keepalive timer associated with each (S, G) route.
	//  Within PIM-DM, route and state information associated with an (S, G) entry MUST be maintained as long as any
	//	timer associated with that (S, G) entry is active.  When no timer associated with an (S, G) entry is active,
	//	all information concerning that (S, G) route may be discarded.
	PIMHeader pimdmPacket;
	receivedPacket->RemoveHeader(pimdmPacket);
//	if(pimdmPacket.GetType()!=PIM_HELLO && !IsValidSG(GetReceivingInterface(receiverIfaceAddr), senderIfaceAddr, group)){
//		NS_LOG_DEBUG ("PIM-DM No running timer: discarded");
//		return;
//	}
	switch (pimdmPacket.GetType()){
		case PIM_HELLO:{
			RecvHello(pimdmPacket.GetHelloMessage(), senderIfaceAddr, receiverIfaceAddr, interface);
			break;
			}
		case PIM_JP:{
			RecvJP(pimdmPacket.GetJoinPruneMessage(), senderIfaceAddr, receiverIfaceAddr, interface);
			break;
			}
		case PIM_ASSERT:{
			RecvAssert(pimdmPacket.GetAssertMessage(), senderIfaceAddr, receiverIfaceAddr, interface);
			break;
			}
		case PIM_GRAFT:{
			RecvGraft(pimdmPacket.GetGraftMessage(), senderIfaceAddr, receiverIfaceAddr, interface);
			break;
			}
		case PIM_GRAFT_ACK:{
			RecvGraftAck(pimdmPacket.GetGraftAckMessage(), senderIfaceAddr, receiverIfaceAddr, interface);
			break;
			}
		case PIM_STATE_REF:{
			RecvStateRefresh(pimdmPacket.GetStateRefreshMessage(), senderIfaceAddr, receiverIfaceAddr, interface);
			break;
			}
		default:{
			NS_LOG_ERROR("Packet unrecognized.... "<< receivedPacket<<"Sender "<< senderIfaceAddr<<", Destination "<< receiverIfaceAddr);
			break;
			}
	}
	m_rxPacketTrace (pimdmPacket);
}

void
MulticastRoutingProtocol::RecvPIMData (Ptr<Packet> receivedPacket, Ipv4Address senderIfaceAddr, uint16_t senderIfacePort, int32_t interface)
{
	NS_LOG_FUNCTION(this);
	NS_ASSERT(interface);
	Ipv4Address source, group, sender, destination, gateway;
	Ptr<Packet> copy = receivedPacket->Copy();// Ipv4Header, UdpHeader and SocketAddressTag must be removed.
	Ipv4Header sourceHeader;
	RelayTag relayTag;
	copy->RemoveHeader(sourceHeader);
	source = sourceHeader.GetSource();
	group = sourceHeader.GetDestination();
	sender = source;
	destination = group;
	bool rtag = copy->RemovePacketTag(relayTag);
	if(rtag){
		sender = relayTag.m_sender;
		destination = relayTag.m_receiver;
	}
	Ptr<Ipv4Route> rpf_route = GetRoute(source);
	gateway = rpf_route->GetGateway();
	int32_t gatewayIface = m_ipv4->GetInterfaceForDevice(rpf_route->GetOutputDevice());
	bool relay_packet_other = rtag && !IsMyOwnAddress(destination); // has the relay tag and the destination is not this node
	bool not_source_packet = !rtag && destination.IsMulticast() && gateway != source; // no relay tag and destination is multicast and was not issued by the source
	if(relay_packet_other || not_source_packet){
		NS_LOG_DEBUG("Drop packet "<< copy->GetUid()<< ", is for someone else [S:"<< source<<"; G:"<<gateway<<"; D:"<<  destination << "] Tag: ["<< relayTag.m_sender << ","<<relayTag.m_receiver<<"]");
		return;
	}
	if(!isValidGateway(gateway) && IsMyOwnAddress(destination)){
		return AskRoute(source);
	}
	NS_ASSERT(IsMyOwnAddress(destination));//useless
	SocketAddressTag satag;
	copy->RemovePacketTag(satag); // LOOK: it must be removed because will be added again by socket.
	NS_ASSERT (group.IsMulticast());
	NS_LOG_LOGIC("Group "<<group<<" Source "<< source<< " Sender ("<< sender<<", " << interface<<") -- Gateway ("<<gateway<< ", " << gatewayIface << ")");
	NS_LOG_LOGIC("\tLocal "<<GetLocalAddress(interface)<< " Metric: "<< GetRouteMetric(interface,source)<<" PacketSize "<<copy->GetSize()<< ", PID "<<receivedPacket->GetUid());
	NS_ASSERT(group.IsMulticast());
	SourceGroupPair sgp (source, group, sender);
	SourceGroupState *sgState = FindSourceGroupState(interface, sender, sgp, true);
	RPFCheck (sgp);
	std::set<WiredEquivalentInterface> fwd_list = olist(source, group);
	if(IsUpstream(interface, sender, sgp)){ /*sender in on the RPF towards the source*/
		switch (sgState->upstream->GraftPrune){
			//The Upstream(S, G) state machine MUST transition to the Pruned (P)
			// state, send a Prune(S, G) to RPF'(S), and set PLT(S, G) to t_limit seconds.
			case GP_Forwarding:{
				if(fwd_list.size() == 0 && gateway != source && !GetMulticastGroup(group)){
					olistCheck(sgp, fwd_list);//CHECK: olist is null and S not directly connected
					sgState->upstream->GraftPrune = GP_Pruned;
					if(sgState->upstream->SG_PLT.IsRunning())
						sgState->upstream->SG_PLT.Cancel();
					sgState->upstream->SG_PLT.SetDelay(Seconds(t_limit));
					sgState->upstream->SG_PLT.SetFunction(&MulticastRoutingProtocol::PLTTimerExpire, this);//re-schedule transmission
					sgState->upstream->SG_PLT.SetArguments(sgp, sender);
					sgState->upstream->SG_PLT.Schedule();
					SendPruneUnicast(sender, sgp);
					return;
					}
					break;
				}
			case GP_Pruned:{
				if(!sgState->upstream->SG_PLT.IsRunning() && gateway != source){
					sgState->upstream->SG_PLT.SetDelay(Seconds(t_limit));
					sgState->upstream->SG_PLT.SetFunction(&MulticastRoutingProtocol::PLTTimerExpire, this);//re-schedule transmission
					sgState->upstream->SG_PLT.SetArguments(sgp, sender);
					sgState->upstream->SG_PLT.Schedule();
					SendPruneUnicast(sender, sgp);
					return;
					}
					break;
				}
			case GP_AckPending:{
				//nothing
				break;
			}
			default:{
				NS_LOG_ERROR("RecvPIMData: Graft Prune state not valid"<<sgState->upstream->GraftPrune);
				break;
			}
		}
		switch (sgState->upstream->origination) {
			case NotOriginator:{
				//Data Packet received from directly connected Source S addressed to group G.
				//	The router MUST transition to an Originator (O) state, set SAT(S, G) to SourceLifetime,
				//	and set SRT(S, G) to StateRefreshInterval.
				//	The router SHOULD record the TTL of the packet for use in State Refresh messages.
				if(source == gateway){
					sgState->upstream->origination = Originator;
					if(sgState->upstream->SG_SAT.IsRunning())
						sgState->upstream->SG_SAT.Cancel();
					sgState->upstream->SG_SAT.SetDelay(Seconds(SourceLifetime));
					sgState->upstream->SG_SAT.SetFunction(&MulticastRoutingProtocol::SATTimerExpire, this);
					sgState->upstream->SG_SAT.SetArguments(sgp, interface, gateway);
					sgState->upstream->SG_SAT.Schedule();
					if(sgState->upstream->SG_SRT.IsRunning())
						sgState->upstream->SG_SRT.Cancel();
					sgState->upstream->SG_SRT.SetDelay(Seconds(RefreshInterval));
					sgState->upstream->SG_SRT.SetFunction(&MulticastRoutingProtocol::SRTTimerExpire, this);
					sgState->upstream->SG_SRT.SetArguments(sgp, interface);
					sgState->upstream->SG_SRT.Schedule();
					sgState->SG_DATA_TTL = sourceHeader.GetTtl();
				}
				break;
			}
			case Originator:{
			//Receive Data Packet from S addressed to G.
			//	The router remains in the Originator (O) state and MUST reset
			//	SAT(S, G) to SourceLifetime.  The router SHOULD increase its
			//	recorded TTL to match the TTL of the packet, if the packet's TTL
			//	is larger than the previously recorded TTL.  A router MAY record
			//	the TTL based on an implementation specific sampling policy to
			//	avoid examining the TTL of every multicast packet it handles.
				if(sgState->upstream->SG_SAT.IsRunning())
					sgState->upstream->SG_SAT.Cancel();
				sgState->upstream->SG_SAT.SetDelay(Seconds(SourceLifetime));
				sgState->upstream->SG_SAT.SetFunction(&MulticastRoutingProtocol::SATTimerExpire, this);
				sgState->upstream->SG_SAT.SetArguments(sgp, interface, gateway);
				sgState->upstream->SG_SAT.Schedule();
				double sample = UniformVariable().GetValue();
				if(sample < TTL_SAMPLE && sourceHeader.GetTtl() > sgState->SG_DATA_TTL){
					sgState->SG_DATA_TTL += 1;
				}
				break;
			}
			default:{
				NS_LOG_ERROR("RecvStateRefresh: Origination state not valid"<<sgState->upstream->origination);
				break;
			}
		}
	}
	else {
		switch (sgState->AssertState){
			case  Assert_NoInfo:
			//An (S, G) data packet arrives on downstream interface I.
			//   An (S, G) data packet arrived on a downstream interface.  It is
			//   optimistically assumed that this router will be the Assert winner
			//   for this (S, G).  The Assert state machine MUST transition to the
			//   "I am Assert Winner" state, send an Assert(S, G) to interface I,
			//   store its own address and metric as the Assert Winner, and set
			//   the Assert_Timer (AT(S, G, I) to Assert_Time, thereby initiating
			//   the Assert negotiation for (S, G).
			case Assert_Winner:{
			//An (S, G) data packet arrives on downstream interface I.
			//	An (S, G) data packet arrived on a downstream interface.
			//	The Assert state machine remains in the "I am Assert Winner" state.
			//	The router MUST send an Assert(S, G) to interface I and set the Assert Timer (AT(S, G, I) to Assert_Time.
				//if(!IsDownstream(interface, sgp)) NS_LOG_ERROR("Packet received on Upstream interface! Assert_NoInfo");//WIRED
				sgState->AssertState = Assert_Winner;
				UpdateAssertWinner(sgState, interface);
				PIMHeader assert;
				ForgeAssertMessage(interface, sender, assert, sgp);
				Ptr<Packet> packetA = Create<Packet> ();
				Simulator::Schedule(TransmissionDelay(),&MulticastRoutingProtocol::SendPacketPIMUnicast, this, packetA, assert, sender);
				if(sgState->SG_AT.IsRunning())
					sgState->SG_AT.Cancel();
				sgState->SG_AT.SetDelay(Seconds(Assert_Time));
				sgState->SG_AT.SetFunction(&MulticastRoutingProtocol::ATTimerExpire, this);
				sgState->SG_AT.SetArguments(sgp, interface, sender);
				sgState->SG_AT.Schedule();
				break;
			}
			case Assert_Loser:{
				//nothing
				break;
			}
			default:{
				NS_LOG_ERROR("RecvPIMData: Assert State not valid "<<sgState->AssertState);
				break;
			}
		}
	}
	//	   Section 4.2. Data Packet Forwarding Rules.
	//	   Upon receipt of a data packet from S addressed to G on interface iif:
	//
	//	   if (iif == RPF_interface(S) AND UpstreamPState(S, G) != Pruned) {
	//	       oiflist = olist(S, G)
	//	   } else {
	//	       oiflist = NULL
	//	   }
	//	   forward packet on all interfaces in oiflist
	//
	//	   This pseudocode employs the following "macro" definition:
	//
	//	   UpstreamPState(S, G) is the state of the Upstream(S, G) state machine in Section 4.4.1.

	///   First, an RPF check MUST be performed to determine whether the packet should be accepted based on TIB state
	///      and the interface on which that the packet arrived.
	if(IsUpstream(interface, sender, sgp) && sgState->PruneState != Prune_Pruned ){
		/// If the RPF check has been passed, an outgoing interface list is constructed for the packet.
		/// If this list is not empty, then the packet MUST be forwarded to all listed interfaces.
//		fwd_list = olist(source, group);
		olistCheck(sgp, fwd_list);
	}
	else {
		//	 If the RPF check has been passed, an outgoing interface list is
		//	   constructed for the packet.  If this list is not empty, then the
		//	   packet MUST be forwarded to all listed interfaces.  If the list is
		//	   empty, then the router will conduct a prune process for the (S,G)
		//	   pair specified in the packet.
		NS_LOG_DEBUG("RPF check failed: Sending Prune to "<< sender);
		SendPruneUnicast(sender, sgp);
		return;
	}
	///   Packets that fail the RPF check MUST NOT be forwarded, and the router will conduct an assert process for the (S, G) pair specified in the packet.
	///   Packets for which a route to the source cannot be found MUST be discarded.
	NS_LOG_DEBUG("Data forwarding towards > "<< fwd_list.size()<<" < interfaces/nodes");
	// Forward packet on all interfaces in oiflist.
	Time delayMS = TransmissionDelay();
	for(std::set<WiredEquivalentInterface>::iterator out = fwd_list.begin(); out != fwd_list.end(); out++){
		Ptr<Packet> fwdPacket = copy->Copy(); // create a copy of the packet for each interface;
		//add a header
		if(!IsMyOwnAddress(out->second)) {//to PIM neighbors
			Ipv4Address localAddr = GetLocalAddress(out->first);
			RelayTag relayF (localAddr, out->second);
			fwdPacket->AddPacketTag(relayF);
			fwdPacket->AddHeader(sourceHeader);
			NS_LOG_DEBUG("DataFwd towards node ("<<out->second <<", "<< out->first <<") bytes: " << fwdPacket->GetSize()<< ", delay: "<<delayMS.GetSeconds()<<"ms");
			Simulator::Schedule(delayMS,&MulticastRoutingProtocol::SendPacketUnicast, this, fwdPacket, out->second);
		}
//		else{
//			relyTag.m_rely = 2;//to Clients
//			fwdPacket->AddPacketTag(relyTag);
//			NS_LOG_DEBUG("DataFwd towards clients ("<<out->second <<", "<< out->first <<") interfaces/nodes "<< fwdPacket->GetSize()<< " delay "<<delayMS.GetSeconds());
//			Simulator::Schedule(delayMS,&MulticastRoutingProtocol::SendPacketHBroadcastInterface, this, fwdPacket, sourceHeader, out->first);
//		}
		delayMS += TransmissionDelay();
	}
}

void
MulticastRoutingProtocol::RecvGraft (PIMHeader::GraftMessage &graft, Ipv4Address sender, Ipv4Address receiver, int32_t interface)
{
	NS_LOG_FUNCTION(this << sender << receiver << interface);
	for(std::vector<PIMHeader::MulticastGroupEntry>::iterator mgroup = graft.m_multicastGroups.begin();
			mgroup!=graft.m_multicastGroups.end(); mgroup++){
		for(std::vector<PIMHeader::EncodedSource>::iterator msource = mgroup->m_joinedSourceAddrs.begin();
					msource != mgroup->m_joinedSourceAddrs.end(); msource++){
			if(!IsUpstream(interface, sender, msource->m_sourceAddress, mgroup->m_multicastGroupAddr.m_groupAddress)){
				RecvGraftDownstream (graft, sender, receiver, *msource, mgroup->m_multicastGroupAddr, interface);
			}
		}
	}
}

void
MulticastRoutingProtocol::RecvGraftDownstream(PIMHeader::GraftMessage &graft, Ipv4Address sender, Ipv4Address receiver, const PIMHeader::EncodedSource &source, PIMHeader::EncodedGroup &group, int32_t interface)
{
	NS_LOG_FUNCTION(this<<sender<<receiver<<interface<<source.m_sourceAddress<<group.m_groupAddress);
	SourceGroupPair sgp (source.m_sourceAddress, group.m_groupAddress, sender);
	SourceGroupState *sgState = FindSourceGroupState(interface, sender, sgp, true);
	if(graft.m_joinPruneMessage.m_upstreamNeighborAddr.m_unicastAddress == receiver){
		switch (sgState->PruneState) {
			case Prune_NoInfo:{
			//A Graft(S, G) is received on the interface I with the upstream neighbor field set to the router's
			//	address on I.  The Prune(S, G) Downstream state machine on interface I stays in the NoInfo (NI)
			//	state.  A GraftAck(S, G) MUST be unicast to the originator of the Graft(S, G) message.
				SendGraftAckUnicast(sgp, sender);
				break;
			}
			case Prune_PrunePending:{
			//Receive Graft(S, G): A Graft(S, G) is received on interface I with the upstream neighbor
			//	field set to the router's address on I.  The Prune(S, G) Downstream state machine on
			//	interface I MUST transition to the NoInfo (NI) state and MUST unicast a Graft Ack
			//	message to the Graft originator.  The PrunePending Timer (PPT(S, G, I)) MUST be cancelled.
				sgState->PruneState = Prune_NoInfo;
				SendGraftAckUnicast(sgp, sender);
				sgState->SG_PPT.Cancel();
				break;
			}
			//Receive Graft(S, G). A Graft(S, G) is received on interface I with the upstream neighbor field
			//	set to the router's address on I.  The Prune(S, G) Downstream state machine on interface I
			//	MUST transition to the NoInfo (NI) state and send a Graft Ack back to the Graft's source.
			//	The Prune Timer (PT(S, G, I)) MUST be cancelled.
			//	The router MUST evaluate any possible transitions in the Upstream(S, G) state machine.
			case Prune_Pruned:{
				sgState->PruneState = Prune_NoInfo;
				SendGraftAckUnicast(sgp, sender);
				if(sgState->SG_PPT.IsRunning())
					sgState->SG_PPT.Cancel();
				UpstreamStateMachine(sgp);
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
				//Receive Prune(S, G), Join(S, G), or Graft(S, G).
				//	A Prune(S, G), Join(S, G), or Graft(S, G) message was received on
				//	interface I with its upstream neighbor address set to the
				//	router's address on I.  The router MUST send an Assert(S, G) on
				//	the receiving interface I to initiate an Assert negotiation.  The
				//	Assert state machine remains in the Assert Loser(L) state.  If a
				//	Graft(S, G) was received, the router MUST respond with a GraftAck(S, G).
				PIMHeader assertR;
				ForgeAssertMessage(interface, sender, assertR, sgp);
				Ptr<Packet> packet = Create<Packet> ();
				Simulator::Schedule(TransmissionDelay(),&MulticastRoutingProtocol::SendPacketPIMUnicast, this, packet, assertR, sender);
				SendGraftAckUnicast(sgp, sender);
//				sgState->AssertState = Assert_Winner; ***
//				UpdateAssertWinner(sgState, interface);
				//An Assert loser that receives a Prune(S, G), Join(S, G), or
				//  Graft(S, G) directed to it initiates a new Assert negotiation so
				//  that the downstream router can correct its RPF'(S).
				break;
			}
			default:{
				NS_LOG_ERROR("RecvGraftDownstream: Assert State not valid"<<sgState->AssertState);
				break;
			}
		}
	}
}

void
MulticastRoutingProtocol::RecvGraftAck (PIMHeader::GraftAckMessage &graftAck, Ipv4Address sender, Ipv4Address receiver, int32_t interface)
{
	NS_LOG_FUNCTION(this<<sender<<receiver<<interface);
	//The transition event "RcvGraftAck(S, G)" implies receiving a Graft Ack message targeted to this router's address on the incoming interface
	//	for the (S, G) entry.  If the destination address is not correct, the state transitions in this state machine must not occur.
	if(GetLocalAddress(interface) != graftAck.m_joinPruneMessage.m_upstreamNeighborAddr.m_unicastAddress) return;
	for(std::vector<struct PIMHeader::MulticastGroupEntry>::iterator groups = graftAck.m_multicastGroups.begin();
			groups != graftAck.m_multicastGroups.end(); groups++){
		for(std::vector<PIMHeader::EncodedSource>::const_iterator iterSource = groups->m_joinedSourceAddrs.begin();
				iterSource!=groups->m_joinedSourceAddrs.end(); iterSource++){
			SourceGroupPair sgp (iterSource->m_sourceAddress, groups->m_multicastGroupAddr.m_groupAddress, sender);
			SourceGroupState *sgState = FindSourceGroupState(interface, sender, sgp);
			NS_LOG_DEBUG("Removing Timer GRAFT " << sgState->upstream->SG_GRT.GetDelayLeft().GetMilliSeconds()<<" ms");
			if(IsUpstream(interface, sender, sgp) ){
				switch (sgState->upstream->GraftPrune){
				//The Upstream(S, G) state machine MUST transition to the Pruned (P)
				// state, send a Prune(S, G) to RPF'(S), and set PLT(S, G) to t_limit seconds.
					case GP_Forwarding:{
						//nothing
						break;
					}
					case GP_Pruned:{
						//nothing
						break;
					}
					case GP_AckPending:{
						if(sgState->upstream->SG_GRT.IsRunning())
							sgState->upstream->SG_GRT.Cancel();
						sgState->upstream->GraftPrune = GP_Forwarding;
						break;
					}
					default:{
						NS_LOG_ERROR("RecvGraftAck: Graft Prune state not valid"<<sgState->upstream->GraftPrune);
						break;
					}
				}
			}
	}
}
}

void
MulticastRoutingProtocol::NeighborRestart (int32_t interface, Ipv4Address neighbor)
{
//   If a Hello message is received from an active neighbor with a
//   different Generation ID (GenID), the neighbor has restarted and may
//   not contain the correct (S, G) state.  A Hello message SHOULD be sent
//   after a random delay between 0 and Triggered_Hello_Delay (see 4.8)
//   before any other messages are sent.
	Time delay = TransmissionDelay(0, Triggered_Hello_Delay);
	Simulator::Schedule (Seconds(0), &MulticastRoutingProtocol::SetStopTx, this);
	Simulator::Schedule (delay, &MulticastRoutingProtocol::UnsetStopTx, this);
	Time hellos = TransmissionDelay(delay.GetDouble(), Triggered_Hello_Delay);
	Simulator::Schedule (hellos, &MulticastRoutingProtocol::SendHelloReply, this, interface, neighbor);
//   If the neighbor is downstream, the router MAY replay the last State Refresh message for any (S, G)
//   pairs for which it is the Assert Winner indicating Prune and Assert status to the downstream router.
//	 These State Refresh messages SHOULD be sent out immediately after the Hello message.
	SourceGroupList sgList = m_IfaceSourceGroup.find(WiredEquivalentInterface(interface,neighbor))->second;
	Time srm = TransmissionDelay(hellos.GetDouble(), Triggered_Hello_Delay);
	NS_LOG_DEBUG("Stop @ 0; Start @ "<<delay.GetSeconds()<<"; Hello @ "<< hellos.GetSeconds()<<"; SRM @ "<<srm.GetSeconds());
	for(std::list<SourceGroupState>::iterator sgState = sgList.begin(); sgState!=sgList.end(); sgState++){
		if(IsDownstream(interface, neighbor, sgState->SGPair) && sgState->AssertState == Assert_Winner){
			Simulator::Schedule (srm, &MulticastRoutingProtocol::SendStateRefreshMessage, this, interface, neighbor, sgState->SGPair);
			break;
		}
		// If the neighbor is the upstream neighbor for an (S, G) entry, the router MAY cancel its
		//     Prune Limit Timer to permit sending a prune and reestablishing a Pruned state in the upstream router.
		else if (IsUpstream(interface, neighbor, sgState->SGPair) && sgState->PruneState == Prune_Pruned){
			if(sgState->SG_PT.IsRunning())
				sgState->SG_PT.Cancel();
			sgState->SG_PT.SetDelay(Seconds(2*RefreshInterval));
			sgState->SG_PT.SetFunction(&MulticastRoutingProtocol::PTTimerExpire, this);
			sgState->SG_PT.SetArguments(sgState->SGPair);
			sgState->SG_PT.Schedule();
			Simulator::Schedule (Seconds(0), &MulticastRoutingProtocol::SendPruneUnicast, this, neighbor, sgState->SGPair);
		}
	}
}

void
MulticastRoutingProtocol::SendPacketPIMRoutersInterface(Ptr<Packet> packet, const PIMHeader &message, int32_t interface)
{
  if(m_stopTx) return;
  packet->AddHeader(message);
  Ipv4Header ipv4header = BuildHeader(GetLocalAddress(interface), Ipv4Address(ALL_PIM_ROUTERS4), PIM_IP_PROTOCOL_NUM, packet->GetSize(), PIMDM_TTL, false);
  packet->AddHeader(ipv4header);
  // Trace it
  m_txPacketTrace (message);
  // Send
  if(interface != 0 && !GetPimInterface(interface)){
	  NS_LOG_DEBUG("Interface "<<interface<<" is PIM-DISABLED");
	  return;
  }
  for (std::map<Ptr<Socket> , Ipv4InterfaceAddress>::const_iterator i =
        m_socketAddresses.begin (); i != m_socketAddresses.end (); i++)
      {
	  NS_LOG_DEBUG ("Socket ("<<i->first<<") "<< i->second.GetLocal() << " to Destination: " << ALL_PIM_ROUTERS4 << ":"<<PIM_PORT_NUMBER
			  << ", Local "<<GetLocalAddress(interface)<< ", If "<<  m_ipv4->GetInterfaceForDevice (i->first->GetBoundNetDevice()));
	  if(m_ipv4->GetInterfaceForDevice (i->first->GetBoundNetDevice()) == interface && !i->second.GetLocal ().IsMulticast()){
		  Ipv4Address bcast = i->second.GetLocal ().GetSubnetDirectedBroadcast (i->second.GetMask ());
		  NS_LOG_LOGIC ("Node " << GetLocalAddress(interface)<< " is sending to "<< bcast<<":"<<PIM_PORT_NUMBER<<", Socket "<< i->first);
		  i->first->SendTo (packet, 0, InetSocketAddress (bcast, PIM_PORT_NUMBER));
		  break;
	  }
      }
}

void
MulticastRoutingProtocol::SendPacketPIMUnicast(Ptr<Packet> packet, const PIMHeader &message, Ipv4Address destination)
{
  if(m_stopTx) return;
  packet->AddHeader(message);
  // Trace it
  m_txPacketTrace (message);
  // Send
  WiredEquivalentInterface wei = RPF_interface(destination);
  int32_t interface = wei.first >0 ? wei.first : m_ipv4->GetInterfaceForAddress(m_mainAddress);
  Ipv4Address local = GetLocalAddress(interface);
  for (std::map<Ptr<Socket> , Ipv4InterfaceAddress>::const_iterator i =
	m_socketAddresses.begin (); i != m_socketAddresses.end (); i++)
	{
	  if(local == i->second.GetLocal () ){
		Ptr<Packet> copy = packet->Copy();
		Ipv4Header ipv4Header = BuildHeader(i->second.GetLocal (), destination, PIM_IP_PROTOCOL_NUM, copy->GetSize(), 1, false);
		copy->AddHeader(ipv4Header);
		NS_LOG_LOGIC ("Node " << local << " is sending packet "<<copy  <<"("<<copy->GetSize() <<  ") to Destination: " << destination << ":"<<PIM_PORT_NUMBER<<", Interface "<<interface<<", Socket "<<i->first);
		i->first->SendTo (copy, 0, InetSocketAddress (destination, PIM_PORT_NUMBER));
		break;
		}
	}
}


void
MulticastRoutingProtocol::SendPacketUnicast(Ptr<Packet> packet, Ipv4Address destination)
{
  if(m_stopTx) return;
  // trace
  m_txDataPacketTrace (packet);
  // Send
  WiredEquivalentInterface wei = RPF_interface(destination);
  int32_t interface = wei.first >0 ? wei.first : m_ipv4->GetInterfaceForAddress(m_mainAddress);
  Ipv4Address local = GetLocalAddress(interface);
  for (std::map<Ptr<Socket> , Ipv4InterfaceAddress>::const_iterator i =
        m_socketAddresses.begin (); i != m_socketAddresses.end (); i++)
      {
  	  if(local == i->second.GetLocal () ){
  		  Ptr<Packet> copy = packet->Copy();
  		  NS_LOG_LOGIC ("Node " << local << " is sending packet "<<copy <<"("<<copy->GetSize() << ") to Destination: " << destination << ", Interface "<<interface<<", Socket "<<i->first);
  		  i->first->SendTo (copy, 0, InetSocketAddress (destination, PIM_PORT_NUMBER));
  		  break;
  	  }
	}
}

void
MulticastRoutingProtocol::SendPacketHBroadcastInterface (Ptr<Packet> packet, Ipv4Header &ipv4Header, int32_t interface)
{
	if(m_stopTx) return;
	NS_LOG_FUNCTION(this);
	// Send it
	Ipv4Header senderHeader;
	UdpHeader udpHeader;
	packet->RemoveHeader(senderHeader);
	packet->RemoveHeader(udpHeader);
	Ipv4Address remote = senderHeader.GetDestination();
	for (std::map<Ptr<Socket> , Ipv4InterfaceAddress>::const_iterator i =
	  m_socketAddresses.begin (); i != m_socketAddresses.end (); i++)
	{
	  NS_LOG_DEBUG("Local "<<i->second.GetLocal()<<", Broad "<<i->second.GetBroadcast()<<", Mask "<<i->second.GetMask());
	  if(GetLocalAddress(interface) == i->second.GetLocal ()){
		  packet->AddHeader(ipv4Header);
		  NS_LOG_LOGIC ("Node " << GetObject<Node> ()->GetId() << " is forwarding packet " << packet <<"("<<packet->GetSize() << ") to Destination "<< ipv4Header.GetDestination() <<", Interface "<< interface<< ", Pid "<< packet->GetUid()<<", Socket "<<i->first);
		  i->first->SendTo (packet, 0, InetSocketAddress (remote));
		  break; // Just to speedup and avoid the complete loop over all sockets.
	  }
	}
}

bool
MulticastRoutingProtocol::IsValidSG(int32_t interface, const Ipv4Address & source, const Ipv4Address & group){
	Ipv4Address nexthop = RPF_interface(source).second;
	SourceGroupPair sgp (source, group, nexthop);
	SourceGroupState *sgState = FindSourceGroupState(interface, nexthop, sgp, true);
	bool valid = false;
	if(sgState){
		valid = valid || sgState->SG_PT.IsRunning();
		valid = valid || sgState->SG_AT.IsRunning();
		valid = valid || sgState->SG_PPT.IsRunning();
		///     Upstream interface-specific
		if(IsUpstream(interface, nexthop, sgp)){
			valid = valid || sgState->upstream->SG_OT.IsRunning();
			valid = valid || sgState->upstream->SG_GRT.IsRunning();
			valid = valid || sgState->upstream->SG_PLT.IsRunning();
			valid = valid || sgState->upstream->SG_SAT.IsRunning();
			valid = valid || sgState->upstream->SG_SRT.IsRunning();
		}
	}
	return valid;
}

//This timer is used to rate-limit Prunes on a LAN.
//       It is only used when the Upstream(S, G) state machine is in the Pruned state.
//       A Prune cannot be sent if this timer is running.
//       This timer is normally set to t_limit (see 4.8).
void
MulticastRoutingProtocol::PLTTimerExpire (SourceGroupPair &sgp, Ipv4Address destination)
{
	NS_LOG_FUNCTION(this);
	WiredEquivalentInterface wei = RPF_interface(destination);
	SourceGroupState *sgState = FindSourceGroupState(wei.first, destination, sgp);
	if(!IsUpstream(wei.first, destination, sgp)) return; // interface changed
	if(sgState->PruneState == Prune_Pruned) return;
	SendPruneUnicast(destination, sgp);
	if(sgState->upstream->SG_PLT.IsRunning())
		sgState->upstream->SG_PLT.Cancel();
	sgState->upstream->SG_PLT.SetFunction(&MulticastRoutingProtocol::PLTTimerExpire, this);
	sgState->upstream->SG_PLT.SetArguments(sgp, destination);
	sgState->upstream->SG_PLT.Schedule();
}

void
MulticastRoutingProtocol::NLTTimerExpire (Ipv4Address neighborIfaceAddr, Ipv4Address receivingIfaceAddr, int32_t interface)
{
	SourceGroupList *sgList= FindSourceGroupList(interface, neighborIfaceAddr); // get all the S, G pair
	for (SourceGroupList::iterator sgState = sgList->begin(); sgState != sgList->end() ; sgState++){
		if(sgState->AssertWinner.IPAddress == neighborIfaceAddr){// Find the assert winner
			switch (sgState->AssertState){
				case  Assert_NoInfo:{
					break;
					}
				case Assert_Winner:{
					break;
					}
				case Assert_Loser:{
					//Current Assert Winner's NeighborLiveness Timer Expires
					//	The current Assert winner's NeighborLiveness Timer (NLT(N, I)) has
					//	expired.  The Assert state machine MUST transition to the NoInfo
					//	(NI) state, delete the Assert Winner's address and metric, and
					//	evaluate any possible transitions to its Upstream(S, G) state machine.
					sgState->AssertState = Assert_NoInfo;
					UpdateAssertWinner(&*sgState, 0xffffffff, 0xffffffff, Ipv4Address("255.255.255.255"));
					UpstreamStateMachine(sgState->SGPair);
					break;
				}
				default:{
					NS_LOG_ERROR("NLTTimerExpire: Assert State not valid"<<sgState->AssertState);
					break;
				}
			}
		}
	}
}

void
MulticastRoutingProtocol::OTTimerExpire (SourceGroupPair &sgp, int32_t interface)
{
	NS_LOG_FUNCTION(this);
	Ipv4Address gateway = RPF_prime(sgp.sourceMulticastAddr, sgp.groupMulticastAddr);
	SourceGroupState *sgState = FindSourceGroupState(interface, sgp.nextMulticastAddr, sgp);
	NS_ASSERT(sgState);
	NS_ASSERT(sgState->upstream);
	if(!isValidGateway(gateway)){
		if(sgState->upstream){
			sgState->upstream->SG_OT.Cancel();
			sgState->upstream->SG_OT.SetDelay(Seconds(t_override(interface)));
			sgState->upstream->SG_OT.SetFunction(&MulticastRoutingProtocol::OTTimerExpire, this);
			sgState->upstream->SG_OT.SetArguments(sgp, interface);
			sgState->upstream->SG_OT.Schedule();
		}
		return AskRoute(gateway);
	}
	sgState = FindSourceGroupState(interface, gateway, sgp, true);
	switch (sgState->upstream->GraftPrune){
		case GP_Forwarding:{
			//    OT(S,G) Expires AND S NOT directly connected
			//      The OverrideTimer (OT(S,G)) expires.  The router MUST send a
			//      Join(S,G) to RPF'(S) to override a previously detected prune.
			//      The Upstream(S,G) state machine remains in the Forwarding (F) state.
			if(gateway != sgp.sourceMulticastAddr)
				SendJoinUnicast(gateway, sgp);
			break;
		}
		case GP_AckPending:{
			//    OT(S,G) Expires
			//      The OverrideTimer (OT(S,G)) expires.  The router MUST send a
			//      Join(S,G) to RPF'(S).  The Upstream(S,G) state machine remains in
			//      the AckPending (AP) state.
			SendJoinUnicast(gateway, sgp); //broadcast
			break;
		}
		case GP_Pruned:{
			break;
		}
		default:{
			NS_LOG_ERROR("OT_Timer: state not valid"<<sgState->upstream->GraftPrune);
			break;
		}
	}
	sgState->upstream->SG_OT.Cancel();
}

void
MulticastRoutingProtocol::GRTTimerExpire (SourceGroupPair &sgp, int32_t interface, Ipv4Address destination)
{
	NS_LOG_FUNCTION(this);
	SourceGroupState *sgState = FindSourceGroupState(interface, destination, sgp);
	NS_ASSERT(sgState);
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
		//The GraftRetry Timer (GRT(S, G)) expires for this (S, G) entry.
		//	The Upstream(S, G) state machine stays in the AckPending (AP) state.
		//	Another Graft message for (S, G) SHOULD be unicast to RPF'(S) and the GraftRetry Timer (GRT(S, G)) reset to Graft_Retry_Period.
		//	It is RECOMMENDED that the router retry a configured number of times before ceasing retries.
			NeighborState dest(destination, GetLocalAddress(interface));
			NeighborState *ns = FindNeighborState(interface, dest, true);
//			Ptr<Ipv4Route> route = GetRoute(destination);
//			if(route->GetGateway() == Ipv4Address::GetLoopback()) break; //Node lost the neighbor -> send graft guarantee to find the gw
			if(ns->neighborGraftRetry[0]<ns->neighborGraftRetry[1]){//increase counter retries
				ns->neighborGraftRetry[0]++;
				SendGraftUnicast(destination, sgp);
				if(sgState->upstream->SG_GRT.IsRunning())
					sgState->upstream->SG_GRT.Cancel();
				sgState->upstream->SG_GRT.SetDelay(Seconds(Graft_Retry_Period));
				sgState->upstream->SG_GRT.SetFunction(&MulticastRoutingProtocol::GRTTimerExpire, this);
				sgState->upstream->SG_GRT.SetArguments(sgp, interface, destination);
				sgState->upstream->SG_GRT.Schedule();
			}else{
				ns->neighborGraftRetry[0] = 0;//reset counter retries
			}
			break;
		}
		default:{
			NS_LOG_ERROR("GRTTimerExpire: state not valid"<<sgState->upstream->GraftPrune);
			break;
		}
	}
}

void
MulticastRoutingProtocol::PPTTimerExpire (SourceGroupPair &sgp, int32_t interface, Ipv4Address destination)
{
	NS_LOG_FUNCTION(this << sgp.sourceMulticastAddr << sgp.groupMulticastAddr << interface<<GetLocalAddress(interface) << destination);
	SourceGroupState *sgState = FindSourceGroupState(interface, destination, sgp);
	NS_ASSERT_MSG(sgState,"PPTTimerExpire sgState is null");
	switch (sgState->PruneState) {
		case Prune_NoInfo:{
			// nothing
			break;
		}
		case Prune_PrunePending:{
		//PPT(S, G, I) Expires: The PrunePending Timer (PPT(S, G, I)) expires, indicating that no
		//	neighbors have overridden the previous Prune(S, G) message.  The Prune(S, G) Downstream
		//	state machine on interface I MUST transition to the Pruned (P) state.
			sgState->PruneState = Prune_Pruned;
		//	The Prune Timer (PT(S, G, I)) is started and MUST be initialized to the received
		//	Prune_Hold_Time minus J/P_Override_Interval.
			NeighborhoodStatus *nstatus = FindNeighborhoodStatus(interface);
			Time JP_Override_Interval= nstatus->overrideInterval+nstatus->propagationDelay;
			Time Delay = nstatus->pruneHoldtime - JP_Override_Interval;
			Delay = (Delay.GetSeconds()>=0 ? Delay: Seconds(0));
			if(nstatus->neighbors.size()>1){// Prune echo
			//  A PruneEcho(S, G) MUST be sent on I if I has more than one PIM neighbor.
			//	A PruneEcho(S, G) is simply a Prune(S, G) message
			//	multicast by the upstream router to a LAN, with itself as the Upstream Neighbor.
				int32_t interface = RPF_interface(sgp.sourceMulticastAddr).first;
				PIMHeader prune;
				ForgeJoinPruneMessage(prune, GetLocalAddress(interface));
				PIMHeader::MulticastGroupEntry mge;
				CreateMulticastGroupEntry(mge, ForgeEncodedGroup(sgp.groupMulticastAddr));
				AddMulticastGroupSourcePrune(mge, ForgeEncodedSource(sgp.sourceMulticastAddr));
				AddMulticastGroupEntry(prune, mge);
				Ptr<Packet> packet = Create<Packet> ();
				Simulator::Schedule(TransmissionDelay(),&MulticastRoutingProtocol::SendPacketPIMUnicast, this, packet, prune, destination);
			//	Its purpose is to add additional reliability so that if a Join that should have
			//	overridden the Prune is lost locally on the LAN, the PruneEcho(S, G) may be received
			//	and trigger a new Join message.
			//	A PruneEcho(S, G) is OPTIONAL on an interface with only one PIM neighbor.
			//	In addition, the router MUST evaluate any possible transitions in the Upstream(S, G) state machine.
				UpstreamStateMachine(sgp);
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
MulticastRoutingProtocol::PTTimerExpire (SourceGroupPair &sgp, int32_t interface)
{
	NS_LOG_FUNCTION(this<<interface<<sgp.sourceMulticastAddr<<sgp.groupMulticastAddr);
	Ipv4Address nexthop = GetNextHop(sgp.sourceMulticastAddr);
	SourceGroupState *sgState = FindSourceGroupState(interface, nexthop, sgp);
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
		//PT(S, G, I) Expires. The Prune Timer (PT(S, G, I)) expires, indicating that it is again
		//	time to flood data from S addressed to group G onto interface I.
		//	The Prune(S, G) Downstream state machine on interface I MUST transition to the NoInfo (NI) state.
		//	The router MUST evaluate any possible transitions in the Upstream(S, G) state machine.
			sgState->PruneState = Prune_NoInfo;
			UpstreamStateMachine(sgp);
			break;
		}
		default:
			NS_LOG_ERROR("PTTimerExpire: Prune state not valid"<<sgState->PruneState);
			break;
	}
}

//This timer controls when State Refresh messages are generated.
//     The timer is initially set when that Origination(S, G) state
//     machine transitions to the O state.  It is cancelled when the
//     Origination(S, G) state machine transitions to the NO state.  This
//     timer is normally set to StateRefreshInterval (see 4.8).
void
MulticastRoutingProtocol::SRTTimerExpire (SourceGroupPair &sgp, int32_t interface)
{
	NS_LOG_FUNCTION(this<<interface<<sgp.sourceMulticastAddr<<sgp.groupMulticastAddr);
	Ipv4Address gw = RPF_interface(sgp.sourceMulticastAddr).second;
	SourceGroupState *sgState = FindSourceGroupState(interface, gw, sgp);
	if(!sgState)return AskRoute(sgp.sourceMulticastAddr);
	for(NeighborList::iterator iter = m_IfaceNeighbors.find(interface)->second.neighbors.begin();
						iter != m_IfaceNeighbors.find(interface)->second.neighbors.end(); iter++){
		Ipv4Address destination = iter->neighborIfaceAddr;
		SourceGroupState *sgStateBis = FindSourceGroupState(interface, destination, sgp, true);
		if(sgState->upstream->origination){
		switch (sgState->upstream->origination) {
			case NotOriginator:{
				//nothing
				break;
			}
			case Originator:{
			//SRT(S, G) Expires.
			//	The router remains in the Originator (O) state and MUST reset
			//	SRT(S, G) to StateRefreshInterval. The router MUST also generate
			//	State Refresh messages for transmission, as described in the
			//	State Refresh Forwarding rules (Section 4.5.1), except for the TTL.
			//	If the TTL of data packets from S to G are being recorded,
			//	then the TTL of each State Refresh message is set to the highest
			//	recorded TTL.  Otherwise, the TTL is set to the configured State
			//	Refresh TTL.  Let I denote the interface over which a State
			//	Refresh message is being sent.  If the Prune(S, G) Downstream
			//	state machine is in the Pruned (P) state, then the Prune-
			//	Indicator bit MUST be set to 1 in the State Refresh message being
			//	sent over I. Otherwise, the Prune-Indicator bit MUST be set to 0.
				if(sgState->upstream->SG_SRT.IsRunning())
					sgState->upstream->SG_SRT.Cancel();
				sgState->upstream->SG_SRT.SetDelay(Seconds(RefreshInterval));
				sgState->upstream->SG_SRT.SetFunction(&MulticastRoutingProtocol::SRTTimerExpire, this);
				sgState->upstream->SG_SRT.SetArguments(sgp, interface);
				sgState->upstream->SG_SRT.Schedule();
				PIMHeader refresh;
				ForgeStateRefresh(interface, destination, sgp, refresh);
				refresh.GetStateRefreshMessage().m_P = (IsDownstream(interface, destination, sgp) && (sgStateBis->PruneState == Prune_Pruned) ? 1 : 0);
				Ptr<Packet> packet = Create<Packet> ();
				Simulator::Schedule(TransmissionDelay(),&MulticastRoutingProtocol::SendPacketPIMUnicast, this, packet, refresh, destination);
				break;
			}
			default:{
				NS_LOG_ERROR("SRTTimerExpire: Origination state not valid"<<sgState->upstream->origination);
				break;
			}
		}
	}
	}
}

void
MulticastRoutingProtocol::ATTimerExpire (SourceGroupPair &sgp, int32_t interface, Ipv4Address destination)
{
	NS_LOG_FUNCTION(this<<destination<<interface<<sgp.sourceMulticastAddr<<sgp.groupMulticastAddr);
	SourceGroupState *sgState = FindSourceGroupState(interface, destination, sgp);
	switch (sgState->AssertState){
		case  Assert_NoInfo:{
			break;
			}
		case Assert_Winner:{
			//AT(S, G, I) Expires
			//	The (S, G) Assert Timer (AT(S, G, I)) expires.  The Assert state
			//	machine MUST transition to the NoInfo (NI) state.
			sgState->AssertState = Assert_NoInfo;
			break;
			}
		case Assert_Loser:{
			//AT(S, G, I) Expires
			//	The (S, G) Assert Timer (AT(S, G, I)) expires.  The Assert state
			//	machine MUST transition to NoInfo (NI) state.  The router MUST
			//	delete the Assert Winner's address and metric.
			sgState->AssertState = Assert_NoInfo;
			UpdateAssertWinner(sgState, 0xffffffff, 0xffffffff, Ipv4Address("255.255.255.255"));
			//If CouldAssert == TRUE, the router MUST evaluate any possible transitions to its Upstream(S, G) state machine.
			if(CouldAssert(sgp.sourceMulticastAddr, sgp.groupMulticastAddr, interface, destination)){
				UpstreamStateMachine(sgp);
			}
			break;
		}
		default:{
			NS_LOG_ERROR("ATTimerExpire: Assert State not valid"<<sgState->AssertState);
			break;
		}
	}
}

//Source Active Timer (SAT(S,G))
//      This timer is first set when the Origination(S,G) state machine
//      transitions to the O state and is reset on the receipt of every
//      data packet from S addressed to group G.  When it expires, the
//      Origination(S,G) state machine transitions to the NO state.  This
//      timer is normally set to SourceLifetime (see 4.8).
void
MulticastRoutingProtocol::SATTimerExpire (SourceGroupPair &sgp, int32_t interface, Ipv4Address destination)
{
	SourceGroupState *sgState = FindSourceGroupState(interface, destination, sgp);
	if(sgState->upstream){
		switch (sgState->upstream->origination) {
			case NotOriginator:{
				//nothing
				break;
			}
			case Originator:{
			//SAT(S, G) Expires.
			//	The router MUST cancel the SRT(S, G) timer and transition to the NotOriginator (NO) state.
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

void MulticastRoutingProtocol::UpstreamStateMachine(SourceGroupPair &sgp){
	NS_LOG_FUNCTION(this<<sgp);
	WiredEquivalentInterface wei = RPF_interface(sgp.sourceMulticastAddr);
	if (wei.second != sgp.nextMulticastAddr) {
		NS_LOG_DEBUG("No rpf node "<<sgp.nextMulticastAddr);
		return;
	}
	std::set<WiredEquivalentInterface> list = olist(sgp.sourceMulticastAddr, sgp.groupMulticastAddr);
	olistCheck(sgp, list);
}

void
MulticastRoutingProtocol::olistCheck(SourceGroupPair &sgp, std::set<WiredEquivalentInterface> &list)
{
	NS_LOG_FUNCTION(this);
	if(list.size() == 0)
		olistEmpty(sgp);
	else
		olistFull(sgp);
	}

void
MulticastRoutingProtocol::olistEmpty(SourceGroupPair &sgp)
{
	NS_LOG_FUNCTION(this<<sgp.sourceMulticastAddr<<sgp.groupMulticastAddr);
	WiredEquivalentInterface wei = RPF_interface(sgp.sourceMulticastAddr);
	SourceGroupState *sgState = FindSourceGroupState(wei.first, wei.second, sgp);
	switch (sgState->upstream->GraftPrune){
		case GP_Forwarding:{
		// olist(S, G) -> NULL AND S NOT directly connected
       	//   The Upstream(S, G) state machine MUST transition to the Pruned (P)  state,
       	//   send a Prune(S, G) to RPF'(S), and set PLT(S, G) to t_limit seconds.
			if(GetNextHop(sgp.sourceMulticastAddr) != sgp.sourceMulticastAddr){
				sgState ->upstream->GraftPrune = GP_Pruned;
				Ipv4Address gateway = RPF_prime(sgp.sourceMulticastAddr, sgp.groupMulticastAddr);
				SendPruneUnicast(gateway, sgp);
				if(sgState->upstream->SG_PLT.IsRunning())
					sgState->upstream->SG_PLT.Cancel();
				sgState->upstream->SG_PLT.SetDelay(Seconds(t_limit));
				sgState->upstream->SG_PLT.SetFunction(&MulticastRoutingProtocol::PLTTimerExpire, this);
				sgState->upstream->SG_PLT.SetArguments(sgp, gateway);
				sgState->upstream->SG_PLT.Schedule();
			}
			break;
		}
		case GP_Pruned:{
			//nothing
			break;
		}
		case GP_AckPending:{
		//The set of interfaces defined by the olist(S, G) macro becomes null, indicating that traffic from S addressed to group G should
		//	no longer be forwarded.  The Upstream(S, G) state machine MUST transition to the Pruned (P) state.
		//	A Prune(S, G) MUST be multicast to the RPF_interface(S), with RPF'(S) named in the upstream neighbor field.
		//	The GraftRetry Timer (GRT(S, G)) MUST be cancelled, and PLT(S, G) MUST be set to t_limit seconds.
			sgState->upstream->GraftPrune = GP_Pruned;
			WiredEquivalentInterface wei= RPF_interface(sgp.sourceMulticastAddr);
			PIMHeader msg;
			ForgeJoinPruneMessage(msg, wei.second);
			PIMHeader::MulticastGroupEntry mge;
			CreateMulticastGroupEntry(mge, ForgeEncodedGroup(sgp.groupMulticastAddr));
			AddMulticastGroupSourcePrune(mge, ForgeEncodedSource(sgp.sourceMulticastAddr));
			AddMulticastGroupEntry(msg, mge);
			Ptr<Packet> packet = Create<Packet> ();
			Simulator::Schedule(TransmissionDelay(),&MulticastRoutingProtocol::SendPacketPIMUnicast, this, packet, msg, wei.second);
			sgState->upstream->SG_GRT.Cancel();
			sgState->upstream->SG_PLT.SetDelay(Seconds(t_limit));

			break;
		}
		default:{
			NS_LOG_ERROR("OList is empty: state not valid"<<sgState->upstream->GraftPrune);
			break;
		}
	}
}

void
MulticastRoutingProtocol::olistFull(SourceGroupPair &sgp)
{
	WiredEquivalentInterface wei = RPF_interface(sgp.sourceMulticastAddr);
	NS_LOG_FUNCTION(this <<  wei.first << wei.second);
	if(!isValidGateway(wei.second)) return AskRoute(sgp.sourceMulticastAddr);
	SourceGroupState *sgState = FindSourceGroupState(wei.first, wei.second, sgp, true);
	NS_ASSERT(sgState && sgState->upstream);
	switch (sgState->upstream->GraftPrune){
		case GP_Forwarding:{
			//nothing
			break;
		}
		case GP_Pruned:{
		// olist(S, G)->non-NULL AND S NOT directly connected
        //   The set of interfaces defined by the olist(S, G) macro becomes non-empty,
        //   indicating that traffic from S addressed to group G  must be forwarded.
        //   The Upstream(S, G) state machine MUST cancel PLT(S, G), transition to the AckPending (AP) state and unicast a Graft message to RPF'(S).
        //   The Graft Retry Timer (GRT(S, G)) MUST be set to Graft_Retry_Period.
			if(GetNextHop(sgp.sourceMulticastAddr) != sgp.sourceMulticastAddr){
				sgState->upstream->SG_PLT.Cancel();
				sgState->upstream->GraftPrune = GP_AckPending;
				SendGraftUnicast(wei.second, sgp);
				sgState->upstream->SG_GRT.Cancel();
				sgState->upstream->SG_GRT.SetDelay(Seconds(Graft_Retry_Period));
				sgState->upstream->SG_GRT.SetFunction(&MulticastRoutingProtocol::GRTTimerExpire, this);
				sgState->upstream->SG_GRT.SetArguments(sgp, wei.first, wei.second);
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
			break;
		}
	}
}

void
MulticastRoutingProtocol::SourceDirectlyConnected(SourceGroupPair &sgp)
{
	NS_LOG_FUNCTION(this);
	WiredEquivalentInterface wei = RPF_interface(sgp.sourceMulticastAddr);
	SourceGroupState *sgState = FindSourceGroupState(wei.first, wei.second, sgp);
	int32_t interface = wei.first;
	Ipv4Address destination = wei.second;
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
		//	The GraftRetry Timer MUST be canceled, and the Upstream(S, G) state machine MUST transition to the Forwarding(F) state.
			sgState->upstream->SG_GRT.Cancel();
			sgState->upstream->GraftPrune = GP_Forwarding;
			break;
		}
		default:{
			NS_LOG_ERROR("SourceDirectlyConnected: state not valid"<<sgState->upstream->GraftPrune);
			break;
		}
	}
	switch (sgState->upstream->origination) {
		case NotOriginator:{
			sgState->upstream->origination = Originator;
			if(sgState->upstream->SG_SRT.IsRunning())
				sgState->upstream->SG_SRT.Cancel();
			sgState->upstream->SG_SRT.SetDelay(Seconds(RefreshInterval));
			sgState->upstream->SG_SRT.SetFunction(&MulticastRoutingProtocol::SRTTimerExpire, this);
			sgState->upstream->SG_SRT.SetArguments(sgp, interface);
			sgState->upstream->SG_SRT.Schedule();
			if(sgState->upstream->SG_SAT.IsRunning())
				sgState->upstream->SG_SAT.Cancel();
			sgState->upstream->SG_SAT.SetDelay(Seconds(SourceLifetime));
			sgState->upstream->SG_SAT.SetFunction(&MulticastRoutingProtocol::SATTimerExpire, this);
			sgState->upstream->SG_SAT.SetArguments(sgp, interface, destination);
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

void
MulticastRoutingProtocol::SourceNoDirectlyConnected(SourceGroupPair &sgp, uint32_t interface, Ipv4Address gateway)
{
	NS_LOG_FUNCTION(this);
	SourceGroupState *sgState = FindSourceGroupState(interface, gateway, sgp);
	switch (sgState->upstream->origination) {
		case NotOriginator:{
			//nothing
			break;
		}
		case Originator:{
			sgState->upstream->origination = NotOriginator;
			if(sgState->upstream->SG_SRT.IsRunning())
				sgState->upstream->SG_SRT.Cancel();
			if(sgState->upstream->SG_SAT.IsRunning())
				sgState->upstream->SG_SAT.Cancel();
			break;
		}
		default:{
			NS_LOG_ERROR("SourceNoDirectlyConnected: Origination state not valid"<<sgState->upstream->origination);
			break;
		}
	}
}

void
MulticastRoutingProtocol::CouldAssertCheck (Ipv4Address source, Ipv4Address group, int32_t interface, Ipv4Address destination, bool couldAssert) {
	SourceGroupPair sgp (source, group, destination);
	SourceGroupState *sgState = FindSourceGroupState(interface, destination, sgp);//true
	switch (sgState->AssertState){
		case  Assert_NoInfo:{
			break;
			}
		case Assert_Winner:{
			if(couldAssert) break;
			//CouldAssert(S, G, I) -> FALSE
			//	This router's RPF interface changed, making CouldAssert(S, G, I) false.
			//	This router can no longer perform the actions of the Assert winner,
			//	so the Assert state machine MUST transition to NoInfo (NI) state,
			sgState->AssertState = Assert_NoInfo;
			//	send an AssertCancel(S, G) to interface I,
			PIMHeader assertR;
			ForgeAssertCancelMessage(interface, assertR, sgp);
			Ptr<Packet> packet = Create<Packet> ();
			Simulator::Schedule(TransmissionDelay(),&MulticastRoutingProtocol::SendPacketPIMUnicast, this, packet, assertR, destination);
			//  cancel the Assert Timer (AT(S, G, I)),
			if(sgState->SG_AT.IsRunning())
				sgState->SG_AT.Cancel();
			//  and remove itself as the Assert Winner.
			UpdateAssertWinner(sgState, 0xffffffff, 0xffffffff, Ipv4Address("255.255.255.255"));
			break;
			//An Assert winner for (S, G) sends a cancelling assert when it is
			//about to stop forwarding on an (S, G) entry.  Example: If a router
			//is being taken down, then a canceling assert is sent.
			}
		case Assert_Loser:{
			if(couldAssert){
				//CouldAssert -> TRUE
				//	CouldAssert has become TRUE because interface I used to be the
				//	RPF interface for S, and now it is not.  The Assert state machine
				//	MUST transition to NoInfo (NI) state, cancel AT(S, G, I), and
				//	delete information concerning the Assert Winner on I.
				sgState->AssertState = Assert_NoInfo;
				if(sgState->SG_AT.IsRunning())
					sgState->SG_AT.Cancel();
				UpdateAssertWinner(sgState, 0xffffffff, 0xffffffff, Ipv4Address("255.255.255.255"));
			}else{
				//CouldAssert -> FALSE
				//	CouldAssert has become FALSE because interface I has become the
				//	RPF interface for S.  The Assert state machine MUST transition to
				//	NoInfo (NI) state, cancel AT(S, G, I), and delete information
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
			break;
		}
	}
}

void
MulticastRoutingProtocol::RecvJP (PIMHeader::JoinPruneMessage &jp, Ipv4Address sender, Ipv4Address receiver, int32_t interface)
{
	NS_LOG_FUNCTION(this << sender << receiver << interface << jp.m_joinPruneMessage.m_upstreamNeighborAddr.m_unicastAddress);
	NS_LOG_DEBUG("Node  "<<receiver <<" receives JP from "<<sender);
	uint16_t groups = jp.m_joinPruneMessage.m_numGroups;
	Time HoldTime = jp.m_joinPruneMessage.m_holdTime;
	NS_LOG_LOGIC("Upstream Neighbor "<< jp.m_joinPruneMessage.m_upstreamNeighborAddr.m_unicastAddress << ", Groups = " << groups << ", HoldTime = " << HoldTime.GetSeconds());
//	Receive Join(S,G)
//	   A Join(S,G) is received on interface I with the upstream neighbor
//	   field set to the router's address on I.  The Prune(S,G)
//	   Downstream state machine on interface I MUST transition to the
//	   NoInfo (NI) state.  The PrunePending Timer (PPT(S,G,I)) MUST be cancelled.
	for(std::vector<PIMHeader::MulticastGroupEntry>::iterator iter = jp.m_multicastGroups.begin();
			iter != jp.m_multicastGroups.end(); iter++){///<Section 4.4.1.
		NS_LOG_DEBUG("Join = "<<iter->m_numberJoinedSources<<", Prune = "<<iter->m_numberPrunedSources);
		//JOIN sources' addresses
		for(std::vector<PIMHeader::EncodedSource>::iterator iterJoin = iter->m_joinedSourceAddrs.begin();
			iterJoin != iter->m_joinedSourceAddrs.end(); iterJoin++){
//			std::set<WiredEquivalentInterface> joinList = olist(iterJoin->m_sourceAddress, iter->m_multicastGroupAddr.m_groupAddress);
			//Interfaces interested in JOIN
//			for(std::set<WiredEquivalentInterface>::const_iterator iterList = joinList.begin(); iterList != joinList.end(); iterList++){
//				int32_t out_interface = iterList->first;
				// Upstream state machine
				RecvJoin(jp, sender, receiver, interface, *iterJoin, iter->m_multicastGroupAddr);
//			}
		}
		//PRUNE
//		A Prune(S,G) is received on interface I with the upstream
//			neighbor field set to the router's address on I.  The Prune(S,G)
//			Downstream state machine on interface I MUST transition to the
//			PrunePending (PP) state.  The PrunePending Timer (PPT(S,G,I))
//			MUST be set to J/P_Override_Interval if the router has more than
//			one neighbor on I.  If the router has only one neighbor on
//			interface I, then it SHOULD set the PPT(S,G,I) to zero,
//			effectively transitioning immediately to the Pruned (P) state.
		for(std::vector<PIMHeader::EncodedSource>::iterator iterPrune = iter->m_prunedSourceAddrs.begin();
					iterPrune != iter->m_prunedSourceAddrs.end(); iterPrune++){
			//This timer is set when a Prune(S, G) is received on the upstream interface where olist(S, G) != NULL.
			//	When the timer expires, a Join(S, G) message is sent on the upstream interface.  This timer
			//	is normally set to t_override (see 4.8).
//			std::set<WiredEquivalentInterface> pruneList = olist(iterPrune->m_sourceAddress, iter->m_multicastGroupAddr.m_groupAddress);
//			for(std::set<WiredEquivalentInterface>::const_iterator iterList = pruneList.begin(); iterList != pruneList.end(); iterList++){
//				int32_t out_interface = iterList->first;
				SourceGroupPair sgp (iterPrune->m_sourceAddress, iter->m_multicastGroupAddr.m_groupAddress, sender);
				if(IsUpstream(interface, sender, sgp)){
					SourceGroupState *sgState = FindSourceGroupState(interface, sender, sgp, true);
					NS_ASSERT(sgState->upstream);
					NS_LOG_LOGIC("Setting TIMER OT "<< sgp.sourceMulticastAddr<<", "<< sgp.groupMulticastAddr<<", "<<sgp.nextMulticastAddr<<", "<<interface);
					if(sgState->upstream->SG_OT.IsRunning())
						sgState->upstream->SG_OT.Cancel();
					sgState->upstream->SG_OT.SetDelay(Seconds(t_override(interface)));
					sgState->upstream->SG_OT.SetFunction(&MulticastRoutingProtocol::OTTimerExpire, this);
					sgState->upstream->SG_OT.SetArguments(sgp, interface);
					sgState->upstream->SG_OT.Schedule();
				}
				RecvPrune(jp, sender, receiver, interface, *iterPrune, iter->m_multicastGroupAddr);
//			}
		}
	}
}

void
MulticastRoutingProtocol::RecvPrune (PIMHeader::JoinPruneMessage &jp, Ipv4Address &sender, Ipv4Address &receiver, int32_t &interface, const PIMHeader::EncodedSource &source, PIMHeader::EncodedGroup &group)
{
	NS_LOG_FUNCTION(this << sender << receiver << interface << source.m_sourceAddress << group.m_groupAddress);
	NeighborhoodStatus *nstatus = FindNeighborhoodStatus(interface);
	nstatus->pruneHoldtime = Time(jp.m_joinPruneMessage.m_holdTime);
	// The node is not directly connected to S.
	if(IsUpstream(interface, sender, source.m_sourceAddress, group.m_groupAddress))
		RecvPruneUpstream(jp, sender, receiver, interface, source, group);
	else
		RecvPruneDownstream(jp, sender, receiver, interface, source, group);
}

//4.4.  PIM-DM Prune, Join, and Graft Messages
//	This section describes the generation and processing of PIM-DM Join, Prune, and Graft messages.
//	Prune messages are sent toward the upstream neighbor for S to indicate that traffic from S addressed to group G is not desired.
//	In the case of downstream routers A and B, where A wishes to continue receiving data and B does not, A will send
//	a Join in response to B's Prune to override the Prune.  This is the only situation in PIM-DM in which a Join message is used.
//	Finally, a Graft message is used to re-join a previously pruned branch to the delivery tree.
void
MulticastRoutingProtocol::RecvPruneUpstream(PIMHeader::JoinPruneMessage &jp, Ipv4Address &sender, Ipv4Address &receiver, int32_t &interface, const PIMHeader::EncodedSource &source, PIMHeader::EncodedGroup &group)
{
	NS_LOG_FUNCTION(this << sender<<receiver<<interface<<source.m_sourceAddress<<group.m_groupAddress);
	SourceGroupPair sgp (source.m_sourceAddress, group.m_groupAddress, sender);
	SourceGroupState *sgState = FindSourceGroupState(interface, sender, sgp, true);
	// The node is not directly connected to S.
	switch (sgState->upstream->GraftPrune) {
		case GP_Forwarding:{
		//This event is only relevant if RPF_interface(S) is a shared medium.
		//	This router sees another router on RPF_interface(S) send a Prune(S, G).
		//	As this router is in Forwarding state, it must override the Prune after a short random interval.
		//	If OT(S, G) is not running, the router MUST set OT(S, G) to t_override seconds.
		//	The Upstream(S, G) state machine remains in Forwarding (F) state.
			if(GetNextHop(source.m_sourceAddress) != source.m_sourceAddress && !sgState->upstream->SG_OT.IsRunning()){
				sgState->upstream->SG_OT.SetDelay(Seconds(t_override(interface)));
				sgState->upstream->SG_OT.SetFunction(&MulticastRoutingProtocol::OTTimerExpire, this);
				NS_LOG_LOGIC("Setting TIMER OT "<< sgp.sourceMulticastAddr<<", "<< sgp.groupMulticastAddr<<", "<<sgp.nextMulticastAddr<<", "<<interface);
				sgState->upstream->SG_OT.SetArguments(sgp, interface);
				sgState->upstream->SG_OT.Schedule();
				}
			break;
		}
		case GP_Pruned:{
		//A Prune(S, G) is seen on RPF_interface(S) to RPF'(S).
		//	The Upstream(S, G) state machine stays in the Pruned (P) state.
		//	The router MAY reset its PLT(S, G) to the value in the Holdtime field of the received message
		//	if it is greater than the current value of the PLT(S, G).
			if(GetNextHop(source.m_sourceAddress) == sender && jp.m_joinPruneMessage.m_holdTime>sgState->upstream->SG_PLT.GetDelay()){
				if(sgState->upstream->SG_PLT.IsRunning())
					sgState->upstream->SG_PLT.Cancel();
				sgState->upstream->SG_PLT.SetDelay(jp.m_joinPruneMessage.m_holdTime);
				sgState->upstream->SG_PLT.SetFunction(&MulticastRoutingProtocol::PLTTimerExpire, this);
				sgState->upstream->SG_PLT.SetArguments(sgp, sender);
				sgState->upstream->SG_PLT.Schedule();
			}
			break;
		}
		case GP_AckPending:{
		//This event is only relevant if RPF_interface(S) is a shared medium.
		//	This router sees another router on RPF_interface(S) send a Prune(S, G).
		//	As this router is in AckPending (AP) state, it must override the Prune after a short random interval.
		//	If OT(S, G) is not running, the router MUST set OT(S, G) to t_override seconds.
		//	The Upstream(S, G) state machine remains in AckPending (AP) state.
			if(!sgState->upstream->SG_OT.IsRunning()){
				sgState->upstream->SG_OT.SetDelay(Seconds(t_override(interface)));
				sgState->upstream->SG_OT.SetFunction(&MulticastRoutingProtocol::OTTimerExpire, this);
				NS_LOG_LOGIC("Setting TIMER OT "<< sgp.sourceMulticastAddr<<", "<< sgp.groupMulticastAddr<<", "<<sgp.nextMulticastAddr<<", "<<interface);
				sgState->upstream->SG_OT.SetArguments(sgp, interface);
				sgState->upstream->SG_OT.Schedule();
			}
			break;
		}
		default:{
			NS_LOG_ERROR("RecvPruneUpstream: Graft Prune state not valid"<<sgState->upstream->GraftPrune);
			break;
		}
	}
}

void
MulticastRoutingProtocol::RecvPruneDownstream (PIMHeader::JoinPruneMessage &jp, Ipv4Address &sender, Ipv4Address &receiver, int32_t &interface, const PIMHeader::EncodedSource &source, PIMHeader::EncodedGroup &group)
{
	NS_LOG_FUNCTION(this<<sender<<receiver<<interface<<source.m_sourceAddress<< group.m_groupAddress);
	SourceGroupPair sgp (source.m_sourceAddress, group.m_groupAddress, sender);
 	SourceGroupState *sgState = FindSourceGroupState(interface, sender, sgp, true);
	switch (sgState->PruneState) {
		case Prune_NoInfo:{
			//Receive Prune(S, G): A Prune(S, G) is received on interface I with the upstream neighbor field
			//  set to the router's address on I.  The Prune(S, G) Downstream state machine on interface I
			//  MUST transition to the PrunePending (PP) state.  The PrunePending Timer (PPT(S, G, I))
			//  MUST be set to J/P_Override_Interval if the router has more than one neighbor on I.
			//  If the router has only one neighbor on interface I, then it SHOULD set the PPT(S, G, I) to zero,
		    //  effectively transitioning immediately to the Pruned (P) state.
			if(IsMyOwnAddress(jp.m_joinPruneMessage.m_upstreamNeighborAddr.m_unicastAddress)){
				sgState->PruneState = Prune_PrunePending;
				NeighborhoodStatus *nstatus = FindNeighborhoodStatus(interface);
				Time delay = Seconds(0);
				if(nstatus->neighbors.size() == 1 )
					sgState->PruneState = Prune_Pruned;
				if(nstatus->neighbors.size()>1)
					delay = Seconds(nstatus->overrideInterval.GetSeconds()+nstatus->propagationDelay.GetSeconds());
				NS_LOG_DEBUG("Neighbor size "<< nstatus->neighbors.size()<< " Delay "<<delay.GetSeconds()<<"sec");
				if(sgState->SG_PPT.IsRunning())
					sgState->SG_PPT.Cancel();
				sgState->SG_PPT.SetDelay(delay);
				sgState->SG_PPT.SetFunction(&MulticastRoutingProtocol::PPTTimerExpire, this);
				sgState->SG_PPT.SetArguments(sgp, interface, sender);
				sgState->SG_PPT.Schedule();
			}
			break;
		}
		case Prune_PrunePending:{
			break;
		}
		case Prune_Pruned:{
		//Receive Prune(S, G). A Prune(S, G) is received on the interface I with the upstream
		//	neighbor field set to the router's address on I.
		//	The Prune(S, G) Downstream state machine on interface I remains in the Pruned (P) state.
		//	The Prune Timer (PT(S, G, I)) SHOULD be reset to the holdtime contained in the Prune(S, G)
		//	message if it is greater than the current value.
			if(IsMyOwnAddress(jp.m_joinPruneMessage.m_upstreamNeighborAddr.m_unicastAddress)){
				if(jp.m_joinPruneMessage.m_holdTime >sgState->SG_PT.GetDelay()){
					if(sgState->SG_PT.IsRunning())
						sgState->SG_PT.Cancel();
					sgState->SG_PT.SetDelay(jp.m_joinPruneMessage.m_holdTime);
					sgState->SG_PT.SetFunction(&MulticastRoutingProtocol::PTTimerExpire, this);
					sgState->SG_PT.SetArguments(sgp, interface);
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
			//Receive Prune(S, G), Join(S, G), or Graft(S, G).
			//	A Prune(S, G), Join(S, G), or Graft(S, G) message was received on
			//	interface I with its upstream neighbor address set to the
			//	router's address on I.  The router MUST send an Assert(S, G) on
			//	the receiving interface I to initiate an Assert negotiation.  The
			//	Assert state machine remains in the Assert Loser(L) state.  If a
			//	Graft(S, G) was received, the router MUST respond with a GraftAck(S, G).
			if(IsMyOwnAddress(jp.m_joinPruneMessage.m_upstreamNeighborAddr.m_unicastAddress)){
				PIMHeader assertR;
				SourceGroupPair sgp (source.m_sourceAddress, group.m_groupAddress, sender);
				ForgeAssertMessage(interface, sender, assertR, sgp);
				Ptr<Packet> packet = Create<Packet> ();
				Simulator::Schedule(TransmissionDelay(),&MulticastRoutingProtocol::SendPacketPIMUnicast, this, packet, assertR, sender);
			}
			//An Assert loser that receives a Prune(S, G), Join(S, G), or
			//  Graft(S, G) directed to it initiates a new Assert negotiation so
			//  that the downstream router can correct its RPF'(S).
			break;
			}
		default:{
			NS_LOG_ERROR("RecvPruneDownstream: Assert State not valid"<<sgState->AssertState);
			break;
		}
	}
}

void
MulticastRoutingProtocol::RecvJoin(PIMHeader::JoinPruneMessage &jp, Ipv4Address &sender, Ipv4Address &receiver, int32_t &interface, const PIMHeader::EncodedSource &source, PIMHeader::EncodedGroup &group)
{
	NS_LOG_FUNCTION(this<<sender<<receiver<<interface<<source.m_sourceAddress<<group.m_groupAddress);
	if(IsUpstream(interface, sender, source.m_sourceAddress, group.m_groupAddress))
		RecvJoinUpstream(jp, sender, receiver, interface, source, group);
	else
		RecvJoinDownstream(jp, sender, receiver, interface, source, group);
}

void
MulticastRoutingProtocol::RecvJoinUpstream(PIMHeader::JoinPruneMessage &jp, Ipv4Address &sender, Ipv4Address &receiver, int32_t &interface, const PIMHeader::EncodedSource &source, PIMHeader::EncodedGroup &group)
{
	NS_LOG_FUNCTION(this<<sender<<receiver<<interface<<source.m_sourceAddress<<group.m_groupAddress);
	SourceGroupPair sgp (source.m_sourceAddress, group.m_groupAddress, sender);
	SourceGroupState *sgState = FindSourceGroupState(interface, sender, sgp);
		switch (sgState->upstream->GraftPrune) {
			case GP_Forwarding:{
			//This event is only relevant if RPF_interface(S) is a shared medium.
			//	This router sees another router on RPF_interface(S) send a Join(S, G) to RPF'(S, G).
			//	If the OT(S, G) is running, then it means that the router had scheduled a Join to override a previously received Prune.
			//	Another router has responded more quickly with a Join, so the local router SHOULD cancel its OT(S, G), if it is running.
			//	The Upstream(S, G) state machine remains in the Forwarding (F) state.
				if(sender == RPF_prime(source.m_sourceAddress, group.m_groupAddress) && sgState->upstream->SG_OT.IsRunning()){ //HERE
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
			//	This router sees another router on RPF_interface(S) send a Join(S, G) to RPF'(S, G).
			//	If the OT(S, G) is running, then it means that the router had scheduled a Join to override a previously received Prune.
			//	Another router has responded more quickly with a Join, so the local router SHOULD cancel its OT(S, G), if it is running.
			//	The Upstream(S, G) state machine remains in the AckPending (AP) state.
				if(receiver == GetNextHop(source.m_sourceAddress) && sgState->upstream->SG_OT.IsRunning()){
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
MulticastRoutingProtocol::RecvJoinDownstream(PIMHeader::JoinPruneMessage &jp, Ipv4Address &sender, Ipv4Address &receiver, int32_t &interface, const PIMHeader::EncodedSource &source, PIMHeader::EncodedGroup &group)
{
	NS_LOG_FUNCTION(this<<sender<<receiver<<interface<<source.m_sourceAddress<<group.m_groupAddress);
	SourceGroupPair sgp (source.m_sourceAddress, group.m_groupAddress, sender);
	SourceGroupState *sgState = FindSourceGroupState(interface, sender, sgp, true);
	Ipv4Address current = GetLocalAddress(interface);
	switch (sgState->PruneState) {
		case Prune_NoInfo:{
			break;
		}
		case Prune_PrunePending:{
			//Receive Join(S, G): A Join(S, G) is received on interface I with the upstream neighbor
			//	field set to the router's address on I.  The Prune(S, G) Downstream state machine
			//	on interface I MUST transition to the NoInfo (NI) state.
			//	The PrunePending Timer (PPT(S, G, I)) MUST be cancelled.
			if(jp.m_joinPruneMessage.m_upstreamNeighborAddr.m_unicastAddress == current){
				sgState->PruneState = Prune_NoInfo;
				sgState->SG_PPT.Cancel();
				sgState->SG_PPT.Remove();
			}
			break;
		}
		case Prune_Pruned:{
		//Receive Join(S, G). A Join(S, G) is received on the interface I with the upstream
		//	neighbor field set to the router's address on I.  The Prune(S, G) downstream state
		//	machine on interface I MUST transition to the NoInfo (NI) state.
		//	The Prune Timer (PT(S, G, I)) MUST be cancelled.
		//	The router MUST evaluate any possible transitions in the Upstream(S, G) state machine.
			if(jp.m_joinPruneMessage.m_upstreamNeighborAddr.m_unicastAddress == current){
				sgState->PruneState = Prune_NoInfo;
				sgState->SG_PPT.Cancel();
			}
			UpstreamStateMachine(sgp);
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
			//Receive Prune(S, G), Join(S, G), or Graft(S, G).
			//	A Prune(S, G), Join(S, G), or Graft(S, G) message was received on
			//	interface I with its upstream neighbor address set to the
			//	router's address on I.  The router MUST send an Assert(S, G) on
			//	the receiving interface I to initiate an Assert negotiation.  The
			//	Assert state machine remains in the Assert Loser(L) state.  If a
			//	Graft(S, G) was received, the router MUST respond with a GraftAck(S, G).
			if(jp.m_joinPruneMessage.m_upstreamNeighborAddr.m_unicastAddress == current){
				PIMHeader assertR;
				SourceGroupPair sgp (source.m_sourceAddress, group.m_groupAddress, sender);
				ForgeAssertMessage(interface, sender, assertR, sgp);
				Ptr<Packet> packet = Create<Packet> ();
				Simulator::Schedule(TransmissionDelay(),&MulticastRoutingProtocol::SendPacketPIMUnicast, this, packet, assertR, sender);
			}
			//An Assert loser that receives a Prune(S, G), Join(S, G), or
			//  Graft(S, G) directed to it initiates a new Assert negotiation so
			//  that the downstream router can correct its RPF'(S).
			break;
		}
		default:{
			NS_LOG_ERROR("RecvJoinDownstream: Assert State not valid"<<sgState->AssertState);
			break;
		}
	}
}

void
MulticastRoutingProtocol::RecvAssert (PIMHeader::AssertMessage &assert, Ipv4Address sender, Ipv4Address receiver, int32_t interface)
{
	NS_LOG_FUNCTION(this<<sender<<receiver<<interface);
	SourceGroupPair sgp (assert.m_sourceAddr.m_unicastAddress, assert.m_multicastGroupAddr.m_groupAddress, sender);
	SourceGroupState *sgState = FindSourceGroupState(interface, sender, sgp, true);
	struct AssertMetric received (assert.m_metricPreference, assert.m_metric, sender);
	struct AssertMetric myMetric;
	bool couldAssert = CouldAssert(assert.m_sourceAddr.m_unicastAddress, assert.m_multicastGroupAddr.m_groupAddress, interface, sender);
	switch (sgState->AssertState){
		case  Assert_NoInfo:{
		//Receive Inferior (Assert OR State Refresh) AND CouldAssert(S, G, I)==TRUE.
		//   An Assert or State Refresh is received for (S, G) that is inferior
		//   to our own assert metric on interface I. The Assert state machine
		//   MUST transition to the "I am Assert Winner" state, send an Assert(S, G)
		//   to interface I, store its own address and metric as the Assert Winner,
		//   and set the Assert Timer (AT(S, G, I)) to Assert_Time.
			myMetric = my_assert_metric(assert.m_sourceAddr.m_unicastAddress, assert.m_multicastGroupAddr.m_groupAddress, interface, sender);
			if(myMetric > received && couldAssert){
				sgState->AssertState = Assert_Winner;
				UpdateAssertWinner(sgState, myMetric);
				PIMHeader assertR;
				ForgeAssertMessage(interface, sender, assertR, sgp);
				Ptr<Packet> packet = Create<Packet> ();
				Simulator::Schedule(TransmissionDelay(),&MulticastRoutingProtocol::SendPacketPIMUnicast, this, packet, assertR, sender);
				if(sgState->SG_AT.IsRunning())
					sgState->SG_AT.Cancel();
				sgState->SG_AT.SetDelay(Seconds(Assert_Time));
				sgState->SG_AT.SetFunction(&MulticastRoutingProtocol::ATTimerExpire, this);
				sgState->SG_AT.SetArguments(sgp, interface, sender);
				sgState->SG_AT.Schedule();
			}
			else{
				//Receive Preferred Assert or State Refresh.
				//	The received Assert or State Refresh has a better metric than
				//	this router's, and therefore the Assert state machine MUST
				//	transition to the "I am Assert Loser" state and store the Assert
				//	Winner's address and metric.  If the metric was received in an
				//	Assert, the router MUST set the Assert Timer (AT(S, G, I)) to
				//	Assert_Time.  If the metric was received in a State Refresh, the
				//	router MUST set the Assert Timer (AT(S, G, I)) to three times the
				//	received State Refresh Interval.
				sgState->AssertState = Assert_Loser;
				UpdateAssertWinner(sgState, received);
				if(sgState->SG_AT.IsRunning())
					sgState->SG_AT.Cancel();
				sgState->SG_AT.SetDelay(Seconds(Assert_Time));
				sgState->SG_AT.SetFunction(&MulticastRoutingProtocol::ATTimerExpire, this);
				sgState->SG_AT.SetArguments(sgp, interface, sender);
				sgState->SG_AT.Schedule();
				if(couldAssert){
					//If CouldAssert(S, G, I) == TRUE,
					//	the router MUST also multicast a Prune(S, G) to the Assert winner
					//	with a Prune Hold Time equal to the Assert Timer and
					//  evaluate any changes in its Upstream(S, G) state machine.
					PIMHeader prune;
					ForgeJoinPruneMessage(prune, sender);
					PIMHeader::MulticastGroupEntry mge;
					CreateMulticastGroupEntry(mge, ForgeEncodedGroup(assert.m_multicastGroupAddr.m_groupAddress));
					AddMulticastGroupSourcePrune(mge, ForgeEncodedSource(assert.m_sourceAddr.m_unicastAddress));
					AddMulticastGroupEntry(prune, mge);
					prune.GetJoinPruneMessage().m_joinPruneMessage.m_holdTime = sgState->SG_AT.GetDelay();
					Ptr<Packet> packet = Create<Packet> ();
					Simulator::Schedule(TransmissionDelay(),&MulticastRoutingProtocol::SendPacketPIMUnicast, this, packet, prune, sender);
					UpstreamStateMachine(sgp);
				}
			}
			break;
			}
		case Assert_Winner:{
			myMetric = my_assert_metric(assert.m_sourceAddr.m_unicastAddress, assert.m_multicastGroupAddr.m_groupAddress, interface, sender);
			if(received < myMetric){
			//Receive Inferior Assert or State Refresh
			//	An (S, G) Assert is received containing a metric for S that is worse than this router's metric for S.
			//	Whoever sent the Assert is in error.  The router MUST send an Assert(S, G) to interface I
			//	and reset the Assert Timer (AT(S, G, I)) to Assert_Time.
				PIMHeader assertR;
				ForgeAssertMessage(interface, sender, assertR, sgp);
				assertR.GetAssertMessage().m_metricPreference = sgState->AssertWinner.metricPreference;
				assertR.GetAssertMessage().m_metric = sgState->AssertWinner.routeMetric;
				Ptr<Packet> packet = Create<Packet> ();
				Simulator::Schedule(TransmissionDelay(),&MulticastRoutingProtocol::SendPacketPIMUnicast, this, packet, assertR, sender);
				if(sgState->SG_AT.IsRunning())
					sgState->SG_AT.Cancel();
				sgState->SG_AT.SetDelay(Seconds(Assert_Time));
				sgState->SG_AT.SetFunction(&MulticastRoutingProtocol::ATTimerExpire, this);
				sgState->SG_AT.SetArguments(sgp, interface, sender);
				sgState->SG_AT.Schedule();
			}
			else{
				//Receive Preferred Assert or State Refresh
				//   An (S,G) Assert or State Refresh is received that has a better
				//   metric than this router's metric for S on interface I.  The
				//   Assert state machine MUST transition to "I am Assert Loser" state
				//   and store the new Assert Winner's address and metric.  If the
				//   metric was received in an Assert, the router MUST set the Assert
				//   Timer (AT(S,G,I)) to Assert_Time.  If the metric was received in
				//   a State Refresh, the router MUST set the Assert Timer (AT(S,G,I))
				//   to three times the State Refresh Interval.  The router MUST also
				//	 multicast a Prune(S,G) to the Assert winner, with a Prune Hold
				//   Time equal to the Assert Timer, and evaluate any changes in its
				//   Upstream(S,G) state machine.
				sgState->AssertState = Assert_Loser;
				UpdateAssertWinner(sgState, received);
				if(sgState->SG_AT.IsRunning())
					sgState->SG_AT.Cancel();
				sgState->SG_AT.SetDelay(Seconds(Assert_Time));
				sgState->SG_AT.SetFunction(&MulticastRoutingProtocol::ATTimerExpire, this);
				sgState->SG_AT.SetArguments(sgp, interface, sender);
				sgState->SG_AT.Schedule();
				//TODO previously commented out
				PIMHeader prune;
				ForgeJoinPruneMessage(prune, sender);
				PIMHeader::MulticastGroupEntry mge;
				CreateMulticastGroupEntry(mge, ForgeEncodedGroup(assert.m_multicastGroupAddr.m_groupAddress));
				AddMulticastGroupSourcePrune(mge, ForgeEncodedSource(assert.m_sourceAddr.m_unicastAddress));
				AddMulticastGroupEntry(prune, mge);
				prune.GetJoinPruneMessage().m_joinPruneMessage.m_holdTime = sgState->SG_AT.GetDelay();
				Ptr<Packet> packet = Create<Packet> ();
				Simulator::Schedule(TransmissionDelay(),&MulticastRoutingProtocol::SendPacketPIMUnicast, this, packet, prune, sender);
				UpstreamStateMachine(sgp);
				}
			break;
		}
		case Assert_Loser:{
		//Receive Inferior Assert or State Refresh from Current Winner
		//	An Assert or State Refresh is received from the current Assert
		//  winner that is worse than this router's metric for S (typically,
		//  the winner's metric became worse).  The Assert state machine MUST
		//  transition to NoInfo (NI) state and cancel AT(S, G, I).  The router
		//  MUST delete the previous Assert Winner's address and metric and
		//  evaluate any possible transitions to its Upstream(S, G) state machine.
		//	Usually this router will eventually re-assert and win
		//  when data packets from S have started flowing again.
			myMetric = my_assert_metric(assert.m_sourceAddr.m_unicastAddress, assert.m_multicastGroupAddr.m_groupAddress, interface, sender);
			if(received < myMetric){
				sgState->AssertState = Assert_NoInfo;
				if(sgState->SG_AT.IsRunning())
					sgState->SG_AT.Cancel();
				UpdateAssertWinner(sgState, infinite_assert_metric());
				UpstreamStateMachine(sgp);
			}
			else if(received > sgState->AssertWinner) {
				//Receive Preferred Assert or State Refresh
				//	An Assert or State Refresh is received that has a metric better
				//	than or equal to that of the current Assert winner.  The Assert
				//	state machine remains in Loser (L) state.  If the metric was
				//	received in an Assert, the router MUST set the Assert Timer
				//	(AT(S, G, I)) to Assert_Time.  If the metric was received in a
				//	State Refresh, the router MUST set the Assert Timer (AT(S, G, I))
				//	to three times the received State Refresh Interval.  If the
				//	metric is better than the current Assert Winner, the router MUST
				//	store the address and metric of the new Assert Winner, and if
				//	CouldAssert(S, G, I) == TRUE, the router MUST multicast a
				//	Prune(S, G) to the new Assert winner.
				sgState->AssertState = Assert_Loser;
				if(sgState->SG_AT.IsRunning())
					sgState->SG_AT.Cancel();
				sgState->SG_AT.SetDelay(Seconds(Assert_Time));
				sgState->SG_AT.SetFunction(&MulticastRoutingProtocol::ATTimerExpire, this);
				sgState->SG_AT.SetArguments(sgp, interface, sender);
				sgState->SG_AT.Schedule();
				UpdateAssertWinner(sgState, assert.m_metricPreference, assert.m_metric, sender);
				if(couldAssert){
					PIMHeader prune;
					ForgeJoinPruneMessage(prune, sender);
					PIMHeader::MulticastGroupEntry mge;
					CreateMulticastGroupEntry(mge, ForgeEncodedGroup(assert.m_multicastGroupAddr.m_groupAddress));
					AddMulticastGroupSourcePrune(mge, ForgeEncodedSource(assert.m_sourceAddr.m_unicastAddress));
					AddMulticastGroupEntry(prune, mge);
					prune.GetJoinPruneMessage().m_joinPruneMessage.m_holdTime = sgState->SG_AT.GetDelay();
					Ptr<Packet> packet = Create<Packet> ();
					Simulator::Schedule(TransmissionDelay(),&MulticastRoutingProtocol::SendPacketPIMUnicast, this, packet, prune, sender);
				}
			}
			break;
		}
		default:{
			NS_LOG_ERROR("RecvAssert: Assert State not valid"<<sgState->AssertState);
			break;
		}
	}
//	NS_LOG_DEBUG("Sender "<< sender <<" ("<<received<<") Receiver "<<receiver<<" ("<<myMetric<<")");
}

void
MulticastRoutingProtocol::RecvStateRefresh(PIMHeader::StateRefreshMessage &refresh, Ipv4Address sender, Ipv4Address receiver, int32_t interface)
{
	NS_LOG_FUNCTION(this<<sender<<receiver<<interface);
	NeighborState neighbor (refresh.m_originatorAddr.m_unicastAddress, receiver);
	NeighborState *ns = FindNeighborState(interface, neighbor);
	SourceGroupPair sgp (refresh.m_sourceAddr.m_unicastAddress, refresh.m_multicastGroupAddr.m_groupAddress, sender);
	SourceGroupState *sgState = FindSourceGroupState(interface, sender, sgp, true);
	WiredEquivalentInterface wei = RPF_interface(sgp.sourceMulticastAddr);
	Ipv4Address gateway = wei.second;
	NS_LOG_LOGIC("Source " << sgp.sourceMulticastAddr << " Group " << sgp.groupMulticastAddr << " Gateway "<< gateway << " Sender "<< sender <<" Receiver "<<receiver << " Interface "<< interface);
	if(!isValidGateway(gateway)) return AskRoute(sgp.sourceMulticastAddr);
	//TODO: Upon startup, a router MAY use any State Refresh messages received within Hello_Period of its first Hello message on an interface to establish state information.
	for(int32_t i = 0; Simulator::Now() < Seconds(m_startTime.GetSeconds()+Hello_Period) && i < m_ipv4->GetNInterfaces() &&  refresh.m_P == 1;i++){
		if(IsLoopInterface(i)) continue;
		SourceGroupState *sgStateB;
		//	The State Refresh source will be the RPF'(S), and Prune status for all interfaces will be set according to the Prune Indicator bit in the State Refresh message.
		//	  If the Prune Indicator is set, the router SHOULD set the PruneLimitTimer
		//    to Prune_Holdtime and set the PruneTimer on all downstream interfaces to the State Refresh's Interval times two.
		for(std::map<WiredEquivalentInterface, SourceGroupList>::iterator iter = m_IfaceSourceGroup.begin(); iter != m_IfaceSourceGroup.end(); iter++){
			Ipv4Address neighbor = iter->first.second;
			sgStateB = FindSourceGroupState(interface, neighbor, sgp);
			if (IsUpstream(interface, neighbor, sgp) && refresh.m_P){
				if(sgStateB->upstream->SG_PLT.IsRunning())
					sgStateB->upstream->SG_PLT.Cancel();
				sgStateB->upstream->SG_PLT.SetDelay(Seconds(PruneHoldTime));
				sgStateB->upstream->SG_PLT.SetFunction(&MulticastRoutingProtocol::PLTTimerExpire, this);
				sgStateB->upstream->SG_PLT.SetArguments(sgp, gateway);
				sgStateB->upstream->SG_PLT.Schedule();
			}
			else if(IsDownstream(interface, neighbor, sgp) && refresh.m_P){
				if(sgStateB->SG_PT.IsRunning())
					sgStateB->SG_PT.Cancel();
				sgStateB->SG_PT.SetDelay(Seconds(2 * StateRefreshInterval));
				sgStateB->SG_PT.SetFunction(&MulticastRoutingProtocol::PLTTimerExpire, this);
				sgStateB->SG_PT.SetArguments(sgp, gateway);
				sgStateB->SG_PT.Schedule();
				ForwardingStateRefresh(refresh, sender, receiver);
			}
			sgStateB->PruneState = (refresh.m_P ? Prune_Pruned: Prune_NoInfo);
		}
	}
	if(IsUpstream(interface, sender, sgp)){
		switch (sgState->upstream->GraftPrune) {
			case GP_Forwarding:{
//				State Refresh(S,G) Received from RPF'(S)
//			       The Upstream(S,G) state machine remains in a Forwarding state. If the received State Refresh has the Prune Indicator bit set to one,
//				   this router must override the upstream router's Prune state after a short random interval.  If OT(S,G) is not running and the
//			       Prune Indicator bit equals one, the router MUST set OT(S,G) to t_override seconds.
				if(refresh.m_P == 1){
					Simulator::Schedule (TransmissionDelay(0, t_shorter), &MulticastRoutingProtocol::SetPruneState, this, interface, sender, sgp, Prune_Pruned); //TODO: sure about this schedule
					if(!sgState->upstream->SG_OT.IsRunning()){
					sgState->upstream->SG_OT.SetDelay(Seconds(t_override(interface)));
					sgState->upstream->SG_OT.SetFunction(&MulticastRoutingProtocol::OTTimerExpire, this);
					NS_LOG_LOGIC("Setting TIMER OT "<< sgp.sourceMulticastAddr<<", "<< sgp.groupMulticastAddr<<", "<<sgp.nextMulticastAddr<<", "<<interface);
					sgState->upstream->SG_OT.SetArguments(sgp, interface);
					sgState->upstream->SG_OT.Schedule();
					}
				}
				break;
			}
			case GP_Pruned:{
			//The Upstream(S, G) state machine remains in a Pruned state. If the State Refresh has its Prune Indicator bit set to zero and
			//	   PLT(S, G) is not running, a Prune(S, G) MUST be sent to RPF'(S), and the PLT(S, G) MUST be set to t_limit.
			//	   If the State Refresh has its Prune Indicator bit set to one, the router MUST reset PLT(S, G) to t_limit.
				if(refresh.m_P==0 && !sgState->upstream->SG_PLT.IsRunning()){
						sgState->upstream->SG_PLT.SetDelay(Seconds(t_limit));
						sgState->upstream->SG_PLT.SetFunction(&MulticastRoutingProtocol::PLTTimerExpire, this);
						sgState->upstream->SG_PLT.SetArguments(sgp, gateway);
						sgState->upstream->SG_PLT.Schedule();
						SendPruneUnicast(sender, sgp);
					}
				else if(refresh.m_P){
					if(sgState->upstream->SG_PLT.IsRunning())
						sgState->upstream->SG_PLT.Cancel();
					sgState->upstream->SG_PLT.SetDelay(Seconds(t_limit));
					sgState->upstream->SG_PLT.SetFunction(&MulticastRoutingProtocol::PLTTimerExpire, this);
					sgState->upstream->SG_PLT.SetArguments(sgp, gateway);
					sgState->upstream->SG_PLT.Schedule();
				}
				break;
			}
			case GP_AckPending:{
			//The Upstream(S, G) state machine remains in an AckPending state.
			//   The router must override the upstream router's Prune state after a short random interval.
			//   If OT(S, G) is not running and the Prune Indicator bit equals one, the router MUST set OT(S, G) to t_override seconds.
				if(refresh.m_P){
					Simulator::Schedule (TransmissionDelay(0, t_shorter), &MulticastRoutingProtocol::SetPruneState, this, interface, sender, sgp, Prune_Pruned);//TODO: sure about this schedule
					if(!sgState->upstream->SG_OT.IsRunning()){
						sgState->upstream->SG_OT.SetDelay(Seconds(t_override(interface)));
						sgState->upstream->SG_OT.SetFunction(&MulticastRoutingProtocol::OTTimerExpire, this);
						NS_LOG_LOGIC("Setting TIMER OT "<< sgp.sourceMulticastAddr<<", "<< sgp.groupMulticastAddr<<", "<<sgp.nextMulticastAddr<<", "<<interface);
						sgState->upstream->SG_OT.SetArguments(sgp, interface);
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
	switch (sgState->AssertState){
		case  Assert_NoInfo:{
			//Receive Inferior (Assert OR State Refresh) AND CouldAssert(S, G, I)==TRUE.
			//   An Assert or State Refresh is received for (S, G) that is inferior
			//   to our own assert metric on interface I. The Assert state machine
			//   MUST transition to the "I am Assert Winner" state, send an Assert(S, G)
			//   to interface I, store its own address and metric as the Assert Winner,
			//   and set the Assert Timer (AT(S, G, I)) to Assert_Time.
				struct AssertMetric received (refresh.m_metricPreference, refresh.m_metric, refresh.m_originatorAddr.m_unicastAddress);
				if(my_assert_metric(refresh.m_sourceAddr.m_unicastAddress, refresh.m_multicastGroupAddr.m_groupAddress, interface, sender) > received
						&& CouldAssert(refresh.m_sourceAddr.m_unicastAddress, refresh.m_multicastGroupAddr.m_groupAddress, interface, sender)){
					sgState->AssertState = Assert_Winner;
					UpdateAssertWinner(sgState, interface);
					PIMHeader assertR;
					ForgeAssertMessage(interface, sender, assertR, sgp);
					Ptr<Packet> packet = Create<Packet> ();
					Simulator::Schedule(TransmissionDelay(),&MulticastRoutingProtocol::SendPacketPIMUnicast, this, packet, assertR, sender);
					if(sgState->SG_AT.IsRunning())
						sgState->SG_AT.Cancel();
					sgState->SG_AT.SetDelay(Seconds(Assert_Time));
					sgState->SG_AT.SetFunction(&MulticastRoutingProtocol::ATTimerExpire, this);
					sgState->SG_AT.SetArguments(sgp, interface, sender);
					sgState->SG_AT.Schedule();
				}
				else{
					//Receive Preferred Assert or State Refresh.
					//	The received Assert or State Refresh has a better metric than
					//	this router's, and therefore the Assert state machine MUST
					//	transition to the "I am Assert Loser" state and store the Assert
					//	Winner's address and metric.  If the metric was received in an
					//	Assert, the router MUST set the Assert Timer (AT(S, G, I)) to
					//	Assert_Time.  If the metric was received in a State Refresh, the
					//	router MUST set the Assert Timer (AT(S, G, I)) to three times the
					//	received State Refresh Interval.
					sgState->AssertState = Assert_Loser;
					UpdateAssertWinner(sgState, refresh.m_metricPreference, refresh.m_metric, refresh.m_originatorAddr.m_unicastAddress);
					if(sgState->SG_AT.IsRunning())
						sgState->SG_AT.Cancel();
					sgState->SG_AT.SetDelay(Seconds(3*RefreshInterval));
					sgState->SG_AT.SetFunction(&MulticastRoutingProtocol::ATTimerExpire, this);
					sgState->SG_AT.SetArguments(sgp, interface, sender);
					sgState->SG_AT.Schedule();
					if(CouldAssert(refresh.m_sourceAddr.m_unicastAddress, refresh.m_multicastGroupAddr.m_groupAddress, interface, sender)){
						//If CouldAssert(S, G, I) == TRUE,
						//	the router MUST also multicast a Prune(S, G) to the Assert winner
						//	with a Prune Hold Time equal to the Assert Timer
						//	TODO: and evaluate any changes in its Upstream(S, G) state machine.
						PIMHeader msg;
						ForgeJoinPruneMessage(msg, refresh.m_originatorAddr.m_unicastAddress);
						PIMHeader::MulticastGroupEntry mge;
						CreateMulticastGroupEntry(mge, ForgeEncodedGroup(refresh.m_multicastGroupAddr.m_groupAddress));
						AddMulticastGroupSourcePrune(mge, ForgeEncodedSource(refresh.m_sourceAddr.m_unicastAddress));
						AddMulticastGroupEntry(msg, mge);
						msg.GetJoinPruneMessage().m_joinPruneMessage.m_holdTime = sgState->SG_AT.GetDelay();
						Ptr<Packet> packet = Create<Packet> ();
						Simulator::Schedule(TransmissionDelay(),&MulticastRoutingProtocol::SendPacketPIMUnicast, this,packet, msg, refresh.m_originatorAddr.m_unicastAddress);
						UpstreamStateMachine(sgp);
					}
				}
				break;
				}
		case Assert_Winner:{
			//Receive Inferior Assert or State Refresh
			//	An (S, G) Assert is received containing a metric for S that is
			//	worse than this router's metric for S.  Whoever sent the Assert
			//	is in error.  The router MUST send an Assert(S, G) to interface I
			//	and reset the Assert Timer (AT(S, G, I)) to Assert_Time.
			struct AssertMetric received (refresh.m_metricPreference, refresh.m_metric, refresh.m_originatorAddr.m_unicastAddress);
			if(received < my_assert_metric(refresh.m_sourceAddr.m_unicastAddress, refresh.m_multicastGroupAddr.m_groupAddress, interface, sender)){
				PIMHeader assertR;
				ForgeAssertMessage(interface, sender, assertR, sgp);
				assertR.GetAssertMessage().m_metricPreference = sgState->AssertWinner.metricPreference;
				assertR.GetAssertMessage().m_metric = sgState->AssertWinner.routeMetric;
				Ptr<Packet> packet = Create<Packet> ();
				Simulator::Schedule(TransmissionDelay(),&MulticastRoutingProtocol::SendPacketPIMUnicast, this, packet, assertR, sender);
				if(sgState->SG_AT.IsRunning())
					sgState->SG_AT.Cancel();
				sgState->SG_AT.SetDelay(Seconds(Assert_Time));
				sgState->SG_AT.SetFunction(&MulticastRoutingProtocol::ATTimerExpire, this);
				sgState->SG_AT.SetArguments(sgp, interface, sender);
				sgState->SG_AT.Schedule();
			}
			else{
				//Receive Preferred Assert or State Refresh.
				//	An (S, G) Assert or State Refresh is received that has a better
				//	metric than this router's metric for S on interface I. The
				//	Assert state machine MUST transition to "I am Assert Loser" state
				//	and store the new Assert Winner's address and metric.  If the
				//	metric was received in an Assert, the router MUST set the Assert
				//	Timer (AT(S, G, I)) to Assert_Time.  If the metric was received in
				//	a State Refresh, the router MUST set the Assert Timer (AT(S, G, I))
				//	to three times the State Refresh Interval.
				sgState->AssertState = Assert_Loser;
				UpdateAssertWinner(sgState, refresh.m_metricPreference, refresh.m_metric, refresh.m_originatorAddr.m_unicastAddress);
				if(sgState->SG_AT.IsRunning())
					sgState->SG_AT.Cancel();
				sgState->SG_AT.SetDelay(Seconds(3*RefreshInterval));
				sgState->SG_AT.SetFunction(&MulticastRoutingProtocol::ATTimerExpire, this);
				sgState->SG_AT.SetArguments(sgp, interface, sender);
				sgState->SG_AT.Schedule();
				//The router MUST also
				//	multicast a Prune(S, G) to the Assert winner, with a Prune Hold
				//	Time equal to the Assert Timer, and evaluate any changes in its
				//	Upstream(S, G) state machine.
				PIMHeader prune;
				ForgeJoinPruneMessage(prune, refresh.m_originatorAddr.m_unicastAddress);
				PIMHeader::MulticastGroupEntry mge;
				CreateMulticastGroupEntry(mge, ForgeEncodedGroup(refresh.m_multicastGroupAddr.m_groupAddress));
				AddMulticastGroupSourcePrune(mge, ForgeEncodedSource(refresh.m_sourceAddr.m_unicastAddress));
				AddMulticastGroupEntry(prune, mge);
				prune.GetJoinPruneMessage().m_joinPruneMessage.m_holdTime = sgState->SG_AT.GetDelay();
				Ptr<Packet> packet = Create<Packet> ();
				Simulator::Schedule(TransmissionDelay(),&MulticastRoutingProtocol::SendPacketPIMUnicast, this, packet, prune, refresh.m_originatorAddr.m_unicastAddress);
				UpstreamStateMachine(sgp);
			}
			break;
			}
		case Assert_Loser:{
			//Receive Inferior Assert or State Refresh from Current Winner.
			//   An Assert or State Refresh is received from the current Assert
			//   winner that is worse than this router's metric for S (typically,
			//   the winner's metric became worse).  The Assert state machine MUST
			//   transition to NoInfo (NI) state and cancel AT(S, G, I).  The router
			//   MUST delete the previous Assert Winner's address and metric and
			//   evaluate any possible transitions to its Upstream(S, G) state
			//   machine.  Usually this router will eventually re-assert and win
			//   when data packets from S have started flowing again.
			struct AssertMetric received (refresh.m_metricPreference, refresh.m_metric, refresh.m_originatorAddr.m_unicastAddress);
			if(received < my_assert_metric(refresh.m_sourceAddr.m_unicastAddress, refresh.m_multicastGroupAddr.m_groupAddress, interface, sender)){
				sgState->AssertState = Assert_NoInfo;
				if(sgState->SG_AT.IsRunning())
					sgState->SG_AT.Cancel();
				UpdateAssertWinner(sgState, 0XFFFFFFFF, 0XFFFFFFFF, Ipv4Address("255.255.255.255"));
				UpstreamStateMachine(sgp);
			}
			else{
			//Receive Preferred Assert or State Refresh.
			//	An Assert or State Refresh is received that has a metric better
			//	than or equal to that of the current Assert winner.  The Assert
			//	state machine remains in Loser (L) state.  If the metric was
			//	received in an Assert, the router MUST set the Assert Timer
			//	(AT(S, G, I)) to Assert_Time.  If the metric was received in a
			//	State Refresh, the router MUST set the Assert Timer (AT(S, G, I))
			//	to three times the received State Refresh Interval.  If the
			//	metric is better than the current Assert Winner, the router MUST
			//	store the address and metric of the new Assert Winner,
				if(sgState->SG_AT.IsRunning())
					sgState->SG_AT.Cancel();
				sgState->SG_AT.SetDelay(Seconds(3*refresh.m_interval));
				sgState->SG_AT.SetFunction(&MulticastRoutingProtocol::ATTimerExpire, this);
				sgState->SG_AT.SetArguments(sgp, interface, sender);
				sgState->SG_AT.Schedule();
				UpdateAssertWinner(sgState, refresh.m_metricPreference, refresh.m_metric, refresh.m_originatorAddr.m_unicastAddress);
				if(CouldAssert(refresh.m_sourceAddr.m_unicastAddress, refresh.m_multicastGroupAddr.m_groupAddress, interface, sender)){
					//	and if CouldAssert(S, G, I) == TRUE, the router MUST multicast a
					//	Prune(S, G) to the new Assert winner.
					PIMHeader prune;
					ForgeJoinPruneMessage(prune, refresh.m_originatorAddr.m_unicastAddress);
					PIMHeader::MulticastGroupEntry mge;
					CreateMulticastGroupEntry(mge, ForgeEncodedGroup(refresh.m_multicastGroupAddr.m_groupAddress));
					AddMulticastGroupSourcePrune(mge, ForgeEncodedSource(refresh.m_sourceAddr.m_unicastAddress));
					AddMulticastGroupEntry(prune, mge);
//					prune.GetJoinPruneMessage().m_joinPruneMessage.m_holdTime = sgState->SG_AT.GetDelay(); \\ TODO check
					Ptr<Packet> packet = Create<Packet> ();
					Simulator::Schedule(TransmissionDelay(),&MulticastRoutingProtocol::SendPacketPIMUnicast, this, packet, prune, refresh.m_originatorAddr.m_unicastAddress);
				}
			}
			break;
		}
		default:{
			NS_LOG_ERROR("RecvStateRefresh: Assert State not valid"<<sgState->AssertState);
			break;
		}
	}
}

void
MulticastRoutingProtocol::ForwardingStateRefresh(PIMHeader::StateRefreshMessage &refresh, Ipv4Address sender, Ipv4Address receiver)
{
	//4.5.1.  Forwarding of State Refresh Messages.
	//	When a State Refresh message, SRM, is received, it is forwarded according to the following pseudo-code.
	WiredEquivalentInterface wei = RPF_interface(refresh.m_sourceAddr.m_unicastAddress);
	int32_t iif = RPF_interface(sender).first;
	if (iif<0 || IsDownstream(iif, sender, refresh.m_sourceAddr.m_unicastAddress, refresh.m_multicastGroupAddr.m_groupAddress ))
		return;
	//srcaddr(SRM) returns the source address contained in the network
	//	protocol (e.g., IPv4) header of the State Refresh Message, SRM.
	if (RPF_prime(refresh.m_sourceAddr.m_unicastAddress, refresh.m_multicastGroupAddr.m_groupAddress) != sender)//source=sender here? refresh.m_sourceAddr.m_unicastAddress
		return;
	//StateRefreshRateLimit(S, G) is TRUE if the time elapsed since the last received StateRefresh(S, G)
	//	is less than the configured RefreshLimitInterval.
	if (StateRefreshRateLimit(refresh.m_sourceAddr.m_unicastAddress, refresh.m_multicastGroupAddr.m_groupAddress))
		return;
	std::set<WiredEquivalentInterface> nbrs = pim_nbrs();
	for(std::set<WiredEquivalentInterface>::iterator i_nbrs = nbrs.begin(); i_nbrs != nbrs.end() ; i_nbrs++){
		//TTL(SRM) returns the TTL contained in the State Refresh Message, SRM.
		//	This is different from the TTL contained in the IP header.
		//
		//Threshold(I) returns the minimum TTL that a packet must have before it can be transmitted on interface I.
		if (refresh.m_ttl == 0 || (refresh.m_ttl - 1) < getThreshold(i_nbrs->first))
			continue;     /* Out of TTL, skip this interface */
		//Boundary(I, G) is TRUE if an administratively scoped boundary for group G is configured on interface I.
		if (boundary(i_nbrs->first, refresh.m_multicastGroupAddr.m_groupAddress))
			continue;     /* This interface is scope boundary, skip it */
		if (i_nbrs->first == iif)
			continue;     /* This is the incoming interface, skip it */
		if (lost_assert(refresh.m_sourceAddr.m_unicastAddress, refresh.m_multicastGroupAddr.m_groupAddress, i_nbrs->first, i_nbrs->second))
			continue;     /* Let the Assert Winner do State Refresh */
		// Create a new message
		PIMHeader refreshFRW;
		refreshFRW.GetStateRefreshMessage() = refresh;
		PIMHeader::StateRefreshMessage SRMP = refreshFRW.GetStateRefreshMessage();
		// Copy SRM to SRMP';   /* Make a copy of SRM to forward */
		std::set<WiredEquivalentInterface> prunez = prunes(refresh.m_sourceAddr.m_unicastAddress, refresh.m_multicastGroupAddr.m_groupAddress);
		// if (I contained in prunes(S, G)) {
		WiredEquivalentInterface match (i_nbrs->first, i_nbrs->second);
		if(prunez.find(match)!=prunez.end()){
			SRMP.m_P = 1;
			// set Prune Indicator bit of SRMP' to 1;
			// StateRefreshCapable(I) is TRUE if all neighbors on an interface use the State Refresh option.
			if (StateRefreshCapable(i_nbrs->first)){
				SourceGroupPair sgp (refresh.m_sourceAddr.m_unicastAddress, refresh.m_multicastGroupAddr.m_groupAddress, sender);
				SourceGroupState *sgState = FindSourceGroupState(i_nbrs->first, i_nbrs->second, sgp);
				Time pruneHoldTime = FindNeighborhoodStatus(i_nbrs->first)->pruneHoldtime;
				//set PT(S, G) to largest active holdtime read from a Prune  message accepted on I;
				sgState->SG_PT.SetDelay(pruneHoldTime);
				//sgState->SG_SR_TTL = (sgState->SG_SR_TTL > refresh.m_ttl? sgState->SG_SR_TTL:refresh.m_ttl);
			}
		} else {// set Prune Indicator bit of SRMP' to 0;
			SRMP.m_P = 0;
		}
		// set srcaddr(SRMP') to my_addr(I): my_addr(I) returns this node's network (e.g., IPv4) address on interface I.
		SRMP.m_originatorAddr.m_unicastAddress = GetLocalAddress(i_nbrs->first);
		// set TTL of SRMP' to TTL(SRM) - 1;
		SRMP.m_ttl = refresh.m_ttl-1;
		// set metric of SRMP' to metric of unicast route used to reach S;
		SRMP.m_metric = GetRouteMetric(wei.first, refresh.m_sourceAddr.m_unicastAddress);//(refresh.m_sourceAddr.m_unicastAddress));
		// set pref of ' to preference of unicast route used to reach S;
		SRMP.m_metricPreference = GetMetricPreference(wei.first);//GetReceivingInterface(refresh.m_sourceAddr.m_unicastAddress));
		// set mask of SRMP' to mask of route used to reach S;
		SourceGroupPair sgp (refresh.m_sourceAddr.m_unicastAddress, refresh.m_multicastGroupAddr.m_groupAddress, sender);
		SourceGroupState *sgState = FindSourceGroupState(i_nbrs->first, i_nbrs->second, sgp);
		SRMP.m_O = (sgState->AssertState == Assert_NoInfo) ? 1: 0;
		//set Assert Override of SRMP' to 1;
		//set Assert Override of SRMP' to 0;
		//transmit SRMP' on I;
		Ptr<Packet> packet;
		Simulator::Schedule(TransmissionDelay(),&MulticastRoutingProtocol::SendPacketPIMUnicast, this, packet, refreshFRW, i_nbrs->second);
	}
}

void
MulticastRoutingProtocol::RecvHello(PIMHeader::HelloMessage &hello, Ipv4Address sender, Ipv4Address receiver, int32_t interface)
{
	NS_LOG_LOGIC("Sender = "<< sender<< " Receiver = "<< receiver);
	uint16_t entry = 0;
	NeighborState *tmp = new NeighborState (sender, receiver);
	NeighborState *ns = FindNeighborState(interface, *tmp);
	if(!ns){// Hello message received from a new neighbor
		InsertNeighborState(interface, *tmp);
		ns = FindNeighborState(interface, *tmp);
		NeighborhoodStatus *nst = FindNeighborhoodStatus(interface);
		// If a Hello message is received from a new neighbor, the receiving router SHOULD send its own Hello message
		//    after a random delay between 0 and Triggered_Hello_Delay.
		Time delay = Seconds(UniformVariable().GetValue(0, Triggered_Hello_Delay));
		Simulator::Schedule (delay, &MulticastRoutingProtocol::SendHelloReply, this, interface, sender);
		NS_LOG_DEBUG("Neighbors = "<< nst->neighbors.size() << ", reply at "<<(Simulator::Now()+delay).GetSeconds());
		SourceGroupList *sgl = FindSourceGroupList(interface, sender);
		if(!sgl) InsertSourceGroupList(interface, sender);
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
						EraseNeighborState(interface, *tmp);
						break;
					default:
						if(ns->neigborNLT.IsRunning()){
							ns->neigborNLT.Cancel();
						}
						ns->neigborNLT.SetDelay(value);
						ns->neigborNLT.SetFunction(&MulticastRoutingProtocol::NLTTimerExpire, this);
						ns->neigborNLT.SetArguments(ns->neighborIfaceAddr, ns->receivingIfaceAddr, interface);
						ns->neigborNLT.Schedule();
						if(ns->neighborTimeoutB)
							ns->neighborTimeout += Seconds(value.GetSeconds());
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
					EraseNeighborState(interface, *ns);
					InsertNeighborState(interface, *tmp);
					NeighborRestart(interface, sender);
				}
				break;
			}
			case PIMHeader::HelloMessage::LANPruneDelay:{
				NeighborhoodStatus *nStatus = FindNeighborhoodStatus(interface);
				//If all routers on a LAN support the LAN Prune Delay option, then the PIM routers on that LAN will use the values received to adjust their
				//	J/P_Override_Interval on that interface and the interface is LAN Delay Enabled.
				if(nStatus->LANDelayEnabled){
				//  Briefly, to avoid synchronization of Prune Override (Join) messages when multiple downstream routers share a multi-access link,
				//	sending of these messages is delayed by a small random amount of time.  The period of randomization is configurable and has a default value of 3 seconds.
					ns->neighborT = hello.m_optionList[entry].m_optionValue.lanPruneDelay.m_T;
					if(ns->neighborPropagationDelay != Time(hello.m_optionList[entry].m_optionValue.lanPruneDelay.m_propagationDelay)){
						// When all routers on a link use the LAN Prune Delay Option, all routers on the
						//   LAN MUST set Propagation Delay to the largest LAN Delay on the LAN.
						ns->neighborPropagationDelay = Time(hello.m_optionList[entry].m_optionValue.lanPruneDelay.m_propagationDelay);
						nStatus->propagationDelay = Max(ns->neighborPropagationDelay, nStatus->propagationDelay);
					}
					if(ns->neighborOverrideInterval != Time(hello.m_optionList[entry].m_optionValue.lanPruneDelay.m_overrideInterval)){
						// When all routers on a LAN use the LAN Prune Delay Option, all routers on the
						//   LAN MUST set their Override_Interval to the largest Override value on the LAN.
						ns->neighborOverrideInterval = Time(hello.m_optionList[entry].m_optionValue.lanPruneDelay.m_overrideInterval);
						nStatus->overrideInterval = Max(ns->neighborOverrideInterval, nStatus->overrideInterval);
					}
				}
				break;
			}
			case PIMHeader::HelloMessage::StateRefreshCapable:{
				ns->neighborVersion = hello.m_optionList[entry].m_optionValue.stateRefreshCapable.m_version;
				ns->neighborInterval = hello.m_optionList[entry].m_optionValue.stateRefreshCapable.m_interval;
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
	NeighborTimeout(interface);//just on this interface
}

struct IsExpired
{
  bool operator() (const NeighborState & ns) const
  {
    return (ns.neighborTimeoutB && ns.neighborTimeout < Simulator::Now());
  }
};

void
MulticastRoutingProtocol::NeighborTimeout(int32_t interface)
{
	NS_LOG_FUNCTION(this);
	NeighborhoodStatus *nl = FindNeighborhoodStatus(interface);
	int32_t size = nl->neighbors.size();
	IsExpired pred;
	nl->neighbors.erase (std::remove_if (nl->neighbors.begin (), nl->neighbors.end (), pred), nl->neighbors.end ());
	NS_LOG_LOGIC("Clean neighbors list on interface "<< interface<<": "<< size << " -> "<< nl->neighbors.size());
}

void
MulticastRoutingProtocol::SetInterfaceExclusions (std::set<uint32_t> exceptions)
{
	NS_LOG_FUNCTION(this);
	m_interfaceExclusions = exceptions;
}

void
MulticastRoutingProtocol::UpdateAssertWinner (SourceGroupState *sgState, int32_t interface){
	NS_LOG_FUNCTION(this);
	sgState->AssertWinner.metricPreference = GetMetricPreference (interface);
	sgState->AssertWinner.routeMetric = GetRouteMetric (interface,sgState->SGPair.sourceMulticastAddr);
	sgState->AssertWinner.IPAddress = GetLocalAddress (interface);
}

void
MulticastRoutingProtocol::UpdateAssertWinner (SourceGroupState *sgState, AssertMetric update){
	NS_LOG_FUNCTION(this);
	sgState->AssertWinner.metricPreference = update.metricPreference;
	sgState->AssertWinner.routeMetric = update.routeMetric;
	sgState->AssertWinner.IPAddress = update.IPAddress;
}

void MulticastRoutingProtocol::UpdateAssertWinner (SourceGroupState *sgState, uint32_t metricP, uint32_t routeP, Ipv4Address winner){
	NS_LOG_FUNCTION(this);
	sgState->AssertWinner.metricPreference = metricP;
	sgState->AssertWinner.routeMetric = routeP;
	sgState->AssertWinner.IPAddress = winner;
}

SourceGroupList* MulticastRoutingProtocol::FindSourceGroupList (int32_t interface, Ipv4Address neighbor) {
	NS_LOG_FUNCTION(this<<interface<<neighbor);
	std::map<WiredEquivalentInterface, SourceGroupList>::iterator iter =
			m_IfaceSourceGroup.find (WiredEquivalentInterface(interface,neighbor));
	return (iter == m_IfaceSourceGroup.end () ? NULL : &iter->second);
}

void MulticastRoutingProtocol::InsertSourceGroupList (int32_t interface, Ipv4Address neighbor) {
	NS_LOG_FUNCTION(this<<interface<<neighbor);
	WiredEquivalentInterface i_n (interface,neighbor);
	std::map<WiredEquivalentInterface, SourceGroupList>::iterator iter =
			m_IfaceSourceGroup.find (i_n);
	if (iter != m_IfaceSourceGroup.end ())
		return;
	SourceGroupList *sgl = new SourceGroupList ();
	std::pair<WiredEquivalentInterface , SourceGroupList> i_s (i_n, *sgl);
	m_IfaceSourceGroup.insert (i_s);
}

void MulticastRoutingProtocol::InsertSourceGroupState (int32_t interface, Ipv4Address neighbor, SourceGroupPair sgp) {
	NS_LOG_FUNCTION(this<<interface<<neighbor<<sgp.sourceMulticastAddr<<sgp.groupMulticastAddr);
	SourceGroupState *sgState = FindSourceGroupState (interface, neighbor, sgp);
	NS_ASSERT(interface >0 && interface <m_ipv4->GetNInterfaces());
	if (!sgState) {
		SourceGroupState *sgs = new SourceGroupState (sgp);
		sgs->SGPair.nextMulticastAddr = neighbor;
		sgs->LocalMembership = Local_NoInfo;
		sgs->PruneState = Prune_NoInfo;
		sgs->AssertState = Assert_NoInfo;
		WiredEquivalentInterface key(interface,neighbor);
		SourceGroupList *sgl = new SourceGroupList ();
		std::pair<WiredEquivalentInterface,SourceGroupList> k_pair(key,*sgl);
		m_IfaceSourceGroup.insert(k_pair);
		NS_ASSERT(m_IfaceSourceGroup.find(key) != m_IfaceSourceGroup.end());
		m_IfaceSourceGroup.find(key)->second.push_back(*sgs);
		NS_ASSERT(m_IfaceSourceGroup.find(key)->second.size() > 0);
		sgState = FindSourceGroupState (interface, neighbor, sgp);
		if(IsUpstream(interface,neighbor,sgp) && !sgState->upstream){
			sgState->upstream = new UpstreamState ();
		}
		}
	}

SourceGroupState* MulticastRoutingProtocol::FindSourceGroupState (int32_t interface, Ipv4Address neighbor, const SourceGroupPair &sgp) {
	NS_LOG_FUNCTION(this<<interface<<neighbor<<sgp.sourceMulticastAddr<<sgp.groupMulticastAddr);
	SourceGroupList *sgl = FindSourceGroupList (interface, neighbor);
	if (!sgl)
		return NULL;
	for (SourceGroupList::iterator iter = sgl->begin (); iter != sgl->end (); iter++) {
		if (iter->SGPair == sgp)
			return & (*iter);
	}
	return NULL;
}

SourceGroupState* MulticastRoutingProtocol::FindSourceGroupState (int32_t interface, Ipv4Address neighbor, const SourceGroupPair &sgp, bool add) {
	NS_LOG_FUNCTION(this<<interface<<neighbor<<sgp.sourceMulticastAddr<<sgp.groupMulticastAddr);
	if (add && !FindSourceGroupList(interface, neighbor))
		InsertSourceGroupList(interface, neighbor);
	if (add && !FindSourceGroupState(interface, neighbor, sgp))
		InsertSourceGroupState(interface, neighbor, sgp);
	SourceGroupState *sgState = FindSourceGroupState(interface, neighbor, sgp);
	if(add //&& IsUpstream(interface, neighbor, sgp)
			&& sgState->upstream == NULL){
		sgState->upstream = new UpstreamState ();
	}
	return FindSourceGroupState(interface, neighbor, sgp);
}

SourceGroupState* MulticastRoutingProtocol::FindSourceGroupState (int32_t interface, Ipv4Address neighbor, const Ipv4Address source, const Ipv4Address group) {
	NS_LOG_FUNCTION(this<<interface<<neighbor<<source<<group);
	SourceGroupPair *sgp =new SourceGroupPair (source, group, neighbor);
	return FindSourceGroupState (interface, neighbor, *sgp);
}

void MulticastRoutingProtocol::EraseSourceGroupList (int32_t interface, Ipv4Address neighbor) {
	NS_LOG_FUNCTION(this<<interface<<neighbor);
	m_IfaceSourceGroup.erase (WiredEquivalentInterface(interface,neighbor));
}

NeighborhoodStatus* MulticastRoutingProtocol::FindNeighborhoodStatus (int32_t interface) {
	std::map<int32_t, NeighborhoodStatus>::iterator iter = m_IfaceNeighbors.find (interface);
	return (iter == m_IfaceNeighbors.end () ? NULL : & (iter->second));
}

void MulticastRoutingProtocol::InsertNeighborhoodStatus (const int32_t interface) {
	if (!FindNeighborhoodStatus (interface)) {
		NeighborhoodStatus *is = new NeighborhoodStatus;
		m_IfaceNeighbors.insert (std::pair<int32_t, NeighborhoodStatus> (interface, *is));
	}
}

void MulticastRoutingProtocol::EraseNeighborhoodStatus (const int32_t interface) {
	m_IfaceNeighbors.erase (interface);
}

NeighborState* MulticastRoutingProtocol::FindNeighborState (int32_t interface, const NeighborState ns) {
	NeighborhoodStatus *status = FindNeighborhoodStatus (interface);
	if (!status)
		return NULL;
	NeighborList *list = &status->neighbors;
	for (NeighborList::iterator iter = list->begin (); iter != list->end (); iter++) {
		NeighborState *no = & (*iter);
		if (*iter == ns)
			return & (*iter);
	}
	return NULL;
}

NeighborState* MulticastRoutingProtocol::FindNeighborState (int32_t interface, const NeighborState ns, bool append) {
	if(append) {
		InsertNeighborhoodStatus(interface);
		InsertNeighborState(interface,ns);
	}
	return FindNeighborState(interface, ns);
}

void MulticastRoutingProtocol::InsertNeighborState(int32_t interface, const NeighborState ns) {
	if (!FindNeighborState(interface, ns)) {
		NeighborhoodStatus *nstatus = FindNeighborhoodStatus(interface);
		NS_ASSERT(nstatus!=NULL);
		nstatus->neighbors.push_back(ns);
		NeighborState *neighbor = FindNeighborState(interface, ns);
		NS_ASSERT(neighbor!=NULL);
		if(neighbor->neigborNLT.IsRunning())
			neighbor->neigborNLT.Cancel();
		neighbor->neighborCreation = Simulator::Now();
		neighbor->neighborTimeout = neighbor->neighborCreation;
		neighbor->neighborTimeoutB = true;
	}
}

void MulticastRoutingProtocol::EraseNeighborState (int32_t interface, const NeighborState &ns) {
	NeighborhoodStatus *nstatus = FindNeighborhoodStatus (interface);
	if(nstatus)	nstatus->neighbors.remove(ns);
}

void MulticastRoutingProtocol::SetPropagationDelay (int32_t interface, Time delay) {
	NeighborhoodStatus *in = FindNeighborhoodStatus (interface);
	in->propagationDelay = delay;
}

void MulticastRoutingProtocol::SetOverrideInterval (int32_t interface, Time interval) {
	NeighborhoodStatus *in = FindNeighborhoodStatus (interface);
	in->overrideInterval = interval;
}

void MulticastRoutingProtocol::GetPrinterList (std::string string, std::set<WiredEquivalentInterface > resB){
	std::cout<<string<<": ";
	for (std::set<WiredEquivalentInterface >::iterator iter = resB.begin (); iter!= resB.end (); iter++){
		std::cout<<"("<<iter->first<<","<<iter->second<<") ";
	}
	std::cout<< (resB.begin () == resB.end ()?"-":".")<<"\n";
}

void MulticastRoutingProtocol::SetLANDelayEnabled (int32_t interface, bool state) {
	NeighborhoodStatus *in = FindNeighborhoodStatus (interface);
	in->LANDelayEnabled = state;
}

void MulticastRoutingProtocol::EnablePimInterface(int32_t interface){
	if(m_IfacePimEnabled.find(interface) == m_IfacePimEnabled.end())
		m_IfacePimEnabled.insert(std::pair<int32_t,bool>(interface,true));
	else m_IfacePimEnabled.find(interface)->second = true;
}

void MulticastRoutingProtocol::DisablePimInterface(int32_t interface){
	if(m_IfacePimEnabled.find(interface) == m_IfacePimEnabled.end())
		m_IfacePimEnabled.insert(std::pair<int32_t,bool>(interface,false));
	else m_IfacePimEnabled.find(interface)->second = false;
}

bool MulticastRoutingProtocol::GetPimInterface(int32_t interface){
	if(m_IfacePimEnabled.find(interface) == m_IfacePimEnabled.end())
		return false;
	else
		return m_IfacePimEnabled.find(interface)->second;
}

void MulticastRoutingProtocol::SetHelloHoldTime (uint16_t holdt){
	m_helloHoldTime = holdt;
}

uint16_t MulticastRoutingProtocol::GetHelloHoldTime (){
	return m_helloHoldTime;
}

void MulticastRoutingProtocol::SetGenerationID (uint32_t gid) {
	m_generationID = gid;
}
uint32_t MulticastRoutingProtocol::GetGenerationID () {
	return m_generationID;
}

void MulticastRoutingProtocol::SetStopTx () {
	m_stopTx = true;
}

void MulticastRoutingProtocol::UnsetStopTx () {
	m_stopTx = false;
}

bool MulticastRoutingProtocol::GetStopTx (){
	return m_stopTx;
}

bool MulticastRoutingProtocol::GetMulticastGroup (Ipv4Address group){
	return (group.IsMulticast () && m_mrib.find (group)!=m_mrib.end ());
}

void MulticastRoutingProtocol::DelMulticastGroup (Ipv4Address group){
	if (group.IsMulticast () && GetMulticastGroup (group)){
		m_mrib.find(group)->second.mgroup.clear();
		m_mrib.erase (group);
	}
}

//int32_t MulticastRoutingProtocol::GetReceivingInterface (Ipv4Address addr){
//	int32_t interface = -1;
//	if (!addr.IsMulticast ()){
//		Ptr<Ipv4Route> route = GetRoute (addr);
//		if(route){
//			Ptr<NetDevice> dev = route->GetOutputDevice ();
//			interface = m_ipv4->GetInterfaceForDevice (dev);
//		}
//	}
//	return interface;
//}

/// Threshold (I) returns the minimum TTL that a packet must have before it can be transmitted on interface I.
uint32_t MulticastRoutingProtocol::getThreshold (int32_t interface){
	return 2; //TODO check what is it
}


void MulticastRoutingProtocol::Tokenize(const std::string& str, std::vector<std::string>& tokens, const std::string& delimiters)
{
// Skip delimiters at beginning.
std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
// Find first "non-delimiter".
std::string::size_type pos     = str.find_first_of(delimiters, lastPos);
	while (std::string::npos != pos || std::string::npos != lastPos)
	{
		// Found a token, add it to the vector.
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		NS_LOG_DEBUG("\""<<str.substr(lastPos, pos - lastPos)<<"\""<< " POS "<< pos << " LAST "<< lastPos);
		// Skip delimiters.  Note the "not_of"
		lastPos = str.find_first_not_of(delimiters, pos);
		// Find next "non-delimiter"
		pos = str.find_first_of(delimiters, lastPos);
	}
}

Ipv4Header MulticastRoutingProtocol::BuildHeader (Ipv4Address source, Ipv4Address destination, uint8_t protocol, uint16_t payloadSize, uint8_t ttl, bool mayFragment)
{
	Ipv4Header ipv4header;
	ipv4header.SetSource(source);
	ipv4header.SetDestination(destination);
	ipv4header.SetProtocol(protocol);
	ipv4header.SetPayloadSize(payloadSize);
	ipv4header.SetTtl((ttl>0?ttl:1));
	if(mayFragment){
		ipv4header.SetMayFragment();
		ipv4header.SetIdentification(m_identification);
		m_identification++;
	}
	else {
		ipv4header.SetDontFragment ();
		ipv4header.SetIdentification (m_identification);
		m_identification++;
	}
	if (Node::ChecksumEnabled ()){
		ipv4header.EnableChecksum ();
	}
	return ipv4header;
}

///< Randomized delay to prevent response implosion when sending a join message to override someone else's prune
/// t_override is a random value between 0 and the interface's Override_Interval (OI (I)).
/// If all routers on a LAN are using the LAN Prune Delay option, the Override_Interval (OI (I)) MUST be set to the
/// largest value on the LAN. Otherwise, the Override_Interval (OI (I)) MUST be set to 2.5 seconds.

double MulticastRoutingProtocol::t_override (int32_t interface){
	return UniformVariable ().GetValue (0, OverrideInterval (interface));
}

double MulticastRoutingProtocol::OverrideInterval (int32_t interface){
		NeighborhoodStatus *ns = FindNeighborhoodStatus (interface);
		bool LPDO = true;
		for (std::list<NeighborState>::iterator iter = ns->neighbors.begin (); iter!=ns->neighbors.end () && LPDO; iter++){
			LPDO = LPDO && (iter->neighborOverrideInterval.GetSeconds ()>0);
			ns->overrideInterval = Max (ns->overrideInterval ,iter->neighborOverrideInterval);
		}
		return (LPDO?ns->overrideInterval.GetSeconds ():Override_Interval);
}

PIMHeader::EncodedUnicast MulticastRoutingProtocol::ForgeEncodedUnicast (Ipv4Address unicast){
		PIMHeader::EncodedUnicast egroup = {AF_IPv4, NATIVE_ENCODING, unicast};
		return egroup;
	}

PIMHeader::EncodedGroup MulticastRoutingProtocol::ForgeEncodedGroup (Ipv4Address group){
	PIMHeader::EncodedGroup egroup = {AF_IPv4, NATIVE_ENCODING, 0, 0, 0, IPV4_ADDRESS_SIZE, group};
	return egroup;
}

PIMHeader::EncodedSource MulticastRoutingProtocol::ForgeEncodedSource (Ipv4Address source){
	PIMHeader::EncodedSource esource = {AF_IPv4, NATIVE_ENCODING, 0, 0, 0, 0, IPV4_ADDRESS_SIZE, source};
	return esource;
}

//The macro I_Am_Assert_loser (S, G, I) is true if the Assert state
//  machine (in Section 4.6) for (S,G) on interface I is in the "I am
//  Assert Loser" state.
Ipv4Address MulticastRoutingProtocol::RPF_prime (Ipv4Address source, Ipv4Address group) {
	WiredEquivalentInterface wei = RPF_interface (source);
	if (I_Am_Assert_loser (source, group, wei.first, wei.second)) {
		return AssertWinner (source, group, wei.first, wei.second);
	} else {
		return wei.second;
	}
}

bool MulticastRoutingProtocol::I_Am_Assert_loser (Ipv4Address source, Ipv4Address group, int32_t interface, Ipv4Address nexthop) {
	SourceGroupState *sgState = FindSourceGroupState (interface, nexthop, source, group);
	return (sgState != NULL?sgState->AssertState == Assert_Loser: false);
}

bool MulticastRoutingProtocol::CouldAssert (Ipv4Address source, Ipv4Address group, int32_t interface, Ipv4Address neighbor) {
	WiredEquivalentInterface rpfCheck = RPF_interface (source);
	bool couldAssert = !(rpfCheck.first == interface && rpfCheck.second == neighbor);
	return couldAssert;
}

struct AssertMetric MulticastRoutingProtocol::spt_assert_metric (Ipv4Address source, int32_t interface) {
	struct AssertMetric assertMetric (GetMetricPreference (interface), GetRouteMetric (interface,source), GetLocalAddress (interface));
	return assertMetric;
}

struct AssertMetric MulticastRoutingProtocol::infinite_assert_metric (){
	struct AssertMetric assertMetric (0xFFFFFFFF, 0xFFFFFFFF, Ipv4Address ("255.255.255.255"));
	return assertMetric;
}

struct AssertMetric MulticastRoutingProtocol::my_assert_metric (Ipv4Address source, Ipv4Address group, int32_t interface, Ipv4Address neighbor) {
	if (CouldAssert (source, group, interface, neighbor)) {
		return spt_assert_metric (source, interface);
	} else {
		return infinite_assert_metric ();
	}
}

//StateRefreshRateLimit (S,G) is TRUE if the time elapsed since the last received StateRefresh (S,G)
//	is less than the configured RefreshLimitInterval.
bool MulticastRoutingProtocol::StateRefreshRateLimit (Ipv4Address source, Ipv4Address group){
	WiredEquivalentInterface wei = RPF_interface (source);
	return FindSourceGroupState (wei.first, wei.second, source, group)->lastStateRefresh.GetSeconds () < RefreshInterval;
}

bool MulticastRoutingProtocol::StateRefreshCapable (int32_t interface){
	return FindNeighborhoodStatus (interface)->stateRefreshCapable;
}

void MulticastRoutingProtocol::SetPruneState (int32_t interface, Ipv4Address neighbor, SourceGroupPair sgp, PruneState state){
	FindSourceGroupState (interface, neighbor, sgp)->PruneState = state;
}

/// \brief The outgoing interfaces except the RPF_interface.
///
/// \param source Source IPv4 address
/// \param group Multicast group IPv4 address
std::set<WiredEquivalentInterface > MulticastRoutingProtocol::olist (Ipv4Address source, Ipv4Address group) {
	std::set<WiredEquivalentInterface > _olist = immediate_olist (source, group);
	// GetPrinterList ("olist", _olist);
	_olist.erase (RPF_interface(source, group));
	// GetPrinterList ("olist-RPF interface",_olist);
	return _olist;
}

void MulticastRoutingProtocol::AskRoute (Ipv4Address destination){
	//TODO: We don't know the next hop towards the source: first node finds it, then it relies packets.
	NS_LOG_FUNCTION(this<< destination);
	PIMHeader msg;
	Ptr<Packet> packet = Create<Packet> (); //forge a hello reply
	int32_t interface = m_ipv4->GetInterfaceForAddress(m_mainAddress);
	ForgeHelloMessage(interface, msg);
	if(m_stopTx) return;
	packet->AddHeader(msg);
	// Trace it
	m_txPacketTrace (msg);
	// Send
	Ipv4Address local = GetLocalAddress(interface);
	for (std::map<Ptr<Socket> , Ipv4InterfaceAddress>::const_iterator i =
			m_socketAddresses.begin (); i != m_socketAddresses.end (); i++)
	{
	  if(local == i->second.GetLocal () ){
		Ptr<Packet> copy = packet->Copy();
		Ipv4Header ipv4Header = BuildHeader(i->second.GetLocal (), destination, PIM_IP_PROTOCOL_NUM, copy->GetSize(), 1, false);
		copy->AddHeader(ipv4Header);
		NS_LOG_LOGIC ("Node " << local << " is sending packet "<<copy  <<"("<<copy->GetSize() <<  ") to Destination: " << destination << ":"<<PIM_PORT_NUMBER<<", Interface "<<interface<<", Socket "<<i->first);
		i->first->SendTo (copy, 0, InetSocketAddress (destination, PIM_PORT_NUMBER));
		break;
		}
	}
}

/// \brief There are receivers for the given SourceGroup pair.
/// \param sgp source-group pair.
/// \return True if there are receivers interested in, false otherwise.
bool MulticastRoutingProtocol::GetLocalReceiver(SourceGroupPair sgp){
	return m_LocalReceiver.find(sgp) != m_LocalReceiver.end();
}

/// \brief There are receivers for the given SourceGroup pair on that interface.
/// \param sgp source-group pair.
/// \param interface node interface
/// \return True if there are receivers on the particular interface that are interested in, false otherwise.
bool MulticastRoutingProtocol::GetLocalReceiverInterface(SourceGroupPair sgp, int32_t interface){
	return GetLocalReceiver(sgp) && m_LocalReceiver.find(sgp)->second.find(interface) != m_LocalReceiver.find(sgp)->second.end();
}

/*
 * The macro local_receiver_include (S,G,I) is true if the IGMP module or
 * other local membership mechanism has determined that there are local
 * members on interface I that seek to receive traffic sent specifically by S to G.
 */
bool MulticastRoutingProtocol::local_receiver_include (Ipv4Address source, Ipv4Address group, int32_t interface) {
	if (group==Ipv4Address::GetAny () || source == Ipv4Address::GetAny())//no group or no source: no way to identify members
		return false;
	SourceGroupPair sgp (source, group);
	return GetLocalReceiverInterface(sgp, interface);
}

//
///The interfaces to which traffic might be forwarded because
//  of hosts that are local members on those interfaces.
//
//  pim_include (*,G) = {all interfaces I such that: local_receiver_include (*,G,I)}
//  pim_include (S,G) = {all interfaces I such that: local_receiver_include (S,G,I)}
std::set<WiredEquivalentInterface > MulticastRoutingProtocol::pim_include (Ipv4Address source, Ipv4Address group) {
	std::set<WiredEquivalentInterface > include;
	SourceGroupPair sgp (source,group);
	for (int32_t i = 0; i < m_ipv4->GetNInterfaces (); i++) {
		if (IsLoopInterface (i))continue;
		if (local_receiver_include (source, group, i)) {
			WiredEquivalentInterface n_include (i,GetLocalAddress(i));
			include.insert (n_include);
		}
	}
	return include;
}

//The macro local_receiver_include(*,G,I) is true if the IGMP module or
//   other local membership mechanism has determined that there are local
//   members on interface I that seek to receive all traffic sent to G.
//   Note that this determination is expected to account for membership
//   joins initiated on or by the router.
bool MulticastRoutingProtocol::seek_traffic_from (Ipv4Address source, Ipv4Address group,int32_t interface) {
	Ipv4Address nexthop = RPF_interface(source).second;
	SourceGroupState *sgs = FindSourceGroupState (interface, nexthop, source, group);
	return (sgs ? local_receiver_include(source,group,interface) : true);
}

// Local members for a (source,group) pair.
// True if local_receiver_include (*,G,I) is true
// but none of the local members seek to receive traffic from S.
bool MulticastRoutingProtocol::local_receiver_exclude (Ipv4Address source, Ipv4Address group, int32_t interface) {
	return local_receiver_include (Ipv4Address::GetAny (), group, interface)
			&& seek_traffic_from (source,group,interface);
}

/// The interfaces to which traffic might not be forwarded because of hosts that are not local members on those interfaces.
///  pim_exclude (S,G) = {all interfaces I such that: local_receiver_exclude (S,G,I)}
std::set<WiredEquivalentInterface > MulticastRoutingProtocol::pim_exclude (Ipv4Address source, Ipv4Address group) {
	std::set<WiredEquivalentInterface > exclude;
	for (int32_t i = 0; i < m_ipv4->GetNInterfaces (); i++) {
		if (IsLoopInterface (i)) continue;
		if (local_receiver_exclude (source, group, i)) {
			WiredEquivalentInterface n_exclude(i, GetLocalAddress(i));
			exclude.insert (n_exclude);
		}
	}
	return exclude;
}

bool MulticastRoutingProtocol::IsLoopInterface (int32_t interface){
	return GetLocalAddress(interface) == Ipv4Address::GetLoopback();
}

/*
 * All interfaces on which the router has at least one active PIM neighbor.
 */
std::set<WiredEquivalentInterface > MulticastRoutingProtocol::pim_nbrs (void) {
	std::set<WiredEquivalentInterface > pimNbrs;
	for (int32_t i = 0; i < m_ipv4->GetNInterfaces (); i++) {
		if (IsLoopInterface (i) || m_IfaceNeighbors.find(i) == m_IfaceNeighbors.end())continue;
		for(NeighborList::iterator iter = m_IfaceNeighbors.find(i)->second.neighbors.begin();
				iter != m_IfaceNeighbors.find(i)->second.neighbors.end(); iter++)
			pimNbrs.insert(WiredEquivalentInterface (i, iter->neighborIfaceAddr));
	}
	return pimNbrs;
}

/*
 * The set of all interfaces on which the router has received Prune (S,G) messages:
 *   prunes (S,G) = {all interfaces I such that DownstreamPState (S,G,I) is in Pruned state}
 */
std::set<WiredEquivalentInterface > MulticastRoutingProtocol::prunes (Ipv4Address source, Ipv4Address group) {
	std::set<WiredEquivalentInterface > prune;
	SourceGroupPair sgp (source,group);
	for (int32_t i = 0; i < m_ipv4->GetNInterfaces (); i++) {
		if (IsLoopInterface (i))continue;
		for(std::map<WiredEquivalentInterface, SourceGroupList>::iterator iter = m_IfaceSourceGroup.begin();
				iter != m_IfaceSourceGroup.end(); iter++){
			if(i!=iter->first.first) continue;
			SourceGroupState *sgState = FindSourceGroupState (iter->first.first, iter->first.second, sgp);
			if (!sgState) continue;
			if (IsDownstream(iter->first.first, iter->first.second, sgp) && sgState->PruneState == Prune_Pruned) {
				prune.insert (iter->first);
			}
		}
	}
	return prune;
}

/* The set lost_assert (S,G) is the set of all interfaces on which the
 *  router has lost an (S,G) Assert.
 *  lost_assert (S,G) = {all interfaces I such that
 *            lost_assert (S,G,I) == TRUE}
 *
 */
std::set<WiredEquivalentInterface > MulticastRoutingProtocol::lost_assert (Ipv4Address source, Ipv4Address group) {
	std::set<WiredEquivalentInterface > set;
	SourceGroupPair sgp (source, group);
	for (int32_t i = 0; i < m_ipv4->GetNInterfaces (); i++) {
		if (IsLoopInterface (i)) continue;
		for(std::map<WiredEquivalentInterface, SourceGroupList>::iterator iter = m_IfaceSourceGroup.begin();
				iter != m_IfaceSourceGroup.end(); iter++){
			SourceGroupState *sgState = FindSourceGroupState (i, iter->first.second, sgp);
			if (!sgState) continue;
			if (lost_assert (source, group, i, iter->first.second))
				set.insert (iter->first);
		}
	}
	return set;
}

/*
 * True if the node has lost an (S,G) Assert on that interface.
 */
bool MulticastRoutingProtocol::lost_assert (Ipv4Address source, Ipv4Address group, int32_t interface, Ipv4Address neighbor) {
	if(IsUpstream(interface, neighbor, source, group))
		return false;
	Ipv4Address assertWinner = AssertWinner (source, group, interface, neighbor);
	bool result = assertWinner != Ipv4Address::GetAny () && assertWinner != Ipv4Address::GetBroadcast();
	result = result && !IsMyOwnAddress(assertWinner);
	result = result && AssertWinnerMetric (source, group, interface, neighbor) > spt_assert_metric (source, interface);
	return result;
}

//AssertWinner (S,G,I) defaults to NULL -> ANY
Ipv4Address MulticastRoutingProtocol::AssertWinner (Ipv4Address source, Ipv4Address group, int32_t interface, Ipv4Address neighbor) {
	SourceGroupState *sgState = FindSourceGroupState (interface, neighbor, source, group);
	return (sgState) ? sgState->AssertWinner.IPAddress : Ipv4Address::GetAny ();
}

struct AssertMetric MulticastRoutingProtocol::AssertWinnerMetric (Ipv4Address source, Ipv4Address group, int32_t interface, Ipv4Address neighbor) {
	SourceGroupState *sgState = FindSourceGroupState (interface, neighbor, source, group);
	return (!sgState || sgState->AssertState == Assert_NoInfo) ? infinite_assert_metric () : sgState->AssertWinner;
}

bool MulticastRoutingProtocol::boundary (int32_t interface, Ipv4Address group){
	//TODO administratively scoped boundary
	return false;
}

/*
 * boundary (G) = {all interfaces I with an administratively scoped boundary for group G}
 */
std::set<WiredEquivalentInterface > MulticastRoutingProtocol::boundary (Ipv4Address G) {
	std::set<WiredEquivalentInterface > bound;
	for (int32_t i = 0; i < m_ipv4->GetNInterfaces (); i++) {
		if (IsLoopInterface (i))continue;
		if (boundary (i,G)){ //administratively scoped boundary
			WiredEquivalentInterface b_pair (i ,GetLocalAddress(i));
			bound.insert(b_pair); //TODO
		}
	}
	return bound;
}

std::set<WiredEquivalentInterface > MulticastRoutingProtocol::immediate_olist (Ipv4Address source, Ipv4Address group) {
	std::set<WiredEquivalentInterface > resA;
	/// The set pim_nbrs is the set of all interfaces on which the router has at least one active PIM neighbor.
	std::set<WiredEquivalentInterface > pim_nbrz = pim_nbrs ();
	// GetPrinterList ("pim_nbrz",pim_nbrz);
	/// prunes (S,G) = {all interfaces I such that DownstreamPState (S,G,I) is in Pruned state}
	std::set<WiredEquivalentInterface > prunez = prunes (source, group);
	// GetPrinterList ("prunez",prunez);
	/// pim_nbrs * (-)* prunes (S,G)
	std::set_difference (pim_nbrz.begin (), pim_nbrz.end (), prunez.begin (), prunez.end (),
			 std::inserter (resA, resA.end ()));
	// GetPrinterList ("pim_nbrs * (-)* prunes (S,G)",resA);
	std::set<WiredEquivalentInterface > resB;
	/// pim_include (*,G) = {all interfaces I such that: local_receiver_include (*,G,I)}
	std::set<WiredEquivalentInterface > inc = pim_include (Ipv4Address::GetAny (), group);
	// GetPrinterList ("pim_include (*,G)",inc);
	/// pim_exclude (S,G) = {all interfaces I such that: local_receiver_exclude (S,G,I)}
	std::set<WiredEquivalentInterface > exc = pim_exclude (source, group);
	// GetPrinterList ("pim_exclude (S,G)",exc);
	/// pim_include (*,G) * (-)* pim_exclude (S,G)
	std::set_difference (inc.begin (), inc.end (), exc.begin (), exc.end (), std::inserter (resB, resB.end ()));
	// GetPrinterList ("pim_include (*,G) * (-)* pim_exclude (S,G)",resB);
	std::set<WiredEquivalentInterface > result;
	/// pim_nbrs (-) prunes (S,G) * (+)* (pim_include (*,G) (-) pim_exclude (S,G) )
	std::set_union (resA.begin (), resA.end (), resB.begin (), resB.end (), std::inserter (result, result.end ()));
	// GetPrinterList ("pim_nbrs (-) prunes (S,G) * (+)* (pim_include (*,G) (-) pim_exclude (S,G))",result);
	/// pim_include (S,G) = {all interfaces I such that: local_receiver_include (S,G,I)}
	std::set<WiredEquivalentInterface > incC = pim_include (source, group);
	// GetPrinterList ("pim_include (S,G)",incC);
	/// pim_nbrs (-) prunes (S,G) (+) (pim_include (*,G) (-) pim_exclude (S,G) ) * (+)* pim_include (S,G)
	std::set_union (result.begin (), result.end (), incC.begin (), incC.end (), std::inserter (resA, resA.end ()));
	// GetPrinterList ("pim_nbrs (-) prunes (S,G) (+) (pim_include (*,G) (-) pim_exclude (S,G) ) * (+)* pim_include (S,G)",resA);
	std::set<WiredEquivalentInterface > lostC = lost_assert (source, group);
	// GetPrinterList ("lost_assert",lostC);
	/// pim_nbrs (-) prunes (S,G) (+) (pim_include (*,G) (-) pim_exclude (S,G) ) (+) pim_include (S,G) * (-)* lost_assert (S,G)
	std::set_difference (resA.begin (), resA.end (), lostC.begin (), lostC.end (),std::inserter (resB, resB.end ()));
	// GetPrinterList ("pim_nbrs (-) prunes (S,G) (+) (pim_include (*,G) (-) pim_exclude (S,G) ) (+) pim_include (S,G) * (-)* lost_assert (S,G)",resB);
	std::set<WiredEquivalentInterface > boundC = boundary (group);
	// GetPrinterList ("boundary",boundC);
	std::set<WiredEquivalentInterface > resC;
	/// pim_nbrs (-) prunes (S,G) (+) (pim_include (*,G) (-) pim_exclude (S,G) ) (+) pim_include (S,G) (-) lost_assert (S,G) * (-)* boundary (G)
	std::set_difference (resB.begin (), resB.end (), boundC.begin (), boundC.end (),std::inserter (resC, resC.end ()));
	// GetPrinterList ("pim_nbrs (-) prunes (S,G) (+) (pim_include (*,G) (-) pim_exclude (S,G) ) (+) pim_include (S,G) (-) lost_assert (S,G) * (-)* boundary (G)",resC);
	return resC;
}

Time MulticastRoutingProtocol::TransmissionDelay (){
	return TransmissionDelay(50, 1500, Time::US);
}

Time MulticastRoutingProtocol::TransmissionDelay (double l, double u){
	return TransmissionDelay(l, u, Time::S);
}

Time MulticastRoutingProtocol::TransmissionDelay (double l, double u, enum Time::Unit unit){
	double delay = UniformVariable().GetValue(l,u);
	Time delayms = Time::FromDouble(delay, unit);
//	NS_LOG_DEBUG("Time ("<<l<<","<<u<<") = "<<delayms.GetSeconds()<<"s "<< delay);
	return delayms;
}

bool
MulticastRoutingProtocol::isValidGateway(Ipv4Address gw)
{
return !(gw == Ipv4Address::GetAny() || gw == Ipv4Address::GetLoopback());
}
}
}// namespace ns3

//TODO LIST
//* The LAN Delay inserted by a router in the LAN Prune Delay option expresses the expected message propagation delay on the link and
//		SHOULD be configurable by the system administrator.
//* When a PIM router takes an interface down or changes IP address, a Hello message with a zero Hold Time SHOULD be sent immediately (with the old IP address if the IP address is
//		changed) to cause any PIM neighbors to remove the old information immediately.
//* All PIM-DM packets use the same format as PIM-SM packets.  In the event of a discrepancy, PIM-SM [4] should be considered the definitive specification.
//		All PIM control messages have IP protocol number 103.  All PIM-DM messages MUST be sent with a TTL of 1 (IPV4).
//		All PIM-DM messages except Graft and Graft Ack messages MUST be sent to the ALL-PIM-ROUTERS group.
//		Graft messages SHOULD be unicast to the RPF'(S).  Graft Ack messages MUST be unicast to the sender of the Graft.
//* When a PIM router takes an interface down or changes IP address, a Hello message with a zero Hold Time SHOULD be
//		sent immediately (with the old IP address if the IP address is changed) to cause any PIM neighbors to remove the old information immediately.
//* Packets TTL
