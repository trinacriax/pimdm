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
#include "ns3/ipv4-raw-socket-factory.h"
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
#include "ns3/ipv4-routing-table-entry.h"
#include "ns3/udp-header.h"
#include "ns3/udp-l4-protocol.h"
#include "ns3/aodv-rtable.h"
#include "ns3/aodv-routing-protocol.h"
#include "ns3/olsr-routing-protocol.h"
#include "ns3/dsdv-rtable.h"
#include "ns3/dsdv-routing-protocol.h"
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
	.AddAttribute ("HelloHoldTime", "HoldTime used in hello messages",
			 	 	UintegerValue (Hold_Time_Default),
			        MakeUintegerAccessor (&MulticastRoutingProtocol::SetHelloHoldTime),
			        MakeUintegerChecker<uint16_t> ())
	.AddAttribute ("RegisterMember", "Register a new member triple (group, source, interface) like a new IGMP entry",
					StringValue("0,0,0"),
					MakeStringAccessor(&MulticastRoutingProtocol::register_member),
					MakeStringChecker())
	.AddTraceSource ("Rx", "Receive PIM packet.",
					 MakeTraceSourceAccessor (&MulticastRoutingProtocol::m_rxPacketTrace))
	.AddTraceSource ("Tx", "Send PIM packet.",
					 MakeTraceSourceAccessor (&MulticastRoutingProtocol::m_txPacketTrace))
    .AddTraceSource ("RoutingTableChanged", "The PIM-DM routing table has changed.",
		     MakeTraceSourceAccessor (&MulticastRoutingProtocol::m_routingTableChanged))

    ;
  return tid;
}


