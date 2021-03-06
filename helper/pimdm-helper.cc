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

#include "pimdm-helper.h"
#include <ns3/pimdm-routing.h>
#include <ns3/node-list.h>
#include <ns3/names.h>
#include <ns3/ipv4-list-routing.h>

namespace ns3
{

  PimDmHelper::PimDmHelper ()
  {
    m_agentFactory.SetTypeId("ns3::pimdm::MulticastRoutingProtocol");
  }

  PimDmHelper::PimDmHelper (const PimDmHelper &o) :
      m_agentFactory(o.m_agentFactory)
  {
    m_interfaceExclusions = o.m_interfaceExclusions;
  }

  PimDmHelper*
  PimDmHelper::Copy (void) const
  {
    return new PimDmHelper(*this);
  }

  void
  PimDmHelper::ExcludeInterface (Ptr<Node> node, uint32_t interface)
  {
    std::map<Ptr<Node>, std::set<uint32_t> >::iterator it = m_interfaceExclusions.find(node);

    if (it == m_interfaceExclusions.end())
      {
        std::set<uint32_t> interfaces;
        interfaces.insert(interface);

        m_interfaceExclusions.insert(std::make_pair(node, std::set<uint32_t>(interfaces)));
      }
    else
      {
        it->second.insert(interface);
      }
  }

  Ptr<Ipv4RoutingProtocol>
  PimDmHelper::Create (Ptr<Node> node) const
  {
    Ptr<pimdm::MulticastRoutingProtocol> agent = m_agentFactory.Create<pimdm::MulticastRoutingProtocol>();

    std::map<Ptr<Node>, std::set<uint32_t> >::const_iterator it = m_interfaceExclusions.find(node);

    if (it != m_interfaceExclusions.end())
      {
        agent->SetInterfaceExclusions(it->second);
      }

    node->AggregateObject(agent);
    return agent;
  }

  void
  PimDmHelper::Set (std::string name, const AttributeValue &value)
  {
    m_agentFactory.Set(name, value);
  }

} // namespace ns3