uint16_t
MulticastRoutingProtocol::GetRouteMetric(uint32_t interface, Ipv4Address source)
{//TODO: The cost metric of the unicast route to the source.  The metric is in units applicable to the unicast routing protocol used.
  Ptr<Ipv4RoutingProtocol> rp_Gw = (m_ipv4->GetRoutingProtocol ());
  Ptr<Ipv4ListRouting> lrp_Gw = DynamicCast<Ipv4ListRouting> (rp_Gw);
  Ptr<olsr::RoutingProtocol> olsr_Gw;
//  Ptr<aodv::RoutingProtocol> aodv_Gw;
//  Ptr<dsdv::RoutingProtocol> dsdv_Gw;
  for (uint32_t i = 0; i < lrp_Gw->GetNRoutingProtocols ();  i++)
	{
	  int16_t priority;
	  Ptr<Ipv4RoutingProtocol> temp = lrp_Gw->GetRoutingProtocol (i, priority);
	  if (DynamicCast<olsr::RoutingProtocol> (temp))
		{
		  olsr_Gw = DynamicCast<olsr::RoutingProtocol> (temp);
		  std::vector<olsr::RoutingTableEntry> olsr_table = olsr_Gw->GetRoutingTableEntries();
		  for(std::vector<olsr::RoutingTableEntry>::const_iterator iter = olsr_table.begin(); iter!=olsr_table.end(); iter++){
			  if(iter->destAddr!=Ipv4Address::GetAny() && iter->destAddr == source)return iter->distance;
		  }
		}
//	  else if (DynamicCast<aodv::RoutingProtocol> (temp))
//	  		{
//	  		  aodv_Gw = DynamicCast<aodv::RoutingProtocol> (temp);
//	  		  aodv::RoutingTableEntry aodv_rte;
//	  		  aodv_Gw->m_routingTable.LookupRoute(source,aodv_rte);
//	  		  return aodv_rte.GetHop();
//	  		}
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
MulticastRoutingProtocol::GetMetricPreference(uint32_t interface)
{//TODO: The preference value assigned to the unicast routing protocol that provided the route to the source
	return 1;
}


void
MulticastRoutingProtocol::register_member (std::string SGI){
	///////////////////////// TODO: TO REMOVE WITH IGMP
	NS_LOG_FUNCTION(this);
	// Just to get the IP info
	Ipv4Address group, source;
	uint32_t interface;
	ParseSourceGroupInterface(SGI, group, source, interface);
	if(source == group && interface == 0)return;//skip initialization
	NS_LOG_DEBUG("Member for ("<<source<<","<<group<<") over interface "<< interface);
	SourceGroupPair sgp (source,group);
	if(m_LocalReceiver.find(sgp)==m_LocalReceiver.end()){//add a new receiver on a specific (source,group) on a given interface
		std::set<uint32_t> iface;
		m_LocalReceiver.insert(std::pair<SourceGroupPair, std::set<uint32_t> >(sgp,iface));
		NS_LOG_DEBUG("Adding Source-Group ("<<source<<","<<group<<") to the map");
	}
	if(m_LocalReceiver.find(sgp)->second.find(interface) == m_LocalReceiver.find(sgp)->second.end() && interface<m_ipv4->GetNInterfaces()){
		m_LocalReceiver.find(sgp)->second.insert(interface);
		NS_LOG_DEBUG("Adding interface " << interface<< " to ("<<source<<","<<group<<")");
	}
	AddEntry(group,source,Ipv4Address::GetAny(),-1);//We got an entry from IGMP for this source-group
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
	NS_LOG_FUNCTION(this);
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
	NS_LOG_FUNCTION(this << group);
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
	NS_LOG_FUNCTION(this << group<< source);
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
MulticastRoutingProtocol::UpdateEntry(Ipv4Address const group, Ipv4Address const source, Ipv4Address const next, uint32_t const interface)
{
	NS_LOG_FUNCTION(this << group<< interface);
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
MulticastRoutingProtocol::AddEntry (const Ipv4Address group, const Ipv4Address source, const Ipv4Address next, const uint32_t interface)
{
  NS_LOG_FUNCTION (this << "Group: "<< group << " Source: "<< source <<" Next: "<< next << " RPF_I: "<< interface << " MainAddress: "<< m_mainAddress);
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
	if (m_socketAddresses.empty ())
	{
	  sockerr = Socket::ERROR_NOROUTETOHOST;
	  NS_LOG_LOGIC ("No PIMDM interfaces");
	  return rtentry;
	}

	sockerr = Socket::ERROR_NOTERROR;
	RoutingMulticastTable entry1;
	bool found = Lookup(header.GetDestination(), entry1);
	NS_LOG_DEBUG ("PIM-DM node " << m_mainAddress << ": RouteOutput for dest=" << header.GetDestination ());
	if(header.GetDestination().IsMulticast()) {//entry in the routing table found
		uint32_t interfaceIdx = -1;
		if(oif!=NULL)//we are sending on a specific device, so we "want" to use that interface
			interfaceIdx = m_ipv4->GetInterfaceForDevice (oif);//
		else if(IsMyOwnAddress(header.GetSource()))//since we deal with multicast packet, and the interface is null...this might be the source
			interfaceIdx = m_ipv4->GetInterfaceForAddress(header.GetSource());
		else if(Lookup(header.GetDestination(), entry1))//we don't know anything :( looking for the first entry for this group;
			interfaceIdx = entry1.mgroup.begin()->second.interface;
		if (oif && m_ipv4->GetInterfaceForDevice (oif) != static_cast<int> (interfaceIdx)){
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

		rtentry = Create<Ipv4Route> ();
		rtentry->SetDestination (header.GetDestination ());
		// the source address is the interface address that matches
		// the destination address (when multiple are present on the
		// outgoing interface, one is selected via scoping rules)
		NS_ASSERT (m_ipv4);
		uint32_t numOifAddresses = m_ipv4->GetNAddresses (interfaceIdx);
		NS_ASSERT (numOifAddresses > 0);
		Ipv4InterfaceAddress ifAddr;
		if (numOifAddresses == 1) {
		  ifAddr = m_ipv4->GetAddress (interfaceIdx, 0);
		} else {
		  NS_FATAL_ERROR ("TODO Not implemented yet:  IP aliasing");
		}
		rtentry->SetSource (ifAddr.GetLocal ());
		rtentry->SetOutputDevice (m_ipv4->GetNetDevice (interfaceIdx));
//		rtentry->SetGateway(entry1.mgroup[interfaceIdx].nextAddr);

		Ipv4Address bcast = m_ipv4->GetAddress (interfaceIdx, 0).GetLocal().GetSubnetDirectedBroadcast ( m_ipv4->GetAddress (interfaceIdx, 0).GetMask());
		rtentry->SetGateway(bcast);
		//m_ipv4->GetAddress (interfaceIdx, 0).GetLocal().GetBroadcast());//*** Problem with GW
		sockerr = Socket::ERROR_NOTERROR;
		NS_LOG_DEBUG ("PIM-DM Routing: Src = " << rtentry->GetSource() << ", Dest = " << rtentry->GetDestination()<< ", GW = "<< rtentry->GetGateway () << ", interface = " << interfaceIdx<<" device = "<<rtentry->GetOutputDevice()->GetMulticast(rtentry->GetDestination()));
		found = true;
	}
	if (!found)
	{
	  NS_LOG_DEBUG ("PIM-DM node " << m_mainAddress
			  << ": RouteOutput for dest=" << header.GetDestination ()
			  << " No route to host");
	  sockerr = Socket::ERROR_NOROUTETOHOST;
	}
	return rtentry;
}

bool MulticastRoutingProtocol::RouteInput  (Ptr<const Packet> p,
  const Ipv4Header &header, Ptr<const NetDevice> idev,
  UnicastForwardCallback ucb, MulticastForwardCallback mcb,
  LocalDeliverCallback lcb, ErrorCallback ecb)
{
	  NS_LOG_FUNCTION (this << " " << m_ipv4->GetObject<Node> ()->GetId () << " " << header.GetDestination ());

	  Ipv4Address dst = header.GetDestination ();
	  Ipv4Address origin = header.GetSource ();

	  // Consume self-originated packets
	  if (IsMyOwnAddress (origin) == true)
	    {
	      return true;
	    }

	  // Local delivery
	  NS_ASSERT (m_ipv4->GetInterfaceForDevice (idev) >= 0);
	  uint32_t iif = m_ipv4->GetInterfaceForDevice (idev);
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
//	               NS_LOG_DEBUG ("dest=" << iter->first
////	            		   << " --> next=" << iter->second.nextAddr
//	                       << " via interface " << iter->second.interface);
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
{NS_LOG_FUNCTION(this);NS_LOG_DEBUG("Interface Up: "<<i);}

void
MulticastRoutingProtocol::NotifyInterfaceDown (uint32_t i)
{NS_LOG_FUNCTION(this);NS_LOG_DEBUG("Interface Down "<<i);}

void
MulticastRoutingProtocol::NotifyAddAddress (uint32_t interface, Ipv4InterfaceAddress address)
{NS_LOG_FUNCTION(this);}

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
MulticastRoutingProtocol::GetLocalAddress (uint32_t interface)
{
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
	NS_LOG_FUNCTION(this);
    Ipv4Address loopback ("127.0.0.1");
	if (m_mainAddress == Ipv4Address ())
	    {
	      for (uint32_t i = 0; i < m_ipv4->GetNInterfaces (); i++)
	        {
	          // Use primary address, if multiple
	          Ipv4Address addr = m_ipv4->GetAddress (i, 0).GetLocal ();
	          if (addr != loopback)
	            {
	              m_mainAddress = addr;
	              // ALL-PIM-ROUTERS socket
	              break;
	            }
	        }

	      NS_ASSERT (m_mainAddress != Ipv4Address ());
	    }
	if(m_generationID==0)
		m_generationID = UniformVariable().GetInteger(1, INT_MAX);///force value > 0
	m_startTime = Simulator::Now();
	m_rpfChecker.Cancel();
	m_rpfChecker.SetDelay(Seconds(5));
	m_rpfChecker.SetFunction(&MulticastRoutingProtocol::RPFCheckAll,this);
	m_rpfChecker.Schedule();

	NS_LOG_DEBUG ("Starting PIM_DM on node " << m_mainAddress);

	for (uint32_t i = 0; i < m_ipv4->GetNInterfaces (); i++)
		{
		Ipv4Address addr = m_ipv4->GetAddress (i, 0).GetLocal ();
		if (addr == loopback)
			continue;
		// Create socket to listen on ALL_PIM_ROUTERS4 group
		Ptr<Socket> socketP = Socket::CreateSocket (GetObject<Node> (), Ipv4RawSocketFactory::GetTypeId());
		socketP->SetAttribute("Protocol", UintegerValue(PIM_IP_PROTOCOL_NUM));
		socketP->SetAttribute("IpHeaderInclude", BooleanValue(true));
		socketP->SetAllowBroadcast (false);
		InetSocketAddress inetAddrP (ALL_PIM_ROUTERS4, PIM_PORT_NUMBER);
		socketP->SetRecvCallback (MakeCallback (&MulticastRoutingProtocol::RecvPimDm, this));
		// Add ALL_PIM_ROUTERS4 multicast group, where the source is the node it self.
		AddEntry(ALL_PIM_ROUTERS4, addr, Ipv4Address::GetAny(), i);
		if (socketP->Bind (inetAddrP)){
			NS_FATAL_ERROR ("Failed to bind() PIMDM socket");
		}
		socketP->BindToNetDevice (m_ipv4->GetNetDevice (i));
		Ipv4InterfaceAddress mpim(Ipv4Address(ALL_PIM_ROUTERS4), Ipv4Mask::GetOnes());
		m_socketAddresses[socketP] = mpim; //m_ipv4->GetAddress (i, 0);
		NS_LOG_DEBUG("Registering PIM Socket = "<<socketP << " Device = "<<m_ipv4->GetNetDevice (i)<< ", LocalAddr = "<<mpim.GetLocal()<<" Destination = "<<  ALL_PIM_ROUTERS4<<", I = "<<i<<" IfaceAddr "<<m_ipv4->GetAddress (i, 0).GetLocal());

		// Create a socket to listen only on this interface
		Ptr<Socket> socket = Socket::CreateSocket (GetObject<Node> (), Ipv4RawSocketFactory::GetTypeId());
		socket->SetAttribute("Protocol", UintegerValue(PIM_IP_PROTOCOL_NUM));
		socket->SetAttribute("IpHeaderInclude", BooleanValue(true));
		socket->SetAllowBroadcast (true);
		InetSocketAddress inetAddr (addr , PIM_PORT_NUMBER);
		socket->SetRecvCallback (MakeCallback (&MulticastRoutingProtocol::RecvPimDm, this));
		if (socket->Bind (inetAddr)){
			NS_FATAL_ERROR ("Failed to bind() PIMDM socket "<< addr<<":"<<PIM_PORT_NUMBER);
		}
		socket->BindToNetDevice (m_ipv4->GetNetDevice (i));
		m_socketAddresses[socket] = m_ipv4->GetAddress (i, 0);
		NS_LOG_DEBUG("Registering Local Socket = "<<socket << " Device = "<<m_ipv4->GetNetDevice (i)<< ", LocalAddr = "<<m_ipv4->GetAddress (i, 0).GetLocal()<<" Destination = "<<  m_ipv4->GetAddress (i, 0).GetLocal ().GetSubnetDirectedBroadcast (m_ipv4->GetAddress (i, 0).GetMask ())<<", I = "<<i<<" IfaceAddr "<<m_ipv4->GetAddress (i, 0).GetLocal());

		NS_LOG_DEBUG ("PIMDM up on " << m_ipv4->GetAddress (i, 0).GetLocal () << ", Generation Id = "<< m_generationID<<", Starting @ "<<m_startTime);
		NeighborhoodStatus *ns = FindNeighborhoodStatus(i);
		NS_ASSERT(ns == NULL);
		InsertNeighborhoodStatus(i);
		ns = FindNeighborhoodStatus(i);
		EnablePimInterface(i);
		ns->propagationDelay = Seconds(UniformVariable().GetValue(Propagation_Delay*.3, Propagation_Delay));
		ns->overrideInterval = Seconds(UniformVariable().GetValue(Override_Interval*.3, Override_Interval));
		ns->stateRefreshInterval = Seconds(UniformVariable().GetValue(RefreshInterval*.3, RefreshInterval));
		ns->pruneHoldtime = Seconds(UniformVariable().GetValue(PruneHoldTime*.3, PruneHoldTime));
		ns->LANDelayEnabled = true;
		ns->stateRefreshCapable = true;
		NS_LOG_DEBUG ("Generating Neighborhood ("<<i<<"): PD=" << ns->propagationDelay.GetSeconds() <<"s, OI="<< ns->overrideInterval.GetSeconds() <<
				"s, SRI="<< ns->stateRefreshInterval.GetSeconds()<<"s, PHT="<< ns->pruneHoldtime.GetSeconds()<<"s, LDE="<<ns->LANDelayEnabled<<
				"s, SRC="<< ns->stateRefreshCapable);
		SourceGroupList *sgl = FindSourceGroupList(i);
		NS_ASSERT(sgl==NULL);
		InsertSourceGroupList(i);
		Time rndHello = Seconds(UniformVariable().GetValue(0, Triggered_Hello_Delay));
		Simulator::Schedule (rndHello, &MulticastRoutingProtocol::HelloTimerExpire, this, i);
		ns->hello_timer.SetDelay(m_helloTime);
		NS_LOG_DEBUG ("Generating SG List("<<i<<") HT="<<m_helloTime.GetSeconds()<<"s, Starting "<< rndHello.GetSeconds()<<"s");

		for(std::map<Ipv4Address, RoutingMulticastTable>::iterator group = m_mrib.begin(); group!=m_mrib.end(); group++){
			Ipv4Address groupIP = group->second.groupAddr;
			if(groupIP == ALL_PIM_ROUTERS4) continue;
			NS_LOG_DEBUG("D("<<i<<") = " << m_ipv4->GetNetDevice (i)<<", LocalAddr = "<<  addr<< ", Group "<<groupIP<<", #Source: "<< group->second.mgroup.size());
			///Registering endpoint for that address... by creating a socket to listen only on this interface
			Ptr<Socket> socketG = Socket::CreateSocket (GetObject<Node> (), Ipv4RawSocketFactory::GetTypeId());
			socketG->SetAttribute("Protocol", UintegerValue(UdpL4Protocol::PROT_NUMBER));
			socketG->SetAttribute("IpHeaderInclude", BooleanValue(true));
			socketG->SetAllowBroadcast (true);
			InetSocketAddress inetAddr (groupIP, PIM_PORT_NUMBER);
			socketG->SetRecvCallback (MakeCallback (&MulticastRoutingProtocol::RecvData, this));
			if (socketG->Bind (inetAddr)){
				NS_FATAL_ERROR ("Failed to bind() PIMDM socket for group "<<groupIP);
			}
			socketG->BindToNetDevice (m_ipv4->GetNetDevice (i));
//			m_socketAddresses[socket] = m_ipv4->GetAddress (i, 0); //PROBLEM; does not broadcast onlocal IP, takes the other group-interface
			Ipv4InterfaceAddress mgroup(groupIP, Ipv4Mask::GetOnes());
			m_socketAddresses[socketG] = mgroup;
			NS_LOG_DEBUG("Registering Group Socket = "<<socketG<< " Device = "<<socketG->GetBoundNetDevice()<< ", LocalAddr = "<<mgroup.GetLocal()<<" Destination = "<<  groupIP<<", I = "<<i<<" IfaceAddr "<<m_ipv4->GetAddress (i, 0).GetLocal());
		}
	}
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
MulticastRoutingProtocol::HelloTimerExpire (uint32_t i)
{
	Ipv4Address loopback ("127.0.0.1");
	  Ipv4Address addr = m_ipv4->GetAddress (i, 0).GetLocal ();
	  if (addr == loopback)
		  return;
	  NS_LOG_DEBUG("Interface "<< i<< " [ E "<<m_IfaceNeighbors.find(i)->second.hello_timer.IsExpired() <<
			  ", R " << m_IfaceNeighbors.find(i)->second.hello_timer.IsRunning()<<", S:" << m_IfaceNeighbors.find(i)->second.hello_timer.IsSuspended()<<"].");
	  if(!m_IfaceNeighbors.find(i)->second.hello_timer.IsRunning()){
		  m_IfaceNeighbors.find(i)->second.hello_timer.SetFunction(&MulticastRoutingProtocol::HelloTimerExpire, this);
		  m_IfaceNeighbors.find(i)->second.hello_timer.SetArguments(i);
		  m_IfaceNeighbors.find(i)->second.hello_timer.Schedule();
	  }
	  SendHello (i);
}

bool
MulticastRoutingProtocol::IsDownstream (uint32_t interface, SourceGroupPair sgpair)
{
	uint32_t rpfInterface = RPF_interface(sgpair.sourceIfaceAddr);
	return (rpfInterface>=0 && rpfInterface<m_ipv4->GetNInterfaces() && interface != rpfInterface);
}
bool
MulticastRoutingProtocol::IsUpstream (uint32_t interface, SourceGroupPair sgpair)
{
	uint32_t rpfInterface = RPF_interface(sgpair.sourceIfaceAddr);
	return (rpfInterface>=0 && rpfInterface<m_ipv4->GetNInterfaces() && interface == rpfInterface);
}

uint32_t
MulticastRoutingProtocol::RPF_interface(Ipv4Address source) {
	Ptr<Ipv4Route> route = GetRoute(source);
	if(route)
		return m_ipv4->GetInterfaceForDevice(route->GetOutputDevice());
	else
		return -1;
}

Ptr<Ipv4Route>
MulticastRoutingProtocol::GetRoute(Ipv4Address destination) {
	Ptr<Ipv4Route> route = 0;
	Ptr<Packet> receivedPacket;
	Ipv4Header hdr;
	hdr.SetDestination(destination);
	Ptr<NetDevice> oif (0);
	Socket::SocketErrno err = Socket::ERROR_NOTERROR;
	return m_ipv4->GetRoutingProtocol()->RouteOutput(receivedPacket, hdr, oif, err);
}

Ipv4Address
MulticastRoutingProtocol::GetNextHop(Ipv4Address destination)
{
	Ptr<Ipv4Route> route = GetRoute(destination);
	return (route?route->GetGateway():Ipv4Address::GetAny());
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
	msg.SetVersion(2);
	msg.SetType(type);
	msg.SetReserved(0);
}

void
MulticastRoutingProtocol::ForgeHelloMessageHoldTime (uint32_t interface, PIMHeader &msg)
{
	PIMHeader::HelloMessage &helloMessage = msg.GetHelloMessage();//TODO holdtime for the corresponding interface
	PIMHeader::HelloMessage::HelloEntry holdtime = {PIMHeader::HelloMessage::HelloHoldTime, PIM_DM_HELLO_HOLDTIME};
	holdtime.m_optionValue.holdTime.m_holdTime = Seconds(m_helloHoldTime);
	msg.GetHelloMessage().m_optionList.push_back(holdtime);
}

void
MulticastRoutingProtocol::ForgeHelloMessageLANPD (uint32_t interface, PIMHeader &msg)
{
	PIMHeader::HelloMessage::HelloEntry lanpd = {PIMHeader::HelloMessage::LANPruneDelay, PIM_DM_HELLO_LANPRUNDELAY};
	lanpd.m_optionValue.lanPruneDelay.m_T = 0;
	lanpd.m_optionValue.lanPruneDelay.m_propagationDelay = m_IfaceNeighbors.find(interface)->second.propagationDelay;
	lanpd.m_optionValue.lanPruneDelay.m_overrideInterval = m_IfaceNeighbors.find(interface)->second.overrideInterval;
	msg.GetHelloMessage().m_optionList.push_back(lanpd);
}

void
MulticastRoutingProtocol::ForgeHelloMessageGenID (uint32_t interface, PIMHeader &msg)
{
	PIMHeader::HelloMessage::HelloEntry genid = {PIMHeader::HelloMessage::GenerationID, PIM_DM_HELLO_GENERATIONID};
	genid.m_optionValue.generationID.m_generatioID = m_generationID;
	msg.GetHelloMessage().m_optionList.push_back(genid);
}

void
MulticastRoutingProtocol::ForgeHelloMessageStateRefresh (uint32_t interface, PIMHeader &msg)
{
	PIMHeader::HelloMessage::HelloEntry staterefresh = {PIMHeader::HelloMessage::StateRefreshCapable, PIM_DM_HELLO_STATEREFRESH};
	staterefresh.m_optionValue.stateRefreshCapable.m_version = 1;
	staterefresh.m_optionValue.stateRefreshCapable.m_interval = (uint8_t)(m_IfaceNeighbors.find(interface)->second.stateRefreshInterval).GetSeconds();
	staterefresh.m_optionValue.stateRefreshCapable.m_reserved = 0;
	msg.GetHelloMessage().m_optionList.push_back(staterefresh);
}

void
MulticastRoutingProtocol::ForgeHelloMessage (uint32_t interface, PIMHeader &msg)
{
	NS_LOG_FUNCTION(this);
	ForgeHeaderMessage(PIM_HELLO, msg);
	ForgeHelloMessageHoldTime(interface, msg);
	ForgeHelloMessageLANPD(interface, msg);
	ForgeHelloMessageGenID(interface, msg);
	if(m_IfaceNeighbors.find(interface)->second.stateRefreshCapable){
		ForgeHelloMessageStateRefresh(interface, msg);
	}
}

void
MulticastRoutingProtocol::SendHello (uint32_t interface)
{///< Sec. 4.3.1. RFC 3973
	NS_LOG_FUNCTION(this);
	NS_LOG_DEBUG("Sender = "<<GetLocalAddress(interface)<< ", Interface "<<interface);
	Ptr<Packet> packet = Create<Packet> ();
	PIMHeader msg;
	ForgeHelloMessage(interface, msg);
	//	SendPacketPIMRouters(packet, msg, interface);
	Simulator::Schedule(MilliSeconds(UniformVariable().GetValue()),&MulticastRoutingProtocol::SendPacketPIMRoutersInterface, this, packet, msg, interface);
}

void
MulticastRoutingProtocol::SendHelloReply (uint32_t interface, Ipv4Address destination)
{///< Sec. 4.3.1. RFC 3973
	NS_LOG_FUNCTION(this);
	NS_LOG_DEBUG("Sender = "<<GetLocalAddress(interface)<<", Destination = "<<destination<<", Interface "<<interface);
	Ptr<Packet> packet = Create<Packet> ();
	PIMHeader msg;
	ForgeHelloMessage(interface, msg);
	NS_LOG_DEBUG("Send Hello Reply to "<< destination);
	Simulator::Schedule(MilliSeconds(UniformVariable().GetValue()),&MulticastRoutingProtocol::SendPacketUnicast, this,packet, msg, destination);
//	SendPacketUnicast(packet, msg, destination);
}

void
MulticastRoutingProtocol::ForgeJoinPruneMessage (PIMHeader &msg, Ipv4Address const upstreamNeighbor)
{
	NS_LOG_FUNCTION(this);
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
	NS_LOG_FUNCTION(this);
	PIMHeader msg;
	ForgeJoinPruneMessage(msg, destination);
	PIMHeader::MulticastGroupEntry mge;
	CreateMulticastGroupEntry(mge, ForgeEncodedGroup(sgp.groupMulticastAddr));
	AddMulticastGroupSourcePrune(mge, ForgeEncodedSource(sgp.sourceIfaceAddr));
	AddMulticastGroupEntry(msg, mge);
	msg.Print(std::cout);
	Ptr<Packet> packet = Create<Packet> ();
	Simulator::Schedule(MilliSeconds(UniformVariable().GetValue()),&MulticastRoutingProtocol::SendPacketUnicast, this,packet, msg, destination);
//	SendPacketUnicast(packet, msg, destination);
}

void
MulticastRoutingProtocol::SendPruneBroadcast (uint32_t interface, SourceGroupPair &sgp)
{
	NS_LOG_FUNCTION(this);
	PIMHeader::MulticastGroupEntry mge;
	PIMHeader msg;
	Ipv4Address destination = RPF_prime(sgp.sourceIfaceAddr, sgp.groupMulticastAddr);
	if(destination == Ipv4Address::GetAny()) return;
	ForgeJoinPruneMessage(msg, destination);
	CreateMulticastGroupEntry(mge, ForgeEncodedGroup(sgp.groupMulticastAddr));
	AddMulticastGroupSourcePrune(mge, ForgeEncodedSource(sgp.sourceIfaceAddr));
	AddMulticastGroupEntry(msg, mge);
	Ptr<Packet> packet = Create<Packet> ();
	NS_LOG_DEBUG("SG Pair ("<<sgp.sourceIfaceAddr <<", "<< sgp.groupMulticastAddr<<") via UpstreamNeighbor \""<< destination<<"\"");
	Simulator::Schedule(MilliSeconds(UniformVariable().GetValue()),&MulticastRoutingProtocol::SendPacketUnicast, this,packet, msg, destination);
//	SendPacketUnicast(packet, msg, target);
}

void
MulticastRoutingProtocol::SendJoinUnicast (Ipv4Address destination, SourceGroupPair &sgp)
{
	NS_LOG_FUNCTION(this);
	PIMHeader msg;
	ForgeJoinPruneMessage(msg, destination);
	PIMHeader::MulticastGroupEntry mge;
	CreateMulticastGroupEntry(mge, ForgeEncodedGroup(sgp.groupMulticastAddr));
	AddMulticastGroupSourceJoin(mge, ForgeEncodedSource(sgp.sourceIfaceAddr));
	AddMulticastGroupEntry(msg, mge);
	msg.Print(std::cout);
	Ptr<Packet> packet = Create<Packet> ();
	Simulator::Schedule(MilliSeconds(UniformVariable().GetValue()),&MulticastRoutingProtocol::SendPacketUnicast, this,packet, msg, destination);
//	SendPacketUnicast(packet, msg, destination);
}

void
MulticastRoutingProtocol::ForgeAssertMessage (uint32_t interface, PIMHeader &msg, SourceGroupPair &sgp)
{
	NS_LOG_FUNCTION(this);
	SourceGroupState *sgState = FindSourceGroupState(interface, sgp);
	ForgeHeaderMessage(PIM_ASSERT, msg);
	PIMHeader::AssertMessage &assertMessage = msg.GetAssertMessage();
	assertMessage.m_sourceAddr =  ForgeEncodedUnicast(sgp.sourceIfaceAddr);
	assertMessage.m_multicastGroupAddr = ForgeEncodedGroup(sgp.groupMulticastAddr);
	assertMessage.m_R = 0;
	assertMessage.m_metricPreference = (sgState==NULL) ? GetMetricPreference(GetReceivingInterface(sgp.sourceIfaceAddr)):sgState->AssertWinner.metricPreference;
	assertMessage.m_metric = (sgState==NULL) ? GetRouteMetric(GetReceivingInterface(sgp.sourceIfaceAddr),sgp.sourceIfaceAddr): sgState->AssertWinner.routeMetric;
}

void
MulticastRoutingProtocol::ForgeAssertCancelMessage (uint32_t interface, PIMHeader &msg, SourceGroupPair &sgp)
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
	assertMessage.m_sourceAddr =  ForgeEncodedUnicast(sgp.sourceIfaceAddr);
	assertMessage.m_multicastGroupAddr = ForgeEncodedGroup(sgp.groupMulticastAddr);
	assertMessage.m_R = 0;
	assertMessage.m_metricPreference = 0xffffffff;
	assertMessage.m_metric = 0xffffffff;
}

void
MulticastRoutingProtocol::ForgeGraftMessage (uint32_t interface, PIMHeader &msg, SourceGroupPair &sgp, Ipv4Address upstreamNeighbor)
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
	PIMHeader msg;
	// Create the graft packet
	ForgeGraftMessage(PIM_GRAFT, msg, sgp, destination);
	PIMHeader::MulticastGroupEntry mge;
	CreateMulticastGroupEntry(mge, ForgeEncodedGroup(sgp.groupMulticastAddr));
	AddMulticastGroupSourceJoin(mge, ForgeEncodedSource(sgp.sourceIfaceAddr));
	AddMulticastGroupEntry(msg, mge);
	NS_LOG_DEBUG("SG Pair ("<<sgp.sourceIfaceAddr <<", "<< sgp.groupMulticastAddr<<") via UpstreamNeighbor \""<< destination<<"\"");
	// Send the packet toward the RPF(S)
	Simulator::Schedule(MilliSeconds(UniformVariable().GetValue()),&MulticastRoutingProtocol::SendPacketUnicast, this,packet, msg, destination);
//	SendPacketUnicast(packet, msg, destination);
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
	AddMulticastGroupSourceJoin(mge, ForgeEncodedSource(sgp.sourceIfaceAddr));
	PIMHeader msg;
	// Create the graft packet
	ForgeGraftAckMessage(msg, destination);
	AddMulticastGroupEntry(msg, mge);
	NS_LOG_DEBUG("SG Pair ("<<sgp.sourceIfaceAddr <<", "<< sgp.groupMulticastAddr<<") via UpstreamNeighbor \""<< destination);
	// Send the packet toward the RPF(S)
	Simulator::Schedule(MilliSeconds(UniformVariable().GetValue()),&MulticastRoutingProtocol::SendPacketUnicast, this,packet, msg, destination);
//	SendPacketUnicast(packet, msg, destination);
}

void
MulticastRoutingProtocol::ForgeStateRefresh (uint32_t interface, SourceGroupPair &sgp, PIMHeader &msg)
{
	NS_LOG_FUNCTION(this);
	SourceGroupState *sgState = FindSourceGroupState(interface, sgp);
	ForgeHeaderMessage(PIM_STATE_REF, msg);
	PIMHeader::StateRefreshMessage &refresh = msg.GetStateRefreshMessage();
	refresh.m_multicastGroupAddr = ForgeEncodedGroup(sgp.groupMulticastAddr);
	refresh.m_sourceAddr = ForgeEncodedUnicast(sgp.sourceIfaceAddr);
	Ipv4Address nextHop = GetNextHop(sgp.sourceIfaceAddr);
	refresh.m_originatorAddr = ForgeEncodedUnicast(Ipv4Address(GetLocalAddress(interface)));
	refresh.m_R = 0;
	refresh.m_metricPreference = GetMetricPreference(GetReceivingInterface(sgp.sourceIfaceAddr));
	refresh.m_metric = GetRouteMetric(GetReceivingInterface(sgp.sourceIfaceAddr),sgp.sourceIfaceAddr);
	refresh.m_maskLength = IPV4_ADDRESS_SIZE;
	refresh.m_ttl = (sgState->SG_DATA_TTL>0 ? sgState->SG_DATA_TTL : sgState->SG_SR_TTL);
	refresh.m_P = (sgState->PruneState==Prune_Pruned?1:0);
	refresh.m_N = 0;
	refresh.m_O = (!sgState->SG_AT.IsRunning() && GetRoute(sgp.sourceIfaceAddr) && (m_ipv4->GetInterfaceForDevice(GetRoute(sgp.sourceIfaceAddr)->GetOutputDevice())==RPF_interface(sgp.sourceIfaceAddr)))?1:0;
	refresh.m_reserved = 0;
	refresh.m_interval = RefreshInterval;
}

void
MulticastRoutingProtocol::SendStateRefreshMessage (uint32_t interface, Ipv4Address target, SourceGroupPair &sgp)
{
	NS_LOG_FUNCTION(this);
	SourceGroupState *sgState = FindSourceGroupState(interface, sgp);
	Ptr<Packet> packet = Create<Packet> ();
	PIMHeader msg;
	ForgeStateRefresh(interface, sgp, msg);
	NeighborhoodStatus *ns = FindNeighborhoodStatus(interface);
	NS_ASSERT_MSG(ns!=NULL, "SendStateRefreshMessage, invalid NeighborhoodStatus on "<< interface);
	Time tmp = ns->stateRefreshInterval;
	msg.GetStateRefreshMessage().m_metricPreference = sgState->AssertWinner.metricPreference;
	msg.GetStateRefreshMessage().m_metric = sgState->AssertWinner.routeMetric;
	msg.GetStateRefreshMessage().m_interval = (uint8_t)(tmp.GetSeconds());

//	SendPacketUnicast(packet, msg, target);
	Simulator::Schedule(MilliSeconds(UniformVariable().GetValue()),&MulticastRoutingProtocol::SendPacketUnicast, this,packet, msg, target);
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
			sgState->SG_AT.SetArguments(sgp, interface);
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
	for(std::map<uint32_t, SourceGroupList>::iterator sgList = m_IfaceSourceGroup.begin();
			sgList != m_IfaceSourceGroup.end();  sgList++){
		uint32_t interface = sgList->first;
		NS_LOG_DEBUG("Interface "<<interface<<" SGPairs: "<<sgList->second.size());
		for(std::list<SourceGroupState>::iterator sgState = sgList->second.begin();
				sgState != sgList->second.end(); sgState++){
//				RPFCheck(sgState->SGPair, interface);
			NS_ASSERT(interface < m_ipv4->GetNInterfaces());
				Simulator::Schedule(Seconds(0),&MulticastRoutingProtocol::RPFCheck, this,sgState->SGPair, interface);
		}
		}
	m_rpfChecker.Schedule();
}

void
MulticastRoutingProtocol::RPFCheck(SourceGroupPair sgp, uint32_t interface)
{
	NS_LOG_DEBUG("("<<sgp.sourceIfaceAddr<<", "<<sgp.groupMulticastAddr<<") I="<<interface);
	Ptr<Ipv4Route> rpf_route = GetRoute(sgp.sourceIfaceAddr);
	RoutingMulticastTable entry;
	MulticastEntry me;
	bool ret = Lookup(sgp.groupMulticastAddr,sgp.sourceIfaceAddr, entry, me) ;
	ret = ret && rpf_route != NULL ;
	ret = ret && entry.mgroup.find(sgp.sourceIfaceAddr) != entry.mgroup.end();
	if(ret) {
		uint32_t interfaceN = m_ipv4->GetInterfaceForDevice(rpf_route->GetOutputDevice());
		Ipv4Address gatewayN = rpf_route->GetGateway();
		if(me.nextAddr == Ipv4Address::GetAny()){//now we now the RPF for the first time, just update it!
			UpdateEntry(sgp.groupMulticastAddr,sgp.sourceIfaceAddr,gatewayN,interfaceN);
		}
		if(me.interface != interfaceN){//RPF interface has changed
			RPF_Changes(sgp, entry.mgroup[sgp.sourceIfaceAddr].interface, interfaceN);
			UpdateEntry(sgp.groupMulticastAddr,sgp.sourceIfaceAddr,me.nextAddr,interfaceN);
		}
		if(me.nextAddr != gatewayN){//RPF neighbor has changed
			RPF_primeChanges(sgp);
			UpdateEntry(sgp.groupMulticastAddr,sgp.sourceIfaceAddr,gatewayN,interfaceN);
		}
	}
}


void
MulticastRoutingProtocol::RecvPimDm (Ptr<Socket> socket)
{
	NS_LOG_FUNCTION(this);
	Ptr<Packet> receivedPacket;
	Address sourceAddress;
	uint32_t interface = m_ipv4->GetInterfaceForDevice(socket->GetBoundNetDevice());
	receivedPacket = socket->RecvFrom (sourceAddress);
	InetSocketAddress inetSourceAddr = InetSocketAddress::ConvertFrom (sourceAddress);
	Ipv4Address senderIfaceAddr = inetSourceAddr.GetIpv4 ();
	uint16_t senderIfacePort = inetSourceAddr.GetPort();
	Ipv4Address receiverIfaceAddr = m_ipv4->GetAddress(interface, 0).GetLocal();
	NS_ASSERT (receiverIfaceAddr != Ipv4Address ());
    Ptr<Ipv4Route> route = GetRoute(senderIfaceAddr);
	Ipv4Header ipv4header;
	receivedPacket->RemoveHeader(ipv4header);
	Ipv4Address group = ipv4header.GetDestination();
	NS_LOG_DEBUG("Sender = "<< senderIfaceAddr<<", Group = " << group << ", Destination = "<< receiverIfaceAddr<< ", Socket = " << socket);
	if(route) NS_LOG_DEBUG("\t Route = "<<route->GetSource()<< " <"<<interface<<"> " <<route->GetGateway() <<" <...> "<<senderIfaceAddr);
	if(ipv4header.GetDestination().IsMulticast() && ipv4header.GetDestination() != Ipv4Address(ALL_PIM_ROUTERS4)) {
		NS_LOG_ERROR("Received "<< ipv4header.GetDestination() <<" it should be captured by another callback.");
		SourceGroupPair sgp (senderIfaceAddr, receiverIfaceAddr);
		RPFCheck(sgp, interface);
	}
	NS_ASSERT (senderIfacePort != PIM_PORT_NUMBER);
	//Unlike PIM-SM, PIM-DM does not maintain a keepalive timer associated with each (S, G) route.
	//  Within PIM-DM, route and state information associated with an (S, G) entry MUST be maintained as long as any
	//	timer associated with that (S, G) entry is active.  When no timer associated with an (S, G) entry is active,
	//	all information concerning that (S, G) route may be discarded.
	PIMHeader pimdmPacket;
	receivedPacket->RemoveHeader(pimdmPacket);
//	if(pimdmPacket.GetType()!=PIM_HELLO && !IsValidSG(GetReceivingInterface(receiverIfaceAddr), senderIfaceAddr, group)){
//			NS_LOG_DEBUG ("PIM-DM No running timer: discarded");
//			return;
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
MulticastRoutingProtocol::RecvData (Ptr<Socket> socket)
{
	NS_LOG_FUNCTION(this<< socket->GetBoundNetDevice());
	Ptr<Packet> receivedPacket;
	Address sourceAddress;
	receivedPacket = socket->RecvFrom (sourceAddress);
	Ptr<Packet> copy = receivedPacket->Copy();
	// Ipv4Header, UdpHeader and SocketAddressTag must be removed.
	Ipv4Header ipv4Header;
	copy->RemoveHeader(ipv4Header);
//	UdpHeader udpHeader;
//	copy->RemoveHeader(udpHeader);
	SocketAddressTag tag;
	copy->RemovePacketTag(tag); // LOOK: it must be removed because will be added again by socket.
	InetSocketAddress inetSourceAddr = InetSocketAddress::ConvertFrom (sourceAddress);
	Ipv4Address sender = inetSourceAddr.GetIpv4 ();
	uint16_t senderIfacePort = inetSourceAddr.GetPort();
	Ipv4Address group = m_socketAddresses[socket].GetLocal ();
	NS_ASSERT (group != Ipv4Address ()|| group != Ipv4Address::GetAny());
	SourceGroupPair sgp(sender, group);
	Ptr<Ipv4Route> rpf_route = GetRoute(sender);
	uint32_t interface = -1;
	if(socket->GetBoundNetDevice())
		interface = m_ipv4->GetInterfaceForDevice(socket->GetBoundNetDevice());
	else if (rpf_route)
		interface = m_ipv4->GetInterfaceForDevice(rpf_route->GetOutputDevice());
	else //the underlying routing protocol is not able to get the right interface for the sender address:we guess it is the main interface..
		interface = m_ipv4->GetInterfaceForAddress(m_mainAddress);//DEFAULT interface
	// Data Packet arrives on RPF_Interface(S) AND olist(S, G) == NULL AND S NOT directly connected
	Ipv4Address gateway = GetNextHop(sender);
	NS_LOG_DEBUG("LOCAL: "<<GetLocalAddress(interface)<<" GRP: "<<group<<" SRC: "<< sender<< " Metric: "<< GetRouteMetric(interface,sender) <<" IFC: "<<interface<<" GW: "<<gateway<< " PacketSize "<<copy->GetSize());
	SourceGroupState *sgState = FindSourceGroupState(interface, sgp);
	if(!sgState){
		InsertSourceGroupState(interface, sgp);
		sgState = FindSourceGroupState(interface, sgp);
		RoutingMulticastTable entry;
		MulticastEntry mentry;
		NS_ASSERT(Lookup(group, entry));
		Lookup(group,sender,entry,mentry);
		if(mentry.nextAddr == Ipv4Address::GetAny() && mentry.interface < 0){
			UpdateEntry(group, sender, gateway, interface);
		}
	}
	RPFCheck(sgp, interface);
	gateway = GetNextHop(sender);
	if(RPF_interface(sender) == interface){
		switch (sgState->upstream->GraftPrune){
			//The Upstream(S, G) state machine MUST transition to the Pruned (P)
			// state, send a Prune(S, G) to RPF'(S), and set PLT(S, G) to t_limit seconds.
			case GP_Forwarding:{
				if(olist(sender, group).size() == 0 && gateway != sender && !GetMulticastGroup(group)){//TODO fix with the interface towards nodes
					olistCheck(sgp);//CHECK: olist is null and S not directly connected
					sgState->upstream->GraftPrune = GP_Pruned;
					Ipv4Address destination = RPF_prime(sgp);
					SendPruneUnicast(destination, sgp);
					sgState->upstream->SG_PLT.SetDelay(Seconds(t_limit));
					}
					break;
				}
			case GP_Pruned:{
				if(!sgState->upstream->SG_PLT.IsRunning() && gateway != sender){
					sgState->upstream->SG_PLT.SetDelay(Seconds(t_limit));
					sgState->upstream->SG_PLT.Schedule();
					sgState->upstream->SG_PLT.SetFunction(&MulticastRoutingProtocol::PLTTimerExpire, this);//re-schedule transmission
					sgState->upstream->SG_PLT.SetArguments(sgp, interface);
					uint32_t interface_prime = GetReceivingInterface(RPF_prime(sgp.sourceIfaceAddr));
					SendPruneBroadcast(interface_prime, sgp);
					}
					break;
				}
			case GP_AckPending:{
				//nothing
				break;
			}
			default:{
				NS_LOG_ERROR("RecvData: Graft Prune state not valid"<<sgState->upstream->GraftPrune);
				break;
			}
		}
	}
	else{
		switch (sgState->AssertState){
			case  Assert_NoInfo:{
			//An (S, G) data packet arrives on downstream interface I.
			//   An (S, G) data packet arrived on a downstream interface.  It is
			//   optimistically assumed that this router will be the Assert winner
			//   for this (S, G).  The Assert state machine MUST transition to the
			//   "I am Assert Winner" state, send an Assert(S, G) to interface I,
			//   store its own address and metric as the Assert Winner, and set
			//   the Assert_Timer (AT(S, G, I) to Assert_Time, thereby initiating
			//   the Assert negotiation for (S, G).
				if(!IsDownstream(interface, sgp)) NS_LOG_ERROR("Packet received on Upstream interface! Assert_NoInfo");
				sgState->AssertState = Assert_Winner;
				UpdateAssertWinner(sgState, interface);
				PIMHeader msg;
				ForgeAssertMessage(interface, msg, sgp);
				Ptr<Packet> packetA = Create<Packet> ();
//				SendPacketPIMRouters(packetA, msg, interface);
				Simulator::Schedule(MilliSeconds(UniformVariable().GetValue()),&MulticastRoutingProtocol::SendPacketPIMRoutersInterface, this, packetA, msg, interface);
				if(sgState->SG_AT.IsRunning())
					sgState->SG_AT.Cancel();
				sgState->SG_AT.SetDelay(Seconds(Assert_Time));
				sgState->SG_AT.SetFunction(&MulticastRoutingProtocol::ATTimerExpire, this);
				sgState->SG_AT.SetArguments(sgp, interface);
				sgState->SG_AT.Schedule();
				break;
				}
			case Assert_Winner:{
				//An (S, G) data packet arrives on downstream interface I.
				//	An (S, G) data packet arrived on a downstream interface.
				//	The Assert state machine remains in the "I am Assert Winner" state.
				//	The router MUST send an Assert(S, G) to interface I and set the Assert Timer (AT(S, G, I) to Assert_Time.
				if(!IsDownstream(interface, sgp))break;
				PIMHeader assert;
				ForgeAssertMessage(interface, assert, sgp);
				UpdateAssertWinner(sgState, interface);
				Ptr<Packet> packetA = Create<Packet> ();
//				SendPacketPIMRouters(packetA, assert, interface);
				Simulator::Schedule(MilliSeconds(UniformVariable().GetValue()),&MulticastRoutingProtocol::SendPacketPIMRoutersInterface, this, packetA, assert, interface);
				//The Assert winner for (S, G) must act as the local forwarder for
				//  (S, G) on behalf of all downstream members.
				if(sgState->SG_AT.IsRunning())
					sgState->SG_AT.Cancel();
				sgState->SG_AT.SetDelay(Seconds(Assert_Time));
				sgState->SG_AT.SetFunction(&MulticastRoutingProtocol::ATTimerExpire, this);
				sgState->SG_AT.SetArguments(sgp,interface);
				sgState->SG_AT.Schedule();
				break;
			}
			case Assert_Loser:{
				//nothing
				break;
			}
			default:{
				NS_LOG_ERROR("RecvData: Assert State not valid "<<sgState->AssertState);
				break;
			}
		}
	}
	if(sgState->upstream != NULL){
	switch (sgState->upstream->origination) {
		case NotOriginator:{
			//Data Packet received from directly connected Source S addressed to group G.
			//	The router MUST transition to an Originator (O) state, set SAT(S, G) to SourceLifetime,
			//	and set SRT(S, G) to StateRefreshInterval.
			//	The router SHOULD record the TTL of the packet for use in State Refresh messages.
			if(gateway == sender){
				sgState->upstream->origination = Originator;
				if(sgState->upstream->SG_SAT.IsRunning())
					sgState->upstream->SG_SAT.Cancel();
				sgState->upstream->SG_SAT.SetDelay(Seconds(SourceLifetime));
				sgState->upstream->SG_SAT.SetFunction(&MulticastRoutingProtocol::SATTimerExpire, this);
				sgState->upstream->SG_SAT.SetArguments(sgp, interface);
				sgState->upstream->SG_SAT.Schedule();
				if(sgState->upstream->SG_SRT.IsRunning())
					sgState->upstream->SG_SRT.Cancel();
				sgState->upstream->SG_SRT.SetDelay(Seconds(RefreshInterval));
				sgState->upstream->SG_SRT.SetFunction(&MulticastRoutingProtocol::SRTTimerExpire, this);
				sgState->upstream->SG_SRT.SetArguments(sgp, interface);
				sgState->upstream->SG_SRT.Schedule();
				sgState->SG_DATA_TTL = ipv4Header.GetTtl();
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
			sgState->upstream->SG_SAT.SetArguments(sgp, interface);
			sgState->upstream->SG_SAT.Schedule();
			double sample = UniformVariable().GetValue();
			if(sample < TTL_SAMPLE && ipv4Header.GetTtl() > sgState->SG_DATA_TTL){//TODO: increase means +1 or equal to packet's TTL?
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
	std::set<uint32_t> oiflist;
	///   First, an RPF check MUST be performed to determine whether the packet should be accepted based on TIB state
	///      and the interface on which that the packet arrived.
	///   Packets that fail the RPF check MUST NOT be forwarded, and the router will conduct an assert process for the (S, G) pair specified in the packet.
	///   Packets for which a route to the source cannot be found MUST be discarded.
	if(RPF_interface(sender)<0){///   Packets for which a route to the source cannot be found MUST be discarded.
		NS_LOG_DEBUG("RPF_Interface not found "<<RPF_interface(sender));
		return;
	}
	if(interface == RPF_interface(sender) && sgState->PruneState != Prune_Pruned ){
		/// If the RPF check has been passed, an outgoing interface list is constructed for the packet.
		/// If this list is not empty, then the packet MUST be forwarded to all listed interfaces.
		oiflist = olist(sender, group);
		olistCheck(sgp);
//		GetPrinterList("olist", oiflist);
	}
	else return;
//	NS_LOG_DEBUG("Data forwarding towards > "<< oiflist.size()<<" < interfaces");
//	GetPrinterList("oiflist", oiflist);
	if(oiflist.size()){
		// Forward packet on all interfaces in oiflist.
		for(std::set<uint32_t>::iterator out = oiflist.begin(); out!=oiflist.end(); out++){
			Ptr<Packet> fwdPacket = copy->Copy(); // create a copy of the packet for each interface;
//			SendPacketHBroadcastInterface(fwdPacket, ipv4Header, *out);
			double delayMS = UniformVariable().GetValue()/1000.0;
			Simulator::Schedule(Seconds(delayMS),&MulticastRoutingProtocol::SendPacketHBroadcastInterface, this, fwdPacket, ipv4Header, *out);
		}
	}
	else {
		SendPruneBroadcast(interface, sgp);
	}
}

void
MulticastRoutingProtocol::RecvGraft (PIMHeader::GraftMessage &graft, Ipv4Address sender, Ipv4Address receiver, int32_t interface)
{
	NS_LOG_FUNCTION(this);
	for(std::vector<PIMHeader::MulticastGroupEntry>::iterator mgroup = graft.m_multicastGroups.begin();
			mgroup!=graft.m_multicastGroups.end(); mgroup++){
		for(std::vector<PIMHeader::EncodedSource>::iterator msource = mgroup->m_joinedSourceAddrs.begin();
					msource != mgroup->m_joinedSourceAddrs.end(); msource++){
			uint32_t rpf_i = RPF_interface(msource->m_sourceAddress);
			if(interface != RPF_interface(msource->m_sourceAddress)){
				RecvGraftDownstream (graft, sender, receiver, *msource, mgroup->m_multicastGroupAddr, interface);
			}
		}
	}
}

void //TODO split as done in join
MulticastRoutingProtocol::RecvGraftDownstream(PIMHeader::GraftMessage &graft, Ipv4Address sender, Ipv4Address receiver, const PIMHeader::EncodedSource &source, PIMHeader::EncodedGroup &group, int32_t interface)
{
	NS_LOG_FUNCTION(this);
	Ipv4Address current = GetLocalAddress(interface);
	SourceGroupPair sgp (source.m_sourceAddress, group.m_groupAddress);
	SourceGroupState *sgState = FindSourceGroupState(interface, sgp);
	switch (sgState->PruneState) {
		case Prune_NoInfo:{
		//A Graft(S, G) is received on the interface I with the upstream neighbor field set to the router's
		//	address on I.  The Prune(S, G) Downstream state machine on interface I stays in the NoInfo (NI)
		//	state.  A GraftAck(S, G) MUST be unicast to the originator of the Graft(S, G) message.
			if(graft.m_joinPruneMessage.m_upstreamNeighborAddr.m_unicastAddress == current){
				SendGraftAckUnicast(sgp, sender);
			}
			break;
		}
		case Prune_PrunePending:{
		//Receive Graft(S, G): A Graft(S, G) is received on interface I with the upstream neighbor
		//	field set to the router's address on I.  The Prune(S, G) Downstream state machine on
		//	interface I MUST transition to the NoInfo (NI) state and MUST unicast a Graft Ack
		//	message to the Graft originator.  The PrunePending Timer (PPT(S, G, I)) MUST be cancelled.
			if(graft.m_joinPruneMessage.m_upstreamNeighborAddr.m_unicastAddress == current){
				sgState->PruneState = Prune_NoInfo;
				SendGraftAckUnicast(sgp, sender);
				sgState->SG_PPT.Cancel();
			}
			break;
		}
		//Receive Graft(S, G). A Graft(S, G) is received on interface I with the upstream neighbor field
		//	set to the router's address on I.  The Prune(S, G) Downstream state machine on interface I
		//	MUST transition to the NoInfo (NI) state and send a Graft Ack back to the Graft's source.
		//	The Prune Timer (PT(S, G, I)) MUST be cancelled.
		//	TODO: The router MUST evaluate any possible transitions in the Upstream(S, G) state machine.
		case Prune_Pruned:{
			if(graft.m_joinPruneMessage.m_upstreamNeighborAddr.m_unicastAddress == current){
				sgState->PruneState = Prune_NoInfo;
				SendGraftAckUnicast(sgp, sender);
				sgState->SG_PPT.Cancel();
			}
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
			if(graft.m_joinPruneMessage.m_upstreamNeighborAddr.m_unicastAddress == current){
				PIMHeader assertR;
				ForgeAssertMessage(interface, assertR, sgp);
				Ptr<Packet> packet = Create<Packet> ();
//				SendPacketPIMRoutersInterface(packet, assertR, interface);
				Simulator::Schedule(MilliSeconds(UniformVariable().GetValue()),&MulticastRoutingProtocol::SendPacketPIMRoutersInterface, this, packet, assertR, interface);
				SendGraftAckUnicast(sgp, sender);
			}
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

void
MulticastRoutingProtocol::RecvGraftAck (PIMHeader::GraftAckMessage &graftAck, Ipv4Address sender, Ipv4Address receiver, int32_t interface)
{
	NS_LOG_FUNCTION(this);
	//The transition event "RcvGraftAck(S, G)" implies receiving a Graft Ack message targeted to this router's address on the incoming interface
	//	for the (S, G) entry.  If the destination address is not correct, the state transitions in this state machine must not occur.
	if(GetLocalAddress(interface) != graftAck.m_joinPruneMessage.m_upstreamNeighborAddr.m_unicastAddress) return;
	for(std::vector<struct PIMHeader::MulticastGroupEntry>::iterator groups = graftAck.m_multicastGroups.begin();
			groups != graftAck.m_multicastGroups.end(); groups++){
//		graftAck.Print(std::cout);
		for(std::vector<PIMHeader::EncodedSource>::const_iterator iterSource = groups->m_joinedSourceAddrs.begin();
				iterSource!=groups->m_joinedSourceAddrs.end(); iterSource++){
			SourceGroupPair sgp (iterSource->m_sourceAddress, groups->m_multicastGroupAddr.m_groupAddress);
			SourceGroupState *sgState = FindSourceGroupState(interface, sgp);
			NS_LOG_DEBUG("Removing Timer GRAFT " << sgState->upstream->SG_GRT.GetDelayLeft().GetMilliSeconds()<<" ms");
//			sgp.sourceIfaceAddr.Print(std::cout);
//			sgp.groupMulticastAddr.Print(std::cout);
			if(interface == RPF_interface(sender)){
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
					if(sender == RPF_prime(sgp.sourceIfaceAddr, sgp.groupMulticastAddr)){
						sgState->upstream->SG_GRT.Cancel();
						sgState->upstream->GraftPrune = GP_Forwarding;
					}
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
MulticastRoutingProtocol::NeighborRestart (uint32_t interface, Ipv4Address neighbor)
{
//   If a Hello message is received from an active neighbor with a
//   different Generation ID (GenID), the neighbor has restarted and may
//   not contain the correct (S, G) state.  A Hello message SHOULD be sent
//   after a random delay between 0 and Triggered_Hello_Delay (see 4.8)
//   before any other messages are sent.
	Time delay = Seconds(UniformVariable().GetValue(0, Triggered_Hello_Delay));
	Simulator::Schedule (Seconds(0), &MulticastRoutingProtocol::SetStopTx, this);
	Simulator::Schedule (Seconds(delay.GetMicroSeconds()-1), &MulticastRoutingProtocol::UnsetStopTx, this);
	Simulator::Schedule (delay, &MulticastRoutingProtocol::SendHelloReply, this, interface, neighbor);
	delay = Seconds(delay.GetSeconds()+0.1);
//   If the neighbor is downstream, the router MAY replay the last State Refresh message for any (S, G)
//   pairs for which it is the Assert Winner indicating Prune and Assert status to the downstream router.
//	 These State Refresh messages SHOULD be sent out immediately after the Hello message.
	SourceGroupList sgList = m_IfaceSourceGroup.find(interface)->second;
	for(std::list<SourceGroupState>::iterator sgState = sgList.begin(); sgState!=sgList.end(); sgState++){
		if(IsDownstream(interface, sgState->SGPair) && sgState->AssertState == Assert_Winner){
		Simulator::Schedule (Seconds(delay.GetMicroSeconds()+1), &MulticastRoutingProtocol::SendStateRefreshMessage, this, interface, neighbor, sgState->SGPair);
		break;
		}
		// If the neighbor is the upstream neighbor for an (S, G) entry, the router MAY cancel its
		//     Prune Limit Timer to permit sending a prune and reestablishing a Pruned state in the upstream router.
		else if (IsUpstream(interface, sgState->SGPair) && sgState->PruneState == Prune_Pruned){
			sgState->SG_PT.Cancel();
			sgState->SG_PT.SetDelay(Seconds(2*RefreshInterval));//TODO I am not sure of that: I have to understand the prune better
			sgState->SG_PT.SetFunction(&MulticastRoutingProtocol::PTTimerExpire, this);
			sgState->SG_PT.SetArguments(sgState->SGPair);
			sgState->SG_PT.Schedule();
			Simulator::Schedule (Seconds(0), &MulticastRoutingProtocol::SendPruneBroadcast, this, interface, sgState->SGPair);
		}
	}
//   TODO: Upon startup, a router MAY use any State Refresh messages received
//   within Hello_Period of its first Hello message on an interface to
//   establish state information.  The State Refresh source will be the
//   RPF'(S), and Prune status for all interfaces will be set according to
//   the Prune Indicator bit in the State Refresh message.  If the Prune
//   Indicator is set, the router SHOULD set the PruneLimitTimer to
//   Prune_Holdtime and set the PruneTimer on all downstream interfaces to
//   the State Refresh's Interval times two.  The router SHOULD then
//   propagate the State Refresh as described in Section 4.5.1.
}

Ipv4Header
MulticastRoutingProtocol::BuildHeader(Ipv4Address source, Ipv4Address destination, uint8_t protocol, uint16_t payloadSize, uint8_t ttl, bool mayFragment)
{
	NS_LOG_FUNCTION(this);
	Ipv4Header ipv4header;
	ipv4header.SetSource(source);
	ipv4header.SetDestination(destination);
	ipv4header.SetProtocol(protocol);
	ipv4header.SetPayloadSize(payloadSize);
	ipv4header.SetTtl(ttl);
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

void
MulticastRoutingProtocol::SendPacketPIMRouters(Ptr<Packet> packet, const PIMHeader &message)
{
  if(m_stopTx) return;
  packet->AddHeader(message);
  // Trace it
  m_txPacketTrace (message);
  // Send
  for(int i = 0; i <m_ipv4->GetNInterfaces();i++){
	 if(IsLoopInterface(i) || !GetPimInterface(i)) continue;
	 //	 SendPacketPIMRoutersInterface(packet, message, i);
	 Simulator::Schedule(MilliSeconds(UniformVariable().GetValue()),&MulticastRoutingProtocol::SendPacketPIMRoutersInterface, this, packet, message, i);
  }
}

void
MulticastRoutingProtocol::SendPacketPIMRoutersInterface(Ptr<Packet> packet, const PIMHeader &message, uint32_t interface)
{
  if(m_stopTx) return;
  packet->AddHeader(message);
  Ipv4Header ipv4header = BuildHeader(GetLocalAddress(interface), Ipv4Address(ALL_PIM_ROUTERS4), PIM_IP_PROTOCOL_NUM, packet->GetSize(), 1, false);
  packet->AddHeader(ipv4header);
  // Trace it
  m_txPacketTrace (message);
  // Send
  if(!GetPimInterface(interface)) {
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
		  NS_LOG_DEBUG ("...sending "<< bcast<<":"<<PIM_PORT_NUMBER<<", Socket "<< i->first);
		  i->first->SendTo (packet, 0, InetSocketAddress (bcast, PIM_PORT_NUMBER));
		  break;
	  }
      }
}

void
MulticastRoutingProtocol::SendPacketUnicast(Ptr<Packet> packet, const PIMHeader &message, Ipv4Address destination)
{
  if(m_stopTx) return;
  uint32_t size = message.GetSerializedSize();
  packet->AddHeader(message);
  // Trace it
  m_txPacketTrace (message);
  // Send
  Ptr<Ipv4Route> route = GetRoute(destination);
  if(!route) return;//no route to destination
  uint32_t interface = m_ipv4->GetInterfaceForDevice(route->GetOutputDevice());
  if(!GetPimInterface(interface)) {
	  NS_LOG_DEBUG("Interface "<<interface<<" is PIM-DISABLED");
	  return;
  }
  for (std::map<Ptr<Socket> , Ipv4InterfaceAddress>::const_iterator i =
        m_socketAddresses.begin (); i != m_socketAddresses.end (); i++)
      {
  	  if(route->GetSource() == i->second.GetLocal () ){
  		  Ptr<Packet> copy = packet->Copy();
  		  Ipv4Header ipv4Header = BuildHeader(i->second.GetLocal (), destination, PIM_IP_PROTOCOL_NUM, copy->GetSize(), 1, false);
  		  copy->AddHeader(ipv4Header);
  		  NS_LOG_DEBUG ("...sending Node " << route->GetSource()<< " is sending packet "<<copy << " to Destination: " << destination << ":"<<PIM_PORT_NUMBER<<", Interface "<<interface<<", Socket "<<i->first);
  		  i->first->SendTo (copy, 0, InetSocketAddress (destination, PIM_PORT_NUMBER));
  		  break;
  	  }
	}
}

void
MulticastRoutingProtocol::SendPacketHBroadcastInterface (Ptr<Packet> packet, Ipv4Header &ipv4Header, uint32_t interface)
{
	NS_LOG_FUNCTION(this);
	// Trace it
	// Send it
	if(!GetPimInterface(interface)) {
	  NS_LOG_DEBUG("Interface "<<interface<<" is PIM-DISABLED");
	  return;
	}
	for (std::map<Ptr<Socket> , Ipv4InterfaceAddress>::const_iterator i =
	  m_socketAddresses.begin (); i != m_socketAddresses.end (); i++)
	{
//	  NS_LOG_DEBUG("Local "<<i->second.GetLocal()<<", Broad "<<i->second.GetBroadcast()<<", Mask "<<i->second.GetMask());
	  if(GetLocalAddress(interface) == i->second.GetLocal ()){
		  packet->AddHeader(ipv4Header);
		  Ipv4Address bcast = i->second.GetLocal ().GetSubnetDirectedBroadcast (i->second.GetMask ());
//		  NS_LOG_DEBUG ("...sending Destination: " << bcast << ":"<<PIM_PORT_NUMBER<<", Interface "<<interface<<", Socket "<<i->first);
		  NS_LOG_DEBUG ("DataFwd: Node " << GetObject<Node> ()->GetId() << ", Dest "<< bcast <<", Ifc "<< interface<< ", Pid "<< packet->GetUid() <<", Psize "<<packet->GetSize());
		  i->first->SendTo (packet, 0, InetSocketAddress (ipv4Header.GetDestination(), PIM_PORT_NUMBER));
		  break; // Just to speedup and avoid the complete loop over all sockets.
	  }
	}
}

bool
MulticastRoutingProtocol::IsValidSG(uint32_t interface, const Ipv4Address & source, const Ipv4Address & group){
	SourceGroupPair sgp (source, group);
	SourceGroupState *sgState = FindSourceGroupState(interface, sgp);
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

//This timer is used to rate-limit Prunes on a LAN.
//       It is only used when the Upstream(S, G) state machine is in the Pruned state.
//       A Prune cannot be sent if this timer is running.
//       This timer is normally set to t_limit (see 4.8).
void
MulticastRoutingProtocol::PLTTimerExpire (SourceGroupPair &sgp, uint32_t interface)
{
	NS_LOG_FUNCTION(this);
	SourceGroupState *sgState = FindSourceGroupState(RPF_interface(sgp.sourceIfaceAddr), sgp);
	SendPruneBroadcast(interface, sgp);
	sgState->upstream->SG_PLT.SetFunction(&MulticastRoutingProtocol::PLTTimerExpire, this);
	sgState->upstream->SG_PLT.SetArguments(sgp);
	sgState->upstream->SG_PLT.Schedule();
}


void
MulticastRoutingProtocol::NLTTimerExpire (Ipv4Address neighborIfaceAddr, Ipv4Address receivingIfaceAddr, int32_t interface)
{
	SourceGroupList *sgList= FindSourceGroupList(interface); // get all the S, G pair
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
					//	TODO: evaluate any possible transitions to its Upstream(S, G) state machine.
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
MulticastRoutingProtocol::OTTimerExpire (SourceGroupPair &sgp, uint32_t interface)
{
	NS_LOG_FUNCTION(this);
	SourceGroupState *sgState = FindSourceGroupState(interface, sgp);
	switch (sgState->upstream->GraftPrune){
		case GP_Forwarding:{
			//The OverrideTimer (OT(S, G)) expires.  The router MUST send a Join(S, G) to RPF'(S) to override a previously detected prune.
			//	The Upstream(S, G) state machine remains in the Forwarding (F) state.
			if(sgp.sourceIfaceAddr != GetNextHop(sgp.sourceIfaceAddr)){
				Ipv4Address nextHop = RPF_prime(sgp.sourceIfaceAddr, sgp.groupMulticastAddr);
				SendJoinUnicast(nextHop, sgp); //broadcast
			}
			break;
		}
		case GP_Pruned:{
			break;
		}
		case GP_AckPending:{
			//The OverrideTimer (OT(S, G)) expires.  The router MUST send a Join(S, G) to RPF'(S).
			//	The Upstream(S, G) state machine remains in the AckPending (AP) state.
			Ipv4Address nextHop = RPF_prime(sgp.sourceIfaceAddr, sgp.groupMulticastAddr);
			SendJoinUnicast(nextHop, sgp); //broadcast
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
MulticastRoutingProtocol::GRTTimerExpire (SourceGroupPair &sgp, uint32_t interface)
{
	SourceGroupState *sgState = FindSourceGroupState(interface, sgp);
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
			Ipv4Address target = RPF_prime(sgp.sourceIfaceAddr, sgp.groupMulticastAddr);
			NeighborState dest(target, GetLocalAddress(GetReceivingInterface(target)));
			NeighborState *ns = FindNeighborState(GetReceivingInterface(target), dest);
			if(ns->neighborGraftRetry[0]<ns->neighborGraftRetry[1]){//increase counter retries
				SendGraftUnicast(target, sgp);
				sgState->upstream->SG_GRT.Cancel();
				sgState->upstream->SG_GRT.SetDelay(Seconds(Graft_Retry_Period));
				sgState->upstream->SG_GRT.SetFunction(&MulticastRoutingProtocol::GRTTimerExpire, this);
				sgState->upstream->SG_GRT.SetArguments(sgp, interface);
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
MulticastRoutingProtocol::PPTTimerExpire (SourceGroupPair &sgp, uint32_t interface)
{
	SourceGroupState *sgState = FindSourceGroupState(interface, sgp);
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
				PIMHeader msg;
				ForgeJoinPruneMessage(msg, GetLocalAddress(interface));
				Ptr<Packet> packet = Create<Packet> ();
				SendPacketPIMRouters(packet, msg);
			//	Its purpose is to add additional reliability so that if a Join that should have
			//	overridden the Prune is lost locally on the LAN, the PruneEcho(S, G) may be received
			//	and trigger a new Join message.
			//	TODO: A PruneEcho(S, G) is OPTIONAL on an interface with only one PIM neighbor.
			//	TODO: In addition, the router MUST evaluate any possible transitions in the Upstream(S, G) state machine.
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
MulticastRoutingProtocol::PTTimerExpire (SourceGroupPair &sgp, uint32_t interface)
{
//	uint32_t interface = RPF_interface(sgp.sourceIfaceAddr);
	SourceGroupState *sgState = FindSourceGroupState(interface, sgp);
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
		//	TODO: The router MUST evaluate any possible transitions in the Upstream(S, G) state machine.
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
MulticastRoutingProtocol::SRTTimerExpire (SourceGroupPair &sgp, uint32_t interface)
{
	SourceGroupState *sgState = FindSourceGroupState(interface, sgp);
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
			for (uint32_t i = 0; i < m_ipv4->GetNInterfaces (); i++){
				if(IsLoopInterface(i)|| IsUpstream(i,sgp))continue;//skip loopback and upstream interface
				PIMHeader refresh;//TODO Check to which interfaces should be sent
				ForgeStateRefresh(i, sgp, refresh);
				refresh.GetStateRefreshMessage().m_P = (IsDownstream(i, sgp) ? 1 : 0);
				Ptr<Packet> packet = Create<Packet> ();
//				SendPacketPIMRoutersInterface(packet, refresh, interface);
				Simulator::Schedule(MilliSeconds(UniformVariable().GetValue()),&MulticastRoutingProtocol::SendPacketPIMRoutersInterface, this, packet, refresh, interface);
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
MulticastRoutingProtocol::ATTimerExpire (SourceGroupPair &sgp, uint32_t interface)
{
	SourceGroupState *sgState = FindSourceGroupState(interface, sgp);
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
			//TODO: If CouldAssert == TRUE, the router MUST evaluate any possible transitions to its Upstream(S, G) state machine.
			UpstreamStateMachine(sgp);
			// if(CouldAssert(sgp.sourceIfaceAddr, sgp.groupMulticastAddr, interface)){}
			break;
		}
		default:{
			NS_LOG_ERROR("ATTimerExpire: Assert State not valid"<<sgState->AssertState);
			break;
		}
	}
}

void
MulticastRoutingProtocol::SATTimerExpire (SourceGroupPair &sgp, uint32_t interface)
{
	SourceGroupState *sgState = FindSourceGroupState(interface, sgp);
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
	olistCheck(sgp);
}

void
MulticastRoutingProtocol::olistCheck(SourceGroupPair &sgp)
{
	NS_LOG_FUNCTION(this);
	std::set<uint32_t> list = olist(sgp.sourceIfaceAddr, sgp.groupMulticastAddr);
	if(list.size() == 0)
		olistEmpty(sgp);
	else
		olistFull(sgp);
	}

void
MulticastRoutingProtocol::olistEmpty(SourceGroupPair &sgp)
{
	NS_LOG_FUNCTION(this);
	uint32_t interface = RPF_interface(sgp.sourceIfaceAddr);
	SourceGroupState *sgState = FindSourceGroupState(interface, sgp);
	switch (sgState->upstream->GraftPrune){
		case GP_Forwarding:{
		// olist(S, G) -> NULL AND S NOT directly connected
       	//   The Upstream(S, G) state machine MUST transition to the Pruned (P)  state,
       	//   send a Prune(S, G) to RPF'(S), and set PLT(S, G) to t_limit seconds.
			if(GetNextHop(sgp.sourceIfaceAddr) != sgp.sourceIfaceAddr){
				sgState ->upstream->GraftPrune = GP_Pruned;
				Ipv4Address target = RPF_prime(sgp.sourceIfaceAddr, sgp.groupMulticastAddr);
				SendPruneBroadcast(RPF_interface(target), sgp);
				sgState->upstream->SG_PLT.Cancel();
				sgState->upstream->SG_PLT.SetDelay(Seconds(t_limit));
				sgState->upstream->SG_PLT.SetFunction(&MulticastRoutingProtocol::PLTTimerExpire, this);
				sgState->upstream->SG_PLT.SetArguments(sgp, interface);
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
			uint32_t interface = RPF_interface(sgp.sourceIfaceAddr);
			PIMHeader::MulticastGroupEntry mge;
			AddMulticastGroupSourcePrune(mge, ForgeEncodedSource(sgp.sourceIfaceAddr));
			PIMHeader msg;
			Ipv4Address destination = RPF_prime(sgp.sourceIfaceAddr, sgp.groupMulticastAddr);
			ForgeJoinPruneMessage(msg, destination);
			CreateMulticastGroupEntry(mge, ForgeEncodedGroup(sgp.groupMulticastAddr));
			AddMulticastGroupEntry(msg, mge);
			Ptr<Packet> packet = Create<Packet> ();
//			SendPacketPIMRoutersInterface(packet, msg, GetReceivingInterface(destination));
			Simulator::Schedule(MilliSeconds(UniformVariable().GetValue()),&MulticastRoutingProtocol::SendPacketPIMRoutersInterface, this, packet, msg, GetReceivingInterface(destination));
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
	NS_LOG_FUNCTION(this);
	uint32_t interface = RPF_interface(sgp.sourceIfaceAddr);
	SourceGroupState *sgState = FindSourceGroupState(interface, sgp);
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
			if(GetNextHop(sgp.sourceIfaceAddr) != sgp.sourceIfaceAddr){
				sgState->upstream->SG_PLT.Cancel();
				sgState->upstream->GraftPrune = GP_AckPending;
				Ipv4Address target = RPF_prime(sgp.sourceIfaceAddr, sgp.groupMulticastAddr);
				SendGraftUnicast(target, sgp);
				sgState->upstream->SG_GRT.Cancel();
				sgState->upstream->SG_GRT.SetDelay(Seconds(Graft_Retry_Period));
				sgState->upstream->SG_GRT.SetFunction(&MulticastRoutingProtocol::GRTTimerExpire, this);
				sgState->upstream->SG_GRT.SetArguments(sgp, interface);
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
	uint32_t interface = RPF_interface(sgp.sourceIfaceAddr);//todo check
	SourceGroupState *sgState = FindSourceGroupState(interface, sgp);
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
	if(sgState->upstream){
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
			sgState->upstream->SG_SAT.SetArguments(sgp, interface);
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
MulticastRoutingProtocol::SourceNoDirectlyConnected(SourceGroupPair &sgp)
{
	NS_LOG_FUNCTION(this);
	SourceGroupState *sgState = FindSourceGroupState(RPF_interface(sgp.sourceIfaceAddr), sgp);
	if(sgState->upstream)
{
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
		}
	}
}

void
MulticastRoutingProtocol::RPF_Changes(SourceGroupPair &sgp, uint32_t oldInterface, uint32_t newInterface)
{
	bool couldAssert = CouldAssert(sgp.sourceIfaceAddr, sgp.groupMulticastAddr, oldInterface);
	CouldAssertCheck(sgp.sourceIfaceAddr, sgp.groupMulticastAddr, oldInterface, couldAssert);
	SourceGroupState *sgState = FindSourceGroupState(oldInterface, sgp);
	ChangeSourceGroupState(oldInterface, newInterface, *sgState);
	sgState = FindSourceGroupState(newInterface, sgp);
	switch (sgState->PruneState) {
		case Prune_NoInfo:{
			// nothing
			break;
		}
		case Prune_PrunePending:{
		//RPF_Interface(S) becomes interface I. The upstream interface for S has changed.
		//	The Prune(S, G) Downstream state machine on interface I MUST transition to the
		//	NoInfo (NI) state.  The PrunePending Timer (PPT(S, G, I)) MUST be cancelled.
			sgState->PruneState = Prune_NoInfo;
			if(sgState->SG_PPT.IsRunning())
				sgState->SG_PPT.Cancel();
			break;
		}
		case Prune_Pruned:{
		//RPF_Interface(S) becomes interface I. The upstream interface for S has changed.
		//	The Prune(S, G) Downstream state machine on interface I MUST transition to the NoInfo (NI) state.
		//	The PruneTimer (PT(S, G, I)) MUST be cancelled.
			sgState->PruneState = Prune_NoInfo;
			if(sgState->SG_PT.IsRunning())
				sgState->SG_PT.Cancel();
			break;
		}
		default:
			NS_LOG_ERROR("PPTTimerExpire: Prune state not valid"<<sgState->PruneState);
			break;
	}
}

void
MulticastRoutingProtocol::CouldAssertCheck (Ipv4Address source, Ipv4Address group, uint32_t interface, bool couldAssert) {
	SourceGroupPair sgp(source, group);
	SourceGroupState *sgState = FindSourceGroupState(interface, sgp);
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
//			SendPacketPIMRoutersInterface(packet, assertR, interface);
			Simulator::Schedule(MilliSeconds(UniformVariable().GetValue()),&MulticastRoutingProtocol::SendPacketPIMRoutersInterface, this, packet, assertR, interface);
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
MulticastRoutingProtocol::RPF_primeChanges(SourceGroupPair &sgp)
{
	std::set<uint32_t> outlist = olist(sgp.sourceIfaceAddr, sgp.groupMulticastAddr);
	uint32_t interface = RPF_interface(sgp.sourceIfaceAddr);
	SourceGroupState *sgState = FindSourceGroupState(interface, sgp);
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
			if(outlist.size()>0 && sgp.sourceIfaceAddr != GetNextHop(sgp.sourceIfaceAddr)){
				sgState->upstream->GraftPrune = GP_AckPending;
				Ipv4Address destination = RPF_prime(sgp.sourceIfaceAddr, sgp.groupMulticastAddr);
				SendGraftUnicast(destination, sgp);
				if(sgState->upstream->SG_GRT.IsRunning())
					sgState->upstream->SG_GRT.Cancel();
				sgState->upstream->SG_GRT.SetDelay(Seconds(Graft_Retry_Period));
				sgState->upstream->SG_GRT.SetFunction(&MulticastRoutingProtocol::GRTTimerExpire, this);
				sgState->upstream->SG_GRT.SetArguments(sgp, interface);
				sgState->upstream->SG_GRT.Schedule();
			}
			break;
		}
		case GP_Pruned:{
			if(outlist.size()==0 && sgp.sourceIfaceAddr != GetNextHop(sgp.sourceIfaceAddr)){
			//RPF'(S) Changes AND olist(S, G) == NULL AND S NOT directly connected
			//	Unicast routing or Assert state causes RPF'(S) to change, including changes to RPF_Interface(S).
			//	The Upstream(S, G) state machine stays in the Pruned (P) state and MUST cancel the PLT(S, G) timer.
				sgState->upstream->SG_PLT.Cancel();
			}
			if(outlist.size()>0 && sgp.sourceIfaceAddr != GetNextHop(sgp.sourceIfaceAddr)){
			//RPF'(S) Changes AND olist(S, G) == non-NULL AND S NOT directly connected
			//	Unicast routing or Assert state causes RPF'(S) to change, including changes to RPF_Interface(S).
			//	The Upstream(S, G) state machine MUST cancel PLT(S, G), transition to the AckPending (AP) state,
			//	send a Graft unicast to the new RPF'(S), and set the GraftRetry Timer (GRT(S, G)) to Graft_Retry_Period.
				sgState->upstream->SG_PLT.Cancel();
				sgState->upstream->GraftPrune = GP_AckPending;
				Ipv4Address destination = RPF_prime(sgp.sourceIfaceAddr, sgp.groupMulticastAddr);
				SendGraftUnicast(destination, sgp);//TODO check
				sgState->upstream->SG_GRT.Cancel();
				sgState->upstream->SG_GRT.SetDelay(Seconds(Graft_Retry_Period));
				sgState->upstream->SG_GRT.SetFunction(&MulticastRoutingProtocol::GRTTimerExpire, this);
				sgState->upstream->SG_GRT.SetArguments(sgp, interface);
				sgState->upstream->SG_GRT.Schedule();
			}
			break;
		}
		case GP_AckPending:{
			if(outlist.size()==0 && sgp.sourceIfaceAddr != GetNextHop(sgp.sourceIfaceAddr)){
			//RPF'(S) Changes AND olist(S, G) == NULL AND S NOT directly connected
			//	Unicast routing or Assert state causes RPF'(S) to change, including changes to RPF_Interface(S).
			//	The Upstream(S, G) state machine MUST transition to the Pruned (P) state.
			//	The GraftRetry Timer (GRT(S, G)) MUST be canceled.
				sgState->upstream->GraftPrune = GP_Pruned;
				sgState->upstream->SG_GRT.Cancel();
			}
			if(outlist.size()>0 && sgp.sourceIfaceAddr != GetNextHop(sgp.sourceIfaceAddr)){
				//RPF'(S) Changes AND olist(S, G) does not become NULL AND S NOT directly connected
				//	Unicast routing or Assert state causes RPF'(S) to change, including changes to RPF_Interface(S).
				//	The Upstream(S, G) state machine stays in the AckPending (AP) state.
				//	A Graft MUST be unicast to the new RPF'(S) and the GraftRetry Timer (GRT(S, G)) reset to Graft_Retry_Period.
				Ipv4Address target = RPF_prime(sgp.sourceIfaceAddr, sgp.groupMulticastAddr);
				SendGraftUnicast(target, sgp);//TODO check
				sgState->upstream->SG_GRT.Cancel();
				sgState->upstream->SG_GRT.SetDelay(Seconds(Graft_Retry_Period));
				sgState->upstream->SG_GRT.Schedule();
			}
			break;
		}
		default:{
			NS_LOG_ERROR("RPF prime changed: state not valid"<<sgState->upstream->GraftPrune);
			break;
		}
	}
}


void
MulticastRoutingProtocol::RecvJP (PIMHeader::JoinPruneMessage &jp, Ipv4Address sender, Ipv4Address receiver, int32_t interface)
{
	NS_LOG_FUNCTION(this);
	NS_LOG_DEBUG("Node  "<<receiver <<" receives JP from "<<sender);
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
				// Upstream state machine
				RecvJoin(jp, sender, receiver, out_interface, *iterJoin, iter->m_multicastGroupAddr);
			}
		}
		//PRUNE
		for(std::vector<PIMHeader::EncodedSource>::iterator iterPrune = iter->m_prunedSourceAddrs.begin();
					iterPrune != iter->m_prunedSourceAddrs.end(); iterPrune++){
			//This timer is set when a Prune(S, G) is received on the upstream interface where olist(S, G) != NULL.
			//	When the timer expires, a Join(S, G) message is sent on the upstream interface.  This timer
			//	is normally set to t_override (see 4.8).
			std::set<uint32_t> pruneList = olist(iterPrune->m_sourceAddress, iter->m_multicastGroupAddr.m_groupAddress);
//			GetPrinterList("pruneList", pruneList);
			for(std::set<uint32_t>::const_iterator iterList = pruneList.begin(); iterList != pruneList.end(); iterList++){
				uint32_t out_interface = *iterList;
				SourceGroupPair sgp (iterPrune->m_sourceAddress, iter->m_multicastGroupAddr.m_groupAddress);
				if(IsUpstream(interface, sgp)){
					SourceGroupState *sgState = FindSourceGroupState(interface, sgp);
					if(sgState->upstream->SG_OT.IsRunning())
						sgState->upstream->SG_OT.Cancel();
					sgState->upstream->SG_OT.SetDelay(Seconds(t_override(*iterList)));
					sgState->upstream->SG_OT.SetFunction(&MulticastRoutingProtocol::OTTimerExpire, this);
//					sgState->upstream->SG_OT.SetArguments(jp.m_joinPruneMessage.m_upstreamNeighborAddr.m_unicastAddress, sgp);
					sgState->upstream->SG_OT.SetArguments(sgp, interface);
				}
				// Upstream state machine
				RecvPrune(jp, sender, receiver, out_interface, *iterPrune, iter->m_multicastGroupAddr);
			}
		}
	}
}

void
MulticastRoutingProtocol::RecvPrune (PIMHeader::JoinPruneMessage &jp, Ipv4Address &sender, Ipv4Address &receiver, uint32_t &interface, const PIMHeader::EncodedSource &source, PIMHeader::EncodedGroup &group)
{
	NS_LOG_FUNCTION(this);
	NeighborhoodStatus *nstatus = FindNeighborhoodStatus(interface);
	nstatus->pruneHoldtime = Time(jp.m_joinPruneMessage.m_holdTime);
	// The node is not directly connected to S.
	if(RPF_interface(source.m_sourceAddress)==interface){
		RecvPruneUpstream(jp, sender, receiver, interface, source, group);
	}
	else {
		RecvPruneDownstream(jp, sender, receiver, interface, source, group);
	}
}

//4.4.  PIM-DM Prune, Join, and Graft Messages
//	This section describes the generation and processing of PIM-DM Join, Prune, and Graft messages.
//	Prune messages are sent toward the upstream neighbor for S to indicate that traffic from S addressed to group G is not desired.
//	In the case of downstream routers A and B, where A wishes to continue receiving data and B does not, A will send
//	a Join in response to B's Prune to override the Prune.  This is the only situation in PIM-DM in which a Join message is used.
//	Finally, a Graft message is used to re-join a previously pruned branch to the delivery tree.
void
MulticastRoutingProtocol::RecvPruneUpstream(PIMHeader::JoinPruneMessage &jp, Ipv4Address &sender, Ipv4Address &receiver, uint32_t &interface, const PIMHeader::EncodedSource &source, PIMHeader::EncodedGroup &group)
{
	NS_LOG_FUNCTION(this);
	SourceGroupPair sgp(source.m_sourceAddress, group.m_groupAddress);
	SourceGroupState *sgState = FindSourceGroupState(interface, sgp);
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
			if(RPF_prime(source.m_sourceAddress) == sender && jp.m_joinPruneMessage.m_holdTime>sgState->upstream->SG_PLT.GetDelay()){
				if(sgState->upstream->SG_PLT.IsRunning())
					sgState->upstream->SG_PLT.Cancel();
				sgState->upstream->SG_PLT.SetDelay(jp.m_joinPruneMessage.m_holdTime);
				sgState->upstream->SG_PLT.SetFunction(&MulticastRoutingProtocol::PLTTimerExpire, this);
				sgState->upstream->SG_PLT.SetArguments(sgp, interface);
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
				sgState->upstream->SG_OT.SetArguments(sgp, interface);
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

void
MulticastRoutingProtocol::RecvPruneDownstream (PIMHeader::JoinPruneMessage &jp, Ipv4Address &sender, Ipv4Address &receiver, uint32_t &interface, const PIMHeader::EncodedSource &source, PIMHeader::EncodedGroup &group)
{
	SourceGroupPair sgp(source.m_sourceAddress, group.m_groupAddress);
	uint32_t sourceIface = RPF_interface(source.m_sourceAddress);
 	SourceGroupState *sgState = FindSourceGroupState(interface, sgp);
 	if (sgState == NULL) return;
	Ipv4Address current = GetLocalAddress(interface);
	switch (sgState->PruneState) {
		case Prune_NoInfo:{
			//Receive Prune(S, G): A Prune(S, G) is received on interface I with the upstream neighbor field
			//  set to the router's address on I.  The Prune(S, G) Downstream state machine on interface I
			//  MUST transition to the PrunePending (PP) state.  The PrunePending Timer (PPT(S, G, I))
			//  MUST be set to J/P_Override_Interval if the router has more than one neighbor on I.
			//  If the router has only one neighbor on interface I, then it SHOULD set the PPT(S, G, I) to zero,
		    //  effectively transitioning immediately to the Pruned (P) state.
			if(jp.m_joinPruneMessage.m_upstreamNeighborAddr.m_unicastAddress == current){
				NeighborhoodStatus *nstatus = FindNeighborhoodStatus(interface);
				Time JP_Override_Interval= nstatus->overrideInterval+nstatus->propagationDelay;
				sgState->PruneState = Prune_PrunePending;
				NS_LOG_DEBUG("Neighbor size "<< nstatus->neighbors.size());
				Time delay = Seconds(0);
//				if(nstatus->neighbors.size() == 1){delay = Seconds(0);}else
				if(nstatus->neighbors.size()>1){
					delay = Seconds(JP_Override_Interval);
				}
				if(!sgState->SG_PPT.IsRunning()){
					sgState->SG_PPT.SetDelay(delay);
					sgState->SG_PPT.SetFunction(&MulticastRoutingProtocol::PPTTimerExpire, this);
					sgState->SG_PPT.SetArguments(sgp, interface);
					sgState->SG_PPT.Schedule();
				}
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
			if(jp.m_joinPruneMessage.m_upstreamNeighborAddr.m_unicastAddress == current){
				if(jp.m_joinPruneMessage.m_holdTime >sgState->SG_PT.GetDelay()){
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
			if(jp.m_joinPruneMessage.m_upstreamNeighborAddr.m_unicastAddress == current){
				PIMHeader assertR;
				SourceGroupPair sgp(source.m_sourceAddress, group.m_groupAddress);
				ForgeAssertMessage(interface, assertR, sgp);
				Ptr<Packet> packet = Create<Packet> ();
//				SendPacketPIMRoutersInterface(packet, assertR, interface);
				Simulator::Schedule(MilliSeconds(UniformVariable().GetValue()),&MulticastRoutingProtocol::SendPacketPIMRoutersInterface, this, packet, assertR, interface);
			}
			//An Assert loser that receives a Prune(S, G), Join(S, G), or
			//  Graft(S, G) directed to it initiates a new Assert negotiation so
			//  that the downstream router can correct its RPF'(S).
			// TODO
			break;
			}
		default:{
			NS_LOG_ERROR("RecvPruneDownstream: Assert State not valid"<<sgState->AssertState);
			break;
		}
	}
}

void
MulticastRoutingProtocol::RecvJoin(PIMHeader::JoinPruneMessage &jp, Ipv4Address &sender, Ipv4Address &receiver, uint32_t &interface, const PIMHeader::EncodedSource &source, PIMHeader::EncodedGroup &group)
{
	NS_LOG_FUNCTION(this);
	if(RPF_interface(source.m_sourceAddress)==interface){
		RecvJoinUpstream(jp, sender, receiver, interface, source, group);
	}
	else {
		RecvJoinDownstream(jp, sender, receiver, interface, source, group);
	}
}

void
MulticastRoutingProtocol::RecvJoinUpstream(PIMHeader::JoinPruneMessage &jp, Ipv4Address &sender, Ipv4Address &receiver, uint32_t &interface, const PIMHeader::EncodedSource &source, PIMHeader::EncodedGroup &group)
{
	SourceGroupPair sgp (source.m_sourceAddress, group.m_groupAddress);
	SourceGroupState *sgState = FindSourceGroupState(interface, sgp);
		switch (sgState->upstream->GraftPrune) {
			case GP_Forwarding:{
			//This event is only relevant if RPF_interface(S) is a shared medium.
			//	This router sees another router on RPF_interface(S) send a Join(S, G) to RPF'(S, G).
			//	If the OT(S, G) is running, then it means that the router had scheduled a Join to override a previously received Prune.
			//	Another router has responded more quickly with a Join, so the local router SHOULD cancel its OT(S, G), if it is running.
			//	The Upstream(S, G) state machine remains in the Forwarding (F) state.
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
			//	This router sees another router on RPF_interface(S) send a Join(S, G) to RPF'(S, G).
			//	If the OT(S, G) is running, then it means that the router had scheduled a Join to override a previously received Prune.
			//	Another router has responded more quickly with a Join, so the local router SHOULD cancel its OT(S, G), if it is running.
			//	The Upstream(S, G) state machine remains in the AckPending (AP) state.
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
MulticastRoutingProtocol::RecvJoinDownstream(PIMHeader::JoinPruneMessage &jp, Ipv4Address &sender, Ipv4Address &receiver, uint32_t &interface, const PIMHeader::EncodedSource &source, PIMHeader::EncodedGroup &group)
{
	SourceGroupPair sgp (source.m_sourceAddress, group.m_groupAddress);
		SourceGroupState *sgState = FindSourceGroupState(interface, sgp);
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
				}
				break;
			}
			case Prune_Pruned:{
			//Receive Join(S, G). A Join(S, G) is received on the interface I with the upstream
			//	neighbor field set to the router's address on I.  The Prune(S, G) downstream state
			//	machine on interface I MUST transition to the NoInfo (NI) state.
			//	The Prune Timer (PT(S, G, I)) MUST be cancelled.
			//	TODO: The router MUST evaluate any possible transitions in the Upstream(S, G) state machine.
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
					SourceGroupPair sgp(source.m_sourceAddress, group.m_groupAddress);
					ForgeAssertMessage(interface, assertR, sgp);
					Ptr<Packet> packet = Create<Packet> ();
//					SendPacketPIMRoutersInterface(packet, assertR, interface);
					Simulator::Schedule(MilliSeconds(UniformVariable().GetValue()),&MulticastRoutingProtocol::SendPacketPIMRoutersInterface, this, packet, assertR, interface);
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
	NS_LOG_FUNCTION(this);
	SourceGroupPair sgp(assert.m_sourceAddr.m_unicastAddress, assert.m_multicastGroupAddr.m_groupAddress);
	SourceGroupState *sgState = FindSourceGroupState(interface, sgp);
	struct AssertMetric received (assert.m_metricPreference, assert.m_metric, receiver);
	struct AssertMetric myMetric;
	bool couldAssert = CouldAssert(assert.m_sourceAddr.m_unicastAddress, assert.m_multicastGroupAddr.m_groupAddress, interface);
	switch (sgState->AssertState){
		case  Assert_NoInfo:{
		//Receive Inferior (Assert OR State Refresh) AND CouldAssert(S, G, I)==TRUE.
		//   An Assert or State Refresh is received for (S, G) that is inferior
		//   to our own assert metric on interface I. The Assert state machine
		//   MUST transition to the "I am Assert Winner" state, send an Assert(S, G)
		//   to interface I, store its own address and metric as the Assert Winner,
		//   and set the Assert Timer (AT(S, G, I)) to Assert_Time.
			myMetric = my_assert_metric(assert.m_sourceAddr.m_unicastAddress, assert.m_multicastGroupAddr.m_groupAddress, interface);
			if(myMetric > received && couldAssert){
				sgState->AssertState = Assert_Winner;
				UpdateAssertWinner(sgState, interface);
				PIMHeader assertR;
				ForgeAssertMessage(interface, assertR, sgp);
				Ptr<Packet> packet = Create<Packet> ();
//				SendPacketPIMRoutersInterface(packet, assertR, interface);
				Simulator::Schedule(MilliSeconds(UniformVariable().GetValue()),&MulticastRoutingProtocol::SendPacketPIMRoutersInterface, this, packet, assertR, interface);
				if(sgState->SG_AT.IsRunning())
					sgState->SG_AT.Cancel();
				sgState->SG_AT.SetDelay(Seconds(Assert_Time));
				sgState->SG_AT.SetFunction(&MulticastRoutingProtocol::ATTimerExpire, this);
				sgState->SG_AT.SetArguments(sgp,interface);
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
				UpdateAssertWinner(sgState, assert.m_metricPreference, assert.m_metric, sender);
				if(sgState->SG_AT.IsRunning())
					sgState->SG_AT.Cancel();
				sgState->SG_AT.SetDelay(Seconds(Assert_Time));
				sgState->SG_AT.SetFunction(&MulticastRoutingProtocol::ATTimerExpire, this);
				sgState->SG_AT.SetArguments(sgp,interface);
				sgState->SG_AT.Schedule();
				if(couldAssert){
					//If CouldAssert(S, G, I) == TRUE,
					//	the router MUST also multicast a Prune(S, G) to the Assert winner
					//	with a Prune Hold Time equal to the Assert Timer and
					//  TODO: evaluate any changes in its Upstream(S, G) state machine.
					PIMHeader prune;
					ForgeJoinPruneMessage(prune, sender);
					PIMHeader::MulticastGroupEntry mge;
					CreateMulticastGroupEntry(mge, ForgeEncodedGroup(assert.m_multicastGroupAddr.m_groupAddress));
					AddMulticastGroupSourcePrune(mge, ForgeEncodedSource(assert.m_sourceAddr.m_unicastAddress));
					AddMulticastGroupEntry(prune, mge);
					prune.GetJoinPruneMessage().m_joinPruneMessage.m_holdTime = sgState->SG_AT.GetDelay();
					Ptr<Packet> packet = Create<Packet> ();
//					SendPacketUnicast(packet, prune, sender);
					Simulator::Schedule(MilliSeconds(UniformVariable().GetValue()),&MulticastRoutingProtocol::SendPacketUnicast, this,packet, prune, sender);
					UpstreamStateMachine(sgp);
				}
			}
			break;
			}
		case Assert_Winner:{
			myMetric = my_assert_metric(assert.m_sourceAddr.m_unicastAddress, assert.m_multicastGroupAddr.m_groupAddress, RPF_interface(sender));
			if(received < myMetric){
			//Receive Inferior Assert or State Refresh
			//	An (S, G) Assert is received containing a metric for S that is worse than this router's metric for S.
			//	Whoever sent the Assert is in error.  The router MUST send an Assert(S, G) to interface I
			//	and reset the Assert Timer (AT(S, G, I)) to Assert_Time.
				PIMHeader assertR;
				ForgeAssertMessage(interface, assertR, sgp);
				assertR.GetAssertMessage().m_metricPreference = sgState->AssertWinner.metricPreference;
				assertR.GetAssertMessage().m_metric = sgState->AssertWinner.routeMetric;
				Ptr<Packet> packet = Create<Packet> ();
//				SendPacketPIMRoutersInterface(packet, assertR, interface);
				Simulator::Schedule(MilliSeconds(UniformVariable().GetValue()),&MulticastRoutingProtocol::SendPacketPIMRoutersInterface, this, packet, assertR, interface);
				if(sgState->SG_AT.IsRunning())
					sgState->SG_AT.Cancel();
				sgState->SG_AT.SetDelay(Seconds(Assert_Time));
				sgState->SG_AT.SetFunction(&MulticastRoutingProtocol::ATTimerExpire, this);
				sgState->SG_AT.SetArguments(sgp,interface);
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
				UpdateAssertWinner(sgState, assert.m_metricPreference, assert.m_metric, sender);
				if(sgState->SG_AT.IsRunning())
					sgState->SG_AT.Cancel();
				sgState->SG_AT.SetDelay(Seconds(Assert_Time));
				sgState->SG_AT.SetFunction(&MulticastRoutingProtocol::ATTimerExpire, this);
				sgState->SG_AT.SetArguments(sgp,interface);
				sgState->SG_AT.Schedule();
				//The router MUST also multicast a Prune(S, G) to the Assert winner, with a Prune Hold
				//	Time equal to the Assert Timer, and evaluate any changes in its	Upstream(S, G) state machine.
				PIMHeader prune;
				ForgeJoinPruneMessage(prune, sender);
				PIMHeader::MulticastGroupEntry mge;
				CreateMulticastGroupEntry(mge, ForgeEncodedGroup(assert.m_multicastGroupAddr.m_groupAddress));
				AddMulticastGroupSourcePrune(mge, ForgeEncodedSource(assert.m_sourceAddr.m_unicastAddress));
				AddMulticastGroupEntry(prune, mge);
				prune.GetJoinPruneMessage().m_joinPruneMessage.m_holdTime = sgState->SG_AT.GetDelay();
				Ptr<Packet> packet = Create<Packet> ();
				Simulator::Schedule(MilliSeconds(UniformVariable().GetValue()),&MulticastRoutingProtocol::SendPacketUnicast, this,packet, prune, sender);
//				SendPacketUnicast(packet, prune, sender);
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
		//  TODO: evaluate any possible transitions to its Upstream(S, G) state machine.
		//	Usually this router will eventually re-assert and win
		//  when data packets from S have started flowing again.
			myMetric = my_assert_metric(assert.m_sourceAddr.m_unicastAddress, assert.m_multicastGroupAddr.m_groupAddress, RPF_interface(sender));
			if(received < myMetric){
				sgState->AssertState = Assert_NoInfo;
				if(sgState->SG_AT.IsRunning())
					sgState->SG_AT.Cancel();
				UpdateAssertWinner(sgState, 0XFFFFFFFF, 0XFFFFFFFF, Ipv4Address("255.255.255.255"));
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
				sgState->SG_AT.SetArguments(sgp,interface);
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
					Simulator::Schedule(MilliSeconds(UniformVariable().GetValue()),&MulticastRoutingProtocol::SendPacketUnicast, this,packet, prune, sender);
//					SendPacketUnicast(packet, prune, sender);
				}
			}
			break;
		}
		default:{
			NS_LOG_ERROR("RecvAssert: Assert State not valid"<<sgState->AssertState);
			break;
		}
	}
}

void
MulticastRoutingProtocol::RecvStateRefresh(PIMHeader::StateRefreshMessage &refresh, Ipv4Address sender, Ipv4Address receiver, int32_t interface)
{
	NS_LOG_FUNCTION(this);
	NeighborState tmp (refresh.m_originatorAddr.m_unicastAddress, receiver);
	NeighborState *ns = FindNeighborState(interface, tmp);
	SourceGroupPair sgp (refresh.m_sourceAddr.m_unicastAddress, refresh.m_multicastGroupAddr.m_groupAddress);
	SourceGroupState *sgState = FindSourceGroupState(interface, sgp);
	uint32_t rpf_prime_interface = RPF_interface(RPF_prime(refresh.m_sourceAddr.m_unicastAddress));
	if(rpf_prime_interface == interface && sgState->upstream){
		switch (sgState->upstream->GraftPrune) {
			case GP_Forwarding:{ //OK
				// The Upstream(S, G) state machine remains in a Forwarding state. If the received State Refresh has the Prune Indicator bit set to
				//	   one, this router must override the upstream router's Prune state after a short random interval.
				Simulator::Schedule (Seconds(UniformVariable().GetValue(0, t_shorter)), &MulticastRoutingProtocol::SetPruneState, this, interface, sgp, Prune_Pruned);
				//     If OT(S, G) is not running and the Prune Indicator bit equals one, the router MUST set OT(S, G) to t_override seconds.
				if(refresh.m_P == 1 && !sgState->upstream->SG_OT.IsRunning()){
					sgState->upstream->SG_OT.Cancel();
					sgState->upstream->SG_OT.SetDelay(Seconds(t_override(interface)));
					sgState->upstream->SG_OT.SetFunction(&MulticastRoutingProtocol::OTTimerExpire, this);
					sgState->upstream->SG_OT.SetArguments(sgp, interface);
					sgState->upstream->SG_OT.Schedule();
				}
				break;
			}
			case GP_Pruned:{//OK
			//The Upstream(S, G) state machine remains in a Pruned state. If the State Refresh has its Prune Indicator bit set to zero and
			//	   PLT(S, G) is not running, a Prune(S, G) MUST be sent to RPF'(S), and the PLT(S, G) MUST be set to t_limit.
			//	   If the State Refresh has its Prune Indicator bit set to one, the router MUST reset PLT(S, G) to t_limit.
				if(refresh.m_P==0 && !sgState->upstream->SG_PLT.IsRunning()){
						SendPruneUnicast(RPF_prime(refresh.m_sourceAddr.m_unicastAddress), sgp);
						sgState->upstream->SG_PLT.SetDelay(Seconds(t_limit));
						sgState->upstream->SG_PLT.SetFunction(&MulticastRoutingProtocol::PLTTimerExpire, this);
						sgState->upstream->SG_PLT.SetArguments(sgp,interface);
						sgState->upstream->SG_PLT.Schedule();
					}
				else if(refresh.m_P){
					sgState->upstream->SG_PLT.Cancel();
					sgState->upstream->SG_PLT.SetDelay(Seconds(t_limit));
					sgState->upstream->SG_PLT.SetFunction(&MulticastRoutingProtocol::PLTTimerExpire, this);
					sgState->upstream->SG_PLT.SetArguments(sgp,interface);
					sgState->upstream->SG_PLT.Schedule();
				}
				break;
			}
			case GP_AckPending:{ //OK
			//The Upstream(S, G) state machine remains in an AckPending state.
			//   The router must override the upstream router's Prune state after a short random interval.
			//   If OT(S, G) is not running and the Prune Indicator bit equals one, the router MUST set OT(S, G) to t_override seconds.
				if(refresh.m_P){
					Simulator::Schedule (Seconds(UniformVariable().GetValue(0, t_shorter)), &MulticastRoutingProtocol::SetPruneState, this, interface, sgp, Prune_Pruned);
					if(!sgState->upstream->SG_OT.IsRunning()){
						sgState->upstream->SG_OT.SetDelay(Seconds(t_override(interface)));
						sgState->upstream->SG_OT.SetFunction(&MulticastRoutingProtocol::OTTimerExpire, this);
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
	//TODO: Upon startup, a router MAY use any State Refresh messages received within Hello_Period of its first Hello message on an interface to establish state information.
	for(uint32_t i = 0; i < m_ipv4->GetNInterfaces();i++){
		SourceGroupState *sgStateB = FindSourceGroupState(i, sgp);
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
			sgStateB->SG_PT.SetDelay(Seconds(2 * StateRefreshInterval));
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
				if(my_assert_metric(refresh.m_sourceAddr.m_unicastAddress, refresh.m_multicastGroupAddr.m_groupAddress, interface) > received
						&& CouldAssert(refresh.m_sourceAddr.m_unicastAddress, refresh.m_multicastGroupAddr.m_groupAddress, interface)){
					sgState->AssertState = Assert_Winner;
					UpdateAssertWinner(sgState, interface);
					PIMHeader assertR;
					ForgeAssertMessage(interface, assertR, sgp);
					Ptr<Packet> packet = Create<Packet> ();
//					SendPacketPIMRoutersInterface(packet, assertR, interface);
					Simulator::Schedule(MilliSeconds(UniformVariable().GetValue()),&MulticastRoutingProtocol::SendPacketPIMRoutersInterface, this, packet, assertR, interface);
					if(sgState->SG_AT.IsRunning())
						sgState->SG_AT.Cancel();
					sgState->SG_AT.SetDelay(Seconds(Assert_Time));
					sgState->SG_AT.SetFunction(&MulticastRoutingProtocol::ATTimerExpire, this);
					sgState->SG_AT.SetArguments(sgp,interface);
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
					sgState->SG_AT.SetArguments(sgp, interface);
					sgState->SG_AT.Schedule();
					if(CouldAssert(refresh.m_sourceAddr.m_unicastAddress, refresh.m_multicastGroupAddr.m_groupAddress, interface)){
						//If CouldAssert(S, G, I) == TRUE,
						//	the router MUST also multicast a Prune(S, G) to the Assert winner
						//	with a Prune Hold Time equal to the Assert Timer
						//	TODO: and evaluate any changes in its Upstream(S, G) state machine.
						PIMHeader::MulticastGroupEntry mge;
						AddMulticastGroupSourcePrune(mge, ForgeEncodedSource(refresh.m_sourceAddr.m_unicastAddress));
						PIMHeader msg;
						ForgeJoinPruneMessage(msg, refresh.m_originatorAddr.m_unicastAddress);
						CreateMulticastGroupEntry(mge, ForgeEncodedGroup(refresh.m_multicastGroupAddr.m_groupAddress));
						msg.GetJoinPruneMessage().m_joinPruneMessage.m_holdTime = sgState->SG_AT.GetDelay();
						AddMulticastGroupEntry(msg, mge);
						Ptr<Packet> packet = Create<Packet> ();
						Simulator::Schedule(MilliSeconds(UniformVariable().GetValue()),&MulticastRoutingProtocol::SendPacketUnicast, this,packet, msg, refresh.m_originatorAddr.m_unicastAddress);
//						SendPacketUnicast(packet, msg, refresh.m_originatorAddr.m_unicastAddress);
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
			if(received < my_assert_metric(refresh.m_sourceAddr.m_unicastAddress, refresh.m_multicastGroupAddr.m_groupAddress, interface)){
				PIMHeader assertR;
				ForgeAssertMessage(interface, assertR, sgp);
				assertR.GetAssertMessage().m_metricPreference = sgState->AssertWinner.metricPreference;
				assertR.GetAssertMessage().m_metric = sgState->AssertWinner.routeMetric;
				Ptr<Packet> packet = Create<Packet> ();
//				SendPacketPIMRoutersInterface(packet, assertR, interface);
				Simulator::Schedule(MilliSeconds(UniformVariable().GetValue()),&MulticastRoutingProtocol::SendPacketPIMRoutersInterface, this, packet, assertR, interface);
				if(sgState->SG_AT.IsRunning())
					sgState->SG_AT.Cancel();
				sgState->SG_AT.SetDelay(Seconds(Assert_Time));
				sgState->SG_AT.SetFunction(&MulticastRoutingProtocol::ATTimerExpire, this);
				sgState->SG_AT.SetArguments(sgp, interface);
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
				sgState->SG_AT.SetArguments(sgp, interface);
				sgState->SG_AT.Schedule();
				//The router MUST also
				//	multicast a Prune(S, G) to the Assert winner, with a Prune Hold
				//	Time equal to the Assert Timer, and evaluate any changes in its
				//	Upstream(S, G) state machine.
				PIMHeader::MulticastGroupEntry mge;
				AddMulticastGroupSourcePrune(mge, ForgeEncodedSource(refresh.m_sourceAddr.m_unicastAddress));
				PIMHeader prune;
				ForgeJoinPruneMessage(prune, refresh.m_originatorAddr.m_unicastAddress);
				CreateMulticastGroupEntry(mge, ForgeEncodedGroup(refresh.m_multicastGroupAddr.m_groupAddress));
				prune.GetJoinPruneMessage().m_joinPruneMessage.m_upstreamNeighborAddr.m_unicastAddress = refresh.m_originatorAddr.m_unicastAddress;//TODO check
				prune.GetJoinPruneMessage().m_joinPruneMessage.m_holdTime = sgState->SG_AT.GetDelay();
				AddMulticastGroupEntry(prune, mge);
				Ptr<Packet> packet = Create<Packet> ();
				Simulator::Schedule(MilliSeconds(UniformVariable().GetValue()),&MulticastRoutingProtocol::SendPacketUnicast, this,packet, prune, refresh.m_originatorAddr.m_unicastAddress);
//				SendPacketUnicast(packet, prune, refresh.m_originatorAddr.m_unicastAddress);
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
			if(received < my_assert_metric(refresh.m_sourceAddr.m_unicastAddress, refresh.m_multicastGroupAddr.m_groupAddress, interface)){
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
				sgState->SG_AT.SetArguments(sgp, interface);
				sgState->SG_AT.Schedule();
				UpdateAssertWinner(sgState, refresh.m_metricPreference, refresh.m_metric, refresh.m_originatorAddr.m_unicastAddress);
				if(CouldAssert(refresh.m_sourceAddr.m_unicastAddress, refresh.m_multicastGroupAddr.m_groupAddress, interface)){
					//	and if CouldAssert(S, G, I) == TRUE, the router MUST multicast a
					//	Prune(S, G) to the new Assert winner.
					PIMHeader::MulticastGroupEntry mge;
					AddMulticastGroupSourcePrune(mge, ForgeEncodedSource(refresh.m_sourceAddr.m_unicastAddress));
					PIMHeader prune;
					ForgeJoinPruneMessage(prune, refresh.m_originatorAddr.m_unicastAddress);
					CreateMulticastGroupEntry(mge, ForgeEncodedGroup(refresh.m_multicastGroupAddr.m_groupAddress));
					prune.GetJoinPruneMessage().m_joinPruneMessage.m_holdTime = sgState->SG_AT.GetDelay();
					AddMulticastGroupEntry(prune, mge);
					Ptr<Packet> packet = Create<Packet> ();
					Simulator::Schedule(MilliSeconds(UniformVariable().GetValue()),&MulticastRoutingProtocol::SendPacketUnicast, this,packet, prune, refresh.m_originatorAddr.m_unicastAddress);
//					SendPacketUnicast(packet, prune, refresh.m_originatorAddr.m_unicastAddress);
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
	uint32_t iif = GetReceivingInterface(sender);
	if (iif != RPF_interface(refresh.m_sourceAddr.m_unicastAddress))
		return;
	//srcaddr(SRM) returns the source address contained in the network
	//	protocol (e.g., IPv4) header of the State Refresh Message, SRM.
	if (RPF_prime(refresh.m_sourceAddr.m_unicastAddress, refresh.m_multicastGroupAddr.m_groupAddress) != sender)//source=sender here? refresh.m_sourceAddr.m_unicastAddress
		return;
	//StateRefreshRateLimit(S, G) is TRUE if the time elapsed since the last received StateRefresh(S, G)
	//	is less than the configured RefreshLimitInterval.
	if (StateRefreshRateLimit(refresh.m_sourceAddr.m_unicastAddress, refresh.m_multicastGroupAddr.m_groupAddress))
		return;
	std::set<uint32_t> nbrs = pim_nbrs();
	for(std::set<uint32_t>::iterator i_nbrs = nbrs.begin(); i_nbrs != nbrs.end() ; i_nbrs++){
		//TTL(SRM) returns the TTL contained in the State Refresh Message, SRM.
		//	This is different from the TTL contained in the IP header.
		//
		//Threshold(I) returns the minimum TTL that a packet must have before it can be transmitted on interface I.
		if (refresh.m_ttl == 0 || (refresh.m_ttl - 1) < getThreshold(*i_nbrs))
			continue;     /* Out of TTL, skip this interface */
		//Boundary(I, G) is TRUE if an administratively scoped boundary for group G is configured on interface I.
		if (boundary(*i_nbrs, refresh.m_multicastGroupAddr.m_groupAddress))
			continue;     /* This interface is scope boundary, skip it */
		if (*i_nbrs == iif)
			continue;     /* This is the incoming interface, skip it */
		if (lost_assert(refresh.m_sourceAddr.m_unicastAddress, refresh.m_multicastGroupAddr.m_groupAddress, *i_nbrs))
			continue;     /* Let the Assert Winner do State Refresh */
		// Create a new message
		PIMHeader refreshFRW;
		refreshFRW.GetStateRefreshMessage() = refresh;
		PIMHeader::StateRefreshMessage SRMP = refreshFRW.GetStateRefreshMessage();
		// Copy SRM to SRMP';   /* Make a copy of SRM to forward */
		std::set<uint32_t> prunez = prunes(refresh.m_sourceAddr.m_unicastAddress, refresh.m_multicastGroupAddr.m_groupAddress);
		// if (I contained in prunes(S, G)) {
		if(prunez.find(*i_nbrs)!=prunez.end()){
			SRMP.m_P = 1;
			// set Prune Indicator bit of SRMP' to 1;
			// StateRefreshCapable(I) is TRUE if all neighbors on an interface use the State Refresh option.
			if (StateRefreshCapable(*i_nbrs)){
				SourceGroupPair sgp (refresh.m_sourceAddr.m_unicastAddress, refresh.m_multicastGroupAddr.m_groupAddress);
				SourceGroupState *sgState = FindSourceGroupState(*i_nbrs, sgp);
				Time pruneHoldTime = FindNeighborhoodStatus(*i_nbrs)->pruneHoldtime;
				//set PT(S, G) to largest active holdtime read from a Prune  message accepted on I;
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
		SRMP.m_metric = GetMetricPreference(GetReceivingInterface(refresh.m_sourceAddr.m_unicastAddress));
		// set pref of ' to preference of unicast route used to reach S;
		SRMP.m_metricPreference = GetMetricPreference(GetReceivingInterface(refresh.m_sourceAddr.m_unicastAddress));
		// set mask of SRMP' to mask of route used to reach S;
		SourceGroupPair sgp (refresh.m_sourceAddr.m_unicastAddress, refresh.m_multicastGroupAddr.m_groupAddress);
		SourceGroupState *sgState = FindSourceGroupState(*i_nbrs, sgp);
		if (sgState->AssertState == Assert_NoInfo) {
			SRMP.m_O = 1;//set Assert Override of SRMP' to 1;
		} else {
			SRMP.m_O = 0;//set Assert Override of SRMP' to 0;
		}
		//transmit SRMP' on I;
		Ptr<Packet> packet;
//		SendPacketPIMRoutersInterface(packet, refreshFRW, *i_nbrs);
		Simulator::Schedule(MilliSeconds(UniformVariable().GetValue()),&MulticastRoutingProtocol::SendPacketPIMRoutersInterface, this, packet, refreshFRW, *i_nbrs);
	}
}

void
MulticastRoutingProtocol::RecvHello(PIMHeader::HelloMessage &hello, Ipv4Address sender, Ipv4Address receiver, int32_t interface)
{
	NS_LOG_DEBUG("Sender = "<< sender<< ", Receiver = "<< receiver);
	uint16_t entry = 0;
	NeighborState tmp(sender, receiver);
	NeighborState *ns = FindNeighborState(interface, tmp);
	if(!ns){// Hello message received from a new neighbor
		InsertNeighborState(interface, tmp);
		ns = FindNeighborState(interface, tmp);
		NeighborhoodStatus *nst = FindNeighborhoodStatus(interface);
		// If a Hello message is received from a new neighbor, the receiving router SHOULD send its own Hello message
		//    after a random delay between 0 and Triggered_Hello_Delay.
		Time delay = Seconds(UniformVariable().GetValue(0, Triggered_Hello_Delay));
		Simulator::Schedule (delay, &MulticastRoutingProtocol::SendHelloReply, this, interface, sender);
		NS_LOG_DEBUG("Neighbors = "<< nst->neighbors.size() << ", reply at "<<(Simulator::Now()+delay).GetSeconds());
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
						EraseNeighborState(interface, tmp);
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
					InsertNeighborState(interface, tmp);
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
MulticastRoutingProtocol::NeighborTimeout(uint32_t interface)
{
	NS_LOG_FUNCTION(this);
	NeighborhoodStatus *nl = FindNeighborhoodStatus(interface);
	uint32_t size = nl->neighbors.size();
	IsExpired pred;
	nl->neighbors.erase (std::remove_if (nl->neighbors.begin (), nl->neighbors.end (), pred), nl->neighbors.end ());
	NS_LOG_DEBUG("Clean neighbors list on interface "<< interface<<": "<< size << " -> "<< nl->neighbors.size());
}

void
MulticastRoutingProtocol::SetInterfaceExclusions (std::set<uint32_t> exceptions)
{
	NS_LOG_FUNCTION(this);
	m_interfaceExclusions = exceptions;
}

bool
MulticastRoutingProtocol::UsesNonPimDmOutgoingInterface (const Ipv4RoutingTableEntry &route)
{
	NS_LOG_FUNCTION(this);
	std::set<uint32_t>::const_iterator ci = m_interfaceExclusions.find (route.GetInterface ());
	// The outgoing interface is a non-PIMDM interface if a match is found
	// before reaching the end of the list of excluded interfaces
	return (ci != m_interfaceExclusions.end ());
}

void MulticastRoutingProtocol::InsertNeighborState(uint32_t interface, const NeighborState ns) {
	if (!FindNeighborState(interface, ns)) {
		FindNeighborhoodStatus(interface)->neighbors.push_back(ns);
		NeighborState *neighbor = FindNeighborState(interface, ns);
		neighbor->neigborNLT.Cancel();
		neighbor->neighborCreation = Simulator::Now();
		neighbor->neighborTimeout = neighbor->neighborCreation;
		neighbor->neighborTimeoutB = true;
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
//* All PIM-DM packets use the same format as PIM-SM packets.  In the event of a discrepancy, PIM-SM [4] should be considered the
//		definitive specification.  All PIM control messages have IP protocol number 103.  All PIM-DM messages MUST be sent with a TTL of 1 (IPV4).  All
//		PIM-DM messages except Graft and Graft Ack messages MUST be sent to the ALL-PIM-ROUTERS group.  Graft messages SHOULD be unicast to the
//		RPF'(S).  Graft Ack messages MUST be unicast to the sender of the Graft.
//* When a PIM router takes an interface down or changes IP address, a Hello message with a zero Hold Time SHOULD be
//		sent immediately (with the old IP address if the IP address is changed) to cause any PIM neighbors to remove the old information immediately.
//* Unlike PIM-SM, PIM-DM does not maintain a keepalive timer associated with each (S, G) route.
//  	Within PIM-DM, route and state information associated with an (S, G) entry MUST be maintained as long as any
//		timer associated with that (S, G) entry is active.  When no timer associated with an (S, G) entry is active,
//		all information concerning that (S, G) route may be discarded.
