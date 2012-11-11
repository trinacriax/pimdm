from pybindgen import Module, FileCodeSink, param, retval, cppclass, typehandlers


import pybindgen.settings
import warnings

class ErrorHandler(pybindgen.settings.ErrorHandler):
    def handle_error(self, wrapper, exception, traceback_):
        warnings.warn("exception %r in wrapper %s" % (exception, wrapper))
        return True
pybindgen.settings.error_handler = ErrorHandler()


import sys

def module_init():
    root_module = Module('ns.pimdm', cpp_namespace='::ns3')
    return root_module

def register_types(module):
    root_module = module.get_root()
    
    ## wifi-mac-header.h (module 'wifi'): ns3::WifiMacType [enumeration]
    module.add_enum('WifiMacType', ['WIFI_MAC_CTL_RTS', 'WIFI_MAC_CTL_CTS', 'WIFI_MAC_CTL_ACK', 'WIFI_MAC_CTL_BACKREQ', 'WIFI_MAC_CTL_BACKRESP', 'WIFI_MAC_MGT_BEACON', 'WIFI_MAC_MGT_ASSOCIATION_REQUEST', 'WIFI_MAC_MGT_ASSOCIATION_RESPONSE', 'WIFI_MAC_MGT_DISASSOCIATION', 'WIFI_MAC_MGT_REASSOCIATION_REQUEST', 'WIFI_MAC_MGT_REASSOCIATION_RESPONSE', 'WIFI_MAC_MGT_PROBE_REQUEST', 'WIFI_MAC_MGT_PROBE_RESPONSE', 'WIFI_MAC_MGT_AUTHENTICATION', 'WIFI_MAC_MGT_DEAUTHENTICATION', 'WIFI_MAC_MGT_ACTION', 'WIFI_MAC_MGT_ACTION_NO_ACK', 'WIFI_MAC_MGT_MULTIHOP_ACTION', 'WIFI_MAC_DATA', 'WIFI_MAC_DATA_CFACK', 'WIFI_MAC_DATA_CFPOLL', 'WIFI_MAC_DATA_CFACK_CFPOLL', 'WIFI_MAC_DATA_NULL', 'WIFI_MAC_DATA_NULL_CFACK', 'WIFI_MAC_DATA_NULL_CFPOLL', 'WIFI_MAC_DATA_NULL_CFACK_CFPOLL', 'WIFI_MAC_QOSDATA', 'WIFI_MAC_QOSDATA_CFACK', 'WIFI_MAC_QOSDATA_CFPOLL', 'WIFI_MAC_QOSDATA_CFACK_CFPOLL', 'WIFI_MAC_QOSDATA_NULL', 'WIFI_MAC_QOSDATA_NULL_CFPOLL', 'WIFI_MAC_QOSDATA_NULL_CFACK_CFPOLL'], import_from_module='ns.wifi')
    ## log.h (module 'core'): ns3::LogLevel [enumeration]
    module.add_enum('LogLevel', ['LOG_NONE', 'LOG_ERROR', 'LOG_LEVEL_ERROR', 'LOG_WARN', 'LOG_LEVEL_WARN', 'LOG_DEBUG', 'LOG_LEVEL_DEBUG', 'LOG_INFO', 'LOG_LEVEL_INFO', 'LOG_FUNCTION', 'LOG_LEVEL_FUNCTION', 'LOG_LOGIC', 'LOG_LEVEL_LOGIC', 'LOG_ALL', 'LOG_LEVEL_ALL', 'LOG_PREFIX_FUNC', 'LOG_PREFIX_TIME', 'LOG_PREFIX_NODE'], import_from_module='ns.core')
    ## address.h (module 'network'): ns3::Address [class]
    module.add_class('Address', import_from_module='ns.network')
    ## address.h (module 'network'): ns3::Address::MaxSize_e [enumeration]
    module.add_enum('MaxSize_e', ['MAX_SIZE'], outer_class=root_module['ns3::Address'], import_from_module='ns.network')
    ## attribute-construction-list.h (module 'core'): ns3::AttributeConstructionList [class]
    module.add_class('AttributeConstructionList', import_from_module='ns.core')
    ## attribute-construction-list.h (module 'core'): ns3::AttributeConstructionList::Item [struct]
    module.add_class('Item', import_from_module='ns.core', outer_class=root_module['ns3::AttributeConstructionList'])
    ## buffer.h (module 'network'): ns3::Buffer [class]
    module.add_class('Buffer', import_from_module='ns.network')
    ## buffer.h (module 'network'): ns3::Buffer::Iterator [class]
    module.add_class('Iterator', import_from_module='ns.network', outer_class=root_module['ns3::Buffer'])
    ## packet.h (module 'network'): ns3::ByteTagIterator [class]
    module.add_class('ByteTagIterator', import_from_module='ns.network')
    ## packet.h (module 'network'): ns3::ByteTagIterator::Item [class]
    module.add_class('Item', import_from_module='ns.network', outer_class=root_module['ns3::ByteTagIterator'])
    ## byte-tag-list.h (module 'network'): ns3::ByteTagList [class]
    module.add_class('ByteTagList', import_from_module='ns.network')
    ## byte-tag-list.h (module 'network'): ns3::ByteTagList::Iterator [class]
    module.add_class('Iterator', import_from_module='ns.network', outer_class=root_module['ns3::ByteTagList'])
    ## byte-tag-list.h (module 'network'): ns3::ByteTagList::Iterator::Item [struct]
    module.add_class('Item', import_from_module='ns.network', outer_class=root_module['ns3::ByteTagList::Iterator'])
    ## callback.h (module 'core'): ns3::CallbackBase [class]
    module.add_class('CallbackBase', import_from_module='ns.core')
    ## event-garbage-collector.h (module 'tools'): ns3::EventGarbageCollector [class]
    module.add_class('EventGarbageCollector', import_from_module='ns.tools')
    ## event-id.h (module 'core'): ns3::EventId [class]
    module.add_class('EventId', import_from_module='ns.core')
    ## gnuplot.h (module 'tools'): ns3::Gnuplot [class]
    module.add_class('Gnuplot', import_from_module='ns.tools')
    ## gnuplot.h (module 'tools'): ns3::GnuplotCollection [class]
    module.add_class('GnuplotCollection', import_from_module='ns.tools')
    ## gnuplot.h (module 'tools'): ns3::GnuplotDataset [class]
    module.add_class('GnuplotDataset', import_from_module='ns.tools')
    ## int-to-type.h (module 'core'): ns3::IntToType<0> [struct]
    module.add_class('IntToType', import_from_module='ns.core', template_parameters=['0'])
    ## int-to-type.h (module 'core'): ns3::IntToType<0>::v_e [enumeration]
    module.add_enum('v_e', ['value'], outer_class=root_module['ns3::IntToType< 0 >'], import_from_module='ns.core')
    ## int-to-type.h (module 'core'): ns3::IntToType<1> [struct]
    module.add_class('IntToType', import_from_module='ns.core', template_parameters=['1'])
    ## int-to-type.h (module 'core'): ns3::IntToType<1>::v_e [enumeration]
    module.add_enum('v_e', ['value'], outer_class=root_module['ns3::IntToType< 1 >'], import_from_module='ns.core')
    ## int-to-type.h (module 'core'): ns3::IntToType<2> [struct]
    module.add_class('IntToType', import_from_module='ns.core', template_parameters=['2'])
    ## int-to-type.h (module 'core'): ns3::IntToType<2>::v_e [enumeration]
    module.add_enum('v_e', ['value'], outer_class=root_module['ns3::IntToType< 2 >'], import_from_module='ns.core')
    ## int-to-type.h (module 'core'): ns3::IntToType<3> [struct]
    module.add_class('IntToType', import_from_module='ns.core', template_parameters=['3'])
    ## int-to-type.h (module 'core'): ns3::IntToType<3>::v_e [enumeration]
    module.add_enum('v_e', ['value'], outer_class=root_module['ns3::IntToType< 3 >'], import_from_module='ns.core')
    ## int-to-type.h (module 'core'): ns3::IntToType<4> [struct]
    module.add_class('IntToType', import_from_module='ns.core', template_parameters=['4'])
    ## int-to-type.h (module 'core'): ns3::IntToType<4>::v_e [enumeration]
    module.add_enum('v_e', ['value'], outer_class=root_module['ns3::IntToType< 4 >'], import_from_module='ns.core')
    ## int-to-type.h (module 'core'): ns3::IntToType<5> [struct]
    module.add_class('IntToType', import_from_module='ns.core', template_parameters=['5'])
    ## int-to-type.h (module 'core'): ns3::IntToType<5>::v_e [enumeration]
    module.add_enum('v_e', ['value'], outer_class=root_module['ns3::IntToType< 5 >'], import_from_module='ns.core')
    ## int-to-type.h (module 'core'): ns3::IntToType<6> [struct]
    module.add_class('IntToType', import_from_module='ns.core', template_parameters=['6'])
    ## int-to-type.h (module 'core'): ns3::IntToType<6>::v_e [enumeration]
    module.add_enum('v_e', ['value'], outer_class=root_module['ns3::IntToType< 6 >'], import_from_module='ns.core')
    ## ipv4-address.h (module 'network'): ns3::Ipv4Address [class]
    module.add_class('Ipv4Address', import_from_module='ns.network')
    ## ipv4-address.h (module 'network'): ns3::Ipv4Address [class]
    root_module['ns3::Ipv4Address'].implicitly_converts_to(root_module['ns3::Address'])
    ## ipv4-interface-address.h (module 'internet'): ns3::Ipv4InterfaceAddress [class]
    module.add_class('Ipv4InterfaceAddress', import_from_module='ns.internet')
    ## ipv4-interface-address.h (module 'internet'): ns3::Ipv4InterfaceAddress::InterfaceAddressScope_e [enumeration]
    module.add_enum('InterfaceAddressScope_e', ['HOST', 'LINK', 'GLOBAL'], outer_class=root_module['ns3::Ipv4InterfaceAddress'], import_from_module='ns.internet')
    ## ipv4-address.h (module 'network'): ns3::Ipv4Mask [class]
    module.add_class('Ipv4Mask', import_from_module='ns.network')
    ## ipv4-routing-helper.h (module 'internet'): ns3::Ipv4RoutingHelper [class]
    module.add_class('Ipv4RoutingHelper', allow_subclassing=True, import_from_module='ns.internet')
    ## ipv6-address.h (module 'network'): ns3::Ipv6Address [class]
    module.add_class('Ipv6Address', import_from_module='ns.network')
    ## ipv6-address.h (module 'network'): ns3::Ipv6Address [class]
    root_module['ns3::Ipv6Address'].implicitly_converts_to(root_module['ns3::Address'])
    ## ipv6-interface-address.h (module 'internet'): ns3::Ipv6InterfaceAddress [class]
    module.add_class('Ipv6InterfaceAddress', import_from_module='ns.internet')
    ## ipv6-interface-address.h (module 'internet'): ns3::Ipv6InterfaceAddress::State_e [enumeration]
    module.add_enum('State_e', ['TENTATIVE', 'DEPRECATED', 'PREFERRED', 'PERMANENT', 'HOMEADDRESS', 'TENTATIVE_OPTIMISTIC', 'INVALID'], outer_class=root_module['ns3::Ipv6InterfaceAddress'], import_from_module='ns.internet')
    ## ipv6-interface-address.h (module 'internet'): ns3::Ipv6InterfaceAddress::Scope_e [enumeration]
    module.add_enum('Scope_e', ['HOST', 'LINKLOCAL', 'GLOBAL'], outer_class=root_module['ns3::Ipv6InterfaceAddress'], import_from_module='ns.internet')
    ## ipv6-address.h (module 'network'): ns3::Ipv6Prefix [class]
    module.add_class('Ipv6Prefix', import_from_module='ns.network')
    ## log.h (module 'core'): ns3::LogComponent [class]
    module.add_class('LogComponent', import_from_module='ns.core')
    ## mac48-address.h (module 'network'): ns3::Mac48Address [class]
    module.add_class('Mac48Address', import_from_module='ns.network')
    ## mac48-address.h (module 'network'): ns3::Mac48Address [class]
    root_module['ns3::Mac48Address'].implicitly_converts_to(root_module['ns3::Address'])
    ## node-container.h (module 'network'): ns3::NodeContainer [class]
    module.add_class('NodeContainer', import_from_module='ns.network')
    ## object-base.h (module 'core'): ns3::ObjectBase [class]
    module.add_class('ObjectBase', allow_subclassing=True, import_from_module='ns.core')
    ## object.h (module 'core'): ns3::ObjectDeleter [struct]
    module.add_class('ObjectDeleter', import_from_module='ns.core')
    ## object-factory.h (module 'core'): ns3::ObjectFactory [class]
    module.add_class('ObjectFactory', import_from_module='ns.core')
    ## olsr-state.h (module 'olsr'): ns3::OlsrState [class]
    module.add_class('OlsrState', import_from_module='ns.olsr')
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata [class]
    module.add_class('PacketMetadata', import_from_module='ns.network')
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::Item [struct]
    module.add_class('Item', import_from_module='ns.network', outer_class=root_module['ns3::PacketMetadata'])
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::Item [enumeration]
    module.add_enum('', ['PAYLOAD', 'HEADER', 'TRAILER'], outer_class=root_module['ns3::PacketMetadata::Item'], import_from_module='ns.network')
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::ItemIterator [class]
    module.add_class('ItemIterator', import_from_module='ns.network', outer_class=root_module['ns3::PacketMetadata'])
    ## packet.h (module 'network'): ns3::PacketTagIterator [class]
    module.add_class('PacketTagIterator', import_from_module='ns.network')
    ## packet.h (module 'network'): ns3::PacketTagIterator::Item [class]
    module.add_class('Item', import_from_module='ns.network', outer_class=root_module['ns3::PacketTagIterator'])
    ## packet-tag-list.h (module 'network'): ns3::PacketTagList [class]
    module.add_class('PacketTagList', import_from_module='ns.network')
    ## packet-tag-list.h (module 'network'): ns3::PacketTagList::TagData [struct]
    module.add_class('TagData', import_from_module='ns.network', outer_class=root_module['ns3::PacketTagList'])
    ## pimdm-helper.h (module 'pimdm'): ns3::PimDmHelper [class]
    module.add_class('PimDmHelper', parent=root_module['ns3::Ipv4RoutingHelper'])
    ## random-variable.h (module 'core'): ns3::RandomVariable [class]
    module.add_class('RandomVariable', import_from_module='ns.core')
    ## rng-seed-manager.h (module 'core'): ns3::RngSeedManager [class]
    module.add_class('RngSeedManager', import_from_module='ns.core')
    ## random-variable.h (module 'core'): ns3::SequentialVariable [class]
    module.add_class('SequentialVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariable'])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::Object, ns3::ObjectBase, ns3::ObjectDeleter> [class]
    module.add_class('SimpleRefCount', automatic_type_narrowing=True, import_from_module='ns.core', template_parameters=['ns3::Object', 'ns3::ObjectBase', 'ns3::ObjectDeleter'], parent=root_module['ns3::ObjectBase'], memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'))
    ## simulator.h (module 'core'): ns3::Simulator [class]
    module.add_class('Simulator', destructor_visibility='private', import_from_module='ns.core')
    ## system-wall-clock-ms.h (module 'core'): ns3::SystemWallClockMs [class]
    module.add_class('SystemWallClockMs', import_from_module='ns.core')
    ## tag.h (module 'network'): ns3::Tag [class]
    module.add_class('Tag', import_from_module='ns.network', parent=root_module['ns3::ObjectBase'])
    ## tag-buffer.h (module 'network'): ns3::TagBuffer [class]
    module.add_class('TagBuffer', import_from_module='ns.network')
    ## timer.h (module 'core'): ns3::Timer [class]
    module.add_class('Timer', import_from_module='ns.core')
    ## timer.h (module 'core'): ns3::Timer::DestroyPolicy [enumeration]
    module.add_enum('DestroyPolicy', ['CANCEL_ON_DESTROY', 'REMOVE_ON_DESTROY', 'CHECK_ON_DESTROY'], outer_class=root_module['ns3::Timer'], import_from_module='ns.core')
    ## timer.h (module 'core'): ns3::Timer::State [enumeration]
    module.add_enum('State', ['RUNNING', 'EXPIRED', 'SUSPENDED'], outer_class=root_module['ns3::Timer'], import_from_module='ns.core')
    ## timer-impl.h (module 'core'): ns3::TimerImpl [class]
    module.add_class('TimerImpl', allow_subclassing=True, import_from_module='ns.core')
    ## random-variable.h (module 'core'): ns3::TriangularVariable [class]
    module.add_class('TriangularVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariable'])
    ## type-id.h (module 'core'): ns3::TypeId [class]
    module.add_class('TypeId', import_from_module='ns.core')
    ## type-id.h (module 'core'): ns3::TypeId::AttributeFlag [enumeration]
    module.add_enum('AttributeFlag', ['ATTR_GET', 'ATTR_SET', 'ATTR_CONSTRUCT', 'ATTR_SGC'], outer_class=root_module['ns3::TypeId'], import_from_module='ns.core')
    ## type-id.h (module 'core'): ns3::TypeId::AttributeInformation [struct]
    module.add_class('AttributeInformation', import_from_module='ns.core', outer_class=root_module['ns3::TypeId'])
    ## type-id.h (module 'core'): ns3::TypeId::TraceSourceInformation [struct]
    module.add_class('TraceSourceInformation', import_from_module='ns.core', outer_class=root_module['ns3::TypeId'])
    ## random-variable.h (module 'core'): ns3::UniformVariable [class]
    module.add_class('UniformVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariable'])
    ## random-variable.h (module 'core'): ns3::WeibullVariable [class]
    module.add_class('WeibullVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariable'])
    ## random-variable.h (module 'core'): ns3::ZetaVariable [class]
    module.add_class('ZetaVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariable'])
    ## random-variable.h (module 'core'): ns3::ZipfVariable [class]
    module.add_class('ZipfVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariable'])
    ## empty.h (module 'core'): ns3::empty [class]
    module.add_class('empty', import_from_module='ns.core')
    ## int64x64-double.h (module 'core'): ns3::int64x64_t [class]
    module.add_class('int64x64_t', import_from_module='ns.core')
    ## chunk.h (module 'network'): ns3::Chunk [class]
    module.add_class('Chunk', import_from_module='ns.network', parent=root_module['ns3::ObjectBase'])
    ## random-variable.h (module 'core'): ns3::ConstantVariable [class]
    module.add_class('ConstantVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariable'])
    ## random-variable.h (module 'core'): ns3::DeterministicVariable [class]
    module.add_class('DeterministicVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariable'])
    ## random-variable.h (module 'core'): ns3::EmpiricalVariable [class]
    module.add_class('EmpiricalVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariable'])
    ## random-variable.h (module 'core'): ns3::ErlangVariable [class]
    module.add_class('ErlangVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariable'])
    ## random-variable.h (module 'core'): ns3::ExponentialVariable [class]
    module.add_class('ExponentialVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariable'])
    ## random-variable.h (module 'core'): ns3::GammaVariable [class]
    module.add_class('GammaVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariable'])
    ## gnuplot.h (module 'tools'): ns3::Gnuplot2dDataset [class]
    module.add_class('Gnuplot2dDataset', import_from_module='ns.tools', parent=root_module['ns3::GnuplotDataset'])
    ## gnuplot.h (module 'tools'): ns3::Gnuplot2dDataset::Style [enumeration]
    module.add_enum('Style', ['LINES', 'POINTS', 'LINES_POINTS', 'DOTS', 'IMPULSES', 'STEPS', 'FSTEPS', 'HISTEPS'], outer_class=root_module['ns3::Gnuplot2dDataset'], import_from_module='ns.tools')
    ## gnuplot.h (module 'tools'): ns3::Gnuplot2dDataset::ErrorBars [enumeration]
    module.add_enum('ErrorBars', ['NONE', 'X', 'Y', 'XY'], outer_class=root_module['ns3::Gnuplot2dDataset'], import_from_module='ns.tools')
    ## gnuplot.h (module 'tools'): ns3::Gnuplot2dFunction [class]
    module.add_class('Gnuplot2dFunction', import_from_module='ns.tools', parent=root_module['ns3::GnuplotDataset'])
    ## gnuplot.h (module 'tools'): ns3::Gnuplot3dDataset [class]
    module.add_class('Gnuplot3dDataset', import_from_module='ns.tools', parent=root_module['ns3::GnuplotDataset'])
    ## gnuplot.h (module 'tools'): ns3::Gnuplot3dFunction [class]
    module.add_class('Gnuplot3dFunction', import_from_module='ns.tools', parent=root_module['ns3::GnuplotDataset'])
    ## header.h (module 'network'): ns3::Header [class]
    module.add_class('Header', import_from_module='ns.network', parent=root_module['ns3::Chunk'])
    ## random-variable.h (module 'core'): ns3::IntEmpiricalVariable [class]
    module.add_class('IntEmpiricalVariable', import_from_module='ns.core', parent=root_module['ns3::EmpiricalVariable'])
    ## ipv4-header.h (module 'internet'): ns3::Ipv4Header [class]
    module.add_class('Ipv4Header', import_from_module='ns.internet', parent=root_module['ns3::Header'])
    ## ipv4-header.h (module 'internet'): ns3::Ipv4Header::DscpType [enumeration]
    module.add_enum('DscpType', ['DscpDefault', 'CS1', 'AF11', 'AF12', 'AF13', 'CS2', 'AF21', 'AF22', 'AF23', 'CS3', 'AF31', 'AF32', 'AF33', 'CS4', 'AF41', 'AF42', 'AF43', 'CS5', 'EF', 'CS6', 'CS7'], outer_class=root_module['ns3::Ipv4Header'], import_from_module='ns.internet')
    ## ipv4-header.h (module 'internet'): ns3::Ipv4Header::EcnType [enumeration]
    module.add_enum('EcnType', ['NotECT', 'ECT1', 'ECT0', 'CE'], outer_class=root_module['ns3::Ipv4Header'], import_from_module='ns.internet')
    ## ipv6-header.h (module 'internet'): ns3::Ipv6Header [class]
    module.add_class('Ipv6Header', import_from_module='ns.internet', parent=root_module['ns3::Header'])
    ## ipv6-header.h (module 'internet'): ns3::Ipv6Header::NextHeader_e [enumeration]
    module.add_enum('NextHeader_e', ['IPV6_EXT_HOP_BY_HOP', 'IPV6_IPV4', 'IPV6_TCP', 'IPV6_UDP', 'IPV6_IPV6', 'IPV6_EXT_ROUTING', 'IPV6_EXT_FRAGMENTATION', 'IPV6_EXT_CONFIDENTIALITY', 'IPV6_EXT_AUTHENTIFICATION', 'IPV6_ICMPV6', 'IPV6_EXT_END', 'IPV6_EXT_DESTINATION', 'IPV6_SCTP', 'IPV6_EXT_MOBILITY', 'IPV6_UDP_LITE'], outer_class=root_module['ns3::Ipv6Header'], import_from_module='ns.internet')
    ## random-variable.h (module 'core'): ns3::LogNormalVariable [class]
    module.add_class('LogNormalVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariable'])
    ## random-variable.h (module 'core'): ns3::NormalVariable [class]
    module.add_class('NormalVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariable'])
    ## object.h (module 'core'): ns3::Object [class]
    module.add_class('Object', import_from_module='ns.core', parent=root_module['ns3::SimpleRefCount< ns3::Object, ns3::ObjectBase, ns3::ObjectDeleter >'])
    ## object.h (module 'core'): ns3::Object::AggregateIterator [class]
    module.add_class('AggregateIterator', import_from_module='ns.core', outer_class=root_module['ns3::Object'])
    ## random-variable.h (module 'core'): ns3::ParetoVariable [class]
    module.add_class('ParetoVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariable'])
    ## random-variable-stream.h (module 'core'): ns3::RandomVariableStream [class]
    module.add_class('RandomVariableStream', import_from_module='ns.core', parent=root_module['ns3::Object'])
    ## random-variable-stream.h (module 'core'): ns3::SequentialRandomVariable [class]
    module.add_class('SequentialRandomVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariableStream'])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::AttributeAccessor, ns3::empty, ns3::DefaultDeleter<ns3::AttributeAccessor> > [class]
    module.add_class('SimpleRefCount', automatic_type_narrowing=True, import_from_module='ns.core', template_parameters=['ns3::AttributeAccessor', 'ns3::empty', 'ns3::DefaultDeleter<ns3::AttributeAccessor>'], parent=root_module['ns3::empty'], memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'))
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::AttributeChecker, ns3::empty, ns3::DefaultDeleter<ns3::AttributeChecker> > [class]
    module.add_class('SimpleRefCount', automatic_type_narrowing=True, import_from_module='ns.core', template_parameters=['ns3::AttributeChecker', 'ns3::empty', 'ns3::DefaultDeleter<ns3::AttributeChecker>'], parent=root_module['ns3::empty'], memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'))
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::AttributeValue, ns3::empty, ns3::DefaultDeleter<ns3::AttributeValue> > [class]
    module.add_class('SimpleRefCount', automatic_type_narrowing=True, import_from_module='ns.core', template_parameters=['ns3::AttributeValue', 'ns3::empty', 'ns3::DefaultDeleter<ns3::AttributeValue>'], parent=root_module['ns3::empty'], memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'))
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::CallbackImplBase, ns3::empty, ns3::DefaultDeleter<ns3::CallbackImplBase> > [class]
    module.add_class('SimpleRefCount', automatic_type_narrowing=True, import_from_module='ns.core', template_parameters=['ns3::CallbackImplBase', 'ns3::empty', 'ns3::DefaultDeleter<ns3::CallbackImplBase>'], parent=root_module['ns3::empty'], memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'))
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::EventImpl, ns3::empty, ns3::DefaultDeleter<ns3::EventImpl> > [class]
    module.add_class('SimpleRefCount', automatic_type_narrowing=True, import_from_module='ns.core', template_parameters=['ns3::EventImpl', 'ns3::empty', 'ns3::DefaultDeleter<ns3::EventImpl>'], parent=root_module['ns3::empty'], memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'))
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::Ipv4MulticastRoute, ns3::empty, ns3::DefaultDeleter<ns3::Ipv4MulticastRoute> > [class]
    module.add_class('SimpleRefCount', automatic_type_narrowing=True, import_from_module='ns.core', template_parameters=['ns3::Ipv4MulticastRoute', 'ns3::empty', 'ns3::DefaultDeleter<ns3::Ipv4MulticastRoute>'], parent=root_module['ns3::empty'], memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'))
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::Ipv4Route, ns3::empty, ns3::DefaultDeleter<ns3::Ipv4Route> > [class]
    module.add_class('SimpleRefCount', automatic_type_narrowing=True, import_from_module='ns.core', template_parameters=['ns3::Ipv4Route', 'ns3::empty', 'ns3::DefaultDeleter<ns3::Ipv4Route>'], parent=root_module['ns3::empty'], memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'))
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::NixVector, ns3::empty, ns3::DefaultDeleter<ns3::NixVector> > [class]
    module.add_class('SimpleRefCount', automatic_type_narrowing=True, import_from_module='ns.core', template_parameters=['ns3::NixVector', 'ns3::empty', 'ns3::DefaultDeleter<ns3::NixVector>'], parent=root_module['ns3::empty'], memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'))
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::OutputStreamWrapper, ns3::empty, ns3::DefaultDeleter<ns3::OutputStreamWrapper> > [class]
    module.add_class('SimpleRefCount', automatic_type_narrowing=True, import_from_module='ns.core', template_parameters=['ns3::OutputStreamWrapper', 'ns3::empty', 'ns3::DefaultDeleter<ns3::OutputStreamWrapper>'], parent=root_module['ns3::empty'], memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'))
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::Packet, ns3::empty, ns3::DefaultDeleter<ns3::Packet> > [class]
    module.add_class('SimpleRefCount', automatic_type_narrowing=True, import_from_module='ns.core', template_parameters=['ns3::Packet', 'ns3::empty', 'ns3::DefaultDeleter<ns3::Packet>'], parent=root_module['ns3::empty'], memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'))
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::TraceSourceAccessor, ns3::empty, ns3::DefaultDeleter<ns3::TraceSourceAccessor> > [class]
    module.add_class('SimpleRefCount', automatic_type_narrowing=True, import_from_module='ns.core', template_parameters=['ns3::TraceSourceAccessor', 'ns3::empty', 'ns3::DefaultDeleter<ns3::TraceSourceAccessor>'], parent=root_module['ns3::empty'], memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'))
    ## socket.h (module 'network'): ns3::Socket [class]
    module.add_class('Socket', import_from_module='ns.network', parent=root_module['ns3::Object'])
    ## socket.h (module 'network'): ns3::Socket::SocketErrno [enumeration]
    module.add_enum('SocketErrno', ['ERROR_NOTERROR', 'ERROR_ISCONN', 'ERROR_NOTCONN', 'ERROR_MSGSIZE', 'ERROR_AGAIN', 'ERROR_SHUTDOWN', 'ERROR_OPNOTSUPP', 'ERROR_AFNOSUPPORT', 'ERROR_INVAL', 'ERROR_BADF', 'ERROR_NOROUTETOHOST', 'ERROR_NODEV', 'ERROR_ADDRNOTAVAIL', 'ERROR_ADDRINUSE', 'SOCKET_ERRNO_LAST'], outer_class=root_module['ns3::Socket'], import_from_module='ns.network')
    ## socket.h (module 'network'): ns3::Socket::SocketType [enumeration]
    module.add_enum('SocketType', ['NS3_SOCK_STREAM', 'NS3_SOCK_SEQPACKET', 'NS3_SOCK_DGRAM', 'NS3_SOCK_RAW'], outer_class=root_module['ns3::Socket'], import_from_module='ns.network')
    ## socket.h (module 'network'): ns3::SocketAddressTag [class]
    module.add_class('SocketAddressTag', import_from_module='ns.network', parent=root_module['ns3::Tag'])
    ## socket.h (module 'network'): ns3::SocketIpTtlTag [class]
    module.add_class('SocketIpTtlTag', import_from_module='ns.network', parent=root_module['ns3::Tag'])
    ## socket.h (module 'network'): ns3::SocketSetDontFragmentTag [class]
    module.add_class('SocketSetDontFragmentTag', import_from_module='ns.network', parent=root_module['ns3::Tag'])
    ## nstime.h (module 'core'): ns3::Time [class]
    module.add_class('Time', import_from_module='ns.core')
    ## nstime.h (module 'core'): ns3::Time::Unit [enumeration]
    module.add_enum('Unit', ['S', 'MS', 'US', 'NS', 'PS', 'FS', 'LAST'], outer_class=root_module['ns3::Time'], import_from_module='ns.core')
    ## nstime.h (module 'core'): ns3::Time [class]
    root_module['ns3::Time'].implicitly_converts_to(root_module['ns3::int64x64_t'])
    ## trace-source-accessor.h (module 'core'): ns3::TraceSourceAccessor [class]
    module.add_class('TraceSourceAccessor', import_from_module='ns.core', parent=root_module['ns3::SimpleRefCount< ns3::TraceSourceAccessor, ns3::empty, ns3::DefaultDeleter<ns3::TraceSourceAccessor> >'])
    ## trailer.h (module 'network'): ns3::Trailer [class]
    module.add_class('Trailer', import_from_module='ns.network', parent=root_module['ns3::Chunk'])
    ## random-variable-stream.h (module 'core'): ns3::TriangularRandomVariable [class]
    module.add_class('TriangularRandomVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariableStream'])
    ## random-variable-stream.h (module 'core'): ns3::UniformRandomVariable [class]
    module.add_class('UniformRandomVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariableStream'])
    ## random-variable-stream.h (module 'core'): ns3::WeibullRandomVariable [class]
    module.add_class('WeibullRandomVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariableStream'])
    ## wifi-mac-header.h (module 'wifi'): ns3::WifiMacHeader [class]
    module.add_class('WifiMacHeader', import_from_module='ns.wifi', parent=root_module['ns3::Header'])
    ## wifi-mac-header.h (module 'wifi'): ns3::WifiMacHeader::QosAckPolicy [enumeration]
    module.add_enum('QosAckPolicy', ['NORMAL_ACK', 'NO_ACK', 'NO_EXPLICIT_ACK', 'BLOCK_ACK'], outer_class=root_module['ns3::WifiMacHeader'], import_from_module='ns.wifi')
    ## wifi-mac-header.h (module 'wifi'): ns3::WifiMacHeader::AddressType [enumeration]
    module.add_enum('AddressType', ['ADDR1', 'ADDR2', 'ADDR3', 'ADDR4'], outer_class=root_module['ns3::WifiMacHeader'], import_from_module='ns.wifi')
    ## random-variable-stream.h (module 'core'): ns3::ZetaRandomVariable [class]
    module.add_class('ZetaRandomVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariableStream'])
    ## random-variable-stream.h (module 'core'): ns3::ZipfRandomVariable [class]
    module.add_class('ZipfRandomVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariableStream'])
    ## arp-cache.h (module 'internet'): ns3::ArpCache [class]
    module.add_class('ArpCache', import_from_module='ns.internet', parent=root_module['ns3::Object'])
    ## arp-cache.h (module 'internet'): ns3::ArpCache::Entry [class]
    module.add_class('Entry', import_from_module='ns.internet', outer_class=root_module['ns3::ArpCache'])
    ## attribute.h (module 'core'): ns3::AttributeAccessor [class]
    module.add_class('AttributeAccessor', import_from_module='ns.core', parent=root_module['ns3::SimpleRefCount< ns3::AttributeAccessor, ns3::empty, ns3::DefaultDeleter<ns3::AttributeAccessor> >'])
    ## attribute.h (module 'core'): ns3::AttributeChecker [class]
    module.add_class('AttributeChecker', allow_subclassing=False, automatic_type_narrowing=True, import_from_module='ns.core', parent=root_module['ns3::SimpleRefCount< ns3::AttributeChecker, ns3::empty, ns3::DefaultDeleter<ns3::AttributeChecker> >'])
    ## attribute.h (module 'core'): ns3::AttributeValue [class]
    module.add_class('AttributeValue', allow_subclassing=False, automatic_type_narrowing=True, import_from_module='ns.core', parent=root_module['ns3::SimpleRefCount< ns3::AttributeValue, ns3::empty, ns3::DefaultDeleter<ns3::AttributeValue> >'])
    ## callback.h (module 'core'): ns3::CallbackChecker [class]
    module.add_class('CallbackChecker', import_from_module='ns.core', parent=root_module['ns3::AttributeChecker'])
    ## callback.h (module 'core'): ns3::CallbackImplBase [class]
    module.add_class('CallbackImplBase', import_from_module='ns.core', parent=root_module['ns3::SimpleRefCount< ns3::CallbackImplBase, ns3::empty, ns3::DefaultDeleter<ns3::CallbackImplBase> >'])
    ## callback.h (module 'core'): ns3::CallbackValue [class]
    module.add_class('CallbackValue', import_from_module='ns.core', parent=root_module['ns3::AttributeValue'])
    ## random-variable-stream.h (module 'core'): ns3::ConstantRandomVariable [class]
    module.add_class('ConstantRandomVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariableStream'])
    ## random-variable-stream.h (module 'core'): ns3::DeterministicRandomVariable [class]
    module.add_class('DeterministicRandomVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariableStream'])
    ## random-variable-stream.h (module 'core'): ns3::EmpiricalRandomVariable [class]
    module.add_class('EmpiricalRandomVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariableStream'])
    ## attribute.h (module 'core'): ns3::EmptyAttributeValue [class]
    module.add_class('EmptyAttributeValue', import_from_module='ns.core', parent=root_module['ns3::AttributeValue'])
    ## enum.h (module 'core'): ns3::EnumChecker [class]
    module.add_class('EnumChecker', import_from_module='ns.core', parent=root_module['ns3::AttributeChecker'])
    ## enum.h (module 'core'): ns3::EnumValue [class]
    module.add_class('EnumValue', import_from_module='ns.core', parent=root_module['ns3::AttributeValue'])
    ## random-variable-stream.h (module 'core'): ns3::ErlangRandomVariable [class]
    module.add_class('ErlangRandomVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariableStream'])
    ## event-impl.h (module 'core'): ns3::EventImpl [class]
    module.add_class('EventImpl', import_from_module='ns.core', parent=root_module['ns3::SimpleRefCount< ns3::EventImpl, ns3::empty, ns3::DefaultDeleter<ns3::EventImpl> >'])
    ## random-variable-stream.h (module 'core'): ns3::ExponentialRandomVariable [class]
    module.add_class('ExponentialRandomVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariableStream'])
    ## random-variable-stream.h (module 'core'): ns3::GammaRandomVariable [class]
    module.add_class('GammaRandomVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariableStream'])
    ## ip-l4-protocol.h (module 'internet'): ns3::IpL4Protocol [class]
    module.add_class('IpL4Protocol', import_from_module='ns.internet', parent=root_module['ns3::Object'])
    ## ip-l4-protocol.h (module 'internet'): ns3::IpL4Protocol::RxStatus [enumeration]
    module.add_enum('RxStatus', ['RX_OK', 'RX_CSUM_FAILED', 'RX_ENDPOINT_CLOSED', 'RX_ENDPOINT_UNREACH'], outer_class=root_module['ns3::IpL4Protocol'], import_from_module='ns.internet')
    ## ipv4.h (module 'internet'): ns3::Ipv4 [class]
    module.add_class('Ipv4', import_from_module='ns.internet', parent=root_module['ns3::Object'])
    ## ipv4-address.h (module 'network'): ns3::Ipv4AddressChecker [class]
    module.add_class('Ipv4AddressChecker', import_from_module='ns.network', parent=root_module['ns3::AttributeChecker'])
    ## ipv4-address.h (module 'network'): ns3::Ipv4AddressValue [class]
    module.add_class('Ipv4AddressValue', import_from_module='ns.network', parent=root_module['ns3::AttributeValue'])
    ## ipv4-interface.h (module 'internet'): ns3::Ipv4Interface [class]
    module.add_class('Ipv4Interface', import_from_module='ns.internet', parent=root_module['ns3::Object'])
    ## ipv4-l3-protocol.h (module 'internet'): ns3::Ipv4L3Protocol [class]
    module.add_class('Ipv4L3Protocol', import_from_module='ns.internet', parent=root_module['ns3::Ipv4'])
    ## ipv4-l3-protocol.h (module 'internet'): ns3::Ipv4L3Protocol::DropReason [enumeration]
    module.add_enum('DropReason', ['DROP_TTL_EXPIRED', 'DROP_NO_ROUTE', 'DROP_BAD_CHECKSUM', 'DROP_INTERFACE_DOWN', 'DROP_ROUTE_ERROR', 'DROP_FRAGMENT_TIMEOUT'], outer_class=root_module['ns3::Ipv4L3Protocol'], import_from_module='ns.internet')
    ## ipv4-address.h (module 'network'): ns3::Ipv4MaskChecker [class]
    module.add_class('Ipv4MaskChecker', import_from_module='ns.network', parent=root_module['ns3::AttributeChecker'])
    ## ipv4-address.h (module 'network'): ns3::Ipv4MaskValue [class]
    module.add_class('Ipv4MaskValue', import_from_module='ns.network', parent=root_module['ns3::AttributeValue'])
    ## ipv4-route.h (module 'internet'): ns3::Ipv4MulticastRoute [class]
    module.add_class('Ipv4MulticastRoute', import_from_module='ns.internet', parent=root_module['ns3::SimpleRefCount< ns3::Ipv4MulticastRoute, ns3::empty, ns3::DefaultDeleter<ns3::Ipv4MulticastRoute> >'])
    ## ipv4-route.h (module 'internet'): ns3::Ipv4Route [class]
    module.add_class('Ipv4Route', import_from_module='ns.internet', parent=root_module['ns3::SimpleRefCount< ns3::Ipv4Route, ns3::empty, ns3::DefaultDeleter<ns3::Ipv4Route> >'])
    ## ipv4-routing-protocol.h (module 'internet'): ns3::Ipv4RoutingProtocol [class]
    module.add_class('Ipv4RoutingProtocol', import_from_module='ns.internet', parent=root_module['ns3::Object'])
    ## ipv4-static-routing.h (module 'internet'): ns3::Ipv4StaticRouting [class]
    module.add_class('Ipv4StaticRouting', import_from_module='ns.internet', parent=root_module['ns3::Ipv4RoutingProtocol'])
    ## ipv6-address.h (module 'network'): ns3::Ipv6AddressChecker [class]
    module.add_class('Ipv6AddressChecker', import_from_module='ns.network', parent=root_module['ns3::AttributeChecker'])
    ## ipv6-address.h (module 'network'): ns3::Ipv6AddressValue [class]
    module.add_class('Ipv6AddressValue', import_from_module='ns.network', parent=root_module['ns3::AttributeValue'])
    ## ipv6-interface.h (module 'internet'): ns3::Ipv6Interface [class]
    module.add_class('Ipv6Interface', import_from_module='ns.internet', parent=root_module['ns3::Object'])
    ## ipv6-address.h (module 'network'): ns3::Ipv6PrefixChecker [class]
    module.add_class('Ipv6PrefixChecker', import_from_module='ns.network', parent=root_module['ns3::AttributeChecker'])
    ## ipv6-address.h (module 'network'): ns3::Ipv6PrefixValue [class]
    module.add_class('Ipv6PrefixValue', import_from_module='ns.network', parent=root_module['ns3::AttributeValue'])
    ## random-variable-stream.h (module 'core'): ns3::LogNormalRandomVariable [class]
    module.add_class('LogNormalRandomVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariableStream'])
    ## mac48-address.h (module 'network'): ns3::Mac48AddressChecker [class]
    module.add_class('Mac48AddressChecker', import_from_module='ns.network', parent=root_module['ns3::AttributeChecker'])
    ## mac48-address.h (module 'network'): ns3::Mac48AddressValue [class]
    module.add_class('Mac48AddressValue', import_from_module='ns.network', parent=root_module['ns3::AttributeValue'])
    ## net-device.h (module 'network'): ns3::NetDevice [class]
    module.add_class('NetDevice', import_from_module='ns.network', parent=root_module['ns3::Object'])
    ## net-device.h (module 'network'): ns3::NetDevice::PacketType [enumeration]
    module.add_enum('PacketType', ['PACKET_HOST', 'NS3_PACKET_HOST', 'PACKET_BROADCAST', 'NS3_PACKET_BROADCAST', 'PACKET_MULTICAST', 'NS3_PACKET_MULTICAST', 'PACKET_OTHERHOST', 'NS3_PACKET_OTHERHOST'], outer_class=root_module['ns3::NetDevice'], import_from_module='ns.network')
    ## nix-vector.h (module 'network'): ns3::NixVector [class]
    module.add_class('NixVector', import_from_module='ns.network', parent=root_module['ns3::SimpleRefCount< ns3::NixVector, ns3::empty, ns3::DefaultDeleter<ns3::NixVector> >'])
    ## node.h (module 'network'): ns3::Node [class]
    module.add_class('Node', import_from_module='ns.network', parent=root_module['ns3::Object'])
    ## random-variable-stream.h (module 'core'): ns3::NormalRandomVariable [class]
    module.add_class('NormalRandomVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariableStream'])
    ## object-factory.h (module 'core'): ns3::ObjectFactoryChecker [class]
    module.add_class('ObjectFactoryChecker', import_from_module='ns.core', parent=root_module['ns3::AttributeChecker'])
    ## object-factory.h (module 'core'): ns3::ObjectFactoryValue [class]
    module.add_class('ObjectFactoryValue', import_from_module='ns.core', parent=root_module['ns3::AttributeValue'])
    ## output-stream-wrapper.h (module 'network'): ns3::OutputStreamWrapper [class]
    module.add_class('OutputStreamWrapper', import_from_module='ns.network', parent=root_module['ns3::SimpleRefCount< ns3::OutputStreamWrapper, ns3::empty, ns3::DefaultDeleter<ns3::OutputStreamWrapper> >'])
    ## packet.h (module 'network'): ns3::Packet [class]
    module.add_class('Packet', import_from_module='ns.network', parent=root_module['ns3::SimpleRefCount< ns3::Packet, ns3::empty, ns3::DefaultDeleter<ns3::Packet> >'])
    ## random-variable-stream.h (module 'core'): ns3::ParetoRandomVariable [class]
    module.add_class('ParetoRandomVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariableStream'])
    ## random-variable.h (module 'core'): ns3::RandomVariableChecker [class]
    module.add_class('RandomVariableChecker', import_from_module='ns.core', parent=root_module['ns3::AttributeChecker'])
    ## random-variable.h (module 'core'): ns3::RandomVariableValue [class]
    module.add_class('RandomVariableValue', import_from_module='ns.core', parent=root_module['ns3::AttributeValue'])
    ## string.h (module 'core'): ns3::StringChecker [class]
    module.add_class('StringChecker', import_from_module='ns.core', parent=root_module['ns3::AttributeChecker'])
    ## string.h (module 'core'): ns3::StringValue [class]
    module.add_class('StringValue', import_from_module='ns.core', parent=root_module['ns3::AttributeValue'])
    ## nstime.h (module 'core'): ns3::TimeChecker [class]
    module.add_class('TimeChecker', import_from_module='ns.core', parent=root_module['ns3::AttributeChecker'])
    ## nstime.h (module 'core'): ns3::TimeValue [class]
    module.add_class('TimeValue', import_from_module='ns.core', parent=root_module['ns3::AttributeValue'])
    ## type-id.h (module 'core'): ns3::TypeIdChecker [class]
    module.add_class('TypeIdChecker', import_from_module='ns.core', parent=root_module['ns3::AttributeChecker'])
    ## type-id.h (module 'core'): ns3::TypeIdValue [class]
    module.add_class('TypeIdValue', import_from_module='ns.core', parent=root_module['ns3::AttributeValue'])
    ## uinteger.h (module 'core'): ns3::UintegerValue [class]
    module.add_class('UintegerValue', import_from_module='ns.core', parent=root_module['ns3::AttributeValue'])
    ## address.h (module 'network'): ns3::AddressChecker [class]
    module.add_class('AddressChecker', import_from_module='ns.network', parent=root_module['ns3::AttributeChecker'])
    ## address.h (module 'network'): ns3::AddressValue [class]
    module.add_class('AddressValue', import_from_module='ns.network', parent=root_module['ns3::AttributeValue'])
    ## ipv4-list-routing.h (module 'internet'): ns3::Ipv4ListRouting [class]
    module.add_class('Ipv4ListRouting', import_from_module='ns.internet', parent=root_module['ns3::Ipv4RoutingProtocol'])
    module.add_container('std::vector< ns3::olsr::MprSelectorTuple >', 'ns3::olsr::MprSelectorTuple', container_type='vector')
    module.add_container('std::vector< ns3::olsr::NeighborTuple >', 'ns3::olsr::NeighborTuple', container_type='vector')
    module.add_container('std::vector< ns3::olsr::TwoHopNeighborTuple >', 'ns3::olsr::TwoHopNeighborTuple', container_type='vector')
    module.add_container('ns3::olsr::MprSet', 'ns3::Ipv4Address', container_type='set')
    module.add_container('std::vector< ns3::olsr::LinkTuple >', 'ns3::olsr::LinkTuple', container_type='vector')
    module.add_container('std::vector< ns3::olsr::TopologyTuple >', 'ns3::olsr::TopologyTuple', container_type='vector')
    module.add_container('std::vector< ns3::olsr::IfaceAssocTuple >', 'ns3::olsr::IfaceAssocTuple', container_type='vector')
    module.add_container('std::vector< ns3::olsr::AssociationTuple >', 'ns3::olsr::AssociationTuple', container_type='vector')
    module.add_container('std::vector< ns3::olsr::Association >', 'ns3::olsr::Association', container_type='vector')
    module.add_container('std::vector< ns3::Ipv4Address >', 'ns3::Ipv4Address', container_type='vector')
    module.add_container('std::list< ns3::Ptr< ns3::Packet > >', 'ns3::Ptr< ns3::Packet >', container_type='list')
    module.add_container('std::map< unsigned int, unsigned int >', ('unsigned int', 'unsigned int'), container_type='map')
    module.add_container('std::vector< unsigned int >', 'unsigned int', container_type='vector')
    typehandlers.add_type_alias('ns3::RngSeedManager', 'ns3::SeedManager')
    typehandlers.add_type_alias('ns3::RngSeedManager*', 'ns3::SeedManager*')
    typehandlers.add_type_alias('ns3::RngSeedManager&', 'ns3::SeedManager&')
    module.add_typedef(root_module['ns3::RngSeedManager'], 'SeedManager')
    typehandlers.add_type_alias('void ( * ) ( std::ostream & ) *', 'ns3::LogNodePrinter')
    typehandlers.add_type_alias('void ( * ) ( std::ostream & ) **', 'ns3::LogNodePrinter*')
    typehandlers.add_type_alias('void ( * ) ( std::ostream & ) *&', 'ns3::LogNodePrinter&')
    typehandlers.add_type_alias('void ( * ) ( std::ostream & ) *', 'ns3::LogTimePrinter')
    typehandlers.add_type_alias('void ( * ) ( std::ostream & ) **', 'ns3::LogTimePrinter*')
    typehandlers.add_type_alias('void ( * ) ( std::ostream & ) *&', 'ns3::LogTimePrinter&')
    
    ## Register a nested module for the namespace FatalImpl
    
    nested_module = module.add_cpp_namespace('FatalImpl')
    register_types_ns3_FatalImpl(nested_module)
    
    
    ## Register a nested module for the namespace aodv
    
    nested_module = module.add_cpp_namespace('aodv')
    register_types_ns3_aodv(nested_module)
    
    
    ## Register a nested module for the namespace dsdv
    
    nested_module = module.add_cpp_namespace('dsdv')
    register_types_ns3_dsdv(nested_module)
    
    
    ## Register a nested module for the namespace internal
    
    nested_module = module.add_cpp_namespace('internal')
    register_types_ns3_internal(nested_module)
    
    
    ## Register a nested module for the namespace mbn
    
    nested_module = module.add_cpp_namespace('mbn')
    register_types_ns3_mbn(nested_module)
    
    
    ## Register a nested module for the namespace olsr
    
    nested_module = module.add_cpp_namespace('olsr')
    register_types_ns3_olsr(nested_module)
    
    
    ## Register a nested module for the namespace pimdm
    
    nested_module = module.add_cpp_namespace('pimdm')
    register_types_ns3_pimdm(nested_module)
    

def register_types_ns3_FatalImpl(module):
    root_module = module.get_root()
    

def register_types_ns3_aodv(module):
    root_module = module.get_root()
    
    ## aodv-packet.h (module 'aodv'): ns3::aodv::MessageType [enumeration]
    module.add_enum('MessageType', ['AODVTYPE_RREQ', 'AODVTYPE_RREP', 'AODVTYPE_RERR', 'AODVTYPE_RREP_ACK'], import_from_module='ns.aodv')
    ## aodv-rtable.h (module 'aodv'): ns3::aodv::RouteFlags [enumeration]
    module.add_enum('RouteFlags', ['VALID', 'INVALID', 'IN_SEARCH'], import_from_module='ns.aodv')
    ## aodv-dpd.h (module 'aodv'): ns3::aodv::DuplicatePacketDetection [class]
    module.add_class('DuplicatePacketDetection', import_from_module='ns.aodv')
    ## aodv-id-cache.h (module 'aodv'): ns3::aodv::IdCache [class]
    module.add_class('IdCache', import_from_module='ns.aodv')
    ## aodv-neighbor.h (module 'aodv'): ns3::aodv::Neighbors [class]
    module.add_class('Neighbors', import_from_module='ns.aodv')
    ## aodv-neighbor.h (module 'aodv'): ns3::aodv::Neighbors::Neighbor [struct]
    module.add_class('Neighbor', import_from_module='ns.aodv', outer_class=root_module['ns3::aodv::Neighbors'])
    ## aodv-rqueue.h (module 'aodv'): ns3::aodv::QueueEntry [class]
    module.add_class('QueueEntry', import_from_module='ns.aodv')
    ## aodv-rqueue.h (module 'aodv'): ns3::aodv::RequestQueue [class]
    module.add_class('RequestQueue', import_from_module='ns.aodv')
    ## aodv-packet.h (module 'aodv'): ns3::aodv::RerrHeader [class]
    module.add_class('RerrHeader', import_from_module='ns.aodv', parent=root_module['ns3::Header'])
    ## aodv-routing-protocol.h (module 'aodv'): ns3::aodv::RoutingProtocol [class]
    module.add_class('RoutingProtocol', import_from_module='ns.aodv', parent=root_module['ns3::Ipv4RoutingProtocol'])
    ## aodv-rtable.h (module 'aodv'): ns3::aodv::RoutingTable [class]
    module.add_class('RoutingTable', import_from_module='ns.aodv')
    ## aodv-rtable.h (module 'aodv'): ns3::aodv::RoutingTableEntry [class]
    module.add_class('RoutingTableEntry', import_from_module='ns.aodv')
    ## aodv-packet.h (module 'aodv'): ns3::aodv::RrepAckHeader [class]
    module.add_class('RrepAckHeader', import_from_module='ns.aodv', parent=root_module['ns3::Header'])
    ## aodv-packet.h (module 'aodv'): ns3::aodv::RrepHeader [class]
    module.add_class('RrepHeader', import_from_module='ns.aodv', parent=root_module['ns3::Header'])
    ## aodv-packet.h (module 'aodv'): ns3::aodv::RreqHeader [class]
    module.add_class('RreqHeader', import_from_module='ns.aodv', parent=root_module['ns3::Header'])
    ## aodv-packet.h (module 'aodv'): ns3::aodv::TypeHeader [class]
    module.add_class('TypeHeader', import_from_module='ns.aodv', parent=root_module['ns3::Header'])
    module.add_container('std::map< ns3::Ipv4Address, unsigned int >', ('ns3::Ipv4Address', 'unsigned int'), container_type='map')

def register_types_ns3_dsdv(module):
    root_module = module.get_root()
    
    ## dsdv-rtable.h (module 'dsdv'): ns3::dsdv::RouteFlags [enumeration]
    module.add_enum('RouteFlags', ['VALID', 'INVALID'], import_from_module='ns.dsdv')
    ## dsdv-packet.h (module 'dsdv'): ns3::dsdv::DsdvHeader [class]
    module.add_class('DsdvHeader', import_from_module='ns.dsdv', parent=root_module['ns3::Header'])
    ## dsdv-packet-queue.h (module 'dsdv'): ns3::dsdv::PacketQueue [class]
    module.add_class('PacketQueue', import_from_module='ns.dsdv')
    ## dsdv-packet-queue.h (module 'dsdv'): ns3::dsdv::QueueEntry [class]
    module.add_class('QueueEntry', import_from_module='ns.dsdv')
    ## dsdv-routing-protocol.h (module 'dsdv'): ns3::dsdv::RoutingProtocol [class]
    module.add_class('RoutingProtocol', import_from_module='ns.dsdv', parent=root_module['ns3::Ipv4RoutingProtocol'])
    ## dsdv-rtable.h (module 'dsdv'): ns3::dsdv::RoutingTable [class]
    module.add_class('RoutingTable', import_from_module='ns.dsdv')
    ## dsdv-rtable.h (module 'dsdv'): ns3::dsdv::RoutingTableEntry [class]
    module.add_class('RoutingTableEntry', import_from_module='ns.dsdv')
    module.add_container('std::map< ns3::Ipv4Address, ns3::dsdv::RoutingTableEntry >', ('ns3::Ipv4Address', 'ns3::dsdv::RoutingTableEntry'), container_type='map')

def register_types_ns3_internal(module):
    root_module = module.get_root()
    

def register_types_ns3_mbn(module):
    root_module = module.get_root()
    
    ## mbn-aodv-common.h (module 'mbn-aodv'): ns3::mbn::WeightFunction [enumeration]
    module.add_enum('WeightFunction', ['W_NODE_DEGREE', 'W_NODE_IP', 'W_NODE_RND', 'W_NODE_BNDEGREE'], import_from_module='ns.mbn-aodv')
    ## mbn-aodv-common.h (module 'mbn-aodv'): ns3::mbn::BnBcn_Indicator [enumeration]
    module.add_enum('BnBcn_Indicator', ['CONVERT_BREAK', 'CONVERT_ALLOW', 'CONVERT_OTHER'], import_from_module='ns.mbn-aodv')
    ## mbn-aodv-packet.h (module 'mbn-aodv'): ns3::mbn::MessageType [enumeration]
    module.add_enum('MessageType', ['AODVTYPE_RREQ', 'AODVTYPE_RREP', 'AODVTYPE_RERR', 'AODVTYPE_RREP_ACK', 'TYPE_HELLO'], import_from_module='ns.mbn-aodv')
    ## mbn-aodv-common.h (module 'mbn-aodv'): ns3::mbn::NodeStatus [enumeration]
    module.add_enum('NodeStatus', ['RN_NODE', 'BCN_NODE', 'BN_NODE'], import_from_module='ns.mbn-aodv')
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): ns3::mbn::RouteFlags [enumeration]
    module.add_enum('RouteFlags', ['VALID', 'INVALID', 'IN_SEARCH'], import_from_module='ns.mbn-aodv')
    ## mbn-aodv-dpd.h (module 'mbn-aodv'): ns3::mbn::DuplicatePacketDetection [class]
    module.add_class('DuplicatePacketDetection', import_from_module='ns.mbn_aodv')
    ## mbn-aodv-packet.h (module 'mbn-aodv'): ns3::mbn::HelloHeader [class]
    module.add_class('HelloHeader', import_from_module='ns.mbn_aodv', parent=root_module['ns3::Header'])
    ## mbn-aodv-id-cache.h (module 'mbn-aodv'): ns3::mbn::IdCache [class]
    module.add_class('IdCache', import_from_module='ns.mbn_aodv')
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): ns3::mbn::NeighborPair [struct]
    module.add_class('NeighborPair', import_from_module='ns.mbn_aodv')
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): ns3::mbn::NeighborTriple [struct]
    module.add_class('NeighborTriple', import_from_module='ns.mbn_aodv')
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): ns3::mbn::NeighborTuple [struct]
    module.add_class('NeighborTuple', import_from_module='ns.mbn_aodv')
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): ns3::mbn::Neighbors [class]
    module.add_class('Neighbors', import_from_module='ns.mbn_aodv')
    ## mbn-aodv-rqueue.h (module 'mbn-aodv'): ns3::mbn::QueueEntry [class]
    module.add_class('QueueEntry', import_from_module='ns.mbn_aodv')
    ## mbn-aodv-rqueue.h (module 'mbn-aodv'): ns3::mbn::RequestQueue [class]
    module.add_class('RequestQueue', import_from_module='ns.mbn_aodv')
    ## mbn-aodv-packet.h (module 'mbn-aodv'): ns3::mbn::RerrHeader [class]
    module.add_class('RerrHeader', import_from_module='ns.mbn_aodv', parent=root_module['ns3::Header'])
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): ns3::mbn::RoutingProtocol [class]
    module.add_class('RoutingProtocol', import_from_module='ns.mbn_aodv', parent=root_module['ns3::Ipv4RoutingProtocol'])
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): ns3::mbn::RoutingTable [class]
    module.add_class('RoutingTable', import_from_module='ns.mbn_aodv')
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): ns3::mbn::RoutingTableEntry [class]
    module.add_class('RoutingTableEntry', import_from_module='ns.mbn_aodv')
    ## mbn-aodv-packet.h (module 'mbn-aodv'): ns3::mbn::RrepAckHeader [class]
    module.add_class('RrepAckHeader', import_from_module='ns.mbn_aodv', parent=root_module['ns3::Header'])
    ## mbn-aodv-packet.h (module 'mbn-aodv'): ns3::mbn::RrepHeader [class]
    module.add_class('RrepHeader', import_from_module='ns.mbn_aodv', parent=root_module['ns3::Header'])
    ## mbn-aodv-packet.h (module 'mbn-aodv'): ns3::mbn::RreqHeader [class]
    module.add_class('RreqHeader', import_from_module='ns.mbn_aodv', parent=root_module['ns3::Header'])
    ## mbn-aodv-common.h (module 'mbn-aodv'): ns3::mbn::TwoHopBnNeighborTuple [struct]
    module.add_class('TwoHopBnNeighborTuple', import_from_module='ns.mbn_aodv')
    ## mbn-aodv-packet.h (module 'mbn-aodv'): ns3::mbn::TypeHeader [class]
    module.add_class('TypeHeader', import_from_module='ns.mbn_aodv', parent=root_module['ns3::Header'])
    module.add_container('ns3::mbn::TwoHopBnNeighborSet', 'ns3::mbn::TwoHopBnNeighborTuple', container_type='list')
    module.add_container('std::list< ns3::mbn::TwoHopBnNeighborTuple >', 'ns3::mbn::TwoHopBnNeighborTuple', container_type='list')
    module.add_container('std::list< ns3::mbn::NeighborTuple >', 'ns3::mbn::NeighborTuple', container_type='list')
    module.add_container('ns3::mbn::AddressSet', 'ns3::Ipv4Address', container_type='list')
    module.add_container('ns3::mbn::NeighborSet', 'ns3::mbn::NeighborTuple', container_type='list')
    module.add_container('ns3::mbn::NeighborPairs', 'ns3::mbn::NeighborPair', container_type='list')
    module.add_container('ns3::mbn::NeighborTriples', 'ns3::mbn::NeighborTriple', container_type='list')
    typehandlers.add_type_alias('std::list< ns3::mbn::TwoHopBnNeighborTuple, std::allocator< ns3::mbn::TwoHopBnNeighborTuple > >', 'ns3::mbn::TwoHopBnNeighborSet')
    typehandlers.add_type_alias('std::list< ns3::mbn::TwoHopBnNeighborTuple, std::allocator< ns3::mbn::TwoHopBnNeighborTuple > >*', 'ns3::mbn::TwoHopBnNeighborSet*')
    typehandlers.add_type_alias('std::list< ns3::mbn::TwoHopBnNeighborTuple, std::allocator< ns3::mbn::TwoHopBnNeighborTuple > >&', 'ns3::mbn::TwoHopBnNeighborSet&')
    typehandlers.add_type_alias('std::list< ns3::mbn::NeighborPair, std::allocator< ns3::mbn::NeighborPair > >', 'ns3::mbn::NeighborPairs')
    typehandlers.add_type_alias('std::list< ns3::mbn::NeighborPair, std::allocator< ns3::mbn::NeighborPair > >*', 'ns3::mbn::NeighborPairs*')
    typehandlers.add_type_alias('std::list< ns3::mbn::NeighborPair, std::allocator< ns3::mbn::NeighborPair > >&', 'ns3::mbn::NeighborPairs&')
    typehandlers.add_type_alias('std::list< ns3::Ipv4Address, std::allocator< ns3::Ipv4Address > >', 'ns3::mbn::AddressSet')
    typehandlers.add_type_alias('std::list< ns3::Ipv4Address, std::allocator< ns3::Ipv4Address > >*', 'ns3::mbn::AddressSet*')
    typehandlers.add_type_alias('std::list< ns3::Ipv4Address, std::allocator< ns3::Ipv4Address > >&', 'ns3::mbn::AddressSet&')
    typehandlers.add_type_alias('std::list< ns3::mbn::NeighborTuple, std::allocator< ns3::mbn::NeighborTuple > >', 'ns3::mbn::NeighborSet')
    typehandlers.add_type_alias('std::list< ns3::mbn::NeighborTuple, std::allocator< ns3::mbn::NeighborTuple > >*', 'ns3::mbn::NeighborSet*')
    typehandlers.add_type_alias('std::list< ns3::mbn::NeighborTuple, std::allocator< ns3::mbn::NeighborTuple > >&', 'ns3::mbn::NeighborSet&')
    typehandlers.add_type_alias('std::list< ns3::mbn::NeighborTriple, std::allocator< ns3::mbn::NeighborTriple > >', 'ns3::mbn::NeighborTriples')
    typehandlers.add_type_alias('std::list< ns3::mbn::NeighborTriple, std::allocator< ns3::mbn::NeighborTriple > >*', 'ns3::mbn::NeighborTriples*')
    typehandlers.add_type_alias('std::list< ns3::mbn::NeighborTriple, std::allocator< ns3::mbn::NeighborTriple > >&', 'ns3::mbn::NeighborTriples&')

def register_types_ns3_olsr(module):
    root_module = module.get_root()
    
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::Association [struct]
    module.add_class('Association', import_from_module='ns.olsr')
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::AssociationTuple [struct]
    module.add_class('AssociationTuple', import_from_module='ns.olsr')
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::DuplicateTuple [struct]
    module.add_class('DuplicateTuple', import_from_module='ns.olsr')
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::IfaceAssocTuple [struct]
    module.add_class('IfaceAssocTuple', import_from_module='ns.olsr')
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::LinkTuple [struct]
    module.add_class('LinkTuple', import_from_module='ns.olsr')
    ## olsr-header.h (module 'olsr'): ns3::olsr::MessageHeader [class]
    module.add_class('MessageHeader', import_from_module='ns.olsr', parent=root_module['ns3::Header'])
    ## olsr-header.h (module 'olsr'): ns3::olsr::MessageHeader::MessageType [enumeration]
    module.add_enum('MessageType', ['HELLO_MESSAGE', 'TC_MESSAGE', 'MID_MESSAGE', 'HNA_MESSAGE'], outer_class=root_module['ns3::olsr::MessageHeader'], import_from_module='ns.olsr')
    ## olsr-header.h (module 'olsr'): ns3::olsr::MessageHeader::Hello [struct]
    module.add_class('Hello', import_from_module='ns.olsr', outer_class=root_module['ns3::olsr::MessageHeader'])
    ## olsr-header.h (module 'olsr'): ns3::olsr::MessageHeader::Hello::LinkMessage [struct]
    module.add_class('LinkMessage', import_from_module='ns.olsr', outer_class=root_module['ns3::olsr::MessageHeader::Hello'])
    ## olsr-header.h (module 'olsr'): ns3::olsr::MessageHeader::Hna [struct]
    module.add_class('Hna', import_from_module='ns.olsr', outer_class=root_module['ns3::olsr::MessageHeader'])
    ## olsr-header.h (module 'olsr'): ns3::olsr::MessageHeader::Hna::Association [struct]
    module.add_class('Association', import_from_module='ns.olsr', outer_class=root_module['ns3::olsr::MessageHeader::Hna'])
    ## olsr-header.h (module 'olsr'): ns3::olsr::MessageHeader::Mid [struct]
    module.add_class('Mid', import_from_module='ns.olsr', outer_class=root_module['ns3::olsr::MessageHeader'])
    ## olsr-header.h (module 'olsr'): ns3::olsr::MessageHeader::Tc [struct]
    module.add_class('Tc', import_from_module='ns.olsr', outer_class=root_module['ns3::olsr::MessageHeader'])
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::MprSelectorTuple [struct]
    module.add_class('MprSelectorTuple', import_from_module='ns.olsr')
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::NeighborTuple [struct]
    module.add_class('NeighborTuple', import_from_module='ns.olsr')
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::NeighborTuple::Status [enumeration]
    module.add_enum('Status', ['STATUS_NOT_SYM', 'STATUS_SYM'], outer_class=root_module['ns3::olsr::NeighborTuple'], import_from_module='ns.olsr')
    ## olsr-header.h (module 'olsr'): ns3::olsr::PacketHeader [class]
    module.add_class('PacketHeader', import_from_module='ns.olsr', parent=root_module['ns3::Header'])
    ## olsr-routing-protocol.h (module 'olsr'): ns3::olsr::RoutingProtocol [class]
    module.add_class('RoutingProtocol', import_from_module='ns.olsr', parent=root_module['ns3::Ipv4RoutingProtocol'])
    ## olsr-routing-protocol.h (module 'olsr'): ns3::olsr::RoutingTableEntry [struct]
    module.add_class('RoutingTableEntry', import_from_module='ns.olsr')
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::TopologyTuple [struct]
    module.add_class('TopologyTuple', import_from_module='ns.olsr')
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::TwoHopNeighborTuple [struct]
    module.add_class('TwoHopNeighborTuple', import_from_module='ns.olsr')
    module.add_container('std::vector< ns3::olsr::MessageHeader::Hello::LinkMessage >', 'ns3::olsr::MessageHeader::Hello::LinkMessage', container_type='vector')
    module.add_container('std::vector< ns3::olsr::MessageHeader::Hna::Association >', 'ns3::olsr::MessageHeader::Hna::Association', container_type='vector')
    module.add_container('std::vector< ns3::olsr::RoutingTableEntry >', 'ns3::olsr::RoutingTableEntry', container_type='vector')
    module.add_container('std::set< unsigned int >', 'unsigned int', container_type='set')
    typehandlers.add_type_alias('std::vector< ns3::olsr::DuplicateTuple, std::allocator< ns3::olsr::DuplicateTuple > >', 'ns3::olsr::DuplicateSet')
    typehandlers.add_type_alias('std::vector< ns3::olsr::DuplicateTuple, std::allocator< ns3::olsr::DuplicateTuple > >*', 'ns3::olsr::DuplicateSet*')
    typehandlers.add_type_alias('std::vector< ns3::olsr::DuplicateTuple, std::allocator< ns3::olsr::DuplicateTuple > >&', 'ns3::olsr::DuplicateSet&')
    typehandlers.add_type_alias('std::set< ns3::Ipv4Address, std::less< ns3::Ipv4Address >, std::allocator< ns3::Ipv4Address > >', 'ns3::olsr::MprSet')
    typehandlers.add_type_alias('std::set< ns3::Ipv4Address, std::less< ns3::Ipv4Address >, std::allocator< ns3::Ipv4Address > >*', 'ns3::olsr::MprSet*')
    typehandlers.add_type_alias('std::set< ns3::Ipv4Address, std::less< ns3::Ipv4Address >, std::allocator< ns3::Ipv4Address > >&', 'ns3::olsr::MprSet&')
    typehandlers.add_type_alias('std::vector< ns3::olsr::MprSelectorTuple, std::allocator< ns3::olsr::MprSelectorTuple > >', 'ns3::olsr::MprSelectorSet')
    typehandlers.add_type_alias('std::vector< ns3::olsr::MprSelectorTuple, std::allocator< ns3::olsr::MprSelectorTuple > >*', 'ns3::olsr::MprSelectorSet*')
    typehandlers.add_type_alias('std::vector< ns3::olsr::MprSelectorTuple, std::allocator< ns3::olsr::MprSelectorTuple > >&', 'ns3::olsr::MprSelectorSet&')
    typehandlers.add_type_alias('std::vector< ns3::olsr::TopologyTuple, std::allocator< ns3::olsr::TopologyTuple > >', 'ns3::olsr::TopologySet')
    typehandlers.add_type_alias('std::vector< ns3::olsr::TopologyTuple, std::allocator< ns3::olsr::TopologyTuple > >*', 'ns3::olsr::TopologySet*')
    typehandlers.add_type_alias('std::vector< ns3::olsr::TopologyTuple, std::allocator< ns3::olsr::TopologyTuple > >&', 'ns3::olsr::TopologySet&')
    typehandlers.add_type_alias('std::vector< ns3::olsr::MessageHeader, std::allocator< ns3::olsr::MessageHeader > >', 'ns3::olsr::MessageList')
    typehandlers.add_type_alias('std::vector< ns3::olsr::MessageHeader, std::allocator< ns3::olsr::MessageHeader > >*', 'ns3::olsr::MessageList*')
    typehandlers.add_type_alias('std::vector< ns3::olsr::MessageHeader, std::allocator< ns3::olsr::MessageHeader > >&', 'ns3::olsr::MessageList&')
    typehandlers.add_type_alias('std::vector< ns3::olsr::Association, std::allocator< ns3::olsr::Association > >', 'ns3::olsr::Associations')
    typehandlers.add_type_alias('std::vector< ns3::olsr::Association, std::allocator< ns3::olsr::Association > >*', 'ns3::olsr::Associations*')
    typehandlers.add_type_alias('std::vector< ns3::olsr::Association, std::allocator< ns3::olsr::Association > >&', 'ns3::olsr::Associations&')
    typehandlers.add_type_alias('std::vector< ns3::olsr::IfaceAssocTuple, std::allocator< ns3::olsr::IfaceAssocTuple > >', 'ns3::olsr::IfaceAssocSet')
    typehandlers.add_type_alias('std::vector< ns3::olsr::IfaceAssocTuple, std::allocator< ns3::olsr::IfaceAssocTuple > >*', 'ns3::olsr::IfaceAssocSet*')
    typehandlers.add_type_alias('std::vector< ns3::olsr::IfaceAssocTuple, std::allocator< ns3::olsr::IfaceAssocTuple > >&', 'ns3::olsr::IfaceAssocSet&')
    typehandlers.add_type_alias('std::vector< ns3::olsr::NeighborTuple, std::allocator< ns3::olsr::NeighborTuple > >', 'ns3::olsr::NeighborSet')
    typehandlers.add_type_alias('std::vector< ns3::olsr::NeighborTuple, std::allocator< ns3::olsr::NeighborTuple > >*', 'ns3::olsr::NeighborSet*')
    typehandlers.add_type_alias('std::vector< ns3::olsr::NeighborTuple, std::allocator< ns3::olsr::NeighborTuple > >&', 'ns3::olsr::NeighborSet&')
    typehandlers.add_type_alias('std::vector< ns3::olsr::AssociationTuple, std::allocator< ns3::olsr::AssociationTuple > >', 'ns3::olsr::AssociationSet')
    typehandlers.add_type_alias('std::vector< ns3::olsr::AssociationTuple, std::allocator< ns3::olsr::AssociationTuple > >*', 'ns3::olsr::AssociationSet*')
    typehandlers.add_type_alias('std::vector< ns3::olsr::AssociationTuple, std::allocator< ns3::olsr::AssociationTuple > >&', 'ns3::olsr::AssociationSet&')
    typehandlers.add_type_alias('std::vector< ns3::olsr::TwoHopNeighborTuple, std::allocator< ns3::olsr::TwoHopNeighborTuple > >', 'ns3::olsr::TwoHopNeighborSet')
    typehandlers.add_type_alias('std::vector< ns3::olsr::TwoHopNeighborTuple, std::allocator< ns3::olsr::TwoHopNeighborTuple > >*', 'ns3::olsr::TwoHopNeighborSet*')
    typehandlers.add_type_alias('std::vector< ns3::olsr::TwoHopNeighborTuple, std::allocator< ns3::olsr::TwoHopNeighborTuple > >&', 'ns3::olsr::TwoHopNeighborSet&')
    typehandlers.add_type_alias('std::vector< ns3::olsr::LinkTuple, std::allocator< ns3::olsr::LinkTuple > >', 'ns3::olsr::LinkSet')
    typehandlers.add_type_alias('std::vector< ns3::olsr::LinkTuple, std::allocator< ns3::olsr::LinkTuple > >*', 'ns3::olsr::LinkSet*')
    typehandlers.add_type_alias('std::vector< ns3::olsr::LinkTuple, std::allocator< ns3::olsr::LinkTuple > >&', 'ns3::olsr::LinkSet&')

def register_types_ns3_pimdm(module):
    root_module = module.get_root()
    
    ## pimdm-common.h (module 'pimdm'): ns3::pimdm::AssertWinnerState [enumeration]
    module.add_enum('AssertWinnerState', ['Assert_NoInfo', 'Assert_Loser', 'Assert_Winner'])
    ## pimdm-common.h (module 'pimdm'): ns3::pimdm::Origination [enumeration]
    module.add_enum('Origination', ['NotOriginator', 'Originator'])
    ## pimdm-common.h (module 'pimdm'): ns3::pimdm::GraftPruneState [enumeration]
    module.add_enum('GraftPruneState', ['GP_NoInfo', 'GP_Pruned', 'GP_Forwarding', 'GP_AckPending'])
    ## pimdm-common.h (module 'pimdm'): ns3::pimdm::AddressFamily [enumeration]
    module.add_enum('AddressFamily', ['AF_Reserved', 'AF_IPv4', 'AF_IPv6', 'AF_NSAP', 'AF_HDLC', 'AF_BBN_1822', 'AF_A802', 'AF_E163', 'AF_E164', 'AF_F69', 'AF_X121', 'AF_IPX', 'AF_Appletalk', 'AF_DecnetIV', 'AF_BanyanVines', 'AF_E164N'])
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMType [enumeration]
    module.add_enum('PIMType', ['PIM_HELLO', 'PIM_JP', 'PIM_ASSERT', 'PIM_GRAFT', 'PIM_GRAFT_ACK', 'PIM_STATE_REF'])
    ## pimdm-common.h (module 'pimdm'): ns3::pimdm::LocalMembership [enumeration]
    module.add_enum('LocalMembership', ['Local_NoInfo', 'Local_Include'])
    ## pimdm-common.h (module 'pimdm'): ns3::pimdm::PruneState [enumeration]
    module.add_enum('PruneState', ['Prune_NoInfo', 'Prune_Pruned', 'Prune_PrunePending'])
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::AssertMetric [struct]
    module.add_class('AssertMetric')
    ## pimdm-routing.h (module 'pimdm'): ns3::pimdm::IdTag [struct]
    module.add_class('IdTag', parent=root_module['ns3::Tag'])
    ## pimdm-routing.h (module 'pimdm'): ns3::pimdm::MulticastEntry [struct]
    module.add_class('MulticastEntry')
    ## pimdm-routing.h (module 'pimdm'): ns3::pimdm::MulticastRoutingProtocol [class]
    module.add_class('MulticastRoutingProtocol', parent=root_module['ns3::Ipv4RoutingProtocol'])
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::NeighborState [struct]
    module.add_class('NeighborState')
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::NeighborhoodStatus [struct]
    module.add_class('NeighborhoodStatus')
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader [class]
    module.add_class('PIMHeader', parent=root_module['ns3::Header'])
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::AssertMessage [struct]
    module.add_class('AssertMessage', outer_class=root_module['ns3::pimdm::PIMHeader'])
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::EncodedGroup [struct]
    module.add_class('EncodedGroup', outer_class=root_module['ns3::pimdm::PIMHeader'])
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::EncodedSource [struct]
    module.add_class('EncodedSource', outer_class=root_module['ns3::pimdm::PIMHeader'])
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::EncodedUnicast [struct]
    module.add_class('EncodedUnicast', outer_class=root_module['ns3::pimdm::PIMHeader'])
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::GraftAckMessage [struct]
    module.add_class('GraftAckMessage', outer_class=root_module['ns3::pimdm::PIMHeader'])
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::GraftMessage [struct]
    module.add_class('GraftMessage', outer_class=root_module['ns3::pimdm::PIMHeader'])
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::HelloMessage [struct]
    module.add_class('HelloMessage', outer_class=root_module['ns3::pimdm::PIMHeader'])
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::HelloMessage::OptionType [enumeration]
    module.add_enum('OptionType', ['Reserved', 'HelloHoldTime', 'LANPruneDelay', 'AssignedIANA', 'GenerationID', 'StateRefreshCapable', 'BidirCapable'], outer_class=root_module['ns3::pimdm::PIMHeader::HelloMessage'])
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::HelloMessage::HelloEntry [struct]
    module.add_class('HelloEntry', outer_class=root_module['ns3::pimdm::PIMHeader::HelloMessage'])
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::HelloMessage::HelloEntry::GenerationID [struct]
    module.add_class('GenerationID', outer_class=root_module['ns3::pimdm::PIMHeader::HelloMessage::HelloEntry'])
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::HelloMessage::HelloEntry::HoldTime [struct]
    module.add_class('HoldTime', outer_class=root_module['ns3::pimdm::PIMHeader::HelloMessage::HelloEntry'])
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::HelloMessage::HelloEntry::LanPruneDelay [struct]
    module.add_class('LanPruneDelay', outer_class=root_module['ns3::pimdm::PIMHeader::HelloMessage::HelloEntry'])
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::HelloMessage::HelloEntry::StateRefreshCapable [struct]
    module.add_class('StateRefreshCapable', outer_class=root_module['ns3::pimdm::PIMHeader::HelloMessage::HelloEntry'])
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::JoinPruneGraftMessage [struct]
    module.add_class('JoinPruneGraftMessage', outer_class=root_module['ns3::pimdm::PIMHeader'])
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::JoinPruneMessage [struct]
    module.add_class('JoinPruneMessage', outer_class=root_module['ns3::pimdm::PIMHeader'])
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::MulticastGroupEntry [struct]
    module.add_class('MulticastGroupEntry', outer_class=root_module['ns3::pimdm::PIMHeader'])
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::StateRefreshMessage [struct]
    module.add_class('StateRefreshMessage', outer_class=root_module['ns3::pimdm::PIMHeader'])
    ## pimdm-routing.h (module 'pimdm'): ns3::pimdm::RelayTag [struct]
    module.add_class('RelayTag', parent=root_module['ns3::Tag'])
    ## pimdm-routing.h (module 'pimdm'): ns3::pimdm::RoutingMulticastTable [struct]
    module.add_class('RoutingMulticastTable')
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::SourceGroupPair [struct]
    module.add_class('SourceGroupPair')
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::SourceGroupState [struct]
    module.add_class('SourceGroupState')
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::UpstreamState [struct]
    module.add_class('UpstreamState')
    module.add_container('std::vector< ns3::pimdm::RoutingMulticastTable >', 'ns3::pimdm::RoutingMulticastTable', container_type='vector')
    module.add_container('ns3::pimdm::NeighborList', 'ns3::pimdm::NeighborState', container_type='list')
    module.add_container('std::vector< ns3::pimdm::PIMHeader::EncodedSource >', 'ns3::pimdm::PIMHeader::EncodedSource', container_type='vector')
    module.add_container('std::vector< ns3::pimdm::PIMHeader::HelloMessage::HelloEntry >', 'ns3::pimdm::PIMHeader::HelloMessage::HelloEntry', container_type='vector')
    module.add_container('std::vector< ns3::pimdm::PIMHeader::MulticastGroupEntry >', 'ns3::pimdm::PIMHeader::MulticastGroupEntry', container_type='vector')
    module.add_container('std::map< ns3::Ipv4Address, ns3::pimdm::MulticastEntry >', ('ns3::Ipv4Address', 'ns3::pimdm::MulticastEntry'), container_type='map')
    typehandlers.add_type_alias('std::list< ns3::pimdm::NeighborState, std::allocator< ns3::pimdm::NeighborState > >', 'ns3::pimdm::NeighborList')
    typehandlers.add_type_alias('std::list< ns3::pimdm::NeighborState, std::allocator< ns3::pimdm::NeighborState > >*', 'ns3::pimdm::NeighborList*')
    typehandlers.add_type_alias('std::list< ns3::pimdm::NeighborState, std::allocator< ns3::pimdm::NeighborState > >&', 'ns3::pimdm::NeighborList&')
    typehandlers.add_type_alias('std::pair< unsigned int, ns3::Ipv4Address >', 'ns3::pimdm::WiredEquivalentInterface')
    typehandlers.add_type_alias('std::pair< unsigned int, ns3::Ipv4Address >*', 'ns3::pimdm::WiredEquivalentInterface*')
    typehandlers.add_type_alias('std::pair< unsigned int, ns3::Ipv4Address >&', 'ns3::pimdm::WiredEquivalentInterface&')
    typehandlers.add_type_alias('std::vector< ns3::pimdm::PIMHeader, std::allocator< ns3::pimdm::PIMHeader > >', 'ns3::pimdm::PIMMessageList')
    typehandlers.add_type_alias('std::vector< ns3::pimdm::PIMHeader, std::allocator< ns3::pimdm::PIMHeader > >*', 'ns3::pimdm::PIMMessageList*')
    typehandlers.add_type_alias('std::vector< ns3::pimdm::PIMHeader, std::allocator< ns3::pimdm::PIMHeader > >&', 'ns3::pimdm::PIMMessageList&')
    typehandlers.add_type_alias('std::list< ns3::pimdm::SourceGroupState, std::allocator< ns3::pimdm::SourceGroupState > >', 'ns3::pimdm::SourceGroupList')
    typehandlers.add_type_alias('std::list< ns3::pimdm::SourceGroupState, std::allocator< ns3::pimdm::SourceGroupState > >*', 'ns3::pimdm::SourceGroupList*')
    typehandlers.add_type_alias('std::list< ns3::pimdm::SourceGroupState, std::allocator< ns3::pimdm::SourceGroupState > >&', 'ns3::pimdm::SourceGroupList&')

def register_methods(root_module):
    register_Ns3Address_methods(root_module, root_module['ns3::Address'])
    register_Ns3AttributeConstructionList_methods(root_module, root_module['ns3::AttributeConstructionList'])
    register_Ns3AttributeConstructionListItem_methods(root_module, root_module['ns3::AttributeConstructionList::Item'])
    register_Ns3Buffer_methods(root_module, root_module['ns3::Buffer'])
    register_Ns3BufferIterator_methods(root_module, root_module['ns3::Buffer::Iterator'])
    register_Ns3ByteTagIterator_methods(root_module, root_module['ns3::ByteTagIterator'])
    register_Ns3ByteTagIteratorItem_methods(root_module, root_module['ns3::ByteTagIterator::Item'])
    register_Ns3ByteTagList_methods(root_module, root_module['ns3::ByteTagList'])
    register_Ns3ByteTagListIterator_methods(root_module, root_module['ns3::ByteTagList::Iterator'])
    register_Ns3ByteTagListIteratorItem_methods(root_module, root_module['ns3::ByteTagList::Iterator::Item'])
    register_Ns3CallbackBase_methods(root_module, root_module['ns3::CallbackBase'])
    register_Ns3EventGarbageCollector_methods(root_module, root_module['ns3::EventGarbageCollector'])
    register_Ns3EventId_methods(root_module, root_module['ns3::EventId'])
    register_Ns3Gnuplot_methods(root_module, root_module['ns3::Gnuplot'])
    register_Ns3GnuplotCollection_methods(root_module, root_module['ns3::GnuplotCollection'])
    register_Ns3GnuplotDataset_methods(root_module, root_module['ns3::GnuplotDataset'])
    register_Ns3IntToType__0_methods(root_module, root_module['ns3::IntToType< 0 >'])
    register_Ns3IntToType__1_methods(root_module, root_module['ns3::IntToType< 1 >'])
    register_Ns3IntToType__2_methods(root_module, root_module['ns3::IntToType< 2 >'])
    register_Ns3IntToType__3_methods(root_module, root_module['ns3::IntToType< 3 >'])
    register_Ns3IntToType__4_methods(root_module, root_module['ns3::IntToType< 4 >'])
    register_Ns3IntToType__5_methods(root_module, root_module['ns3::IntToType< 5 >'])
    register_Ns3IntToType__6_methods(root_module, root_module['ns3::IntToType< 6 >'])
    register_Ns3Ipv4Address_methods(root_module, root_module['ns3::Ipv4Address'])
    register_Ns3Ipv4InterfaceAddress_methods(root_module, root_module['ns3::Ipv4InterfaceAddress'])
    register_Ns3Ipv4Mask_methods(root_module, root_module['ns3::Ipv4Mask'])
    register_Ns3Ipv4RoutingHelper_methods(root_module, root_module['ns3::Ipv4RoutingHelper'])
    register_Ns3Ipv6Address_methods(root_module, root_module['ns3::Ipv6Address'])
    register_Ns3Ipv6InterfaceAddress_methods(root_module, root_module['ns3::Ipv6InterfaceAddress'])
    register_Ns3Ipv6Prefix_methods(root_module, root_module['ns3::Ipv6Prefix'])
    register_Ns3LogComponent_methods(root_module, root_module['ns3::LogComponent'])
    register_Ns3Mac48Address_methods(root_module, root_module['ns3::Mac48Address'])
    register_Ns3NodeContainer_methods(root_module, root_module['ns3::NodeContainer'])
    register_Ns3ObjectBase_methods(root_module, root_module['ns3::ObjectBase'])
    register_Ns3ObjectDeleter_methods(root_module, root_module['ns3::ObjectDeleter'])
    register_Ns3ObjectFactory_methods(root_module, root_module['ns3::ObjectFactory'])
    register_Ns3OlsrState_methods(root_module, root_module['ns3::OlsrState'])
    register_Ns3PacketMetadata_methods(root_module, root_module['ns3::PacketMetadata'])
    register_Ns3PacketMetadataItem_methods(root_module, root_module['ns3::PacketMetadata::Item'])
    register_Ns3PacketMetadataItemIterator_methods(root_module, root_module['ns3::PacketMetadata::ItemIterator'])
    register_Ns3PacketTagIterator_methods(root_module, root_module['ns3::PacketTagIterator'])
    register_Ns3PacketTagIteratorItem_methods(root_module, root_module['ns3::PacketTagIterator::Item'])
    register_Ns3PacketTagList_methods(root_module, root_module['ns3::PacketTagList'])
    register_Ns3PacketTagListTagData_methods(root_module, root_module['ns3::PacketTagList::TagData'])
    register_Ns3PimDmHelper_methods(root_module, root_module['ns3::PimDmHelper'])
    register_Ns3RandomVariable_methods(root_module, root_module['ns3::RandomVariable'])
    register_Ns3RngSeedManager_methods(root_module, root_module['ns3::RngSeedManager'])
    register_Ns3SequentialVariable_methods(root_module, root_module['ns3::SequentialVariable'])
    register_Ns3SimpleRefCount__Ns3Object_Ns3ObjectBase_Ns3ObjectDeleter_methods(root_module, root_module['ns3::SimpleRefCount< ns3::Object, ns3::ObjectBase, ns3::ObjectDeleter >'])
    register_Ns3Simulator_methods(root_module, root_module['ns3::Simulator'])
    register_Ns3SystemWallClockMs_methods(root_module, root_module['ns3::SystemWallClockMs'])
    register_Ns3Tag_methods(root_module, root_module['ns3::Tag'])
    register_Ns3TagBuffer_methods(root_module, root_module['ns3::TagBuffer'])
    register_Ns3Timer_methods(root_module, root_module['ns3::Timer'])
    register_Ns3TimerImpl_methods(root_module, root_module['ns3::TimerImpl'])
    register_Ns3TriangularVariable_methods(root_module, root_module['ns3::TriangularVariable'])
    register_Ns3TypeId_methods(root_module, root_module['ns3::TypeId'])
    register_Ns3TypeIdAttributeInformation_methods(root_module, root_module['ns3::TypeId::AttributeInformation'])
    register_Ns3TypeIdTraceSourceInformation_methods(root_module, root_module['ns3::TypeId::TraceSourceInformation'])
    register_Ns3UniformVariable_methods(root_module, root_module['ns3::UniformVariable'])
    register_Ns3WeibullVariable_methods(root_module, root_module['ns3::WeibullVariable'])
    register_Ns3ZetaVariable_methods(root_module, root_module['ns3::ZetaVariable'])
    register_Ns3ZipfVariable_methods(root_module, root_module['ns3::ZipfVariable'])
    register_Ns3Empty_methods(root_module, root_module['ns3::empty'])
    register_Ns3Int64x64_t_methods(root_module, root_module['ns3::int64x64_t'])
    register_Ns3Chunk_methods(root_module, root_module['ns3::Chunk'])
    register_Ns3ConstantVariable_methods(root_module, root_module['ns3::ConstantVariable'])
    register_Ns3DeterministicVariable_methods(root_module, root_module['ns3::DeterministicVariable'])
    register_Ns3EmpiricalVariable_methods(root_module, root_module['ns3::EmpiricalVariable'])
    register_Ns3ErlangVariable_methods(root_module, root_module['ns3::ErlangVariable'])
    register_Ns3ExponentialVariable_methods(root_module, root_module['ns3::ExponentialVariable'])
    register_Ns3GammaVariable_methods(root_module, root_module['ns3::GammaVariable'])
    register_Ns3Gnuplot2dDataset_methods(root_module, root_module['ns3::Gnuplot2dDataset'])
    register_Ns3Gnuplot2dFunction_methods(root_module, root_module['ns3::Gnuplot2dFunction'])
    register_Ns3Gnuplot3dDataset_methods(root_module, root_module['ns3::Gnuplot3dDataset'])
    register_Ns3Gnuplot3dFunction_methods(root_module, root_module['ns3::Gnuplot3dFunction'])
    register_Ns3Header_methods(root_module, root_module['ns3::Header'])
    register_Ns3IntEmpiricalVariable_methods(root_module, root_module['ns3::IntEmpiricalVariable'])
    register_Ns3Ipv4Header_methods(root_module, root_module['ns3::Ipv4Header'])
    register_Ns3Ipv6Header_methods(root_module, root_module['ns3::Ipv6Header'])
    register_Ns3LogNormalVariable_methods(root_module, root_module['ns3::LogNormalVariable'])
    register_Ns3NormalVariable_methods(root_module, root_module['ns3::NormalVariable'])
    register_Ns3Object_methods(root_module, root_module['ns3::Object'])
    register_Ns3ObjectAggregateIterator_methods(root_module, root_module['ns3::Object::AggregateIterator'])
    register_Ns3ParetoVariable_methods(root_module, root_module['ns3::ParetoVariable'])
    register_Ns3RandomVariableStream_methods(root_module, root_module['ns3::RandomVariableStream'])
    register_Ns3SequentialRandomVariable_methods(root_module, root_module['ns3::SequentialRandomVariable'])
    register_Ns3SimpleRefCount__Ns3AttributeAccessor_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeAccessor__gt___methods(root_module, root_module['ns3::SimpleRefCount< ns3::AttributeAccessor, ns3::empty, ns3::DefaultDeleter<ns3::AttributeAccessor> >'])
    register_Ns3SimpleRefCount__Ns3AttributeChecker_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeChecker__gt___methods(root_module, root_module['ns3::SimpleRefCount< ns3::AttributeChecker, ns3::empty, ns3::DefaultDeleter<ns3::AttributeChecker> >'])
    register_Ns3SimpleRefCount__Ns3AttributeValue_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeValue__gt___methods(root_module, root_module['ns3::SimpleRefCount< ns3::AttributeValue, ns3::empty, ns3::DefaultDeleter<ns3::AttributeValue> >'])
    register_Ns3SimpleRefCount__Ns3CallbackImplBase_Ns3Empty_Ns3DefaultDeleter__lt__ns3CallbackImplBase__gt___methods(root_module, root_module['ns3::SimpleRefCount< ns3::CallbackImplBase, ns3::empty, ns3::DefaultDeleter<ns3::CallbackImplBase> >'])
    register_Ns3SimpleRefCount__Ns3EventImpl_Ns3Empty_Ns3DefaultDeleter__lt__ns3EventImpl__gt___methods(root_module, root_module['ns3::SimpleRefCount< ns3::EventImpl, ns3::empty, ns3::DefaultDeleter<ns3::EventImpl> >'])
    register_Ns3SimpleRefCount__Ns3Ipv4MulticastRoute_Ns3Empty_Ns3DefaultDeleter__lt__ns3Ipv4MulticastRoute__gt___methods(root_module, root_module['ns3::SimpleRefCount< ns3::Ipv4MulticastRoute, ns3::empty, ns3::DefaultDeleter<ns3::Ipv4MulticastRoute> >'])
    register_Ns3SimpleRefCount__Ns3Ipv4Route_Ns3Empty_Ns3DefaultDeleter__lt__ns3Ipv4Route__gt___methods(root_module, root_module['ns3::SimpleRefCount< ns3::Ipv4Route, ns3::empty, ns3::DefaultDeleter<ns3::Ipv4Route> >'])
    register_Ns3SimpleRefCount__Ns3NixVector_Ns3Empty_Ns3DefaultDeleter__lt__ns3NixVector__gt___methods(root_module, root_module['ns3::SimpleRefCount< ns3::NixVector, ns3::empty, ns3::DefaultDeleter<ns3::NixVector> >'])
    register_Ns3SimpleRefCount__Ns3OutputStreamWrapper_Ns3Empty_Ns3DefaultDeleter__lt__ns3OutputStreamWrapper__gt___methods(root_module, root_module['ns3::SimpleRefCount< ns3::OutputStreamWrapper, ns3::empty, ns3::DefaultDeleter<ns3::OutputStreamWrapper> >'])
    register_Ns3SimpleRefCount__Ns3Packet_Ns3Empty_Ns3DefaultDeleter__lt__ns3Packet__gt___methods(root_module, root_module['ns3::SimpleRefCount< ns3::Packet, ns3::empty, ns3::DefaultDeleter<ns3::Packet> >'])
    register_Ns3SimpleRefCount__Ns3TraceSourceAccessor_Ns3Empty_Ns3DefaultDeleter__lt__ns3TraceSourceAccessor__gt___methods(root_module, root_module['ns3::SimpleRefCount< ns3::TraceSourceAccessor, ns3::empty, ns3::DefaultDeleter<ns3::TraceSourceAccessor> >'])
    register_Ns3Socket_methods(root_module, root_module['ns3::Socket'])
    register_Ns3SocketAddressTag_methods(root_module, root_module['ns3::SocketAddressTag'])
    register_Ns3SocketIpTtlTag_methods(root_module, root_module['ns3::SocketIpTtlTag'])
    register_Ns3SocketSetDontFragmentTag_methods(root_module, root_module['ns3::SocketSetDontFragmentTag'])
    register_Ns3Time_methods(root_module, root_module['ns3::Time'])
    register_Ns3TraceSourceAccessor_methods(root_module, root_module['ns3::TraceSourceAccessor'])
    register_Ns3Trailer_methods(root_module, root_module['ns3::Trailer'])
    register_Ns3TriangularRandomVariable_methods(root_module, root_module['ns3::TriangularRandomVariable'])
    register_Ns3UniformRandomVariable_methods(root_module, root_module['ns3::UniformRandomVariable'])
    register_Ns3WeibullRandomVariable_methods(root_module, root_module['ns3::WeibullRandomVariable'])
    register_Ns3WifiMacHeader_methods(root_module, root_module['ns3::WifiMacHeader'])
    register_Ns3ZetaRandomVariable_methods(root_module, root_module['ns3::ZetaRandomVariable'])
    register_Ns3ZipfRandomVariable_methods(root_module, root_module['ns3::ZipfRandomVariable'])
    register_Ns3ArpCache_methods(root_module, root_module['ns3::ArpCache'])
    register_Ns3ArpCacheEntry_methods(root_module, root_module['ns3::ArpCache::Entry'])
    register_Ns3AttributeAccessor_methods(root_module, root_module['ns3::AttributeAccessor'])
    register_Ns3AttributeChecker_methods(root_module, root_module['ns3::AttributeChecker'])
    register_Ns3AttributeValue_methods(root_module, root_module['ns3::AttributeValue'])
    register_Ns3CallbackChecker_methods(root_module, root_module['ns3::CallbackChecker'])
    register_Ns3CallbackImplBase_methods(root_module, root_module['ns3::CallbackImplBase'])
    register_Ns3CallbackValue_methods(root_module, root_module['ns3::CallbackValue'])
    register_Ns3ConstantRandomVariable_methods(root_module, root_module['ns3::ConstantRandomVariable'])
    register_Ns3DeterministicRandomVariable_methods(root_module, root_module['ns3::DeterministicRandomVariable'])
    register_Ns3EmpiricalRandomVariable_methods(root_module, root_module['ns3::EmpiricalRandomVariable'])
    register_Ns3EmptyAttributeValue_methods(root_module, root_module['ns3::EmptyAttributeValue'])
    register_Ns3EnumChecker_methods(root_module, root_module['ns3::EnumChecker'])
    register_Ns3EnumValue_methods(root_module, root_module['ns3::EnumValue'])
    register_Ns3ErlangRandomVariable_methods(root_module, root_module['ns3::ErlangRandomVariable'])
    register_Ns3EventImpl_methods(root_module, root_module['ns3::EventImpl'])
    register_Ns3ExponentialRandomVariable_methods(root_module, root_module['ns3::ExponentialRandomVariable'])
    register_Ns3GammaRandomVariable_methods(root_module, root_module['ns3::GammaRandomVariable'])
    register_Ns3IpL4Protocol_methods(root_module, root_module['ns3::IpL4Protocol'])
    register_Ns3Ipv4_methods(root_module, root_module['ns3::Ipv4'])
    register_Ns3Ipv4AddressChecker_methods(root_module, root_module['ns3::Ipv4AddressChecker'])
    register_Ns3Ipv4AddressValue_methods(root_module, root_module['ns3::Ipv4AddressValue'])
    register_Ns3Ipv4Interface_methods(root_module, root_module['ns3::Ipv4Interface'])
    register_Ns3Ipv4L3Protocol_methods(root_module, root_module['ns3::Ipv4L3Protocol'])
    register_Ns3Ipv4MaskChecker_methods(root_module, root_module['ns3::Ipv4MaskChecker'])
    register_Ns3Ipv4MaskValue_methods(root_module, root_module['ns3::Ipv4MaskValue'])
    register_Ns3Ipv4MulticastRoute_methods(root_module, root_module['ns3::Ipv4MulticastRoute'])
    register_Ns3Ipv4Route_methods(root_module, root_module['ns3::Ipv4Route'])
    register_Ns3Ipv4RoutingProtocol_methods(root_module, root_module['ns3::Ipv4RoutingProtocol'])
    register_Ns3Ipv4StaticRouting_methods(root_module, root_module['ns3::Ipv4StaticRouting'])
    register_Ns3Ipv6AddressChecker_methods(root_module, root_module['ns3::Ipv6AddressChecker'])
    register_Ns3Ipv6AddressValue_methods(root_module, root_module['ns3::Ipv6AddressValue'])
    register_Ns3Ipv6Interface_methods(root_module, root_module['ns3::Ipv6Interface'])
    register_Ns3Ipv6PrefixChecker_methods(root_module, root_module['ns3::Ipv6PrefixChecker'])
    register_Ns3Ipv6PrefixValue_methods(root_module, root_module['ns3::Ipv6PrefixValue'])
    register_Ns3LogNormalRandomVariable_methods(root_module, root_module['ns3::LogNormalRandomVariable'])
    register_Ns3Mac48AddressChecker_methods(root_module, root_module['ns3::Mac48AddressChecker'])
    register_Ns3Mac48AddressValue_methods(root_module, root_module['ns3::Mac48AddressValue'])
    register_Ns3NetDevice_methods(root_module, root_module['ns3::NetDevice'])
    register_Ns3NixVector_methods(root_module, root_module['ns3::NixVector'])
    register_Ns3Node_methods(root_module, root_module['ns3::Node'])
    register_Ns3NormalRandomVariable_methods(root_module, root_module['ns3::NormalRandomVariable'])
    register_Ns3ObjectFactoryChecker_methods(root_module, root_module['ns3::ObjectFactoryChecker'])
    register_Ns3ObjectFactoryValue_methods(root_module, root_module['ns3::ObjectFactoryValue'])
    register_Ns3OutputStreamWrapper_methods(root_module, root_module['ns3::OutputStreamWrapper'])
    register_Ns3Packet_methods(root_module, root_module['ns3::Packet'])
    register_Ns3ParetoRandomVariable_methods(root_module, root_module['ns3::ParetoRandomVariable'])
    register_Ns3RandomVariableChecker_methods(root_module, root_module['ns3::RandomVariableChecker'])
    register_Ns3RandomVariableValue_methods(root_module, root_module['ns3::RandomVariableValue'])
    register_Ns3StringChecker_methods(root_module, root_module['ns3::StringChecker'])
    register_Ns3StringValue_methods(root_module, root_module['ns3::StringValue'])
    register_Ns3TimeChecker_methods(root_module, root_module['ns3::TimeChecker'])
    register_Ns3TimeValue_methods(root_module, root_module['ns3::TimeValue'])
    register_Ns3TypeIdChecker_methods(root_module, root_module['ns3::TypeIdChecker'])
    register_Ns3TypeIdValue_methods(root_module, root_module['ns3::TypeIdValue'])
    register_Ns3UintegerValue_methods(root_module, root_module['ns3::UintegerValue'])
    register_Ns3AddressChecker_methods(root_module, root_module['ns3::AddressChecker'])
    register_Ns3AddressValue_methods(root_module, root_module['ns3::AddressValue'])
    register_Ns3Ipv4ListRouting_methods(root_module, root_module['ns3::Ipv4ListRouting'])
    register_Ns3AodvDuplicatePacketDetection_methods(root_module, root_module['ns3::aodv::DuplicatePacketDetection'])
    register_Ns3AodvIdCache_methods(root_module, root_module['ns3::aodv::IdCache'])
    register_Ns3AodvNeighbors_methods(root_module, root_module['ns3::aodv::Neighbors'])
    register_Ns3AodvNeighborsNeighbor_methods(root_module, root_module['ns3::aodv::Neighbors::Neighbor'])
    register_Ns3AodvQueueEntry_methods(root_module, root_module['ns3::aodv::QueueEntry'])
    register_Ns3AodvRequestQueue_methods(root_module, root_module['ns3::aodv::RequestQueue'])
    register_Ns3AodvRerrHeader_methods(root_module, root_module['ns3::aodv::RerrHeader'])
    register_Ns3AodvRoutingProtocol_methods(root_module, root_module['ns3::aodv::RoutingProtocol'])
    register_Ns3AodvRoutingTable_methods(root_module, root_module['ns3::aodv::RoutingTable'])
    register_Ns3AodvRoutingTableEntry_methods(root_module, root_module['ns3::aodv::RoutingTableEntry'])
    register_Ns3AodvRrepAckHeader_methods(root_module, root_module['ns3::aodv::RrepAckHeader'])
    register_Ns3AodvRrepHeader_methods(root_module, root_module['ns3::aodv::RrepHeader'])
    register_Ns3AodvRreqHeader_methods(root_module, root_module['ns3::aodv::RreqHeader'])
    register_Ns3AodvTypeHeader_methods(root_module, root_module['ns3::aodv::TypeHeader'])
    register_Ns3DsdvDsdvHeader_methods(root_module, root_module['ns3::dsdv::DsdvHeader'])
    register_Ns3DsdvPacketQueue_methods(root_module, root_module['ns3::dsdv::PacketQueue'])
    register_Ns3DsdvQueueEntry_methods(root_module, root_module['ns3::dsdv::QueueEntry'])
    register_Ns3DsdvRoutingProtocol_methods(root_module, root_module['ns3::dsdv::RoutingProtocol'])
    register_Ns3DsdvRoutingTable_methods(root_module, root_module['ns3::dsdv::RoutingTable'])
    register_Ns3DsdvRoutingTableEntry_methods(root_module, root_module['ns3::dsdv::RoutingTableEntry'])
    register_Ns3MbnDuplicatePacketDetection_methods(root_module, root_module['ns3::mbn::DuplicatePacketDetection'])
    register_Ns3MbnHelloHeader_methods(root_module, root_module['ns3::mbn::HelloHeader'])
    register_Ns3MbnIdCache_methods(root_module, root_module['ns3::mbn::IdCache'])
    register_Ns3MbnNeighborPair_methods(root_module, root_module['ns3::mbn::NeighborPair'])
    register_Ns3MbnNeighborTriple_methods(root_module, root_module['ns3::mbn::NeighborTriple'])
    register_Ns3MbnNeighborTuple_methods(root_module, root_module['ns3::mbn::NeighborTuple'])
    register_Ns3MbnNeighbors_methods(root_module, root_module['ns3::mbn::Neighbors'])
    register_Ns3MbnQueueEntry_methods(root_module, root_module['ns3::mbn::QueueEntry'])
    register_Ns3MbnRequestQueue_methods(root_module, root_module['ns3::mbn::RequestQueue'])
    register_Ns3MbnRerrHeader_methods(root_module, root_module['ns3::mbn::RerrHeader'])
    register_Ns3MbnRoutingProtocol_methods(root_module, root_module['ns3::mbn::RoutingProtocol'])
    register_Ns3MbnRoutingTable_methods(root_module, root_module['ns3::mbn::RoutingTable'])
    register_Ns3MbnRoutingTableEntry_methods(root_module, root_module['ns3::mbn::RoutingTableEntry'])
    register_Ns3MbnRrepAckHeader_methods(root_module, root_module['ns3::mbn::RrepAckHeader'])
    register_Ns3MbnRrepHeader_methods(root_module, root_module['ns3::mbn::RrepHeader'])
    register_Ns3MbnRreqHeader_methods(root_module, root_module['ns3::mbn::RreqHeader'])
    register_Ns3MbnTwoHopBnNeighborTuple_methods(root_module, root_module['ns3::mbn::TwoHopBnNeighborTuple'])
    register_Ns3MbnTypeHeader_methods(root_module, root_module['ns3::mbn::TypeHeader'])
    register_Ns3OlsrAssociation_methods(root_module, root_module['ns3::olsr::Association'])
    register_Ns3OlsrAssociationTuple_methods(root_module, root_module['ns3::olsr::AssociationTuple'])
    register_Ns3OlsrDuplicateTuple_methods(root_module, root_module['ns3::olsr::DuplicateTuple'])
    register_Ns3OlsrIfaceAssocTuple_methods(root_module, root_module['ns3::olsr::IfaceAssocTuple'])
    register_Ns3OlsrLinkTuple_methods(root_module, root_module['ns3::olsr::LinkTuple'])
    register_Ns3OlsrMessageHeader_methods(root_module, root_module['ns3::olsr::MessageHeader'])
    register_Ns3OlsrMessageHeaderHello_methods(root_module, root_module['ns3::olsr::MessageHeader::Hello'])
    register_Ns3OlsrMessageHeaderHelloLinkMessage_methods(root_module, root_module['ns3::olsr::MessageHeader::Hello::LinkMessage'])
    register_Ns3OlsrMessageHeaderHna_methods(root_module, root_module['ns3::olsr::MessageHeader::Hna'])
    register_Ns3OlsrMessageHeaderHnaAssociation_methods(root_module, root_module['ns3::olsr::MessageHeader::Hna::Association'])
    register_Ns3OlsrMessageHeaderMid_methods(root_module, root_module['ns3::olsr::MessageHeader::Mid'])
    register_Ns3OlsrMessageHeaderTc_methods(root_module, root_module['ns3::olsr::MessageHeader::Tc'])
    register_Ns3OlsrMprSelectorTuple_methods(root_module, root_module['ns3::olsr::MprSelectorTuple'])
    register_Ns3OlsrNeighborTuple_methods(root_module, root_module['ns3::olsr::NeighborTuple'])
    register_Ns3OlsrPacketHeader_methods(root_module, root_module['ns3::olsr::PacketHeader'])
    register_Ns3OlsrRoutingProtocol_methods(root_module, root_module['ns3::olsr::RoutingProtocol'])
    register_Ns3OlsrRoutingTableEntry_methods(root_module, root_module['ns3::olsr::RoutingTableEntry'])
    register_Ns3OlsrTopologyTuple_methods(root_module, root_module['ns3::olsr::TopologyTuple'])
    register_Ns3OlsrTwoHopNeighborTuple_methods(root_module, root_module['ns3::olsr::TwoHopNeighborTuple'])
    register_Ns3PimdmAssertMetric_methods(root_module, root_module['ns3::pimdm::AssertMetric'])
    register_Ns3PimdmIdTag_methods(root_module, root_module['ns3::pimdm::IdTag'])
    register_Ns3PimdmMulticastEntry_methods(root_module, root_module['ns3::pimdm::MulticastEntry'])
    register_Ns3PimdmMulticastRoutingProtocol_methods(root_module, root_module['ns3::pimdm::MulticastRoutingProtocol'])
    register_Ns3PimdmNeighborState_methods(root_module, root_module['ns3::pimdm::NeighborState'])
    register_Ns3PimdmNeighborhoodStatus_methods(root_module, root_module['ns3::pimdm::NeighborhoodStatus'])
    register_Ns3PimdmPIMHeader_methods(root_module, root_module['ns3::pimdm::PIMHeader'])
    register_Ns3PimdmPIMHeaderAssertMessage_methods(root_module, root_module['ns3::pimdm::PIMHeader::AssertMessage'])
    register_Ns3PimdmPIMHeaderEncodedGroup_methods(root_module, root_module['ns3::pimdm::PIMHeader::EncodedGroup'])
    register_Ns3PimdmPIMHeaderEncodedSource_methods(root_module, root_module['ns3::pimdm::PIMHeader::EncodedSource'])
    register_Ns3PimdmPIMHeaderEncodedUnicast_methods(root_module, root_module['ns3::pimdm::PIMHeader::EncodedUnicast'])
    register_Ns3PimdmPIMHeaderGraftAckMessage_methods(root_module, root_module['ns3::pimdm::PIMHeader::GraftAckMessage'])
    register_Ns3PimdmPIMHeaderGraftMessage_methods(root_module, root_module['ns3::pimdm::PIMHeader::GraftMessage'])
    register_Ns3PimdmPIMHeaderHelloMessage_methods(root_module, root_module['ns3::pimdm::PIMHeader::HelloMessage'])
    register_Ns3PimdmPIMHeaderHelloMessageHelloEntry_methods(root_module, root_module['ns3::pimdm::PIMHeader::HelloMessage::HelloEntry'])
    register_Ns3PimdmPIMHeaderHelloMessageHelloEntryGenerationID_methods(root_module, root_module['ns3::pimdm::PIMHeader::HelloMessage::HelloEntry::GenerationID'])
    register_Ns3PimdmPIMHeaderHelloMessageHelloEntryHoldTime_methods(root_module, root_module['ns3::pimdm::PIMHeader::HelloMessage::HelloEntry::HoldTime'])
    register_Ns3PimdmPIMHeaderHelloMessageHelloEntryLanPruneDelay_methods(root_module, root_module['ns3::pimdm::PIMHeader::HelloMessage::HelloEntry::LanPruneDelay'])
    register_Ns3PimdmPIMHeaderHelloMessageHelloEntryStateRefreshCapable_methods(root_module, root_module['ns3::pimdm::PIMHeader::HelloMessage::HelloEntry::StateRefreshCapable'])
    register_Ns3PimdmPIMHeaderJoinPruneGraftMessage_methods(root_module, root_module['ns3::pimdm::PIMHeader::JoinPruneGraftMessage'])
    register_Ns3PimdmPIMHeaderJoinPruneMessage_methods(root_module, root_module['ns3::pimdm::PIMHeader::JoinPruneMessage'])
    register_Ns3PimdmPIMHeaderMulticastGroupEntry_methods(root_module, root_module['ns3::pimdm::PIMHeader::MulticastGroupEntry'])
    register_Ns3PimdmPIMHeaderStateRefreshMessage_methods(root_module, root_module['ns3::pimdm::PIMHeader::StateRefreshMessage'])
    register_Ns3PimdmRelayTag_methods(root_module, root_module['ns3::pimdm::RelayTag'])
    register_Ns3PimdmRoutingMulticastTable_methods(root_module, root_module['ns3::pimdm::RoutingMulticastTable'])
    register_Ns3PimdmSourceGroupPair_methods(root_module, root_module['ns3::pimdm::SourceGroupPair'])
    register_Ns3PimdmSourceGroupState_methods(root_module, root_module['ns3::pimdm::SourceGroupState'])
    register_Ns3PimdmUpstreamState_methods(root_module, root_module['ns3::pimdm::UpstreamState'])
    return

def register_Ns3Address_methods(root_module, cls):
    cls.add_binary_comparison_operator('!=')
    cls.add_binary_comparison_operator('<')
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    ## address.h (module 'network'): ns3::Address::Address() [constructor]
    cls.add_constructor([])
    ## address.h (module 'network'): ns3::Address::Address(uint8_t type, uint8_t const * buffer, uint8_t len) [constructor]
    cls.add_constructor([param('uint8_t', 'type'), param('uint8_t const *', 'buffer'), param('uint8_t', 'len')])
    ## address.h (module 'network'): ns3::Address::Address(ns3::Address const & address) [copy constructor]
    cls.add_constructor([param('ns3::Address const &', 'address')])
    ## address.h (module 'network'): bool ns3::Address::CheckCompatible(uint8_t type, uint8_t len) const [member function]
    cls.add_method('CheckCompatible', 
                   'bool', 
                   [param('uint8_t', 'type'), param('uint8_t', 'len')], 
                   is_const=True)
    ## address.h (module 'network'): uint32_t ns3::Address::CopyAllFrom(uint8_t const * buffer, uint8_t len) [member function]
    cls.add_method('CopyAllFrom', 
                   'uint32_t', 
                   [param('uint8_t const *', 'buffer'), param('uint8_t', 'len')])
    ## address.h (module 'network'): uint32_t ns3::Address::CopyAllTo(uint8_t * buffer, uint8_t len) const [member function]
    cls.add_method('CopyAllTo', 
                   'uint32_t', 
                   [param('uint8_t *', 'buffer'), param('uint8_t', 'len')], 
                   is_const=True)
    ## address.h (module 'network'): uint32_t ns3::Address::CopyFrom(uint8_t const * buffer, uint8_t len) [member function]
    cls.add_method('CopyFrom', 
                   'uint32_t', 
                   [param('uint8_t const *', 'buffer'), param('uint8_t', 'len')])
    ## address.h (module 'network'): uint32_t ns3::Address::CopyTo(uint8_t * buffer) const [member function]
    cls.add_method('CopyTo', 
                   'uint32_t', 
                   [param('uint8_t *', 'buffer')], 
                   is_const=True)
    ## address.h (module 'network'): void ns3::Address::Deserialize(ns3::TagBuffer buffer) [member function]
    cls.add_method('Deserialize', 
                   'void', 
                   [param('ns3::TagBuffer', 'buffer')])
    ## address.h (module 'network'): uint8_t ns3::Address::GetLength() const [member function]
    cls.add_method('GetLength', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## address.h (module 'network'): uint32_t ns3::Address::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## address.h (module 'network'): bool ns3::Address::IsInvalid() const [member function]
    cls.add_method('IsInvalid', 
                   'bool', 
                   [], 
                   is_const=True)
    ## address.h (module 'network'): bool ns3::Address::IsMatchingType(uint8_t type) const [member function]
    cls.add_method('IsMatchingType', 
                   'bool', 
                   [param('uint8_t', 'type')], 
                   is_const=True)
    ## address.h (module 'network'): static uint8_t ns3::Address::Register() [member function]
    cls.add_method('Register', 
                   'uint8_t', 
                   [], 
                   is_static=True)
    ## address.h (module 'network'): void ns3::Address::Serialize(ns3::TagBuffer buffer) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::TagBuffer', 'buffer')], 
                   is_const=True)
    return

def register_Ns3AttributeConstructionList_methods(root_module, cls):
    ## attribute-construction-list.h (module 'core'): ns3::AttributeConstructionList::AttributeConstructionList(ns3::AttributeConstructionList const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::AttributeConstructionList const &', 'arg0')])
    ## attribute-construction-list.h (module 'core'): ns3::AttributeConstructionList::AttributeConstructionList() [constructor]
    cls.add_constructor([])
    ## attribute-construction-list.h (module 'core'): void ns3::AttributeConstructionList::Add(std::string name, ns3::Ptr<ns3::AttributeChecker const> checker, ns3::Ptr<ns3::AttributeValue> value) [member function]
    cls.add_method('Add', 
                   'void', 
                   [param('std::string', 'name'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker'), param('ns3::Ptr< ns3::AttributeValue >', 'value')])
    ## attribute-construction-list.h (module 'core'): std::_List_const_iterator<ns3::AttributeConstructionList::Item> ns3::AttributeConstructionList::Begin() const [member function]
    cls.add_method('Begin', 
                   'std::_List_const_iterator< ns3::AttributeConstructionList::Item >', 
                   [], 
                   is_const=True)
    ## attribute-construction-list.h (module 'core'): std::_List_const_iterator<ns3::AttributeConstructionList::Item> ns3::AttributeConstructionList::End() const [member function]
    cls.add_method('End', 
                   'std::_List_const_iterator< ns3::AttributeConstructionList::Item >', 
                   [], 
                   is_const=True)
    ## attribute-construction-list.h (module 'core'): ns3::Ptr<ns3::AttributeValue> ns3::AttributeConstructionList::Find(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('Find', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True)
    return

def register_Ns3AttributeConstructionListItem_methods(root_module, cls):
    ## attribute-construction-list.h (module 'core'): ns3::AttributeConstructionList::Item::Item() [constructor]
    cls.add_constructor([])
    ## attribute-construction-list.h (module 'core'): ns3::AttributeConstructionList::Item::Item(ns3::AttributeConstructionList::Item const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::AttributeConstructionList::Item const &', 'arg0')])
    ## attribute-construction-list.h (module 'core'): ns3::AttributeConstructionList::Item::checker [variable]
    cls.add_instance_attribute('checker', 'ns3::Ptr< ns3::AttributeChecker const >', is_const=False)
    ## attribute-construction-list.h (module 'core'): ns3::AttributeConstructionList::Item::name [variable]
    cls.add_instance_attribute('name', 'std::string', is_const=False)
    ## attribute-construction-list.h (module 'core'): ns3::AttributeConstructionList::Item::value [variable]
    cls.add_instance_attribute('value', 'ns3::Ptr< ns3::AttributeValue >', is_const=False)
    return

def register_Ns3Buffer_methods(root_module, cls):
    ## buffer.h (module 'network'): ns3::Buffer::Buffer() [constructor]
    cls.add_constructor([])
    ## buffer.h (module 'network'): ns3::Buffer::Buffer(uint32_t dataSize) [constructor]
    cls.add_constructor([param('uint32_t', 'dataSize')])
    ## buffer.h (module 'network'): ns3::Buffer::Buffer(uint32_t dataSize, bool initialize) [constructor]
    cls.add_constructor([param('uint32_t', 'dataSize'), param('bool', 'initialize')])
    ## buffer.h (module 'network'): ns3::Buffer::Buffer(ns3::Buffer const & o) [copy constructor]
    cls.add_constructor([param('ns3::Buffer const &', 'o')])
    ## buffer.h (module 'network'): bool ns3::Buffer::AddAtEnd(uint32_t end) [member function]
    cls.add_method('AddAtEnd', 
                   'bool', 
                   [param('uint32_t', 'end')])
    ## buffer.h (module 'network'): void ns3::Buffer::AddAtEnd(ns3::Buffer const & o) [member function]
    cls.add_method('AddAtEnd', 
                   'void', 
                   [param('ns3::Buffer const &', 'o')])
    ## buffer.h (module 'network'): bool ns3::Buffer::AddAtStart(uint32_t start) [member function]
    cls.add_method('AddAtStart', 
                   'bool', 
                   [param('uint32_t', 'start')])
    ## buffer.h (module 'network'): ns3::Buffer::Iterator ns3::Buffer::Begin() const [member function]
    cls.add_method('Begin', 
                   'ns3::Buffer::Iterator', 
                   [], 
                   is_const=True)
    ## buffer.h (module 'network'): void ns3::Buffer::CopyData(std::ostream * os, uint32_t size) const [member function]
    cls.add_method('CopyData', 
                   'void', 
                   [param('std::ostream *', 'os'), param('uint32_t', 'size')], 
                   is_const=True)
    ## buffer.h (module 'network'): uint32_t ns3::Buffer::CopyData(uint8_t * buffer, uint32_t size) const [member function]
    cls.add_method('CopyData', 
                   'uint32_t', 
                   [param('uint8_t *', 'buffer'), param('uint32_t', 'size')], 
                   is_const=True)
    ## buffer.h (module 'network'): ns3::Buffer ns3::Buffer::CreateFragment(uint32_t start, uint32_t length) const [member function]
    cls.add_method('CreateFragment', 
                   'ns3::Buffer', 
                   [param('uint32_t', 'start'), param('uint32_t', 'length')], 
                   is_const=True)
    ## buffer.h (module 'network'): ns3::Buffer ns3::Buffer::CreateFullCopy() const [member function]
    cls.add_method('CreateFullCopy', 
                   'ns3::Buffer', 
                   [], 
                   is_const=True)
    ## buffer.h (module 'network'): uint32_t ns3::Buffer::Deserialize(uint8_t const * buffer, uint32_t size) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('uint8_t const *', 'buffer'), param('uint32_t', 'size')])
    ## buffer.h (module 'network'): ns3::Buffer::Iterator ns3::Buffer::End() const [member function]
    cls.add_method('End', 
                   'ns3::Buffer::Iterator', 
                   [], 
                   is_const=True)
    ## buffer.h (module 'network'): int32_t ns3::Buffer::GetCurrentEndOffset() const [member function]
    cls.add_method('GetCurrentEndOffset', 
                   'int32_t', 
                   [], 
                   is_const=True)
    ## buffer.h (module 'network'): int32_t ns3::Buffer::GetCurrentStartOffset() const [member function]
    cls.add_method('GetCurrentStartOffset', 
                   'int32_t', 
                   [], 
                   is_const=True)
    ## buffer.h (module 'network'): uint32_t ns3::Buffer::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## buffer.h (module 'network'): uint32_t ns3::Buffer::GetSize() const [member function]
    cls.add_method('GetSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## buffer.h (module 'network'): uint8_t const * ns3::Buffer::PeekData() const [member function]
    cls.add_method('PeekData', 
                   'uint8_t const *', 
                   [], 
                   is_const=True)
    ## buffer.h (module 'network'): void ns3::Buffer::RemoveAtEnd(uint32_t end) [member function]
    cls.add_method('RemoveAtEnd', 
                   'void', 
                   [param('uint32_t', 'end')])
    ## buffer.h (module 'network'): void ns3::Buffer::RemoveAtStart(uint32_t start) [member function]
    cls.add_method('RemoveAtStart', 
                   'void', 
                   [param('uint32_t', 'start')])
    ## buffer.h (module 'network'): uint32_t ns3::Buffer::Serialize(uint8_t * buffer, uint32_t maxSize) const [member function]
    cls.add_method('Serialize', 
                   'uint32_t', 
                   [param('uint8_t *', 'buffer'), param('uint32_t', 'maxSize')], 
                   is_const=True)
    return

def register_Ns3BufferIterator_methods(root_module, cls):
    ## buffer.h (module 'network'): ns3::Buffer::Iterator::Iterator(ns3::Buffer::Iterator const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Buffer::Iterator const &', 'arg0')])
    ## buffer.h (module 'network'): ns3::Buffer::Iterator::Iterator() [constructor]
    cls.add_constructor([])
    ## buffer.h (module 'network'): uint16_t ns3::Buffer::Iterator::CalculateIpChecksum(uint16_t size) [member function]
    cls.add_method('CalculateIpChecksum', 
                   'uint16_t', 
                   [param('uint16_t', 'size')])
    ## buffer.h (module 'network'): uint16_t ns3::Buffer::Iterator::CalculateIpChecksum(uint16_t size, uint32_t initialChecksum) [member function]
    cls.add_method('CalculateIpChecksum', 
                   'uint16_t', 
                   [param('uint16_t', 'size'), param('uint32_t', 'initialChecksum')])
    ## buffer.h (module 'network'): uint32_t ns3::Buffer::Iterator::GetDistanceFrom(ns3::Buffer::Iterator const & o) const [member function]
    cls.add_method('GetDistanceFrom', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator const &', 'o')], 
                   is_const=True)
    ## buffer.h (module 'network'): uint32_t ns3::Buffer::Iterator::GetSize() const [member function]
    cls.add_method('GetSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## buffer.h (module 'network'): bool ns3::Buffer::Iterator::IsEnd() const [member function]
    cls.add_method('IsEnd', 
                   'bool', 
                   [], 
                   is_const=True)
    ## buffer.h (module 'network'): bool ns3::Buffer::Iterator::IsStart() const [member function]
    cls.add_method('IsStart', 
                   'bool', 
                   [], 
                   is_const=True)
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::Next() [member function]
    cls.add_method('Next', 
                   'void', 
                   [])
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::Next(uint32_t delta) [member function]
    cls.add_method('Next', 
                   'void', 
                   [param('uint32_t', 'delta')])
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::Prev() [member function]
    cls.add_method('Prev', 
                   'void', 
                   [])
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::Prev(uint32_t delta) [member function]
    cls.add_method('Prev', 
                   'void', 
                   [param('uint32_t', 'delta')])
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::Read(uint8_t * buffer, uint32_t size) [member function]
    cls.add_method('Read', 
                   'void', 
                   [param('uint8_t *', 'buffer'), param('uint32_t', 'size')])
    ## buffer.h (module 'network'): uint16_t ns3::Buffer::Iterator::ReadLsbtohU16() [member function]
    cls.add_method('ReadLsbtohU16', 
                   'uint16_t', 
                   [])
    ## buffer.h (module 'network'): uint32_t ns3::Buffer::Iterator::ReadLsbtohU32() [member function]
    cls.add_method('ReadLsbtohU32', 
                   'uint32_t', 
                   [])
    ## buffer.h (module 'network'): uint64_t ns3::Buffer::Iterator::ReadLsbtohU64() [member function]
    cls.add_method('ReadLsbtohU64', 
                   'uint64_t', 
                   [])
    ## buffer.h (module 'network'): uint16_t ns3::Buffer::Iterator::ReadNtohU16() [member function]
    cls.add_method('ReadNtohU16', 
                   'uint16_t', 
                   [])
    ## buffer.h (module 'network'): uint32_t ns3::Buffer::Iterator::ReadNtohU32() [member function]
    cls.add_method('ReadNtohU32', 
                   'uint32_t', 
                   [])
    ## buffer.h (module 'network'): uint64_t ns3::Buffer::Iterator::ReadNtohU64() [member function]
    cls.add_method('ReadNtohU64', 
                   'uint64_t', 
                   [])
    ## buffer.h (module 'network'): uint16_t ns3::Buffer::Iterator::ReadU16() [member function]
    cls.add_method('ReadU16', 
                   'uint16_t', 
                   [])
    ## buffer.h (module 'network'): uint32_t ns3::Buffer::Iterator::ReadU32() [member function]
    cls.add_method('ReadU32', 
                   'uint32_t', 
                   [])
    ## buffer.h (module 'network'): uint64_t ns3::Buffer::Iterator::ReadU64() [member function]
    cls.add_method('ReadU64', 
                   'uint64_t', 
                   [])
    ## buffer.h (module 'network'): uint8_t ns3::Buffer::Iterator::ReadU8() [member function]
    cls.add_method('ReadU8', 
                   'uint8_t', 
                   [])
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::Write(uint8_t const * buffer, uint32_t size) [member function]
    cls.add_method('Write', 
                   'void', 
                   [param('uint8_t const *', 'buffer'), param('uint32_t', 'size')])
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::Write(ns3::Buffer::Iterator start, ns3::Buffer::Iterator end) [member function]
    cls.add_method('Write', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start'), param('ns3::Buffer::Iterator', 'end')])
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::WriteHtolsbU16(uint16_t data) [member function]
    cls.add_method('WriteHtolsbU16', 
                   'void', 
                   [param('uint16_t', 'data')])
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::WriteHtolsbU32(uint32_t data) [member function]
    cls.add_method('WriteHtolsbU32', 
                   'void', 
                   [param('uint32_t', 'data')])
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::WriteHtolsbU64(uint64_t data) [member function]
    cls.add_method('WriteHtolsbU64', 
                   'void', 
                   [param('uint64_t', 'data')])
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::WriteHtonU16(uint16_t data) [member function]
    cls.add_method('WriteHtonU16', 
                   'void', 
                   [param('uint16_t', 'data')])
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::WriteHtonU32(uint32_t data) [member function]
    cls.add_method('WriteHtonU32', 
                   'void', 
                   [param('uint32_t', 'data')])
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::WriteHtonU64(uint64_t data) [member function]
    cls.add_method('WriteHtonU64', 
                   'void', 
                   [param('uint64_t', 'data')])
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::WriteU16(uint16_t data) [member function]
    cls.add_method('WriteU16', 
                   'void', 
                   [param('uint16_t', 'data')])
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::WriteU32(uint32_t data) [member function]
    cls.add_method('WriteU32', 
                   'void', 
                   [param('uint32_t', 'data')])
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::WriteU64(uint64_t data) [member function]
    cls.add_method('WriteU64', 
                   'void', 
                   [param('uint64_t', 'data')])
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::WriteU8(uint8_t data) [member function]
    cls.add_method('WriteU8', 
                   'void', 
                   [param('uint8_t', 'data')])
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::WriteU8(uint8_t data, uint32_t len) [member function]
    cls.add_method('WriteU8', 
                   'void', 
                   [param('uint8_t', 'data'), param('uint32_t', 'len')])
    return

def register_Ns3ByteTagIterator_methods(root_module, cls):
    ## packet.h (module 'network'): ns3::ByteTagIterator::ByteTagIterator(ns3::ByteTagIterator const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::ByteTagIterator const &', 'arg0')])
    ## packet.h (module 'network'): bool ns3::ByteTagIterator::HasNext() const [member function]
    cls.add_method('HasNext', 
                   'bool', 
                   [], 
                   is_const=True)
    ## packet.h (module 'network'): ns3::ByteTagIterator::Item ns3::ByteTagIterator::Next() [member function]
    cls.add_method('Next', 
                   'ns3::ByteTagIterator::Item', 
                   [])
    return

def register_Ns3ByteTagIteratorItem_methods(root_module, cls):
    ## packet.h (module 'network'): ns3::ByteTagIterator::Item::Item(ns3::ByteTagIterator::Item const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::ByteTagIterator::Item const &', 'arg0')])
    ## packet.h (module 'network'): uint32_t ns3::ByteTagIterator::Item::GetEnd() const [member function]
    cls.add_method('GetEnd', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## packet.h (module 'network'): uint32_t ns3::ByteTagIterator::Item::GetStart() const [member function]
    cls.add_method('GetStart', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## packet.h (module 'network'): void ns3::ByteTagIterator::Item::GetTag(ns3::Tag & tag) const [member function]
    cls.add_method('GetTag', 
                   'void', 
                   [param('ns3::Tag &', 'tag')], 
                   is_const=True)
    ## packet.h (module 'network'): ns3::TypeId ns3::ByteTagIterator::Item::GetTypeId() const [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True)
    return

def register_Ns3ByteTagList_methods(root_module, cls):
    ## byte-tag-list.h (module 'network'): ns3::ByteTagList::ByteTagList() [constructor]
    cls.add_constructor([])
    ## byte-tag-list.h (module 'network'): ns3::ByteTagList::ByteTagList(ns3::ByteTagList const & o) [copy constructor]
    cls.add_constructor([param('ns3::ByteTagList const &', 'o')])
    ## byte-tag-list.h (module 'network'): ns3::TagBuffer ns3::ByteTagList::Add(ns3::TypeId tid, uint32_t bufferSize, int32_t start, int32_t end) [member function]
    cls.add_method('Add', 
                   'ns3::TagBuffer', 
                   [param('ns3::TypeId', 'tid'), param('uint32_t', 'bufferSize'), param('int32_t', 'start'), param('int32_t', 'end')])
    ## byte-tag-list.h (module 'network'): void ns3::ByteTagList::Add(ns3::ByteTagList const & o) [member function]
    cls.add_method('Add', 
                   'void', 
                   [param('ns3::ByteTagList const &', 'o')])
    ## byte-tag-list.h (module 'network'): void ns3::ByteTagList::AddAtEnd(int32_t adjustment, int32_t appendOffset) [member function]
    cls.add_method('AddAtEnd', 
                   'void', 
                   [param('int32_t', 'adjustment'), param('int32_t', 'appendOffset')])
    ## byte-tag-list.h (module 'network'): void ns3::ByteTagList::AddAtStart(int32_t adjustment, int32_t prependOffset) [member function]
    cls.add_method('AddAtStart', 
                   'void', 
                   [param('int32_t', 'adjustment'), param('int32_t', 'prependOffset')])
    ## byte-tag-list.h (module 'network'): ns3::ByteTagList::Iterator ns3::ByteTagList::Begin(int32_t offsetStart, int32_t offsetEnd) const [member function]
    cls.add_method('Begin', 
                   'ns3::ByteTagList::Iterator', 
                   [param('int32_t', 'offsetStart'), param('int32_t', 'offsetEnd')], 
                   is_const=True)
    ## byte-tag-list.h (module 'network'): void ns3::ByteTagList::RemoveAll() [member function]
    cls.add_method('RemoveAll', 
                   'void', 
                   [])
    return

def register_Ns3ByteTagListIterator_methods(root_module, cls):
    ## byte-tag-list.h (module 'network'): ns3::ByteTagList::Iterator::Iterator(ns3::ByteTagList::Iterator const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::ByteTagList::Iterator const &', 'arg0')])
    ## byte-tag-list.h (module 'network'): uint32_t ns3::ByteTagList::Iterator::GetOffsetStart() const [member function]
    cls.add_method('GetOffsetStart', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## byte-tag-list.h (module 'network'): bool ns3::ByteTagList::Iterator::HasNext() const [member function]
    cls.add_method('HasNext', 
                   'bool', 
                   [], 
                   is_const=True)
    ## byte-tag-list.h (module 'network'): ns3::ByteTagList::Iterator::Item ns3::ByteTagList::Iterator::Next() [member function]
    cls.add_method('Next', 
                   'ns3::ByteTagList::Iterator::Item', 
                   [])
    return

def register_Ns3ByteTagListIteratorItem_methods(root_module, cls):
    ## byte-tag-list.h (module 'network'): ns3::ByteTagList::Iterator::Item::Item(ns3::ByteTagList::Iterator::Item const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::ByteTagList::Iterator::Item const &', 'arg0')])
    ## byte-tag-list.h (module 'network'): ns3::ByteTagList::Iterator::Item::Item(ns3::TagBuffer buf) [constructor]
    cls.add_constructor([param('ns3::TagBuffer', 'buf')])
    ## byte-tag-list.h (module 'network'): ns3::ByteTagList::Iterator::Item::buf [variable]
    cls.add_instance_attribute('buf', 'ns3::TagBuffer', is_const=False)
    ## byte-tag-list.h (module 'network'): ns3::ByteTagList::Iterator::Item::end [variable]
    cls.add_instance_attribute('end', 'int32_t', is_const=False)
    ## byte-tag-list.h (module 'network'): ns3::ByteTagList::Iterator::Item::size [variable]
    cls.add_instance_attribute('size', 'uint32_t', is_const=False)
    ## byte-tag-list.h (module 'network'): ns3::ByteTagList::Iterator::Item::start [variable]
    cls.add_instance_attribute('start', 'int32_t', is_const=False)
    ## byte-tag-list.h (module 'network'): ns3::ByteTagList::Iterator::Item::tid [variable]
    cls.add_instance_attribute('tid', 'ns3::TypeId', is_const=False)
    return

def register_Ns3CallbackBase_methods(root_module, cls):
    ## callback.h (module 'core'): ns3::CallbackBase::CallbackBase(ns3::CallbackBase const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::CallbackBase const &', 'arg0')])
    ## callback.h (module 'core'): ns3::CallbackBase::CallbackBase() [constructor]
    cls.add_constructor([])
    ## callback.h (module 'core'): ns3::Ptr<ns3::CallbackImplBase> ns3::CallbackBase::GetImpl() const [member function]
    cls.add_method('GetImpl', 
                   'ns3::Ptr< ns3::CallbackImplBase >', 
                   [], 
                   is_const=True)
    ## callback.h (module 'core'): ns3::CallbackBase::CallbackBase(ns3::Ptr<ns3::CallbackImplBase> impl) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::CallbackImplBase >', 'impl')], 
                        visibility='protected')
    ## callback.h (module 'core'): static std::string ns3::CallbackBase::Demangle(std::string const & mangled) [member function]
    cls.add_method('Demangle', 
                   'std::string', 
                   [param('std::string const &', 'mangled')], 
                   is_static=True, visibility='protected')
    return

def register_Ns3EventGarbageCollector_methods(root_module, cls):
    ## event-garbage-collector.h (module 'tools'): ns3::EventGarbageCollector::EventGarbageCollector(ns3::EventGarbageCollector const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::EventGarbageCollector const &', 'arg0')])
    ## event-garbage-collector.h (module 'tools'): ns3::EventGarbageCollector::EventGarbageCollector() [constructor]
    cls.add_constructor([])
    ## event-garbage-collector.h (module 'tools'): void ns3::EventGarbageCollector::Track(ns3::EventId event) [member function]
    cls.add_method('Track', 
                   'void', 
                   [param('ns3::EventId', 'event')])
    return

def register_Ns3EventId_methods(root_module, cls):
    cls.add_binary_comparison_operator('!=')
    cls.add_binary_comparison_operator('==')
    ## event-id.h (module 'core'): ns3::EventId::EventId(ns3::EventId const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::EventId const &', 'arg0')])
    ## event-id.h (module 'core'): ns3::EventId::EventId() [constructor]
    cls.add_constructor([])
    ## event-id.h (module 'core'): ns3::EventId::EventId(ns3::Ptr<ns3::EventImpl> const & impl, uint64_t ts, uint32_t context, uint32_t uid) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::EventImpl > const &', 'impl'), param('uint64_t', 'ts'), param('uint32_t', 'context'), param('uint32_t', 'uid')])
    ## event-id.h (module 'core'): void ns3::EventId::Cancel() [member function]
    cls.add_method('Cancel', 
                   'void', 
                   [])
    ## event-id.h (module 'core'): uint32_t ns3::EventId::GetContext() const [member function]
    cls.add_method('GetContext', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## event-id.h (module 'core'): uint64_t ns3::EventId::GetTs() const [member function]
    cls.add_method('GetTs', 
                   'uint64_t', 
                   [], 
                   is_const=True)
    ## event-id.h (module 'core'): uint32_t ns3::EventId::GetUid() const [member function]
    cls.add_method('GetUid', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## event-id.h (module 'core'): bool ns3::EventId::IsExpired() const [member function]
    cls.add_method('IsExpired', 
                   'bool', 
                   [], 
                   is_const=True)
    ## event-id.h (module 'core'): bool ns3::EventId::IsRunning() const [member function]
    cls.add_method('IsRunning', 
                   'bool', 
                   [], 
                   is_const=True)
    ## event-id.h (module 'core'): ns3::EventImpl * ns3::EventId::PeekEventImpl() const [member function]
    cls.add_method('PeekEventImpl', 
                   'ns3::EventImpl *', 
                   [], 
                   is_const=True)
    return

def register_Ns3Gnuplot_methods(root_module, cls):
    ## gnuplot.h (module 'tools'): ns3::Gnuplot::Gnuplot(ns3::Gnuplot const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Gnuplot const &', 'arg0')])
    ## gnuplot.h (module 'tools'): ns3::Gnuplot::Gnuplot(std::string const & outputFilename="", std::string const & title="") [constructor]
    cls.add_constructor([param('std::string const &', 'outputFilename', default_value='""'), param('std::string const &', 'title', default_value='""')])
    ## gnuplot.h (module 'tools'): void ns3::Gnuplot::AddDataset(ns3::GnuplotDataset const & dataset) [member function]
    cls.add_method('AddDataset', 
                   'void', 
                   [param('ns3::GnuplotDataset const &', 'dataset')])
    ## gnuplot.h (module 'tools'): void ns3::Gnuplot::AppendExtra(std::string const & extra) [member function]
    cls.add_method('AppendExtra', 
                   'void', 
                   [param('std::string const &', 'extra')])
    ## gnuplot.h (module 'tools'): static std::string ns3::Gnuplot::DetectTerminal(std::string const & filename) [member function]
    cls.add_method('DetectTerminal', 
                   'std::string', 
                   [param('std::string const &', 'filename')], 
                   is_static=True)
    ## gnuplot.h (module 'tools'): void ns3::Gnuplot::GenerateOutput(std::ostream & os) const [member function]
    cls.add_method('GenerateOutput', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True)
    ## gnuplot.h (module 'tools'): void ns3::Gnuplot::SetExtra(std::string const & extra) [member function]
    cls.add_method('SetExtra', 
                   'void', 
                   [param('std::string const &', 'extra')])
    ## gnuplot.h (module 'tools'): void ns3::Gnuplot::SetLegend(std::string const & xLegend, std::string const & yLegend) [member function]
    cls.add_method('SetLegend', 
                   'void', 
                   [param('std::string const &', 'xLegend'), param('std::string const &', 'yLegend')])
    ## gnuplot.h (module 'tools'): void ns3::Gnuplot::SetTerminal(std::string const & terminal) [member function]
    cls.add_method('SetTerminal', 
                   'void', 
                   [param('std::string const &', 'terminal')])
    ## gnuplot.h (module 'tools'): void ns3::Gnuplot::SetTitle(std::string const & title) [member function]
    cls.add_method('SetTitle', 
                   'void', 
                   [param('std::string const &', 'title')])
    return

def register_Ns3GnuplotCollection_methods(root_module, cls):
    ## gnuplot.h (module 'tools'): ns3::GnuplotCollection::GnuplotCollection(ns3::GnuplotCollection const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::GnuplotCollection const &', 'arg0')])
    ## gnuplot.h (module 'tools'): ns3::GnuplotCollection::GnuplotCollection(std::string const & outputFilename) [constructor]
    cls.add_constructor([param('std::string const &', 'outputFilename')])
    ## gnuplot.h (module 'tools'): void ns3::GnuplotCollection::AddPlot(ns3::Gnuplot const & plot) [member function]
    cls.add_method('AddPlot', 
                   'void', 
                   [param('ns3::Gnuplot const &', 'plot')])
    ## gnuplot.h (module 'tools'): void ns3::GnuplotCollection::GenerateOutput(std::ostream & os) const [member function]
    cls.add_method('GenerateOutput', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True)
    ## gnuplot.h (module 'tools'): ns3::Gnuplot & ns3::GnuplotCollection::GetPlot(unsigned int id) [member function]
    cls.add_method('GetPlot', 
                   'ns3::Gnuplot &', 
                   [param('unsigned int', 'id')])
    ## gnuplot.h (module 'tools'): void ns3::GnuplotCollection::SetTerminal(std::string const & terminal) [member function]
    cls.add_method('SetTerminal', 
                   'void', 
                   [param('std::string const &', 'terminal')])
    return

def register_Ns3GnuplotDataset_methods(root_module, cls):
    ## gnuplot.h (module 'tools'): ns3::GnuplotDataset::GnuplotDataset(ns3::GnuplotDataset const & original) [copy constructor]
    cls.add_constructor([param('ns3::GnuplotDataset const &', 'original')])
    ## gnuplot.h (module 'tools'): static void ns3::GnuplotDataset::SetDefaultExtra(std::string const & extra) [member function]
    cls.add_method('SetDefaultExtra', 
                   'void', 
                   [param('std::string const &', 'extra')], 
                   is_static=True)
    ## gnuplot.h (module 'tools'): void ns3::GnuplotDataset::SetExtra(std::string const & extra) [member function]
    cls.add_method('SetExtra', 
                   'void', 
                   [param('std::string const &', 'extra')])
    ## gnuplot.h (module 'tools'): void ns3::GnuplotDataset::SetTitle(std::string const & title) [member function]
    cls.add_method('SetTitle', 
                   'void', 
                   [param('std::string const &', 'title')])
    ## gnuplot.h (module 'tools'): ns3::GnuplotDataset::GnuplotDataset(ns3::GnuplotDataset::Data * data) [constructor]
    cls.add_constructor([param('ns3::GnuplotDataset::Data *', 'data')], 
                        visibility='protected')
    return

def register_Ns3IntToType__0_methods(root_module, cls):
    ## int-to-type.h (module 'core'): ns3::IntToType<0>::IntToType() [constructor]
    cls.add_constructor([])
    ## int-to-type.h (module 'core'): ns3::IntToType<0>::IntToType(ns3::IntToType<0> const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::IntToType< 0 > const &', 'arg0')])
    return

def register_Ns3IntToType__1_methods(root_module, cls):
    ## int-to-type.h (module 'core'): ns3::IntToType<1>::IntToType() [constructor]
    cls.add_constructor([])
    ## int-to-type.h (module 'core'): ns3::IntToType<1>::IntToType(ns3::IntToType<1> const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::IntToType< 1 > const &', 'arg0')])
    return

def register_Ns3IntToType__2_methods(root_module, cls):
    ## int-to-type.h (module 'core'): ns3::IntToType<2>::IntToType() [constructor]
    cls.add_constructor([])
    ## int-to-type.h (module 'core'): ns3::IntToType<2>::IntToType(ns3::IntToType<2> const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::IntToType< 2 > const &', 'arg0')])
    return

def register_Ns3IntToType__3_methods(root_module, cls):
    ## int-to-type.h (module 'core'): ns3::IntToType<3>::IntToType() [constructor]
    cls.add_constructor([])
    ## int-to-type.h (module 'core'): ns3::IntToType<3>::IntToType(ns3::IntToType<3> const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::IntToType< 3 > const &', 'arg0')])
    return

def register_Ns3IntToType__4_methods(root_module, cls):
    ## int-to-type.h (module 'core'): ns3::IntToType<4>::IntToType() [constructor]
    cls.add_constructor([])
    ## int-to-type.h (module 'core'): ns3::IntToType<4>::IntToType(ns3::IntToType<4> const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::IntToType< 4 > const &', 'arg0')])
    return

def register_Ns3IntToType__5_methods(root_module, cls):
    ## int-to-type.h (module 'core'): ns3::IntToType<5>::IntToType() [constructor]
    cls.add_constructor([])
    ## int-to-type.h (module 'core'): ns3::IntToType<5>::IntToType(ns3::IntToType<5> const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::IntToType< 5 > const &', 'arg0')])
    return

def register_Ns3IntToType__6_methods(root_module, cls):
    ## int-to-type.h (module 'core'): ns3::IntToType<6>::IntToType() [constructor]
    cls.add_constructor([])
    ## int-to-type.h (module 'core'): ns3::IntToType<6>::IntToType(ns3::IntToType<6> const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::IntToType< 6 > const &', 'arg0')])
    return

def register_Ns3Ipv4Address_methods(root_module, cls):
    cls.add_binary_comparison_operator('!=')
    cls.add_binary_comparison_operator('<')
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    ## ipv4-address.h (module 'network'): ns3::Ipv4Address::Ipv4Address(ns3::Ipv4Address const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Ipv4Address const &', 'arg0')])
    ## ipv4-address.h (module 'network'): ns3::Ipv4Address::Ipv4Address() [constructor]
    cls.add_constructor([])
    ## ipv4-address.h (module 'network'): ns3::Ipv4Address::Ipv4Address(uint32_t address) [constructor]
    cls.add_constructor([param('uint32_t', 'address')])
    ## ipv4-address.h (module 'network'): ns3::Ipv4Address::Ipv4Address(char const * address) [constructor]
    cls.add_constructor([param('char const *', 'address')])
    ## ipv4-address.h (module 'network'): ns3::Ipv4Address ns3::Ipv4Address::CombineMask(ns3::Ipv4Mask const & mask) const [member function]
    cls.add_method('CombineMask', 
                   'ns3::Ipv4Address', 
                   [param('ns3::Ipv4Mask const &', 'mask')], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): static ns3::Ipv4Address ns3::Ipv4Address::ConvertFrom(ns3::Address const & address) [member function]
    cls.add_method('ConvertFrom', 
                   'ns3::Ipv4Address', 
                   [param('ns3::Address const &', 'address')], 
                   is_static=True)
    ## ipv4-address.h (module 'network'): static ns3::Ipv4Address ns3::Ipv4Address::Deserialize(uint8_t const * buf) [member function]
    cls.add_method('Deserialize', 
                   'ns3::Ipv4Address', 
                   [param('uint8_t const *', 'buf')], 
                   is_static=True)
    ## ipv4-address.h (module 'network'): uint32_t ns3::Ipv4Address::Get() const [member function]
    cls.add_method('Get', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): static ns3::Ipv4Address ns3::Ipv4Address::GetAny() [member function]
    cls.add_method('GetAny', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_static=True)
    ## ipv4-address.h (module 'network'): static ns3::Ipv4Address ns3::Ipv4Address::GetBroadcast() [member function]
    cls.add_method('GetBroadcast', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_static=True)
    ## ipv4-address.h (module 'network'): static ns3::Ipv4Address ns3::Ipv4Address::GetLoopback() [member function]
    cls.add_method('GetLoopback', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_static=True)
    ## ipv4-address.h (module 'network'): ns3::Ipv4Address ns3::Ipv4Address::GetSubnetDirectedBroadcast(ns3::Ipv4Mask const & mask) const [member function]
    cls.add_method('GetSubnetDirectedBroadcast', 
                   'ns3::Ipv4Address', 
                   [param('ns3::Ipv4Mask const &', 'mask')], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): static ns3::Ipv4Address ns3::Ipv4Address::GetZero() [member function]
    cls.add_method('GetZero', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_static=True)
    ## ipv4-address.h (module 'network'): bool ns3::Ipv4Address::IsBroadcast() const [member function]
    cls.add_method('IsBroadcast', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): bool ns3::Ipv4Address::IsEqual(ns3::Ipv4Address const & other) const [member function]
    cls.add_method('IsEqual', 
                   'bool', 
                   [param('ns3::Ipv4Address const &', 'other')], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): bool ns3::Ipv4Address::IsLocalMulticast() const [member function]
    cls.add_method('IsLocalMulticast', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): static bool ns3::Ipv4Address::IsMatchingType(ns3::Address const & address) [member function]
    cls.add_method('IsMatchingType', 
                   'bool', 
                   [param('ns3::Address const &', 'address')], 
                   is_static=True)
    ## ipv4-address.h (module 'network'): bool ns3::Ipv4Address::IsMulticast() const [member function]
    cls.add_method('IsMulticast', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): bool ns3::Ipv4Address::IsSubnetDirectedBroadcast(ns3::Ipv4Mask const & mask) const [member function]
    cls.add_method('IsSubnetDirectedBroadcast', 
                   'bool', 
                   [param('ns3::Ipv4Mask const &', 'mask')], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): void ns3::Ipv4Address::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): void ns3::Ipv4Address::Serialize(uint8_t * buf) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('uint8_t *', 'buf')], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): void ns3::Ipv4Address::Set(uint32_t address) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('uint32_t', 'address')])
    ## ipv4-address.h (module 'network'): void ns3::Ipv4Address::Set(char const * address) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('char const *', 'address')])
    return

def register_Ns3Ipv4InterfaceAddress_methods(root_module, cls):
    cls.add_binary_comparison_operator('!=')
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    ## ipv4-interface-address.h (module 'internet'): ns3::Ipv4InterfaceAddress::Ipv4InterfaceAddress() [constructor]
    cls.add_constructor([])
    ## ipv4-interface-address.h (module 'internet'): ns3::Ipv4InterfaceAddress::Ipv4InterfaceAddress(ns3::Ipv4Address local, ns3::Ipv4Mask mask) [constructor]
    cls.add_constructor([param('ns3::Ipv4Address', 'local'), param('ns3::Ipv4Mask', 'mask')])
    ## ipv4-interface-address.h (module 'internet'): ns3::Ipv4InterfaceAddress::Ipv4InterfaceAddress(ns3::Ipv4InterfaceAddress const & o) [copy constructor]
    cls.add_constructor([param('ns3::Ipv4InterfaceAddress const &', 'o')])
    ## ipv4-interface-address.h (module 'internet'): ns3::Ipv4Address ns3::Ipv4InterfaceAddress::GetBroadcast() const [member function]
    cls.add_method('GetBroadcast', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## ipv4-interface-address.h (module 'internet'): ns3::Ipv4Address ns3::Ipv4InterfaceAddress::GetLocal() const [member function]
    cls.add_method('GetLocal', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## ipv4-interface-address.h (module 'internet'): ns3::Ipv4Mask ns3::Ipv4InterfaceAddress::GetMask() const [member function]
    cls.add_method('GetMask', 
                   'ns3::Ipv4Mask', 
                   [], 
                   is_const=True)
    ## ipv4-interface-address.h (module 'internet'): ns3::Ipv4InterfaceAddress::InterfaceAddressScope_e ns3::Ipv4InterfaceAddress::GetScope() const [member function]
    cls.add_method('GetScope', 
                   'ns3::Ipv4InterfaceAddress::InterfaceAddressScope_e', 
                   [], 
                   is_const=True)
    ## ipv4-interface-address.h (module 'internet'): bool ns3::Ipv4InterfaceAddress::IsSecondary() const [member function]
    cls.add_method('IsSecondary', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv4-interface-address.h (module 'internet'): void ns3::Ipv4InterfaceAddress::SetBroadcast(ns3::Ipv4Address broadcast) [member function]
    cls.add_method('SetBroadcast', 
                   'void', 
                   [param('ns3::Ipv4Address', 'broadcast')])
    ## ipv4-interface-address.h (module 'internet'): void ns3::Ipv4InterfaceAddress::SetLocal(ns3::Ipv4Address local) [member function]
    cls.add_method('SetLocal', 
                   'void', 
                   [param('ns3::Ipv4Address', 'local')])
    ## ipv4-interface-address.h (module 'internet'): void ns3::Ipv4InterfaceAddress::SetMask(ns3::Ipv4Mask mask) [member function]
    cls.add_method('SetMask', 
                   'void', 
                   [param('ns3::Ipv4Mask', 'mask')])
    ## ipv4-interface-address.h (module 'internet'): void ns3::Ipv4InterfaceAddress::SetPrimary() [member function]
    cls.add_method('SetPrimary', 
                   'void', 
                   [])
    ## ipv4-interface-address.h (module 'internet'): void ns3::Ipv4InterfaceAddress::SetScope(ns3::Ipv4InterfaceAddress::InterfaceAddressScope_e scope) [member function]
    cls.add_method('SetScope', 
                   'void', 
                   [param('ns3::Ipv4InterfaceAddress::InterfaceAddressScope_e', 'scope')])
    ## ipv4-interface-address.h (module 'internet'): void ns3::Ipv4InterfaceAddress::SetSecondary() [member function]
    cls.add_method('SetSecondary', 
                   'void', 
                   [])
    return

def register_Ns3Ipv4Mask_methods(root_module, cls):
    cls.add_binary_comparison_operator('!=')
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    ## ipv4-address.h (module 'network'): ns3::Ipv4Mask::Ipv4Mask(ns3::Ipv4Mask const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Ipv4Mask const &', 'arg0')])
    ## ipv4-address.h (module 'network'): ns3::Ipv4Mask::Ipv4Mask() [constructor]
    cls.add_constructor([])
    ## ipv4-address.h (module 'network'): ns3::Ipv4Mask::Ipv4Mask(uint32_t mask) [constructor]
    cls.add_constructor([param('uint32_t', 'mask')])
    ## ipv4-address.h (module 'network'): ns3::Ipv4Mask::Ipv4Mask(char const * mask) [constructor]
    cls.add_constructor([param('char const *', 'mask')])
    ## ipv4-address.h (module 'network'): uint32_t ns3::Ipv4Mask::Get() const [member function]
    cls.add_method('Get', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): uint32_t ns3::Ipv4Mask::GetInverse() const [member function]
    cls.add_method('GetInverse', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): static ns3::Ipv4Mask ns3::Ipv4Mask::GetLoopback() [member function]
    cls.add_method('GetLoopback', 
                   'ns3::Ipv4Mask', 
                   [], 
                   is_static=True)
    ## ipv4-address.h (module 'network'): static ns3::Ipv4Mask ns3::Ipv4Mask::GetOnes() [member function]
    cls.add_method('GetOnes', 
                   'ns3::Ipv4Mask', 
                   [], 
                   is_static=True)
    ## ipv4-address.h (module 'network'): uint16_t ns3::Ipv4Mask::GetPrefixLength() const [member function]
    cls.add_method('GetPrefixLength', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): static ns3::Ipv4Mask ns3::Ipv4Mask::GetZero() [member function]
    cls.add_method('GetZero', 
                   'ns3::Ipv4Mask', 
                   [], 
                   is_static=True)
    ## ipv4-address.h (module 'network'): bool ns3::Ipv4Mask::IsEqual(ns3::Ipv4Mask other) const [member function]
    cls.add_method('IsEqual', 
                   'bool', 
                   [param('ns3::Ipv4Mask', 'other')], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): bool ns3::Ipv4Mask::IsMatch(ns3::Ipv4Address a, ns3::Ipv4Address b) const [member function]
    cls.add_method('IsMatch', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'a'), param('ns3::Ipv4Address', 'b')], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): void ns3::Ipv4Mask::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): void ns3::Ipv4Mask::Set(uint32_t mask) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('uint32_t', 'mask')])
    return

def register_Ns3Ipv4RoutingHelper_methods(root_module, cls):
    ## ipv4-routing-helper.h (module 'internet'): ns3::Ipv4RoutingHelper::Ipv4RoutingHelper() [constructor]
    cls.add_constructor([])
    ## ipv4-routing-helper.h (module 'internet'): ns3::Ipv4RoutingHelper::Ipv4RoutingHelper(ns3::Ipv4RoutingHelper const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Ipv4RoutingHelper const &', 'arg0')])
    ## ipv4-routing-helper.h (module 'internet'): ns3::Ipv4RoutingHelper * ns3::Ipv4RoutingHelper::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ipv4RoutingHelper *', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## ipv4-routing-helper.h (module 'internet'): ns3::Ptr<ns3::Ipv4RoutingProtocol> ns3::Ipv4RoutingHelper::Create(ns3::Ptr<ns3::Node> node) const [member function]
    cls.add_method('Create', 
                   'ns3::Ptr< ns3::Ipv4RoutingProtocol >', 
                   [param('ns3::Ptr< ns3::Node >', 'node')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## ipv4-routing-helper.h (module 'internet'): void ns3::Ipv4RoutingHelper::PrintRoutingTableAllAt(ns3::Time printTime, ns3::Ptr<ns3::OutputStreamWrapper> stream) const [member function]
    cls.add_method('PrintRoutingTableAllAt', 
                   'void', 
                   [param('ns3::Time', 'printTime'), param('ns3::Ptr< ns3::OutputStreamWrapper >', 'stream')], 
                   is_const=True)
    ## ipv4-routing-helper.h (module 'internet'): void ns3::Ipv4RoutingHelper::PrintRoutingTableAllEvery(ns3::Time printInterval, ns3::Ptr<ns3::OutputStreamWrapper> stream) const [member function]
    cls.add_method('PrintRoutingTableAllEvery', 
                   'void', 
                   [param('ns3::Time', 'printInterval'), param('ns3::Ptr< ns3::OutputStreamWrapper >', 'stream')], 
                   is_const=True)
    ## ipv4-routing-helper.h (module 'internet'): void ns3::Ipv4RoutingHelper::PrintRoutingTableAt(ns3::Time printTime, ns3::Ptr<ns3::Node> node, ns3::Ptr<ns3::OutputStreamWrapper> stream) const [member function]
    cls.add_method('PrintRoutingTableAt', 
                   'void', 
                   [param('ns3::Time', 'printTime'), param('ns3::Ptr< ns3::Node >', 'node'), param('ns3::Ptr< ns3::OutputStreamWrapper >', 'stream')], 
                   is_const=True)
    ## ipv4-routing-helper.h (module 'internet'): void ns3::Ipv4RoutingHelper::PrintRoutingTableEvery(ns3::Time printInterval, ns3::Ptr<ns3::Node> node, ns3::Ptr<ns3::OutputStreamWrapper> stream) const [member function]
    cls.add_method('PrintRoutingTableEvery', 
                   'void', 
                   [param('ns3::Time', 'printInterval'), param('ns3::Ptr< ns3::Node >', 'node'), param('ns3::Ptr< ns3::OutputStreamWrapper >', 'stream')], 
                   is_const=True)
    return

def register_Ns3Ipv6Address_methods(root_module, cls):
    cls.add_binary_comparison_operator('!=')
    cls.add_binary_comparison_operator('<')
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    ## ipv6-address.h (module 'network'): ns3::Ipv6Address::Ipv6Address() [constructor]
    cls.add_constructor([])
    ## ipv6-address.h (module 'network'): ns3::Ipv6Address::Ipv6Address(char const * address) [constructor]
    cls.add_constructor([param('char const *', 'address')])
    ## ipv6-address.h (module 'network'): ns3::Ipv6Address::Ipv6Address(uint8_t * address) [constructor]
    cls.add_constructor([param('uint8_t *', 'address')])
    ## ipv6-address.h (module 'network'): ns3::Ipv6Address::Ipv6Address(ns3::Ipv6Address const & addr) [copy constructor]
    cls.add_constructor([param('ns3::Ipv6Address const &', 'addr')])
    ## ipv6-address.h (module 'network'): ns3::Ipv6Address::Ipv6Address(ns3::Ipv6Address const * addr) [constructor]
    cls.add_constructor([param('ns3::Ipv6Address const *', 'addr')])
    ## ipv6-address.h (module 'network'): ns3::Ipv6Address ns3::Ipv6Address::CombinePrefix(ns3::Ipv6Prefix const & prefix) [member function]
    cls.add_method('CombinePrefix', 
                   'ns3::Ipv6Address', 
                   [param('ns3::Ipv6Prefix const &', 'prefix')])
    ## ipv6-address.h (module 'network'): static ns3::Ipv6Address ns3::Ipv6Address::ConvertFrom(ns3::Address const & address) [member function]
    cls.add_method('ConvertFrom', 
                   'ns3::Ipv6Address', 
                   [param('ns3::Address const &', 'address')], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): static ns3::Ipv6Address ns3::Ipv6Address::Deserialize(uint8_t const * buf) [member function]
    cls.add_method('Deserialize', 
                   'ns3::Ipv6Address', 
                   [param('uint8_t const *', 'buf')], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): static ns3::Ipv6Address ns3::Ipv6Address::GetAllHostsMulticast() [member function]
    cls.add_method('GetAllHostsMulticast', 
                   'ns3::Ipv6Address', 
                   [], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): static ns3::Ipv6Address ns3::Ipv6Address::GetAllNodesMulticast() [member function]
    cls.add_method('GetAllNodesMulticast', 
                   'ns3::Ipv6Address', 
                   [], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): static ns3::Ipv6Address ns3::Ipv6Address::GetAllRoutersMulticast() [member function]
    cls.add_method('GetAllRoutersMulticast', 
                   'ns3::Ipv6Address', 
                   [], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): static ns3::Ipv6Address ns3::Ipv6Address::GetAny() [member function]
    cls.add_method('GetAny', 
                   'ns3::Ipv6Address', 
                   [], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): void ns3::Ipv6Address::GetBytes(uint8_t * buf) const [member function]
    cls.add_method('GetBytes', 
                   'void', 
                   [param('uint8_t *', 'buf')], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): ns3::Ipv4Address ns3::Ipv6Address::GetIpv4MappedAddress() const [member function]
    cls.add_method('GetIpv4MappedAddress', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): static ns3::Ipv6Address ns3::Ipv6Address::GetLoopback() [member function]
    cls.add_method('GetLoopback', 
                   'ns3::Ipv6Address', 
                   [], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): static ns3::Ipv6Address ns3::Ipv6Address::GetOnes() [member function]
    cls.add_method('GetOnes', 
                   'ns3::Ipv6Address', 
                   [], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): static ns3::Ipv6Address ns3::Ipv6Address::GetZero() [member function]
    cls.add_method('GetZero', 
                   'ns3::Ipv6Address', 
                   [], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): bool ns3::Ipv6Address::IsAllHostsMulticast() const [member function]
    cls.add_method('IsAllHostsMulticast', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): bool ns3::Ipv6Address::IsAllNodesMulticast() const [member function]
    cls.add_method('IsAllNodesMulticast', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): bool ns3::Ipv6Address::IsAllRoutersMulticast() const [member function]
    cls.add_method('IsAllRoutersMulticast', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): bool ns3::Ipv6Address::IsAny() const [member function]
    cls.add_method('IsAny', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): bool ns3::Ipv6Address::IsEqual(ns3::Ipv6Address const & other) const [member function]
    cls.add_method('IsEqual', 
                   'bool', 
                   [param('ns3::Ipv6Address const &', 'other')], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): bool ns3::Ipv6Address::IsIpv4MappedAddress() [member function]
    cls.add_method('IsIpv4MappedAddress', 
                   'bool', 
                   [])
    ## ipv6-address.h (module 'network'): bool ns3::Ipv6Address::IsLinkLocal() const [member function]
    cls.add_method('IsLinkLocal', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): bool ns3::Ipv6Address::IsLinkLocalMulticast() const [member function]
    cls.add_method('IsLinkLocalMulticast', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): bool ns3::Ipv6Address::IsLocalhost() const [member function]
    cls.add_method('IsLocalhost', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): static bool ns3::Ipv6Address::IsMatchingType(ns3::Address const & address) [member function]
    cls.add_method('IsMatchingType', 
                   'bool', 
                   [param('ns3::Address const &', 'address')], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): bool ns3::Ipv6Address::IsMulticast() const [member function]
    cls.add_method('IsMulticast', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): bool ns3::Ipv6Address::IsSolicitedMulticast() const [member function]
    cls.add_method('IsSolicitedMulticast', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): static ns3::Ipv6Address ns3::Ipv6Address::MakeAutoconfiguredAddress(ns3::Mac48Address addr, ns3::Ipv6Address prefix) [member function]
    cls.add_method('MakeAutoconfiguredAddress', 
                   'ns3::Ipv6Address', 
                   [param('ns3::Mac48Address', 'addr'), param('ns3::Ipv6Address', 'prefix')], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): static ns3::Ipv6Address ns3::Ipv6Address::MakeAutoconfiguredLinkLocalAddress(ns3::Mac48Address mac) [member function]
    cls.add_method('MakeAutoconfiguredLinkLocalAddress', 
                   'ns3::Ipv6Address', 
                   [param('ns3::Mac48Address', 'mac')], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): static ns3::Ipv6Address ns3::Ipv6Address::MakeIpv4MappedAddress(ns3::Ipv4Address addr) [member function]
    cls.add_method('MakeIpv4MappedAddress', 
                   'ns3::Ipv6Address', 
                   [param('ns3::Ipv4Address', 'addr')], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): static ns3::Ipv6Address ns3::Ipv6Address::MakeSolicitedAddress(ns3::Ipv6Address addr) [member function]
    cls.add_method('MakeSolicitedAddress', 
                   'ns3::Ipv6Address', 
                   [param('ns3::Ipv6Address', 'addr')], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): void ns3::Ipv6Address::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): void ns3::Ipv6Address::Serialize(uint8_t * buf) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('uint8_t *', 'buf')], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): void ns3::Ipv6Address::Set(char const * address) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('char const *', 'address')])
    ## ipv6-address.h (module 'network'): void ns3::Ipv6Address::Set(uint8_t * address) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('uint8_t *', 'address')])
    return

def register_Ns3Ipv6InterfaceAddress_methods(root_module, cls):
    cls.add_binary_comparison_operator('!=')
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    ## ipv6-interface-address.h (module 'internet'): ns3::Ipv6InterfaceAddress::Ipv6InterfaceAddress() [constructor]
    cls.add_constructor([])
    ## ipv6-interface-address.h (module 'internet'): ns3::Ipv6InterfaceAddress::Ipv6InterfaceAddress(ns3::Ipv6Address address) [constructor]
    cls.add_constructor([param('ns3::Ipv6Address', 'address')])
    ## ipv6-interface-address.h (module 'internet'): ns3::Ipv6InterfaceAddress::Ipv6InterfaceAddress(ns3::Ipv6Address address, ns3::Ipv6Prefix prefix) [constructor]
    cls.add_constructor([param('ns3::Ipv6Address', 'address'), param('ns3::Ipv6Prefix', 'prefix')])
    ## ipv6-interface-address.h (module 'internet'): ns3::Ipv6InterfaceAddress::Ipv6InterfaceAddress(ns3::Ipv6InterfaceAddress const & o) [copy constructor]
    cls.add_constructor([param('ns3::Ipv6InterfaceAddress const &', 'o')])
    ## ipv6-interface-address.h (module 'internet'): ns3::Ipv6Address ns3::Ipv6InterfaceAddress::GetAddress() const [member function]
    cls.add_method('GetAddress', 
                   'ns3::Ipv6Address', 
                   [], 
                   is_const=True)
    ## ipv6-interface-address.h (module 'internet'): uint32_t ns3::Ipv6InterfaceAddress::GetNsDadUid() const [member function]
    cls.add_method('GetNsDadUid', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## ipv6-interface-address.h (module 'internet'): ns3::Ipv6Prefix ns3::Ipv6InterfaceAddress::GetPrefix() const [member function]
    cls.add_method('GetPrefix', 
                   'ns3::Ipv6Prefix', 
                   [], 
                   is_const=True)
    ## ipv6-interface-address.h (module 'internet'): ns3::Ipv6InterfaceAddress::Scope_e ns3::Ipv6InterfaceAddress::GetScope() const [member function]
    cls.add_method('GetScope', 
                   'ns3::Ipv6InterfaceAddress::Scope_e', 
                   [], 
                   is_const=True)
    ## ipv6-interface-address.h (module 'internet'): ns3::Ipv6InterfaceAddress::State_e ns3::Ipv6InterfaceAddress::GetState() const [member function]
    cls.add_method('GetState', 
                   'ns3::Ipv6InterfaceAddress::State_e', 
                   [], 
                   is_const=True)
    ## ipv6-interface-address.h (module 'internet'): void ns3::Ipv6InterfaceAddress::SetAddress(ns3::Ipv6Address address) [member function]
    cls.add_method('SetAddress', 
                   'void', 
                   [param('ns3::Ipv6Address', 'address')])
    ## ipv6-interface-address.h (module 'internet'): void ns3::Ipv6InterfaceAddress::SetNsDadUid(uint32_t uid) [member function]
    cls.add_method('SetNsDadUid', 
                   'void', 
                   [param('uint32_t', 'uid')])
    ## ipv6-interface-address.h (module 'internet'): void ns3::Ipv6InterfaceAddress::SetScope(ns3::Ipv6InterfaceAddress::Scope_e scope) [member function]
    cls.add_method('SetScope', 
                   'void', 
                   [param('ns3::Ipv6InterfaceAddress::Scope_e', 'scope')])
    ## ipv6-interface-address.h (module 'internet'): void ns3::Ipv6InterfaceAddress::SetState(ns3::Ipv6InterfaceAddress::State_e state) [member function]
    cls.add_method('SetState', 
                   'void', 
                   [param('ns3::Ipv6InterfaceAddress::State_e', 'state')])
    return

def register_Ns3Ipv6Prefix_methods(root_module, cls):
    cls.add_binary_comparison_operator('!=')
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    ## ipv6-address.h (module 'network'): ns3::Ipv6Prefix::Ipv6Prefix() [constructor]
    cls.add_constructor([])
    ## ipv6-address.h (module 'network'): ns3::Ipv6Prefix::Ipv6Prefix(uint8_t * prefix) [constructor]
    cls.add_constructor([param('uint8_t *', 'prefix')])
    ## ipv6-address.h (module 'network'): ns3::Ipv6Prefix::Ipv6Prefix(char const * prefix) [constructor]
    cls.add_constructor([param('char const *', 'prefix')])
    ## ipv6-address.h (module 'network'): ns3::Ipv6Prefix::Ipv6Prefix(uint8_t prefix) [constructor]
    cls.add_constructor([param('uint8_t', 'prefix')])
    ## ipv6-address.h (module 'network'): ns3::Ipv6Prefix::Ipv6Prefix(ns3::Ipv6Prefix const & prefix) [copy constructor]
    cls.add_constructor([param('ns3::Ipv6Prefix const &', 'prefix')])
    ## ipv6-address.h (module 'network'): ns3::Ipv6Prefix::Ipv6Prefix(ns3::Ipv6Prefix const * prefix) [constructor]
    cls.add_constructor([param('ns3::Ipv6Prefix const *', 'prefix')])
    ## ipv6-address.h (module 'network'): void ns3::Ipv6Prefix::GetBytes(uint8_t * buf) const [member function]
    cls.add_method('GetBytes', 
                   'void', 
                   [param('uint8_t *', 'buf')], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): static ns3::Ipv6Prefix ns3::Ipv6Prefix::GetLoopback() [member function]
    cls.add_method('GetLoopback', 
                   'ns3::Ipv6Prefix', 
                   [], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): static ns3::Ipv6Prefix ns3::Ipv6Prefix::GetOnes() [member function]
    cls.add_method('GetOnes', 
                   'ns3::Ipv6Prefix', 
                   [], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): uint8_t ns3::Ipv6Prefix::GetPrefixLength() const [member function]
    cls.add_method('GetPrefixLength', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): static ns3::Ipv6Prefix ns3::Ipv6Prefix::GetZero() [member function]
    cls.add_method('GetZero', 
                   'ns3::Ipv6Prefix', 
                   [], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): bool ns3::Ipv6Prefix::IsEqual(ns3::Ipv6Prefix const & other) const [member function]
    cls.add_method('IsEqual', 
                   'bool', 
                   [param('ns3::Ipv6Prefix const &', 'other')], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): bool ns3::Ipv6Prefix::IsMatch(ns3::Ipv6Address a, ns3::Ipv6Address b) const [member function]
    cls.add_method('IsMatch', 
                   'bool', 
                   [param('ns3::Ipv6Address', 'a'), param('ns3::Ipv6Address', 'b')], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): void ns3::Ipv6Prefix::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True)
    return

def register_Ns3LogComponent_methods(root_module, cls):
    ## log.h (module 'core'): ns3::LogComponent::LogComponent(ns3::LogComponent const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::LogComponent const &', 'arg0')])
    ## log.h (module 'core'): ns3::LogComponent::LogComponent(char const * name) [constructor]
    cls.add_constructor([param('char const *', 'name')])
    ## log.h (module 'core'): void ns3::LogComponent::Disable(ns3::LogLevel level) [member function]
    cls.add_method('Disable', 
                   'void', 
                   [param('ns3::LogLevel', 'level')])
    ## log.h (module 'core'): void ns3::LogComponent::Enable(ns3::LogLevel level) [member function]
    cls.add_method('Enable', 
                   'void', 
                   [param('ns3::LogLevel', 'level')])
    ## log.h (module 'core'): void ns3::LogComponent::EnvVarCheck(char const * name) [member function]
    cls.add_method('EnvVarCheck', 
                   'void', 
                   [param('char const *', 'name')])
    ## log.h (module 'core'): bool ns3::LogComponent::IsEnabled(ns3::LogLevel level) const [member function]
    cls.add_method('IsEnabled', 
                   'bool', 
                   [param('ns3::LogLevel', 'level')], 
                   is_const=True)
    ## log.h (module 'core'): bool ns3::LogComponent::IsNoneEnabled() const [member function]
    cls.add_method('IsNoneEnabled', 
                   'bool', 
                   [], 
                   is_const=True)
    ## log.h (module 'core'): char const * ns3::LogComponent::Name() const [member function]
    cls.add_method('Name', 
                   'char const *', 
                   [], 
                   is_const=True)
    return

def register_Ns3Mac48Address_methods(root_module, cls):
    cls.add_binary_comparison_operator('!=')
    cls.add_binary_comparison_operator('<')
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    ## mac48-address.h (module 'network'): ns3::Mac48Address::Mac48Address(ns3::Mac48Address const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Mac48Address const &', 'arg0')])
    ## mac48-address.h (module 'network'): ns3::Mac48Address::Mac48Address() [constructor]
    cls.add_constructor([])
    ## mac48-address.h (module 'network'): ns3::Mac48Address::Mac48Address(char const * str) [constructor]
    cls.add_constructor([param('char const *', 'str')])
    ## mac48-address.h (module 'network'): static ns3::Mac48Address ns3::Mac48Address::Allocate() [member function]
    cls.add_method('Allocate', 
                   'ns3::Mac48Address', 
                   [], 
                   is_static=True)
    ## mac48-address.h (module 'network'): static ns3::Mac48Address ns3::Mac48Address::ConvertFrom(ns3::Address const & address) [member function]
    cls.add_method('ConvertFrom', 
                   'ns3::Mac48Address', 
                   [param('ns3::Address const &', 'address')], 
                   is_static=True)
    ## mac48-address.h (module 'network'): void ns3::Mac48Address::CopyFrom(uint8_t const * buffer) [member function]
    cls.add_method('CopyFrom', 
                   'void', 
                   [param('uint8_t const *', 'buffer')])
    ## mac48-address.h (module 'network'): void ns3::Mac48Address::CopyTo(uint8_t * buffer) const [member function]
    cls.add_method('CopyTo', 
                   'void', 
                   [param('uint8_t *', 'buffer')], 
                   is_const=True)
    ## mac48-address.h (module 'network'): static ns3::Mac48Address ns3::Mac48Address::GetBroadcast() [member function]
    cls.add_method('GetBroadcast', 
                   'ns3::Mac48Address', 
                   [], 
                   is_static=True)
    ## mac48-address.h (module 'network'): static ns3::Mac48Address ns3::Mac48Address::GetMulticast(ns3::Ipv4Address address) [member function]
    cls.add_method('GetMulticast', 
                   'ns3::Mac48Address', 
                   [param('ns3::Ipv4Address', 'address')], 
                   is_static=True)
    ## mac48-address.h (module 'network'): static ns3::Mac48Address ns3::Mac48Address::GetMulticast(ns3::Ipv6Address address) [member function]
    cls.add_method('GetMulticast', 
                   'ns3::Mac48Address', 
                   [param('ns3::Ipv6Address', 'address')], 
                   is_static=True)
    ## mac48-address.h (module 'network'): static ns3::Mac48Address ns3::Mac48Address::GetMulticast6Prefix() [member function]
    cls.add_method('GetMulticast6Prefix', 
                   'ns3::Mac48Address', 
                   [], 
                   is_static=True)
    ## mac48-address.h (module 'network'): static ns3::Mac48Address ns3::Mac48Address::GetMulticastPrefix() [member function]
    cls.add_method('GetMulticastPrefix', 
                   'ns3::Mac48Address', 
                   [], 
                   is_static=True)
    ## mac48-address.h (module 'network'): bool ns3::Mac48Address::IsBroadcast() const [member function]
    cls.add_method('IsBroadcast', 
                   'bool', 
                   [], 
                   is_const=True)
    ## mac48-address.h (module 'network'): bool ns3::Mac48Address::IsGroup() const [member function]
    cls.add_method('IsGroup', 
                   'bool', 
                   [], 
                   is_const=True)
    ## mac48-address.h (module 'network'): static bool ns3::Mac48Address::IsMatchingType(ns3::Address const & address) [member function]
    cls.add_method('IsMatchingType', 
                   'bool', 
                   [param('ns3::Address const &', 'address')], 
                   is_static=True)
    return

def register_Ns3NodeContainer_methods(root_module, cls):
    ## node-container.h (module 'network'): ns3::NodeContainer::NodeContainer(ns3::NodeContainer const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::NodeContainer const &', 'arg0')])
    ## node-container.h (module 'network'): ns3::NodeContainer::NodeContainer() [constructor]
    cls.add_constructor([])
    ## node-container.h (module 'network'): ns3::NodeContainer::NodeContainer(ns3::Ptr<ns3::Node> node) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::Node >', 'node')])
    ## node-container.h (module 'network'): ns3::NodeContainer::NodeContainer(std::string nodeName) [constructor]
    cls.add_constructor([param('std::string', 'nodeName')])
    ## node-container.h (module 'network'): ns3::NodeContainer::NodeContainer(ns3::NodeContainer const & a, ns3::NodeContainer const & b) [constructor]
    cls.add_constructor([param('ns3::NodeContainer const &', 'a'), param('ns3::NodeContainer const &', 'b')])
    ## node-container.h (module 'network'): ns3::NodeContainer::NodeContainer(ns3::NodeContainer const & a, ns3::NodeContainer const & b, ns3::NodeContainer const & c) [constructor]
    cls.add_constructor([param('ns3::NodeContainer const &', 'a'), param('ns3::NodeContainer const &', 'b'), param('ns3::NodeContainer const &', 'c')])
    ## node-container.h (module 'network'): ns3::NodeContainer::NodeContainer(ns3::NodeContainer const & a, ns3::NodeContainer const & b, ns3::NodeContainer const & c, ns3::NodeContainer const & d) [constructor]
    cls.add_constructor([param('ns3::NodeContainer const &', 'a'), param('ns3::NodeContainer const &', 'b'), param('ns3::NodeContainer const &', 'c'), param('ns3::NodeContainer const &', 'd')])
    ## node-container.h (module 'network'): ns3::NodeContainer::NodeContainer(ns3::NodeContainer const & a, ns3::NodeContainer const & b, ns3::NodeContainer const & c, ns3::NodeContainer const & d, ns3::NodeContainer const & e) [constructor]
    cls.add_constructor([param('ns3::NodeContainer const &', 'a'), param('ns3::NodeContainer const &', 'b'), param('ns3::NodeContainer const &', 'c'), param('ns3::NodeContainer const &', 'd'), param('ns3::NodeContainer const &', 'e')])
    ## node-container.h (module 'network'): void ns3::NodeContainer::Add(ns3::NodeContainer other) [member function]
    cls.add_method('Add', 
                   'void', 
                   [param('ns3::NodeContainer', 'other')])
    ## node-container.h (module 'network'): void ns3::NodeContainer::Add(ns3::Ptr<ns3::Node> node) [member function]
    cls.add_method('Add', 
                   'void', 
                   [param('ns3::Ptr< ns3::Node >', 'node')])
    ## node-container.h (module 'network'): void ns3::NodeContainer::Add(std::string nodeName) [member function]
    cls.add_method('Add', 
                   'void', 
                   [param('std::string', 'nodeName')])
    ## node-container.h (module 'network'): __gnu_cxx::__normal_iterator<const ns3::Ptr<ns3::Node>*,std::vector<ns3::Ptr<ns3::Node>, std::allocator<ns3::Ptr<ns3::Node> > > > ns3::NodeContainer::Begin() const [member function]
    cls.add_method('Begin', 
                   '__gnu_cxx::__normal_iterator< ns3::Ptr< ns3::Node > const, std::vector< ns3::Ptr< ns3::Node > > >', 
                   [], 
                   is_const=True)
    ## node-container.h (module 'network'): void ns3::NodeContainer::Create(uint32_t n) [member function]
    cls.add_method('Create', 
                   'void', 
                   [param('uint32_t', 'n')])
    ## node-container.h (module 'network'): void ns3::NodeContainer::Create(uint32_t n, uint32_t systemId) [member function]
    cls.add_method('Create', 
                   'void', 
                   [param('uint32_t', 'n'), param('uint32_t', 'systemId')])
    ## node-container.h (module 'network'): __gnu_cxx::__normal_iterator<const ns3::Ptr<ns3::Node>*,std::vector<ns3::Ptr<ns3::Node>, std::allocator<ns3::Ptr<ns3::Node> > > > ns3::NodeContainer::End() const [member function]
    cls.add_method('End', 
                   '__gnu_cxx::__normal_iterator< ns3::Ptr< ns3::Node > const, std::vector< ns3::Ptr< ns3::Node > > >', 
                   [], 
                   is_const=True)
    ## node-container.h (module 'network'): ns3::Ptr<ns3::Node> ns3::NodeContainer::Get(uint32_t i) const [member function]
    cls.add_method('Get', 
                   'ns3::Ptr< ns3::Node >', 
                   [param('uint32_t', 'i')], 
                   is_const=True)
    ## node-container.h (module 'network'): static ns3::NodeContainer ns3::NodeContainer::GetGlobal() [member function]
    cls.add_method('GetGlobal', 
                   'ns3::NodeContainer', 
                   [], 
                   is_static=True)
    ## node-container.h (module 'network'): uint32_t ns3::NodeContainer::GetN() const [member function]
    cls.add_method('GetN', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    return

def register_Ns3ObjectBase_methods(root_module, cls):
    ## object-base.h (module 'core'): ns3::ObjectBase::ObjectBase() [constructor]
    cls.add_constructor([])
    ## object-base.h (module 'core'): ns3::ObjectBase::ObjectBase(ns3::ObjectBase const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::ObjectBase const &', 'arg0')])
    ## object-base.h (module 'core'): void ns3::ObjectBase::GetAttribute(std::string name, ns3::AttributeValue & value) const [member function]
    cls.add_method('GetAttribute', 
                   'void', 
                   [param('std::string', 'name'), param('ns3::AttributeValue &', 'value')], 
                   is_const=True)
    ## object-base.h (module 'core'): bool ns3::ObjectBase::GetAttributeFailSafe(std::string name, ns3::AttributeValue & attribute) const [member function]
    cls.add_method('GetAttributeFailSafe', 
                   'bool', 
                   [param('std::string', 'name'), param('ns3::AttributeValue &', 'attribute')], 
                   is_const=True)
    ## object-base.h (module 'core'): ns3::TypeId ns3::ObjectBase::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## object-base.h (module 'core'): static ns3::TypeId ns3::ObjectBase::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## object-base.h (module 'core'): void ns3::ObjectBase::SetAttribute(std::string name, ns3::AttributeValue const & value) [member function]
    cls.add_method('SetAttribute', 
                   'void', 
                   [param('std::string', 'name'), param('ns3::AttributeValue const &', 'value')])
    ## object-base.h (module 'core'): bool ns3::ObjectBase::SetAttributeFailSafe(std::string name, ns3::AttributeValue const & value) [member function]
    cls.add_method('SetAttributeFailSafe', 
                   'bool', 
                   [param('std::string', 'name'), param('ns3::AttributeValue const &', 'value')])
    ## object-base.h (module 'core'): bool ns3::ObjectBase::TraceConnect(std::string name, std::string context, ns3::CallbackBase const & cb) [member function]
    cls.add_method('TraceConnect', 
                   'bool', 
                   [param('std::string', 'name'), param('std::string', 'context'), param('ns3::CallbackBase const &', 'cb')])
    ## object-base.h (module 'core'): bool ns3::ObjectBase::TraceConnectWithoutContext(std::string name, ns3::CallbackBase const & cb) [member function]
    cls.add_method('TraceConnectWithoutContext', 
                   'bool', 
                   [param('std::string', 'name'), param('ns3::CallbackBase const &', 'cb')])
    ## object-base.h (module 'core'): bool ns3::ObjectBase::TraceDisconnect(std::string name, std::string context, ns3::CallbackBase const & cb) [member function]
    cls.add_method('TraceDisconnect', 
                   'bool', 
                   [param('std::string', 'name'), param('std::string', 'context'), param('ns3::CallbackBase const &', 'cb')])
    ## object-base.h (module 'core'): bool ns3::ObjectBase::TraceDisconnectWithoutContext(std::string name, ns3::CallbackBase const & cb) [member function]
    cls.add_method('TraceDisconnectWithoutContext', 
                   'bool', 
                   [param('std::string', 'name'), param('ns3::CallbackBase const &', 'cb')])
    ## object-base.h (module 'core'): void ns3::ObjectBase::ConstructSelf(ns3::AttributeConstructionList const & attributes) [member function]
    cls.add_method('ConstructSelf', 
                   'void', 
                   [param('ns3::AttributeConstructionList const &', 'attributes')], 
                   visibility='protected')
    ## object-base.h (module 'core'): void ns3::ObjectBase::NotifyConstructionCompleted() [member function]
    cls.add_method('NotifyConstructionCompleted', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    return

def register_Ns3ObjectDeleter_methods(root_module, cls):
    ## object.h (module 'core'): ns3::ObjectDeleter::ObjectDeleter() [constructor]
    cls.add_constructor([])
    ## object.h (module 'core'): ns3::ObjectDeleter::ObjectDeleter(ns3::ObjectDeleter const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::ObjectDeleter const &', 'arg0')])
    ## object.h (module 'core'): static void ns3::ObjectDeleter::Delete(ns3::Object * object) [member function]
    cls.add_method('Delete', 
                   'void', 
                   [param('ns3::Object *', 'object')], 
                   is_static=True)
    return

def register_Ns3ObjectFactory_methods(root_module, cls):
    cls.add_output_stream_operator()
    ## object-factory.h (module 'core'): ns3::ObjectFactory::ObjectFactory(ns3::ObjectFactory const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::ObjectFactory const &', 'arg0')])
    ## object-factory.h (module 'core'): ns3::ObjectFactory::ObjectFactory() [constructor]
    cls.add_constructor([])
    ## object-factory.h (module 'core'): ns3::ObjectFactory::ObjectFactory(std::string typeId) [constructor]
    cls.add_constructor([param('std::string', 'typeId')])
    ## object-factory.h (module 'core'): ns3::Ptr<ns3::Object> ns3::ObjectFactory::Create() const [member function]
    cls.add_method('Create', 
                   'ns3::Ptr< ns3::Object >', 
                   [], 
                   is_const=True)
    ## object-factory.h (module 'core'): ns3::TypeId ns3::ObjectFactory::GetTypeId() const [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True)
    ## object-factory.h (module 'core'): void ns3::ObjectFactory::Set(std::string name, ns3::AttributeValue const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('std::string', 'name'), param('ns3::AttributeValue const &', 'value')])
    ## object-factory.h (module 'core'): void ns3::ObjectFactory::SetTypeId(ns3::TypeId tid) [member function]
    cls.add_method('SetTypeId', 
                   'void', 
                   [param('ns3::TypeId', 'tid')])
    ## object-factory.h (module 'core'): void ns3::ObjectFactory::SetTypeId(char const * tid) [member function]
    cls.add_method('SetTypeId', 
                   'void', 
                   [param('char const *', 'tid')])
    ## object-factory.h (module 'core'): void ns3::ObjectFactory::SetTypeId(std::string tid) [member function]
    cls.add_method('SetTypeId', 
                   'void', 
                   [param('std::string', 'tid')])
    return

def register_Ns3OlsrState_methods(root_module, cls):
    ## olsr-state.h (module 'olsr'): ns3::OlsrState::OlsrState(ns3::OlsrState const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::OlsrState const &', 'arg0')])
    ## olsr-state.h (module 'olsr'): ns3::OlsrState::OlsrState() [constructor]
    cls.add_constructor([])
    ## olsr-state.h (module 'olsr'): void ns3::OlsrState::EraseAssociation(ns3::olsr::Association const & tuple) [member function]
    cls.add_method('EraseAssociation', 
                   'void', 
                   [param('ns3::olsr::Association const &', 'tuple')])
    ## olsr-state.h (module 'olsr'): void ns3::OlsrState::EraseAssociationTuple(ns3::olsr::AssociationTuple const & tuple) [member function]
    cls.add_method('EraseAssociationTuple', 
                   'void', 
                   [param('ns3::olsr::AssociationTuple const &', 'tuple')])
    ## olsr-state.h (module 'olsr'): void ns3::OlsrState::EraseDuplicateTuple(ns3::olsr::DuplicateTuple const & tuple) [member function]
    cls.add_method('EraseDuplicateTuple', 
                   'void', 
                   [param('ns3::olsr::DuplicateTuple const &', 'tuple')])
    ## olsr-state.h (module 'olsr'): void ns3::OlsrState::EraseIfaceAssocTuple(ns3::olsr::IfaceAssocTuple const & tuple) [member function]
    cls.add_method('EraseIfaceAssocTuple', 
                   'void', 
                   [param('ns3::olsr::IfaceAssocTuple const &', 'tuple')])
    ## olsr-state.h (module 'olsr'): void ns3::OlsrState::EraseLinkTuple(ns3::olsr::LinkTuple const & tuple) [member function]
    cls.add_method('EraseLinkTuple', 
                   'void', 
                   [param('ns3::olsr::LinkTuple const &', 'tuple')])
    ## olsr-state.h (module 'olsr'): void ns3::OlsrState::EraseMprSelectorTuple(ns3::olsr::MprSelectorTuple const & tuple) [member function]
    cls.add_method('EraseMprSelectorTuple', 
                   'void', 
                   [param('ns3::olsr::MprSelectorTuple const &', 'tuple')])
    ## olsr-state.h (module 'olsr'): void ns3::OlsrState::EraseMprSelectorTuples(ns3::Ipv4Address const & mainAddr) [member function]
    cls.add_method('EraseMprSelectorTuples', 
                   'void', 
                   [param('ns3::Ipv4Address const &', 'mainAddr')])
    ## olsr-state.h (module 'olsr'): void ns3::OlsrState::EraseNeighborTuple(ns3::olsr::NeighborTuple const & neighborTuple) [member function]
    cls.add_method('EraseNeighborTuple', 
                   'void', 
                   [param('ns3::olsr::NeighborTuple const &', 'neighborTuple')])
    ## olsr-state.h (module 'olsr'): void ns3::OlsrState::EraseNeighborTuple(ns3::Ipv4Address const & mainAddr) [member function]
    cls.add_method('EraseNeighborTuple', 
                   'void', 
                   [param('ns3::Ipv4Address const &', 'mainAddr')])
    ## olsr-state.h (module 'olsr'): void ns3::OlsrState::EraseOlderTopologyTuples(ns3::Ipv4Address const & lastAddr, uint16_t ansn) [member function]
    cls.add_method('EraseOlderTopologyTuples', 
                   'void', 
                   [param('ns3::Ipv4Address const &', 'lastAddr'), param('uint16_t', 'ansn')])
    ## olsr-state.h (module 'olsr'): void ns3::OlsrState::EraseTopologyTuple(ns3::olsr::TopologyTuple const & tuple) [member function]
    cls.add_method('EraseTopologyTuple', 
                   'void', 
                   [param('ns3::olsr::TopologyTuple const &', 'tuple')])
    ## olsr-state.h (module 'olsr'): void ns3::OlsrState::EraseTwoHopNeighborTuple(ns3::olsr::TwoHopNeighborTuple const & tuple) [member function]
    cls.add_method('EraseTwoHopNeighborTuple', 
                   'void', 
                   [param('ns3::olsr::TwoHopNeighborTuple const &', 'tuple')])
    ## olsr-state.h (module 'olsr'): void ns3::OlsrState::EraseTwoHopNeighborTuples(ns3::Ipv4Address const & neighbor) [member function]
    cls.add_method('EraseTwoHopNeighborTuples', 
                   'void', 
                   [param('ns3::Ipv4Address const &', 'neighbor')])
    ## olsr-state.h (module 'olsr'): void ns3::OlsrState::EraseTwoHopNeighborTuples(ns3::Ipv4Address const & neighbor, ns3::Ipv4Address const & twoHopNeighbor) [member function]
    cls.add_method('EraseTwoHopNeighborTuples', 
                   'void', 
                   [param('ns3::Ipv4Address const &', 'neighbor'), param('ns3::Ipv4Address const &', 'twoHopNeighbor')])
    ## olsr-state.h (module 'olsr'): ns3::olsr::AssociationTuple * ns3::OlsrState::FindAssociationTuple(ns3::Ipv4Address const & gatewayAddr, ns3::Ipv4Address const & networkAddr, ns3::Ipv4Mask const & netmask) [member function]
    cls.add_method('FindAssociationTuple', 
                   'ns3::olsr::AssociationTuple *', 
                   [param('ns3::Ipv4Address const &', 'gatewayAddr'), param('ns3::Ipv4Address const &', 'networkAddr'), param('ns3::Ipv4Mask const &', 'netmask')])
    ## olsr-state.h (module 'olsr'): ns3::olsr::DuplicateTuple * ns3::OlsrState::FindDuplicateTuple(ns3::Ipv4Address const & address, uint16_t sequenceNumber) [member function]
    cls.add_method('FindDuplicateTuple', 
                   'ns3::olsr::DuplicateTuple *', 
                   [param('ns3::Ipv4Address const &', 'address'), param('uint16_t', 'sequenceNumber')])
    ## olsr-state.h (module 'olsr'): ns3::olsr::IfaceAssocTuple * ns3::OlsrState::FindIfaceAssocTuple(ns3::Ipv4Address const & ifaceAddr) [member function]
    cls.add_method('FindIfaceAssocTuple', 
                   'ns3::olsr::IfaceAssocTuple *', 
                   [param('ns3::Ipv4Address const &', 'ifaceAddr')])
    ## olsr-state.h (module 'olsr'): ns3::olsr::IfaceAssocTuple const * ns3::OlsrState::FindIfaceAssocTuple(ns3::Ipv4Address const & ifaceAddr) const [member function]
    cls.add_method('FindIfaceAssocTuple', 
                   'ns3::olsr::IfaceAssocTuple const *', 
                   [param('ns3::Ipv4Address const &', 'ifaceAddr')], 
                   is_const=True)
    ## olsr-state.h (module 'olsr'): ns3::olsr::LinkTuple * ns3::OlsrState::FindLinkTuple(ns3::Ipv4Address const & ifaceAddr) [member function]
    cls.add_method('FindLinkTuple', 
                   'ns3::olsr::LinkTuple *', 
                   [param('ns3::Ipv4Address const &', 'ifaceAddr')])
    ## olsr-state.h (module 'olsr'): bool ns3::OlsrState::FindMprAddress(ns3::Ipv4Address const & address) [member function]
    cls.add_method('FindMprAddress', 
                   'bool', 
                   [param('ns3::Ipv4Address const &', 'address')])
    ## olsr-state.h (module 'olsr'): ns3::olsr::MprSelectorTuple * ns3::OlsrState::FindMprSelectorTuple(ns3::Ipv4Address const & mainAddr) [member function]
    cls.add_method('FindMprSelectorTuple', 
                   'ns3::olsr::MprSelectorTuple *', 
                   [param('ns3::Ipv4Address const &', 'mainAddr')])
    ## olsr-state.h (module 'olsr'): std::vector<ns3::Ipv4Address, std::allocator<ns3::Ipv4Address> > ns3::OlsrState::FindNeighborInterfaces(ns3::Ipv4Address const & neighborMainAddr) const [member function]
    cls.add_method('FindNeighborInterfaces', 
                   'std::vector< ns3::Ipv4Address >', 
                   [param('ns3::Ipv4Address const &', 'neighborMainAddr')], 
                   is_const=True)
    ## olsr-state.h (module 'olsr'): ns3::olsr::NeighborTuple * ns3::OlsrState::FindNeighborTuple(ns3::Ipv4Address const & mainAddr) [member function]
    cls.add_method('FindNeighborTuple', 
                   'ns3::olsr::NeighborTuple *', 
                   [param('ns3::Ipv4Address const &', 'mainAddr')])
    ## olsr-state.h (module 'olsr'): ns3::olsr::NeighborTuple * ns3::OlsrState::FindNeighborTuple(ns3::Ipv4Address const & mainAddr, uint8_t willingness) [member function]
    cls.add_method('FindNeighborTuple', 
                   'ns3::olsr::NeighborTuple *', 
                   [param('ns3::Ipv4Address const &', 'mainAddr'), param('uint8_t', 'willingness')])
    ## olsr-state.h (module 'olsr'): ns3::olsr::TopologyTuple * ns3::OlsrState::FindNewerTopologyTuple(ns3::Ipv4Address const & lastAddr, uint16_t ansn) [member function]
    cls.add_method('FindNewerTopologyTuple', 
                   'ns3::olsr::TopologyTuple *', 
                   [param('ns3::Ipv4Address const &', 'lastAddr'), param('uint16_t', 'ansn')])
    ## olsr-state.h (module 'olsr'): ns3::olsr::LinkTuple * ns3::OlsrState::FindSymLinkTuple(ns3::Ipv4Address const & ifaceAddr, ns3::Time time) [member function]
    cls.add_method('FindSymLinkTuple', 
                   'ns3::olsr::LinkTuple *', 
                   [param('ns3::Ipv4Address const &', 'ifaceAddr'), param('ns3::Time', 'time')])
    ## olsr-state.h (module 'olsr'): ns3::olsr::NeighborTuple const * ns3::OlsrState::FindSymNeighborTuple(ns3::Ipv4Address const & mainAddr) const [member function]
    cls.add_method('FindSymNeighborTuple', 
                   'ns3::olsr::NeighborTuple const *', 
                   [param('ns3::Ipv4Address const &', 'mainAddr')], 
                   is_const=True)
    ## olsr-state.h (module 'olsr'): ns3::olsr::TopologyTuple * ns3::OlsrState::FindTopologyTuple(ns3::Ipv4Address const & destAddr, ns3::Ipv4Address const & lastAddr) [member function]
    cls.add_method('FindTopologyTuple', 
                   'ns3::olsr::TopologyTuple *', 
                   [param('ns3::Ipv4Address const &', 'destAddr'), param('ns3::Ipv4Address const &', 'lastAddr')])
    ## olsr-state.h (module 'olsr'): ns3::olsr::TwoHopNeighborTuple * ns3::OlsrState::FindTwoHopNeighborTuple(ns3::Ipv4Address const & neighbor, ns3::Ipv4Address const & twoHopNeighbor) [member function]
    cls.add_method('FindTwoHopNeighborTuple', 
                   'ns3::olsr::TwoHopNeighborTuple *', 
                   [param('ns3::Ipv4Address const &', 'neighbor'), param('ns3::Ipv4Address const &', 'twoHopNeighbor')])
    ## olsr-state.h (module 'olsr'): ns3::olsr::AssociationSet const & ns3::OlsrState::GetAssociationSet() const [member function]
    cls.add_method('GetAssociationSet', 
                   'ns3::olsr::AssociationSet const &', 
                   [], 
                   is_const=True)
    ## olsr-state.h (module 'olsr'): ns3::olsr::Associations const & ns3::OlsrState::GetAssociations() const [member function]
    cls.add_method('GetAssociations', 
                   'ns3::olsr::Associations const &', 
                   [], 
                   is_const=True)
    ## olsr-state.h (module 'olsr'): ns3::olsr::IfaceAssocSet const & ns3::OlsrState::GetIfaceAssocSet() const [member function]
    cls.add_method('GetIfaceAssocSet', 
                   'ns3::olsr::IfaceAssocSet const &', 
                   [], 
                   is_const=True)
    ## olsr-state.h (module 'olsr'): ns3::olsr::IfaceAssocSet & ns3::OlsrState::GetIfaceAssocSetMutable() [member function]
    cls.add_method('GetIfaceAssocSetMutable', 
                   'ns3::olsr::IfaceAssocSet &', 
                   [])
    ## olsr-state.h (module 'olsr'): ns3::olsr::LinkSet const & ns3::OlsrState::GetLinks() const [member function]
    cls.add_method('GetLinks', 
                   'ns3::olsr::LinkSet const &', 
                   [], 
                   is_const=True)
    ## olsr-state.h (module 'olsr'): ns3::olsr::MprSelectorSet const & ns3::OlsrState::GetMprSelectors() const [member function]
    cls.add_method('GetMprSelectors', 
                   'ns3::olsr::MprSelectorSet const &', 
                   [], 
                   is_const=True)
    ## olsr-state.h (module 'olsr'): ns3::olsr::MprSet ns3::OlsrState::GetMprSet() const [member function]
    cls.add_method('GetMprSet', 
                   'ns3::olsr::MprSet', 
                   [], 
                   is_const=True)
    ## olsr-state.h (module 'olsr'): ns3::olsr::NeighborSet const & ns3::OlsrState::GetNeighbors() const [member function]
    cls.add_method('GetNeighbors', 
                   'ns3::olsr::NeighborSet const &', 
                   [], 
                   is_const=True)
    ## olsr-state.h (module 'olsr'): ns3::olsr::NeighborSet & ns3::OlsrState::GetNeighbors() [member function]
    cls.add_method('GetNeighbors', 
                   'ns3::olsr::NeighborSet &', 
                   [])
    ## olsr-state.h (module 'olsr'): ns3::olsr::TopologySet const & ns3::OlsrState::GetTopologySet() const [member function]
    cls.add_method('GetTopologySet', 
                   'ns3::olsr::TopologySet const &', 
                   [], 
                   is_const=True)
    ## olsr-state.h (module 'olsr'): ns3::olsr::TwoHopNeighborSet const & ns3::OlsrState::GetTwoHopNeighbors() const [member function]
    cls.add_method('GetTwoHopNeighbors', 
                   'ns3::olsr::TwoHopNeighborSet const &', 
                   [], 
                   is_const=True)
    ## olsr-state.h (module 'olsr'): ns3::olsr::TwoHopNeighborSet & ns3::OlsrState::GetTwoHopNeighbors() [member function]
    cls.add_method('GetTwoHopNeighbors', 
                   'ns3::olsr::TwoHopNeighborSet &', 
                   [])
    ## olsr-state.h (module 'olsr'): void ns3::OlsrState::InsertAssociation(ns3::olsr::Association const & tuple) [member function]
    cls.add_method('InsertAssociation', 
                   'void', 
                   [param('ns3::olsr::Association const &', 'tuple')])
    ## olsr-state.h (module 'olsr'): void ns3::OlsrState::InsertAssociationTuple(ns3::olsr::AssociationTuple const & tuple) [member function]
    cls.add_method('InsertAssociationTuple', 
                   'void', 
                   [param('ns3::olsr::AssociationTuple const &', 'tuple')])
    ## olsr-state.h (module 'olsr'): void ns3::OlsrState::InsertDuplicateTuple(ns3::olsr::DuplicateTuple const & tuple) [member function]
    cls.add_method('InsertDuplicateTuple', 
                   'void', 
                   [param('ns3::olsr::DuplicateTuple const &', 'tuple')])
    ## olsr-state.h (module 'olsr'): void ns3::OlsrState::InsertIfaceAssocTuple(ns3::olsr::IfaceAssocTuple const & tuple) [member function]
    cls.add_method('InsertIfaceAssocTuple', 
                   'void', 
                   [param('ns3::olsr::IfaceAssocTuple const &', 'tuple')])
    ## olsr-state.h (module 'olsr'): ns3::olsr::LinkTuple & ns3::OlsrState::InsertLinkTuple(ns3::olsr::LinkTuple const & tuple) [member function]
    cls.add_method('InsertLinkTuple', 
                   'ns3::olsr::LinkTuple &', 
                   [param('ns3::olsr::LinkTuple const &', 'tuple')])
    ## olsr-state.h (module 'olsr'): void ns3::OlsrState::InsertMprSelectorTuple(ns3::olsr::MprSelectorTuple const & tuple) [member function]
    cls.add_method('InsertMprSelectorTuple', 
                   'void', 
                   [param('ns3::olsr::MprSelectorTuple const &', 'tuple')])
    ## olsr-state.h (module 'olsr'): void ns3::OlsrState::InsertNeighborTuple(ns3::olsr::NeighborTuple const & tuple) [member function]
    cls.add_method('InsertNeighborTuple', 
                   'void', 
                   [param('ns3::olsr::NeighborTuple const &', 'tuple')])
    ## olsr-state.h (module 'olsr'): void ns3::OlsrState::InsertTopologyTuple(ns3::olsr::TopologyTuple const & tuple) [member function]
    cls.add_method('InsertTopologyTuple', 
                   'void', 
                   [param('ns3::olsr::TopologyTuple const &', 'tuple')])
    ## olsr-state.h (module 'olsr'): void ns3::OlsrState::InsertTwoHopNeighborTuple(ns3::olsr::TwoHopNeighborTuple const & tuple) [member function]
    cls.add_method('InsertTwoHopNeighborTuple', 
                   'void', 
                   [param('ns3::olsr::TwoHopNeighborTuple const &', 'tuple')])
    ## olsr-state.h (module 'olsr'): std::string ns3::OlsrState::PrintMprSelectorSet() const [member function]
    cls.add_method('PrintMprSelectorSet', 
                   'std::string', 
                   [], 
                   is_const=True)
    ## olsr-state.h (module 'olsr'): void ns3::OlsrState::SetMprSet(ns3::olsr::MprSet mprSet) [member function]
    cls.add_method('SetMprSet', 
                   'void', 
                   [param('ns3::olsr::MprSet', 'mprSet')])
    return

def register_Ns3PacketMetadata_methods(root_module, cls):
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::PacketMetadata(uint64_t uid, uint32_t size) [constructor]
    cls.add_constructor([param('uint64_t', 'uid'), param('uint32_t', 'size')])
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::PacketMetadata(ns3::PacketMetadata const & o) [copy constructor]
    cls.add_constructor([param('ns3::PacketMetadata const &', 'o')])
    ## packet-metadata.h (module 'network'): void ns3::PacketMetadata::AddAtEnd(ns3::PacketMetadata const & o) [member function]
    cls.add_method('AddAtEnd', 
                   'void', 
                   [param('ns3::PacketMetadata const &', 'o')])
    ## packet-metadata.h (module 'network'): void ns3::PacketMetadata::AddHeader(ns3::Header const & header, uint32_t size) [member function]
    cls.add_method('AddHeader', 
                   'void', 
                   [param('ns3::Header const &', 'header'), param('uint32_t', 'size')])
    ## packet-metadata.h (module 'network'): void ns3::PacketMetadata::AddPaddingAtEnd(uint32_t end) [member function]
    cls.add_method('AddPaddingAtEnd', 
                   'void', 
                   [param('uint32_t', 'end')])
    ## packet-metadata.h (module 'network'): void ns3::PacketMetadata::AddTrailer(ns3::Trailer const & trailer, uint32_t size) [member function]
    cls.add_method('AddTrailer', 
                   'void', 
                   [param('ns3::Trailer const &', 'trailer'), param('uint32_t', 'size')])
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::ItemIterator ns3::PacketMetadata::BeginItem(ns3::Buffer buffer) const [member function]
    cls.add_method('BeginItem', 
                   'ns3::PacketMetadata::ItemIterator', 
                   [param('ns3::Buffer', 'buffer')], 
                   is_const=True)
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata ns3::PacketMetadata::CreateFragment(uint32_t start, uint32_t end) const [member function]
    cls.add_method('CreateFragment', 
                   'ns3::PacketMetadata', 
                   [param('uint32_t', 'start'), param('uint32_t', 'end')], 
                   is_const=True)
    ## packet-metadata.h (module 'network'): uint32_t ns3::PacketMetadata::Deserialize(uint8_t const * buffer, uint32_t size) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('uint8_t const *', 'buffer'), param('uint32_t', 'size')])
    ## packet-metadata.h (module 'network'): static void ns3::PacketMetadata::Enable() [member function]
    cls.add_method('Enable', 
                   'void', 
                   [], 
                   is_static=True)
    ## packet-metadata.h (module 'network'): static void ns3::PacketMetadata::EnableChecking() [member function]
    cls.add_method('EnableChecking', 
                   'void', 
                   [], 
                   is_static=True)
    ## packet-metadata.h (module 'network'): uint32_t ns3::PacketMetadata::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## packet-metadata.h (module 'network'): uint64_t ns3::PacketMetadata::GetUid() const [member function]
    cls.add_method('GetUid', 
                   'uint64_t', 
                   [], 
                   is_const=True)
    ## packet-metadata.h (module 'network'): void ns3::PacketMetadata::RemoveAtEnd(uint32_t end) [member function]
    cls.add_method('RemoveAtEnd', 
                   'void', 
                   [param('uint32_t', 'end')])
    ## packet-metadata.h (module 'network'): void ns3::PacketMetadata::RemoveAtStart(uint32_t start) [member function]
    cls.add_method('RemoveAtStart', 
                   'void', 
                   [param('uint32_t', 'start')])
    ## packet-metadata.h (module 'network'): void ns3::PacketMetadata::RemoveHeader(ns3::Header const & header, uint32_t size) [member function]
    cls.add_method('RemoveHeader', 
                   'void', 
                   [param('ns3::Header const &', 'header'), param('uint32_t', 'size')])
    ## packet-metadata.h (module 'network'): void ns3::PacketMetadata::RemoveTrailer(ns3::Trailer const & trailer, uint32_t size) [member function]
    cls.add_method('RemoveTrailer', 
                   'void', 
                   [param('ns3::Trailer const &', 'trailer'), param('uint32_t', 'size')])
    ## packet-metadata.h (module 'network'): uint32_t ns3::PacketMetadata::Serialize(uint8_t * buffer, uint32_t maxSize) const [member function]
    cls.add_method('Serialize', 
                   'uint32_t', 
                   [param('uint8_t *', 'buffer'), param('uint32_t', 'maxSize')], 
                   is_const=True)
    return

def register_Ns3PacketMetadataItem_methods(root_module, cls):
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::Item::Item() [constructor]
    cls.add_constructor([])
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::Item::Item(ns3::PacketMetadata::Item const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PacketMetadata::Item const &', 'arg0')])
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::Item::current [variable]
    cls.add_instance_attribute('current', 'ns3::Buffer::Iterator', is_const=False)
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::Item::currentSize [variable]
    cls.add_instance_attribute('currentSize', 'uint32_t', is_const=False)
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::Item::currentTrimedFromEnd [variable]
    cls.add_instance_attribute('currentTrimedFromEnd', 'uint32_t', is_const=False)
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::Item::currentTrimedFromStart [variable]
    cls.add_instance_attribute('currentTrimedFromStart', 'uint32_t', is_const=False)
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::Item::isFragment [variable]
    cls.add_instance_attribute('isFragment', 'bool', is_const=False)
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::Item::tid [variable]
    cls.add_instance_attribute('tid', 'ns3::TypeId', is_const=False)
    return

def register_Ns3PacketMetadataItemIterator_methods(root_module, cls):
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::ItemIterator::ItemIterator(ns3::PacketMetadata::ItemIterator const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PacketMetadata::ItemIterator const &', 'arg0')])
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::ItemIterator::ItemIterator(ns3::PacketMetadata const * metadata, ns3::Buffer buffer) [constructor]
    cls.add_constructor([param('ns3::PacketMetadata const *', 'metadata'), param('ns3::Buffer', 'buffer')])
    ## packet-metadata.h (module 'network'): bool ns3::PacketMetadata::ItemIterator::HasNext() const [member function]
    cls.add_method('HasNext', 
                   'bool', 
                   [], 
                   is_const=True)
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::Item ns3::PacketMetadata::ItemIterator::Next() [member function]
    cls.add_method('Next', 
                   'ns3::PacketMetadata::Item', 
                   [])
    return

def register_Ns3PacketTagIterator_methods(root_module, cls):
    ## packet.h (module 'network'): ns3::PacketTagIterator::PacketTagIterator(ns3::PacketTagIterator const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PacketTagIterator const &', 'arg0')])
    ## packet.h (module 'network'): bool ns3::PacketTagIterator::HasNext() const [member function]
    cls.add_method('HasNext', 
                   'bool', 
                   [], 
                   is_const=True)
    ## packet.h (module 'network'): ns3::PacketTagIterator::Item ns3::PacketTagIterator::Next() [member function]
    cls.add_method('Next', 
                   'ns3::PacketTagIterator::Item', 
                   [])
    return

def register_Ns3PacketTagIteratorItem_methods(root_module, cls):
    ## packet.h (module 'network'): ns3::PacketTagIterator::Item::Item(ns3::PacketTagIterator::Item const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PacketTagIterator::Item const &', 'arg0')])
    ## packet.h (module 'network'): void ns3::PacketTagIterator::Item::GetTag(ns3::Tag & tag) const [member function]
    cls.add_method('GetTag', 
                   'void', 
                   [param('ns3::Tag &', 'tag')], 
                   is_const=True)
    ## packet.h (module 'network'): ns3::TypeId ns3::PacketTagIterator::Item::GetTypeId() const [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True)
    return

def register_Ns3PacketTagList_methods(root_module, cls):
    ## packet-tag-list.h (module 'network'): ns3::PacketTagList::PacketTagList() [constructor]
    cls.add_constructor([])
    ## packet-tag-list.h (module 'network'): ns3::PacketTagList::PacketTagList(ns3::PacketTagList const & o) [copy constructor]
    cls.add_constructor([param('ns3::PacketTagList const &', 'o')])
    ## packet-tag-list.h (module 'network'): void ns3::PacketTagList::Add(ns3::Tag const & tag) const [member function]
    cls.add_method('Add', 
                   'void', 
                   [param('ns3::Tag const &', 'tag')], 
                   is_const=True)
    ## packet-tag-list.h (module 'network'): ns3::PacketTagList::TagData const * ns3::PacketTagList::Head() const [member function]
    cls.add_method('Head', 
                   'ns3::PacketTagList::TagData const *', 
                   [], 
                   is_const=True)
    ## packet-tag-list.h (module 'network'): bool ns3::PacketTagList::Peek(ns3::Tag & tag) const [member function]
    cls.add_method('Peek', 
                   'bool', 
                   [param('ns3::Tag &', 'tag')], 
                   is_const=True)
    ## packet-tag-list.h (module 'network'): bool ns3::PacketTagList::Remove(ns3::Tag & tag) [member function]
    cls.add_method('Remove', 
                   'bool', 
                   [param('ns3::Tag &', 'tag')])
    ## packet-tag-list.h (module 'network'): void ns3::PacketTagList::RemoveAll() [member function]
    cls.add_method('RemoveAll', 
                   'void', 
                   [])
    return

def register_Ns3PacketTagListTagData_methods(root_module, cls):
    ## packet-tag-list.h (module 'network'): ns3::PacketTagList::TagData::TagData() [constructor]
    cls.add_constructor([])
    ## packet-tag-list.h (module 'network'): ns3::PacketTagList::TagData::TagData(ns3::PacketTagList::TagData const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PacketTagList::TagData const &', 'arg0')])
    ## packet-tag-list.h (module 'network'): ns3::PacketTagList::TagData::count [variable]
    cls.add_instance_attribute('count', 'uint32_t', is_const=False)
    ## packet-tag-list.h (module 'network'): ns3::PacketTagList::TagData::data [variable]
    cls.add_instance_attribute('data', 'uint8_t [ 20 ]', is_const=False)
    ## packet-tag-list.h (module 'network'): ns3::PacketTagList::TagData::next [variable]
    cls.add_instance_attribute('next', 'ns3::PacketTagList::TagData *', is_const=False)
    ## packet-tag-list.h (module 'network'): ns3::PacketTagList::TagData::tid [variable]
    cls.add_instance_attribute('tid', 'ns3::TypeId', is_const=False)
    return

def register_Ns3PimDmHelper_methods(root_module, cls):
    ## pimdm-helper.h (module 'pimdm'): ns3::PimDmHelper::PimDmHelper() [constructor]
    cls.add_constructor([])
    ## pimdm-helper.h (module 'pimdm'): ns3::PimDmHelper::PimDmHelper(ns3::PimDmHelper const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PimDmHelper const &', 'arg0')])
    ## pimdm-helper.h (module 'pimdm'): ns3::PimDmHelper * ns3::PimDmHelper::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::PimDmHelper *', 
                   [], 
                   is_const=True, is_virtual=True)
    ## pimdm-helper.h (module 'pimdm'): void ns3::PimDmHelper::ExcludeInterface(ns3::Ptr<ns3::Node> node, uint32_t interface) [member function]
    cls.add_method('ExcludeInterface', 
                   'void', 
                   [param('ns3::Ptr< ns3::Node >', 'node'), param('uint32_t', 'interface')])
    ## pimdm-helper.h (module 'pimdm'): ns3::Ptr<ns3::Ipv4RoutingProtocol> ns3::PimDmHelper::Create(ns3::Ptr<ns3::Node> node) const [member function]
    cls.add_method('Create', 
                   'ns3::Ptr< ns3::Ipv4RoutingProtocol >', 
                   [param('ns3::Ptr< ns3::Node >', 'node')], 
                   is_const=True, is_virtual=True)
    ## pimdm-helper.h (module 'pimdm'): void ns3::PimDmHelper::Set(std::string name, ns3::AttributeValue const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('std::string', 'name'), param('ns3::AttributeValue const &', 'value')])
    return

def register_Ns3RandomVariable_methods(root_module, cls):
    cls.add_output_stream_operator()
    ## random-variable.h (module 'core'): ns3::RandomVariable::RandomVariable() [constructor]
    cls.add_constructor([])
    ## random-variable.h (module 'core'): ns3::RandomVariable::RandomVariable(ns3::RandomVariable const & o) [copy constructor]
    cls.add_constructor([param('ns3::RandomVariable const &', 'o')])
    ## random-variable.h (module 'core'): uint32_t ns3::RandomVariable::GetInteger() const [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## random-variable.h (module 'core'): double ns3::RandomVariable::GetValue() const [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [], 
                   is_const=True)
    return

def register_Ns3RngSeedManager_methods(root_module, cls):
    ## rng-seed-manager.h (module 'core'): ns3::RngSeedManager::RngSeedManager() [constructor]
    cls.add_constructor([])
    ## rng-seed-manager.h (module 'core'): ns3::RngSeedManager::RngSeedManager(ns3::RngSeedManager const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::RngSeedManager const &', 'arg0')])
    ## rng-seed-manager.h (module 'core'): static uint64_t ns3::RngSeedManager::GetNextStreamIndex() [member function]
    cls.add_method('GetNextStreamIndex', 
                   'uint64_t', 
                   [], 
                   is_static=True)
    ## rng-seed-manager.h (module 'core'): static uint64_t ns3::RngSeedManager::GetRun() [member function]
    cls.add_method('GetRun', 
                   'uint64_t', 
                   [], 
                   is_static=True)
    ## rng-seed-manager.h (module 'core'): static uint32_t ns3::RngSeedManager::GetSeed() [member function]
    cls.add_method('GetSeed', 
                   'uint32_t', 
                   [], 
                   is_static=True)
    ## rng-seed-manager.h (module 'core'): static void ns3::RngSeedManager::SetRun(uint64_t run) [member function]
    cls.add_method('SetRun', 
                   'void', 
                   [param('uint64_t', 'run')], 
                   is_static=True)
    ## rng-seed-manager.h (module 'core'): static void ns3::RngSeedManager::SetSeed(uint32_t seed) [member function]
    cls.add_method('SetSeed', 
                   'void', 
                   [param('uint32_t', 'seed')], 
                   is_static=True)
    return

def register_Ns3SequentialVariable_methods(root_module, cls):
    ## random-variable.h (module 'core'): ns3::SequentialVariable::SequentialVariable(ns3::SequentialVariable const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::SequentialVariable const &', 'arg0')])
    ## random-variable.h (module 'core'): ns3::SequentialVariable::SequentialVariable(double f, double l, double i=1, uint32_t c=1) [constructor]
    cls.add_constructor([param('double', 'f'), param('double', 'l'), param('double', 'i', default_value='1'), param('uint32_t', 'c', default_value='1')])
    ## random-variable.h (module 'core'): ns3::SequentialVariable::SequentialVariable(double f, double l, ns3::RandomVariable const & i, uint32_t c=1) [constructor]
    cls.add_constructor([param('double', 'f'), param('double', 'l'), param('ns3::RandomVariable const &', 'i'), param('uint32_t', 'c', default_value='1')])
    return

def register_Ns3SimpleRefCount__Ns3Object_Ns3ObjectBase_Ns3ObjectDeleter_methods(root_module, cls):
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::Object, ns3::ObjectBase, ns3::ObjectDeleter>::SimpleRefCount() [constructor]
    cls.add_constructor([])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::Object, ns3::ObjectBase, ns3::ObjectDeleter>::SimpleRefCount(ns3::SimpleRefCount<ns3::Object, ns3::ObjectBase, ns3::ObjectDeleter> const & o) [copy constructor]
    cls.add_constructor([param('ns3::SimpleRefCount< ns3::Object, ns3::ObjectBase, ns3::ObjectDeleter > const &', 'o')])
    ## simple-ref-count.h (module 'core'): static void ns3::SimpleRefCount<ns3::Object, ns3::ObjectBase, ns3::ObjectDeleter>::Cleanup() [member function]
    cls.add_method('Cleanup', 
                   'void', 
                   [], 
                   is_static=True)
    return

def register_Ns3Simulator_methods(root_module, cls):
    ## simulator.h (module 'core'): ns3::Simulator::Simulator(ns3::Simulator const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Simulator const &', 'arg0')])
    ## simulator.h (module 'core'): static void ns3::Simulator::Cancel(ns3::EventId const & id) [member function]
    cls.add_method('Cancel', 
                   'void', 
                   [param('ns3::EventId const &', 'id')], 
                   is_static=True)
    ## simulator.h (module 'core'): static void ns3::Simulator::Destroy() [member function]
    cls.add_method('Destroy', 
                   'void', 
                   [], 
                   is_static=True)
    ## simulator.h (module 'core'): static uint32_t ns3::Simulator::GetContext() [member function]
    cls.add_method('GetContext', 
                   'uint32_t', 
                   [], 
                   is_static=True)
    ## simulator.h (module 'core'): static ns3::Time ns3::Simulator::GetDelayLeft(ns3::EventId const & id) [member function]
    cls.add_method('GetDelayLeft', 
                   'ns3::Time', 
                   [param('ns3::EventId const &', 'id')], 
                   is_static=True)
    ## simulator.h (module 'core'): static ns3::Ptr<ns3::SimulatorImpl> ns3::Simulator::GetImplementation() [member function]
    cls.add_method('GetImplementation', 
                   'ns3::Ptr< ns3::SimulatorImpl >', 
                   [], 
                   is_static=True)
    ## simulator.h (module 'core'): static ns3::Time ns3::Simulator::GetMaximumSimulationTime() [member function]
    cls.add_method('GetMaximumSimulationTime', 
                   'ns3::Time', 
                   [], 
                   is_static=True)
    ## simulator.h (module 'core'): static uint32_t ns3::Simulator::GetSystemId() [member function]
    cls.add_method('GetSystemId', 
                   'uint32_t', 
                   [], 
                   is_static=True)
    ## simulator.h (module 'core'): static bool ns3::Simulator::IsExpired(ns3::EventId const & id) [member function]
    cls.add_method('IsExpired', 
                   'bool', 
                   [param('ns3::EventId const &', 'id')], 
                   is_static=True)
    ## simulator.h (module 'core'): static bool ns3::Simulator::IsFinished() [member function]
    cls.add_method('IsFinished', 
                   'bool', 
                   [], 
                   is_static=True)
    ## simulator.h (module 'core'): static ns3::Time ns3::Simulator::Now() [member function]
    cls.add_method('Now', 
                   'ns3::Time', 
                   [], 
                   is_static=True)
    ## simulator.h (module 'core'): static void ns3::Simulator::Remove(ns3::EventId const & id) [member function]
    cls.add_method('Remove', 
                   'void', 
                   [param('ns3::EventId const &', 'id')], 
                   is_static=True)
    ## simulator.h (module 'core'): static void ns3::Simulator::SetImplementation(ns3::Ptr<ns3::SimulatorImpl> impl) [member function]
    cls.add_method('SetImplementation', 
                   'void', 
                   [param('ns3::Ptr< ns3::SimulatorImpl >', 'impl')], 
                   is_static=True)
    ## simulator.h (module 'core'): static void ns3::Simulator::SetScheduler(ns3::ObjectFactory schedulerFactory) [member function]
    cls.add_method('SetScheduler', 
                   'void', 
                   [param('ns3::ObjectFactory', 'schedulerFactory')], 
                   is_static=True)
    ## simulator.h (module 'core'): static void ns3::Simulator::Stop() [member function]
    cls.add_method('Stop', 
                   'void', 
                   [], 
                   is_static=True)
    ## simulator.h (module 'core'): static void ns3::Simulator::Stop(ns3::Time const & time) [member function]
    cls.add_method('Stop', 
                   'void', 
                   [param('ns3::Time const &', 'time')], 
                   is_static=True)
    return

def register_Ns3SystemWallClockMs_methods(root_module, cls):
    ## system-wall-clock-ms.h (module 'core'): ns3::SystemWallClockMs::SystemWallClockMs(ns3::SystemWallClockMs const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::SystemWallClockMs const &', 'arg0')])
    ## system-wall-clock-ms.h (module 'core'): ns3::SystemWallClockMs::SystemWallClockMs() [constructor]
    cls.add_constructor([])
    ## system-wall-clock-ms.h (module 'core'): int64_t ns3::SystemWallClockMs::End() [member function]
    cls.add_method('End', 
                   'int64_t', 
                   [])
    ## system-wall-clock-ms.h (module 'core'): int64_t ns3::SystemWallClockMs::GetElapsedReal() const [member function]
    cls.add_method('GetElapsedReal', 
                   'int64_t', 
                   [], 
                   is_const=True)
    ## system-wall-clock-ms.h (module 'core'): int64_t ns3::SystemWallClockMs::GetElapsedSystem() const [member function]
    cls.add_method('GetElapsedSystem', 
                   'int64_t', 
                   [], 
                   is_const=True)
    ## system-wall-clock-ms.h (module 'core'): int64_t ns3::SystemWallClockMs::GetElapsedUser() const [member function]
    cls.add_method('GetElapsedUser', 
                   'int64_t', 
                   [], 
                   is_const=True)
    ## system-wall-clock-ms.h (module 'core'): void ns3::SystemWallClockMs::Start() [member function]
    cls.add_method('Start', 
                   'void', 
                   [])
    return

def register_Ns3Tag_methods(root_module, cls):
    ## tag.h (module 'network'): ns3::Tag::Tag() [constructor]
    cls.add_constructor([])
    ## tag.h (module 'network'): ns3::Tag::Tag(ns3::Tag const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Tag const &', 'arg0')])
    ## tag.h (module 'network'): void ns3::Tag::Deserialize(ns3::TagBuffer i) [member function]
    cls.add_method('Deserialize', 
                   'void', 
                   [param('ns3::TagBuffer', 'i')], 
                   is_pure_virtual=True, is_virtual=True)
    ## tag.h (module 'network'): uint32_t ns3::Tag::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## tag.h (module 'network'): static ns3::TypeId ns3::Tag::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## tag.h (module 'network'): void ns3::Tag::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## tag.h (module 'network'): void ns3::Tag::Serialize(ns3::TagBuffer i) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::TagBuffer', 'i')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    return

def register_Ns3TagBuffer_methods(root_module, cls):
    ## tag-buffer.h (module 'network'): ns3::TagBuffer::TagBuffer(ns3::TagBuffer const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::TagBuffer const &', 'arg0')])
    ## tag-buffer.h (module 'network'): ns3::TagBuffer::TagBuffer(uint8_t * start, uint8_t * end) [constructor]
    cls.add_constructor([param('uint8_t *', 'start'), param('uint8_t *', 'end')])
    ## tag-buffer.h (module 'network'): void ns3::TagBuffer::CopyFrom(ns3::TagBuffer o) [member function]
    cls.add_method('CopyFrom', 
                   'void', 
                   [param('ns3::TagBuffer', 'o')])
    ## tag-buffer.h (module 'network'): void ns3::TagBuffer::Read(uint8_t * buffer, uint32_t size) [member function]
    cls.add_method('Read', 
                   'void', 
                   [param('uint8_t *', 'buffer'), param('uint32_t', 'size')])
    ## tag-buffer.h (module 'network'): double ns3::TagBuffer::ReadDouble() [member function]
    cls.add_method('ReadDouble', 
                   'double', 
                   [])
    ## tag-buffer.h (module 'network'): uint16_t ns3::TagBuffer::ReadU16() [member function]
    cls.add_method('ReadU16', 
                   'uint16_t', 
                   [])
    ## tag-buffer.h (module 'network'): uint32_t ns3::TagBuffer::ReadU32() [member function]
    cls.add_method('ReadU32', 
                   'uint32_t', 
                   [])
    ## tag-buffer.h (module 'network'): uint64_t ns3::TagBuffer::ReadU64() [member function]
    cls.add_method('ReadU64', 
                   'uint64_t', 
                   [])
    ## tag-buffer.h (module 'network'): uint8_t ns3::TagBuffer::ReadU8() [member function]
    cls.add_method('ReadU8', 
                   'uint8_t', 
                   [])
    ## tag-buffer.h (module 'network'): void ns3::TagBuffer::TrimAtEnd(uint32_t trim) [member function]
    cls.add_method('TrimAtEnd', 
                   'void', 
                   [param('uint32_t', 'trim')])
    ## tag-buffer.h (module 'network'): void ns3::TagBuffer::Write(uint8_t const * buffer, uint32_t size) [member function]
    cls.add_method('Write', 
                   'void', 
                   [param('uint8_t const *', 'buffer'), param('uint32_t', 'size')])
    ## tag-buffer.h (module 'network'): void ns3::TagBuffer::WriteDouble(double v) [member function]
    cls.add_method('WriteDouble', 
                   'void', 
                   [param('double', 'v')])
    ## tag-buffer.h (module 'network'): void ns3::TagBuffer::WriteU16(uint16_t data) [member function]
    cls.add_method('WriteU16', 
                   'void', 
                   [param('uint16_t', 'data')])
    ## tag-buffer.h (module 'network'): void ns3::TagBuffer::WriteU32(uint32_t data) [member function]
    cls.add_method('WriteU32', 
                   'void', 
                   [param('uint32_t', 'data')])
    ## tag-buffer.h (module 'network'): void ns3::TagBuffer::WriteU64(uint64_t v) [member function]
    cls.add_method('WriteU64', 
                   'void', 
                   [param('uint64_t', 'v')])
    ## tag-buffer.h (module 'network'): void ns3::TagBuffer::WriteU8(uint8_t v) [member function]
    cls.add_method('WriteU8', 
                   'void', 
                   [param('uint8_t', 'v')])
    return

def register_Ns3Timer_methods(root_module, cls):
    ## timer.h (module 'core'): ns3::Timer::Timer(ns3::Timer const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Timer const &', 'arg0')])
    ## timer.h (module 'core'): ns3::Timer::Timer() [constructor]
    cls.add_constructor([])
    ## timer.h (module 'core'): ns3::Timer::Timer(ns3::Timer::DestroyPolicy destroyPolicy) [constructor]
    cls.add_constructor([param('ns3::Timer::DestroyPolicy', 'destroyPolicy')])
    ## timer.h (module 'core'): void ns3::Timer::Cancel() [member function]
    cls.add_method('Cancel', 
                   'void', 
                   [])
    ## timer.h (module 'core'): ns3::Time ns3::Timer::GetDelay() const [member function]
    cls.add_method('GetDelay', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## timer.h (module 'core'): ns3::Time ns3::Timer::GetDelayLeft() const [member function]
    cls.add_method('GetDelayLeft', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## timer.h (module 'core'): ns3::Timer::State ns3::Timer::GetState() const [member function]
    cls.add_method('GetState', 
                   'ns3::Timer::State', 
                   [], 
                   is_const=True)
    ## timer.h (module 'core'): bool ns3::Timer::IsExpired() const [member function]
    cls.add_method('IsExpired', 
                   'bool', 
                   [], 
                   is_const=True)
    ## timer.h (module 'core'): bool ns3::Timer::IsRunning() const [member function]
    cls.add_method('IsRunning', 
                   'bool', 
                   [], 
                   is_const=True)
    ## timer.h (module 'core'): bool ns3::Timer::IsSuspended() const [member function]
    cls.add_method('IsSuspended', 
                   'bool', 
                   [], 
                   is_const=True)
    ## timer.h (module 'core'): void ns3::Timer::Remove() [member function]
    cls.add_method('Remove', 
                   'void', 
                   [])
    ## timer.h (module 'core'): void ns3::Timer::Resume() [member function]
    cls.add_method('Resume', 
                   'void', 
                   [])
    ## timer.h (module 'core'): void ns3::Timer::Schedule() [member function]
    cls.add_method('Schedule', 
                   'void', 
                   [])
    ## timer.h (module 'core'): void ns3::Timer::Schedule(ns3::Time delay) [member function]
    cls.add_method('Schedule', 
                   'void', 
                   [param('ns3::Time', 'delay')])
    ## timer.h (module 'core'): void ns3::Timer::SetDelay(ns3::Time const & delay) [member function]
    cls.add_method('SetDelay', 
                   'void', 
                   [param('ns3::Time const &', 'delay')])
    ## timer.h (module 'core'): void ns3::Timer::Suspend() [member function]
    cls.add_method('Suspend', 
                   'void', 
                   [])
    return

def register_Ns3TimerImpl_methods(root_module, cls):
    ## timer-impl.h (module 'core'): ns3::TimerImpl::TimerImpl() [constructor]
    cls.add_constructor([])
    ## timer-impl.h (module 'core'): ns3::TimerImpl::TimerImpl(ns3::TimerImpl const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::TimerImpl const &', 'arg0')])
    ## timer-impl.h (module 'core'): void ns3::TimerImpl::Invoke() [member function]
    cls.add_method('Invoke', 
                   'void', 
                   [], 
                   is_pure_virtual=True, is_virtual=True)
    ## timer-impl.h (module 'core'): ns3::EventId ns3::TimerImpl::Schedule(ns3::Time const & delay) [member function]
    cls.add_method('Schedule', 
                   'ns3::EventId', 
                   [param('ns3::Time const &', 'delay')], 
                   is_pure_virtual=True, is_virtual=True)
    return

def register_Ns3TriangularVariable_methods(root_module, cls):
    ## random-variable.h (module 'core'): ns3::TriangularVariable::TriangularVariable(ns3::TriangularVariable const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::TriangularVariable const &', 'arg0')])
    ## random-variable.h (module 'core'): ns3::TriangularVariable::TriangularVariable() [constructor]
    cls.add_constructor([])
    ## random-variable.h (module 'core'): ns3::TriangularVariable::TriangularVariable(double s, double l, double mean) [constructor]
    cls.add_constructor([param('double', 's'), param('double', 'l'), param('double', 'mean')])
    return

def register_Ns3TypeId_methods(root_module, cls):
    cls.add_binary_comparison_operator('!=')
    cls.add_binary_comparison_operator('<')
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    ## type-id.h (module 'core'): ns3::TypeId::TypeId(char const * name) [constructor]
    cls.add_constructor([param('char const *', 'name')])
    ## type-id.h (module 'core'): ns3::TypeId::TypeId() [constructor]
    cls.add_constructor([])
    ## type-id.h (module 'core'): ns3::TypeId::TypeId(ns3::TypeId const & o) [copy constructor]
    cls.add_constructor([param('ns3::TypeId const &', 'o')])
    ## type-id.h (module 'core'): ns3::TypeId ns3::TypeId::AddAttribute(std::string name, std::string help, ns3::AttributeValue const & initialValue, ns3::Ptr<ns3::AttributeAccessor const> accessor, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('AddAttribute', 
                   'ns3::TypeId', 
                   [param('std::string', 'name'), param('std::string', 'help'), param('ns3::AttributeValue const &', 'initialValue'), param('ns3::Ptr< ns3::AttributeAccessor const >', 'accessor'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')])
    ## type-id.h (module 'core'): ns3::TypeId ns3::TypeId::AddAttribute(std::string name, std::string help, uint32_t flags, ns3::AttributeValue const & initialValue, ns3::Ptr<ns3::AttributeAccessor const> accessor, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('AddAttribute', 
                   'ns3::TypeId', 
                   [param('std::string', 'name'), param('std::string', 'help'), param('uint32_t', 'flags'), param('ns3::AttributeValue const &', 'initialValue'), param('ns3::Ptr< ns3::AttributeAccessor const >', 'accessor'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')])
    ## type-id.h (module 'core'): ns3::TypeId ns3::TypeId::AddTraceSource(std::string name, std::string help, ns3::Ptr<ns3::TraceSourceAccessor const> accessor) [member function]
    cls.add_method('AddTraceSource', 
                   'ns3::TypeId', 
                   [param('std::string', 'name'), param('std::string', 'help'), param('ns3::Ptr< ns3::TraceSourceAccessor const >', 'accessor')])
    ## type-id.h (module 'core'): ns3::TypeId::AttributeInformation ns3::TypeId::GetAttribute(uint32_t i) const [member function]
    cls.add_method('GetAttribute', 
                   'ns3::TypeId::AttributeInformation', 
                   [param('uint32_t', 'i')], 
                   is_const=True)
    ## type-id.h (module 'core'): std::string ns3::TypeId::GetAttributeFullName(uint32_t i) const [member function]
    cls.add_method('GetAttributeFullName', 
                   'std::string', 
                   [param('uint32_t', 'i')], 
                   is_const=True)
    ## type-id.h (module 'core'): uint32_t ns3::TypeId::GetAttributeN() const [member function]
    cls.add_method('GetAttributeN', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## type-id.h (module 'core'): ns3::Callback<ns3::ObjectBase*,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty> ns3::TypeId::GetConstructor() const [member function]
    cls.add_method('GetConstructor', 
                   'ns3::Callback< ns3::ObjectBase *, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 
                   [], 
                   is_const=True)
    ## type-id.h (module 'core'): std::string ns3::TypeId::GetGroupName() const [member function]
    cls.add_method('GetGroupName', 
                   'std::string', 
                   [], 
                   is_const=True)
    ## type-id.h (module 'core'): std::string ns3::TypeId::GetName() const [member function]
    cls.add_method('GetName', 
                   'std::string', 
                   [], 
                   is_const=True)
    ## type-id.h (module 'core'): ns3::TypeId ns3::TypeId::GetParent() const [member function]
    cls.add_method('GetParent', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True)
    ## type-id.h (module 'core'): static ns3::TypeId ns3::TypeId::GetRegistered(uint32_t i) [member function]
    cls.add_method('GetRegistered', 
                   'ns3::TypeId', 
                   [param('uint32_t', 'i')], 
                   is_static=True)
    ## type-id.h (module 'core'): static uint32_t ns3::TypeId::GetRegisteredN() [member function]
    cls.add_method('GetRegisteredN', 
                   'uint32_t', 
                   [], 
                   is_static=True)
    ## type-id.h (module 'core'): ns3::TypeId::TraceSourceInformation ns3::TypeId::GetTraceSource(uint32_t i) const [member function]
    cls.add_method('GetTraceSource', 
                   'ns3::TypeId::TraceSourceInformation', 
                   [param('uint32_t', 'i')], 
                   is_const=True)
    ## type-id.h (module 'core'): uint32_t ns3::TypeId::GetTraceSourceN() const [member function]
    cls.add_method('GetTraceSourceN', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## type-id.h (module 'core'): uint16_t ns3::TypeId::GetUid() const [member function]
    cls.add_method('GetUid', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## type-id.h (module 'core'): bool ns3::TypeId::HasConstructor() const [member function]
    cls.add_method('HasConstructor', 
                   'bool', 
                   [], 
                   is_const=True)
    ## type-id.h (module 'core'): bool ns3::TypeId::HasParent() const [member function]
    cls.add_method('HasParent', 
                   'bool', 
                   [], 
                   is_const=True)
    ## type-id.h (module 'core'): ns3::TypeId ns3::TypeId::HideFromDocumentation() [member function]
    cls.add_method('HideFromDocumentation', 
                   'ns3::TypeId', 
                   [])
    ## type-id.h (module 'core'): bool ns3::TypeId::IsChildOf(ns3::TypeId other) const [member function]
    cls.add_method('IsChildOf', 
                   'bool', 
                   [param('ns3::TypeId', 'other')], 
                   is_const=True)
    ## type-id.h (module 'core'): bool ns3::TypeId::LookupAttributeByName(std::string name, ns3::TypeId::AttributeInformation * info) const [member function]
    cls.add_method('LookupAttributeByName', 
                   'bool', 
                   [param('std::string', 'name'), param('ns3::TypeId::AttributeInformation *', 'info', transfer_ownership=False)], 
                   is_const=True)
    ## type-id.h (module 'core'): static ns3::TypeId ns3::TypeId::LookupByName(std::string name) [member function]
    cls.add_method('LookupByName', 
                   'ns3::TypeId', 
                   [param('std::string', 'name')], 
                   is_static=True)
    ## type-id.h (module 'core'): ns3::Ptr<ns3::TraceSourceAccessor const> ns3::TypeId::LookupTraceSourceByName(std::string name) const [member function]
    cls.add_method('LookupTraceSourceByName', 
                   'ns3::Ptr< ns3::TraceSourceAccessor const >', 
                   [param('std::string', 'name')], 
                   is_const=True)
    ## type-id.h (module 'core'): bool ns3::TypeId::MustHideFromDocumentation() const [member function]
    cls.add_method('MustHideFromDocumentation', 
                   'bool', 
                   [], 
                   is_const=True)
    ## type-id.h (module 'core'): bool ns3::TypeId::SetAttributeInitialValue(uint32_t i, ns3::Ptr<ns3::AttributeValue const> initialValue) [member function]
    cls.add_method('SetAttributeInitialValue', 
                   'bool', 
                   [param('uint32_t', 'i'), param('ns3::Ptr< ns3::AttributeValue const >', 'initialValue')])
    ## type-id.h (module 'core'): ns3::TypeId ns3::TypeId::SetGroupName(std::string groupName) [member function]
    cls.add_method('SetGroupName', 
                   'ns3::TypeId', 
                   [param('std::string', 'groupName')])
    ## type-id.h (module 'core'): ns3::TypeId ns3::TypeId::SetParent(ns3::TypeId tid) [member function]
    cls.add_method('SetParent', 
                   'ns3::TypeId', 
                   [param('ns3::TypeId', 'tid')])
    ## type-id.h (module 'core'): ns3::TypeId ns3::TypeId::SetParent() [member function]
    cls.add_method('SetParent', 
                   'ns3::TypeId', 
                   [], 
                   template_parameters=['ns3::Tag'])
    ## type-id.h (module 'core'): void ns3::TypeId::SetUid(uint16_t tid) [member function]
    cls.add_method('SetUid', 
                   'void', 
                   [param('uint16_t', 'tid')])
    return

def register_Ns3TypeIdAttributeInformation_methods(root_module, cls):
    ## type-id.h (module 'core'): ns3::TypeId::AttributeInformation::AttributeInformation() [constructor]
    cls.add_constructor([])
    ## type-id.h (module 'core'): ns3::TypeId::AttributeInformation::AttributeInformation(ns3::TypeId::AttributeInformation const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::TypeId::AttributeInformation const &', 'arg0')])
    ## type-id.h (module 'core'): ns3::TypeId::AttributeInformation::accessor [variable]
    cls.add_instance_attribute('accessor', 'ns3::Ptr< ns3::AttributeAccessor const >', is_const=False)
    ## type-id.h (module 'core'): ns3::TypeId::AttributeInformation::checker [variable]
    cls.add_instance_attribute('checker', 'ns3::Ptr< ns3::AttributeChecker const >', is_const=False)
    ## type-id.h (module 'core'): ns3::TypeId::AttributeInformation::flags [variable]
    cls.add_instance_attribute('flags', 'uint32_t', is_const=False)
    ## type-id.h (module 'core'): ns3::TypeId::AttributeInformation::help [variable]
    cls.add_instance_attribute('help', 'std::string', is_const=False)
    ## type-id.h (module 'core'): ns3::TypeId::AttributeInformation::initialValue [variable]
    cls.add_instance_attribute('initialValue', 'ns3::Ptr< ns3::AttributeValue const >', is_const=False)
    ## type-id.h (module 'core'): ns3::TypeId::AttributeInformation::name [variable]
    cls.add_instance_attribute('name', 'std::string', is_const=False)
    ## type-id.h (module 'core'): ns3::TypeId::AttributeInformation::originalInitialValue [variable]
    cls.add_instance_attribute('originalInitialValue', 'ns3::Ptr< ns3::AttributeValue const >', is_const=False)
    return

def register_Ns3TypeIdTraceSourceInformation_methods(root_module, cls):
    ## type-id.h (module 'core'): ns3::TypeId::TraceSourceInformation::TraceSourceInformation() [constructor]
    cls.add_constructor([])
    ## type-id.h (module 'core'): ns3::TypeId::TraceSourceInformation::TraceSourceInformation(ns3::TypeId::TraceSourceInformation const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::TypeId::TraceSourceInformation const &', 'arg0')])
    ## type-id.h (module 'core'): ns3::TypeId::TraceSourceInformation::accessor [variable]
    cls.add_instance_attribute('accessor', 'ns3::Ptr< ns3::TraceSourceAccessor const >', is_const=False)
    ## type-id.h (module 'core'): ns3::TypeId::TraceSourceInformation::help [variable]
    cls.add_instance_attribute('help', 'std::string', is_const=False)
    ## type-id.h (module 'core'): ns3::TypeId::TraceSourceInformation::name [variable]
    cls.add_instance_attribute('name', 'std::string', is_const=False)
    return

def register_Ns3UniformVariable_methods(root_module, cls):
    ## random-variable.h (module 'core'): ns3::UniformVariable::UniformVariable(ns3::UniformVariable const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::UniformVariable const &', 'arg0')])
    ## random-variable.h (module 'core'): ns3::UniformVariable::UniformVariable() [constructor]
    cls.add_constructor([])
    ## random-variable.h (module 'core'): ns3::UniformVariable::UniformVariable(double s, double l) [constructor]
    cls.add_constructor([param('double', 's'), param('double', 'l')])
    ## random-variable.h (module 'core'): uint32_t ns3::UniformVariable::GetInteger(uint32_t s, uint32_t l) [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [param('uint32_t', 's'), param('uint32_t', 'l')])
    ## random-variable.h (module 'core'): double ns3::UniformVariable::GetValue() const [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable.h (module 'core'): double ns3::UniformVariable::GetValue(double s, double l) [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [param('double', 's'), param('double', 'l')])
    return

def register_Ns3WeibullVariable_methods(root_module, cls):
    ## random-variable.h (module 'core'): ns3::WeibullVariable::WeibullVariable(ns3::WeibullVariable const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::WeibullVariable const &', 'arg0')])
    ## random-variable.h (module 'core'): ns3::WeibullVariable::WeibullVariable() [constructor]
    cls.add_constructor([])
    ## random-variable.h (module 'core'): ns3::WeibullVariable::WeibullVariable(double m) [constructor]
    cls.add_constructor([param('double', 'm')])
    ## random-variable.h (module 'core'): ns3::WeibullVariable::WeibullVariable(double m, double s) [constructor]
    cls.add_constructor([param('double', 'm'), param('double', 's')])
    ## random-variable.h (module 'core'): ns3::WeibullVariable::WeibullVariable(double m, double s, double b) [constructor]
    cls.add_constructor([param('double', 'm'), param('double', 's'), param('double', 'b')])
    return

def register_Ns3ZetaVariable_methods(root_module, cls):
    ## random-variable.h (module 'core'): ns3::ZetaVariable::ZetaVariable(ns3::ZetaVariable const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::ZetaVariable const &', 'arg0')])
    ## random-variable.h (module 'core'): ns3::ZetaVariable::ZetaVariable(double alpha) [constructor]
    cls.add_constructor([param('double', 'alpha')])
    ## random-variable.h (module 'core'): ns3::ZetaVariable::ZetaVariable() [constructor]
    cls.add_constructor([])
    return

def register_Ns3ZipfVariable_methods(root_module, cls):
    ## random-variable.h (module 'core'): ns3::ZipfVariable::ZipfVariable(ns3::ZipfVariable const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::ZipfVariable const &', 'arg0')])
    ## random-variable.h (module 'core'): ns3::ZipfVariable::ZipfVariable(long int N, double alpha) [constructor]
    cls.add_constructor([param('long int', 'N'), param('double', 'alpha')])
    ## random-variable.h (module 'core'): ns3::ZipfVariable::ZipfVariable() [constructor]
    cls.add_constructor([])
    return

def register_Ns3Empty_methods(root_module, cls):
    ## empty.h (module 'core'): ns3::empty::empty() [constructor]
    cls.add_constructor([])
    ## empty.h (module 'core'): ns3::empty::empty(ns3::empty const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::empty const &', 'arg0')])
    return

def register_Ns3Int64x64_t_methods(root_module, cls):
    cls.add_binary_comparison_operator('!=')
    cls.add_inplace_numeric_operator('+=', param('ns3::int64x64_t const &', 'right'))
    cls.add_binary_numeric_operator('*', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('long long unsigned int const', 'right'))
    cls.add_binary_numeric_operator('*', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('long unsigned int const', 'right'))
    cls.add_binary_numeric_operator('*', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('unsigned int const', 'right'))
    cls.add_binary_numeric_operator('*', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('short unsigned int const', 'right'))
    cls.add_binary_numeric_operator('*', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('unsigned char const', 'right'))
    cls.add_binary_numeric_operator('*', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('long long int const', 'right'))
    cls.add_binary_numeric_operator('*', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('long int const', 'right'))
    cls.add_binary_numeric_operator('*', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('int const', 'right'))
    cls.add_binary_numeric_operator('*', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('short int const', 'right'))
    cls.add_binary_numeric_operator('*', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('signed char const', 'right'))
    cls.add_binary_numeric_operator('*', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('double const', 'right'))
    cls.add_binary_numeric_operator('*', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('ns3::int64x64_t const &', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('long long unsigned int const', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('long unsigned int const', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('unsigned int const', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('short unsigned int const', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('unsigned char const', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('long long int const', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('long int const', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('int const', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('short int const', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('signed char const', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('double const', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('ns3::int64x64_t const &', 'right'))
    cls.add_binary_numeric_operator('-', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('long long unsigned int const', 'right'))
    cls.add_binary_numeric_operator('-', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('long unsigned int const', 'right'))
    cls.add_binary_numeric_operator('-', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('unsigned int const', 'right'))
    cls.add_binary_numeric_operator('-', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('short unsigned int const', 'right'))
    cls.add_binary_numeric_operator('-', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('unsigned char const', 'right'))
    cls.add_binary_numeric_operator('-', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('long long int const', 'right'))
    cls.add_binary_numeric_operator('-', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('long int const', 'right'))
    cls.add_binary_numeric_operator('-', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('int const', 'right'))
    cls.add_binary_numeric_operator('-', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('short int const', 'right'))
    cls.add_binary_numeric_operator('-', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('signed char const', 'right'))
    cls.add_binary_numeric_operator('-', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('double const', 'right'))
    cls.add_unary_numeric_operator('-')
    cls.add_binary_numeric_operator('-', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('ns3::int64x64_t const &', 'right'))
    cls.add_binary_numeric_operator('/', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('long long unsigned int const', 'right'))
    cls.add_binary_numeric_operator('/', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('long unsigned int const', 'right'))
    cls.add_binary_numeric_operator('/', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('unsigned int const', 'right'))
    cls.add_binary_numeric_operator('/', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('short unsigned int const', 'right'))
    cls.add_binary_numeric_operator('/', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('unsigned char const', 'right'))
    cls.add_binary_numeric_operator('/', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('long long int const', 'right'))
    cls.add_binary_numeric_operator('/', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('long int const', 'right'))
    cls.add_binary_numeric_operator('/', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('int const', 'right'))
    cls.add_binary_numeric_operator('/', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('short int const', 'right'))
    cls.add_binary_numeric_operator('/', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('signed char const', 'right'))
    cls.add_binary_numeric_operator('/', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('double const', 'right'))
    cls.add_binary_numeric_operator('/', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('ns3::int64x64_t const &', 'right'))
    cls.add_binary_comparison_operator('<')
    cls.add_binary_comparison_operator('>')
    cls.add_inplace_numeric_operator('*=', param('ns3::int64x64_t const &', 'right'))
    cls.add_inplace_numeric_operator('-=', param('ns3::int64x64_t const &', 'right'))
    cls.add_inplace_numeric_operator('/=', param('ns3::int64x64_t const &', 'right'))
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('<=')
    cls.add_binary_comparison_operator('==')
    cls.add_binary_comparison_operator('>=')
    ## int64x64-double.h (module 'core'): ns3::int64x64_t::int64x64_t() [constructor]
    cls.add_constructor([])
    ## int64x64-double.h (module 'core'): ns3::int64x64_t::int64x64_t(double v) [constructor]
    cls.add_constructor([param('double', 'v')])
    ## int64x64-double.h (module 'core'): ns3::int64x64_t::int64x64_t(int v) [constructor]
    cls.add_constructor([param('int', 'v')])
    ## int64x64-double.h (module 'core'): ns3::int64x64_t::int64x64_t(long int v) [constructor]
    cls.add_constructor([param('long int', 'v')])
    ## int64x64-double.h (module 'core'): ns3::int64x64_t::int64x64_t(long long int v) [constructor]
    cls.add_constructor([param('long long int', 'v')])
    ## int64x64-double.h (module 'core'): ns3::int64x64_t::int64x64_t(unsigned int v) [constructor]
    cls.add_constructor([param('unsigned int', 'v')])
    ## int64x64-double.h (module 'core'): ns3::int64x64_t::int64x64_t(long unsigned int v) [constructor]
    cls.add_constructor([param('long unsigned int', 'v')])
    ## int64x64-double.h (module 'core'): ns3::int64x64_t::int64x64_t(long long unsigned int v) [constructor]
    cls.add_constructor([param('long long unsigned int', 'v')])
    ## int64x64-double.h (module 'core'): ns3::int64x64_t::int64x64_t(int64_t hi, uint64_t lo) [constructor]
    cls.add_constructor([param('int64_t', 'hi'), param('uint64_t', 'lo')])
    ## int64x64-double.h (module 'core'): ns3::int64x64_t::int64x64_t(ns3::int64x64_t const & o) [copy constructor]
    cls.add_constructor([param('ns3::int64x64_t const &', 'o')])
    ## int64x64-double.h (module 'core'): double ns3::int64x64_t::GetDouble() const [member function]
    cls.add_method('GetDouble', 
                   'double', 
                   [], 
                   is_const=True)
    ## int64x64-double.h (module 'core'): int64_t ns3::int64x64_t::GetHigh() const [member function]
    cls.add_method('GetHigh', 
                   'int64_t', 
                   [], 
                   is_const=True)
    ## int64x64-double.h (module 'core'): uint64_t ns3::int64x64_t::GetLow() const [member function]
    cls.add_method('GetLow', 
                   'uint64_t', 
                   [], 
                   is_const=True)
    ## int64x64-double.h (module 'core'): static ns3::int64x64_t ns3::int64x64_t::Invert(uint64_t v) [member function]
    cls.add_method('Invert', 
                   'ns3::int64x64_t', 
                   [param('uint64_t', 'v')], 
                   is_static=True)
    ## int64x64-double.h (module 'core'): void ns3::int64x64_t::MulByInvert(ns3::int64x64_t const & o) [member function]
    cls.add_method('MulByInvert', 
                   'void', 
                   [param('ns3::int64x64_t const &', 'o')])
    return

def register_Ns3Chunk_methods(root_module, cls):
    ## chunk.h (module 'network'): ns3::Chunk::Chunk() [constructor]
    cls.add_constructor([])
    ## chunk.h (module 'network'): ns3::Chunk::Chunk(ns3::Chunk const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Chunk const &', 'arg0')])
    ## chunk.h (module 'network'): uint32_t ns3::Chunk::Deserialize(ns3::Buffer::Iterator start) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_pure_virtual=True, is_virtual=True)
    ## chunk.h (module 'network'): static ns3::TypeId ns3::Chunk::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## chunk.h (module 'network'): void ns3::Chunk::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    return

def register_Ns3ConstantVariable_methods(root_module, cls):
    ## random-variable.h (module 'core'): ns3::ConstantVariable::ConstantVariable(ns3::ConstantVariable const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::ConstantVariable const &', 'arg0')])
    ## random-variable.h (module 'core'): ns3::ConstantVariable::ConstantVariable() [constructor]
    cls.add_constructor([])
    ## random-variable.h (module 'core'): ns3::ConstantVariable::ConstantVariable(double c) [constructor]
    cls.add_constructor([param('double', 'c')])
    ## random-variable.h (module 'core'): void ns3::ConstantVariable::SetConstant(double c) [member function]
    cls.add_method('SetConstant', 
                   'void', 
                   [param('double', 'c')])
    return

def register_Ns3DeterministicVariable_methods(root_module, cls):
    ## random-variable.h (module 'core'): ns3::DeterministicVariable::DeterministicVariable(ns3::DeterministicVariable const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::DeterministicVariable const &', 'arg0')])
    ## random-variable.h (module 'core'): ns3::DeterministicVariable::DeterministicVariable(double * d, uint32_t c) [constructor]
    cls.add_constructor([param('double *', 'd'), param('uint32_t', 'c')])
    return

def register_Ns3EmpiricalVariable_methods(root_module, cls):
    ## random-variable.h (module 'core'): ns3::EmpiricalVariable::EmpiricalVariable(ns3::EmpiricalVariable const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::EmpiricalVariable const &', 'arg0')])
    ## random-variable.h (module 'core'): ns3::EmpiricalVariable::EmpiricalVariable() [constructor]
    cls.add_constructor([])
    ## random-variable.h (module 'core'): void ns3::EmpiricalVariable::CDF(double v, double c) [member function]
    cls.add_method('CDF', 
                   'void', 
                   [param('double', 'v'), param('double', 'c')])
    return

def register_Ns3ErlangVariable_methods(root_module, cls):
    ## random-variable.h (module 'core'): ns3::ErlangVariable::ErlangVariable(ns3::ErlangVariable const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::ErlangVariable const &', 'arg0')])
    ## random-variable.h (module 'core'): ns3::ErlangVariable::ErlangVariable() [constructor]
    cls.add_constructor([])
    ## random-variable.h (module 'core'): ns3::ErlangVariable::ErlangVariable(unsigned int k, double lambda) [constructor]
    cls.add_constructor([param('unsigned int', 'k'), param('double', 'lambda')])
    ## random-variable.h (module 'core'): double ns3::ErlangVariable::GetValue() const [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable.h (module 'core'): double ns3::ErlangVariable::GetValue(unsigned int k, double lambda) const [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [param('unsigned int', 'k'), param('double', 'lambda')], 
                   is_const=True)
    return

def register_Ns3ExponentialVariable_methods(root_module, cls):
    ## random-variable.h (module 'core'): ns3::ExponentialVariable::ExponentialVariable(ns3::ExponentialVariable const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::ExponentialVariable const &', 'arg0')])
    ## random-variable.h (module 'core'): ns3::ExponentialVariable::ExponentialVariable() [constructor]
    cls.add_constructor([])
    ## random-variable.h (module 'core'): ns3::ExponentialVariable::ExponentialVariable(double m) [constructor]
    cls.add_constructor([param('double', 'm')])
    ## random-variable.h (module 'core'): ns3::ExponentialVariable::ExponentialVariable(double m, double b) [constructor]
    cls.add_constructor([param('double', 'm'), param('double', 'b')])
    return

def register_Ns3GammaVariable_methods(root_module, cls):
    ## random-variable.h (module 'core'): ns3::GammaVariable::GammaVariable(ns3::GammaVariable const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::GammaVariable const &', 'arg0')])
    ## random-variable.h (module 'core'): ns3::GammaVariable::GammaVariable() [constructor]
    cls.add_constructor([])
    ## random-variable.h (module 'core'): ns3::GammaVariable::GammaVariable(double alpha, double beta) [constructor]
    cls.add_constructor([param('double', 'alpha'), param('double', 'beta')])
    ## random-variable.h (module 'core'): double ns3::GammaVariable::GetValue() const [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable.h (module 'core'): double ns3::GammaVariable::GetValue(double alpha, double beta) const [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [param('double', 'alpha'), param('double', 'beta')], 
                   is_const=True)
    return

def register_Ns3Gnuplot2dDataset_methods(root_module, cls):
    ## gnuplot.h (module 'tools'): ns3::Gnuplot2dDataset::Gnuplot2dDataset(ns3::Gnuplot2dDataset const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Gnuplot2dDataset const &', 'arg0')])
    ## gnuplot.h (module 'tools'): ns3::Gnuplot2dDataset::Gnuplot2dDataset(std::string const & title="Untitled") [constructor]
    cls.add_constructor([param('std::string const &', 'title', default_value='"Untitled"')])
    ## gnuplot.h (module 'tools'): void ns3::Gnuplot2dDataset::Add(double x, double y) [member function]
    cls.add_method('Add', 
                   'void', 
                   [param('double', 'x'), param('double', 'y')])
    ## gnuplot.h (module 'tools'): void ns3::Gnuplot2dDataset::Add(double x, double y, double errorDelta) [member function]
    cls.add_method('Add', 
                   'void', 
                   [param('double', 'x'), param('double', 'y'), param('double', 'errorDelta')])
    ## gnuplot.h (module 'tools'): void ns3::Gnuplot2dDataset::Add(double x, double y, double xErrorDelta, double yErrorDelta) [member function]
    cls.add_method('Add', 
                   'void', 
                   [param('double', 'x'), param('double', 'y'), param('double', 'xErrorDelta'), param('double', 'yErrorDelta')])
    ## gnuplot.h (module 'tools'): void ns3::Gnuplot2dDataset::AddEmptyLine() [member function]
    cls.add_method('AddEmptyLine', 
                   'void', 
                   [])
    ## gnuplot.h (module 'tools'): static void ns3::Gnuplot2dDataset::SetDefaultErrorBars(ns3::Gnuplot2dDataset::ErrorBars errorBars) [member function]
    cls.add_method('SetDefaultErrorBars', 
                   'void', 
                   [param('ns3::Gnuplot2dDataset::ErrorBars', 'errorBars')], 
                   is_static=True)
    ## gnuplot.h (module 'tools'): static void ns3::Gnuplot2dDataset::SetDefaultStyle(ns3::Gnuplot2dDataset::Style style) [member function]
    cls.add_method('SetDefaultStyle', 
                   'void', 
                   [param('ns3::Gnuplot2dDataset::Style', 'style')], 
                   is_static=True)
    ## gnuplot.h (module 'tools'): void ns3::Gnuplot2dDataset::SetErrorBars(ns3::Gnuplot2dDataset::ErrorBars errorBars) [member function]
    cls.add_method('SetErrorBars', 
                   'void', 
                   [param('ns3::Gnuplot2dDataset::ErrorBars', 'errorBars')])
    ## gnuplot.h (module 'tools'): void ns3::Gnuplot2dDataset::SetStyle(ns3::Gnuplot2dDataset::Style style) [member function]
    cls.add_method('SetStyle', 
                   'void', 
                   [param('ns3::Gnuplot2dDataset::Style', 'style')])
    return

def register_Ns3Gnuplot2dFunction_methods(root_module, cls):
    ## gnuplot.h (module 'tools'): ns3::Gnuplot2dFunction::Gnuplot2dFunction(ns3::Gnuplot2dFunction const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Gnuplot2dFunction const &', 'arg0')])
    ## gnuplot.h (module 'tools'): ns3::Gnuplot2dFunction::Gnuplot2dFunction(std::string const & title="Untitled", std::string const & function="") [constructor]
    cls.add_constructor([param('std::string const &', 'title', default_value='"Untitled"'), param('std::string const &', 'function', default_value='""')])
    ## gnuplot.h (module 'tools'): void ns3::Gnuplot2dFunction::SetFunction(std::string const & function) [member function]
    cls.add_method('SetFunction', 
                   'void', 
                   [param('std::string const &', 'function')])
    return

def register_Ns3Gnuplot3dDataset_methods(root_module, cls):
    ## gnuplot.h (module 'tools'): ns3::Gnuplot3dDataset::Gnuplot3dDataset(ns3::Gnuplot3dDataset const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Gnuplot3dDataset const &', 'arg0')])
    ## gnuplot.h (module 'tools'): ns3::Gnuplot3dDataset::Gnuplot3dDataset(std::string const & title="Untitled") [constructor]
    cls.add_constructor([param('std::string const &', 'title', default_value='"Untitled"')])
    ## gnuplot.h (module 'tools'): void ns3::Gnuplot3dDataset::Add(double x, double y, double z) [member function]
    cls.add_method('Add', 
                   'void', 
                   [param('double', 'x'), param('double', 'y'), param('double', 'z')])
    ## gnuplot.h (module 'tools'): void ns3::Gnuplot3dDataset::AddEmptyLine() [member function]
    cls.add_method('AddEmptyLine', 
                   'void', 
                   [])
    ## gnuplot.h (module 'tools'): static void ns3::Gnuplot3dDataset::SetDefaultStyle(std::string const & style) [member function]
    cls.add_method('SetDefaultStyle', 
                   'void', 
                   [param('std::string const &', 'style')], 
                   is_static=True)
    ## gnuplot.h (module 'tools'): void ns3::Gnuplot3dDataset::SetStyle(std::string const & style) [member function]
    cls.add_method('SetStyle', 
                   'void', 
                   [param('std::string const &', 'style')])
    return

def register_Ns3Gnuplot3dFunction_methods(root_module, cls):
    ## gnuplot.h (module 'tools'): ns3::Gnuplot3dFunction::Gnuplot3dFunction(ns3::Gnuplot3dFunction const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Gnuplot3dFunction const &', 'arg0')])
    ## gnuplot.h (module 'tools'): ns3::Gnuplot3dFunction::Gnuplot3dFunction(std::string const & title="Untitled", std::string const & function="") [constructor]
    cls.add_constructor([param('std::string const &', 'title', default_value='"Untitled"'), param('std::string const &', 'function', default_value='""')])
    ## gnuplot.h (module 'tools'): void ns3::Gnuplot3dFunction::SetFunction(std::string const & function) [member function]
    cls.add_method('SetFunction', 
                   'void', 
                   [param('std::string const &', 'function')])
    return

def register_Ns3Header_methods(root_module, cls):
    cls.add_output_stream_operator()
    ## header.h (module 'network'): ns3::Header::Header() [constructor]
    cls.add_constructor([])
    ## header.h (module 'network'): ns3::Header::Header(ns3::Header const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Header const &', 'arg0')])
    ## header.h (module 'network'): uint32_t ns3::Header::Deserialize(ns3::Buffer::Iterator start) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_pure_virtual=True, is_virtual=True)
    ## header.h (module 'network'): uint32_t ns3::Header::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## header.h (module 'network'): static ns3::TypeId ns3::Header::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## header.h (module 'network'): void ns3::Header::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## header.h (module 'network'): void ns3::Header::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    return

def register_Ns3IntEmpiricalVariable_methods(root_module, cls):
    ## random-variable.h (module 'core'): ns3::IntEmpiricalVariable::IntEmpiricalVariable(ns3::IntEmpiricalVariable const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::IntEmpiricalVariable const &', 'arg0')])
    ## random-variable.h (module 'core'): ns3::IntEmpiricalVariable::IntEmpiricalVariable() [constructor]
    cls.add_constructor([])
    return

def register_Ns3Ipv4Header_methods(root_module, cls):
    ## ipv4-header.h (module 'internet'): ns3::Ipv4Header::Ipv4Header(ns3::Ipv4Header const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Ipv4Header const &', 'arg0')])
    ## ipv4-header.h (module 'internet'): ns3::Ipv4Header::Ipv4Header() [constructor]
    cls.add_constructor([])
    ## ipv4-header.h (module 'internet'): uint32_t ns3::Ipv4Header::Deserialize(ns3::Buffer::Iterator start) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_virtual=True)
    ## ipv4-header.h (module 'internet'): std::string ns3::Ipv4Header::DscpTypeToString(ns3::Ipv4Header::DscpType dscp) const [member function]
    cls.add_method('DscpTypeToString', 
                   'std::string', 
                   [param('ns3::Ipv4Header::DscpType', 'dscp')], 
                   is_const=True)
    ## ipv4-header.h (module 'internet'): std::string ns3::Ipv4Header::EcnTypeToString(ns3::Ipv4Header::EcnType ecn) const [member function]
    cls.add_method('EcnTypeToString', 
                   'std::string', 
                   [param('ns3::Ipv4Header::EcnType', 'ecn')], 
                   is_const=True)
    ## ipv4-header.h (module 'internet'): void ns3::Ipv4Header::EnableChecksum() [member function]
    cls.add_method('EnableChecksum', 
                   'void', 
                   [])
    ## ipv4-header.h (module 'internet'): ns3::Ipv4Address ns3::Ipv4Header::GetDestination() const [member function]
    cls.add_method('GetDestination', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## ipv4-header.h (module 'internet'): ns3::Ipv4Header::DscpType ns3::Ipv4Header::GetDscp() const [member function]
    cls.add_method('GetDscp', 
                   'ns3::Ipv4Header::DscpType', 
                   [], 
                   is_const=True)
    ## ipv4-header.h (module 'internet'): ns3::Ipv4Header::EcnType ns3::Ipv4Header::GetEcn() const [member function]
    cls.add_method('GetEcn', 
                   'ns3::Ipv4Header::EcnType', 
                   [], 
                   is_const=True)
    ## ipv4-header.h (module 'internet'): uint16_t ns3::Ipv4Header::GetFragmentOffset() const [member function]
    cls.add_method('GetFragmentOffset', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## ipv4-header.h (module 'internet'): uint16_t ns3::Ipv4Header::GetIdentification() const [member function]
    cls.add_method('GetIdentification', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## ipv4-header.h (module 'internet'): ns3::TypeId ns3::Ipv4Header::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## ipv4-header.h (module 'internet'): uint16_t ns3::Ipv4Header::GetPayloadSize() const [member function]
    cls.add_method('GetPayloadSize', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## ipv4-header.h (module 'internet'): uint8_t ns3::Ipv4Header::GetProtocol() const [member function]
    cls.add_method('GetProtocol', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## ipv4-header.h (module 'internet'): uint32_t ns3::Ipv4Header::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## ipv4-header.h (module 'internet'): ns3::Ipv4Address ns3::Ipv4Header::GetSource() const [member function]
    cls.add_method('GetSource', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## ipv4-header.h (module 'internet'): uint8_t ns3::Ipv4Header::GetTos() const [member function]
    cls.add_method('GetTos', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## ipv4-header.h (module 'internet'): uint8_t ns3::Ipv4Header::GetTtl() const [member function]
    cls.add_method('GetTtl', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## ipv4-header.h (module 'internet'): static ns3::TypeId ns3::Ipv4Header::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## ipv4-header.h (module 'internet'): bool ns3::Ipv4Header::IsChecksumOk() const [member function]
    cls.add_method('IsChecksumOk', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv4-header.h (module 'internet'): bool ns3::Ipv4Header::IsDontFragment() const [member function]
    cls.add_method('IsDontFragment', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv4-header.h (module 'internet'): bool ns3::Ipv4Header::IsLastFragment() const [member function]
    cls.add_method('IsLastFragment', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv4-header.h (module 'internet'): void ns3::Ipv4Header::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## ipv4-header.h (module 'internet'): void ns3::Ipv4Header::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True, is_virtual=True)
    ## ipv4-header.h (module 'internet'): void ns3::Ipv4Header::SetDestination(ns3::Ipv4Address destination) [member function]
    cls.add_method('SetDestination', 
                   'void', 
                   [param('ns3::Ipv4Address', 'destination')])
    ## ipv4-header.h (module 'internet'): void ns3::Ipv4Header::SetDontFragment() [member function]
    cls.add_method('SetDontFragment', 
                   'void', 
                   [])
    ## ipv4-header.h (module 'internet'): void ns3::Ipv4Header::SetDscp(ns3::Ipv4Header::DscpType dscp) [member function]
    cls.add_method('SetDscp', 
                   'void', 
                   [param('ns3::Ipv4Header::DscpType', 'dscp')])
    ## ipv4-header.h (module 'internet'): void ns3::Ipv4Header::SetEcn(ns3::Ipv4Header::EcnType ecn) [member function]
    cls.add_method('SetEcn', 
                   'void', 
                   [param('ns3::Ipv4Header::EcnType', 'ecn')])
    ## ipv4-header.h (module 'internet'): void ns3::Ipv4Header::SetFragmentOffset(uint16_t offsetBytes) [member function]
    cls.add_method('SetFragmentOffset', 
                   'void', 
                   [param('uint16_t', 'offsetBytes')])
    ## ipv4-header.h (module 'internet'): void ns3::Ipv4Header::SetIdentification(uint16_t identification) [member function]
    cls.add_method('SetIdentification', 
                   'void', 
                   [param('uint16_t', 'identification')])
    ## ipv4-header.h (module 'internet'): void ns3::Ipv4Header::SetLastFragment() [member function]
    cls.add_method('SetLastFragment', 
                   'void', 
                   [])
    ## ipv4-header.h (module 'internet'): void ns3::Ipv4Header::SetMayFragment() [member function]
    cls.add_method('SetMayFragment', 
                   'void', 
                   [])
    ## ipv4-header.h (module 'internet'): void ns3::Ipv4Header::SetMoreFragments() [member function]
    cls.add_method('SetMoreFragments', 
                   'void', 
                   [])
    ## ipv4-header.h (module 'internet'): void ns3::Ipv4Header::SetPayloadSize(uint16_t size) [member function]
    cls.add_method('SetPayloadSize', 
                   'void', 
                   [param('uint16_t', 'size')])
    ## ipv4-header.h (module 'internet'): void ns3::Ipv4Header::SetProtocol(uint8_t num) [member function]
    cls.add_method('SetProtocol', 
                   'void', 
                   [param('uint8_t', 'num')])
    ## ipv4-header.h (module 'internet'): void ns3::Ipv4Header::SetSource(ns3::Ipv4Address source) [member function]
    cls.add_method('SetSource', 
                   'void', 
                   [param('ns3::Ipv4Address', 'source')])
    ## ipv4-header.h (module 'internet'): void ns3::Ipv4Header::SetTos(uint8_t tos) [member function]
    cls.add_method('SetTos', 
                   'void', 
                   [param('uint8_t', 'tos')])
    ## ipv4-header.h (module 'internet'): void ns3::Ipv4Header::SetTtl(uint8_t ttl) [member function]
    cls.add_method('SetTtl', 
                   'void', 
                   [param('uint8_t', 'ttl')])
    return

def register_Ns3Ipv6Header_methods(root_module, cls):
    ## ipv6-header.h (module 'internet'): ns3::Ipv6Header::Ipv6Header(ns3::Ipv6Header const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Ipv6Header const &', 'arg0')])
    ## ipv6-header.h (module 'internet'): ns3::Ipv6Header::Ipv6Header() [constructor]
    cls.add_constructor([])
    ## ipv6-header.h (module 'internet'): uint32_t ns3::Ipv6Header::Deserialize(ns3::Buffer::Iterator start) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_virtual=True)
    ## ipv6-header.h (module 'internet'): ns3::Ipv6Address ns3::Ipv6Header::GetDestinationAddress() const [member function]
    cls.add_method('GetDestinationAddress', 
                   'ns3::Ipv6Address', 
                   [], 
                   is_const=True)
    ## ipv6-header.h (module 'internet'): uint32_t ns3::Ipv6Header::GetFlowLabel() const [member function]
    cls.add_method('GetFlowLabel', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## ipv6-header.h (module 'internet'): uint8_t ns3::Ipv6Header::GetHopLimit() const [member function]
    cls.add_method('GetHopLimit', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## ipv6-header.h (module 'internet'): ns3::TypeId ns3::Ipv6Header::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## ipv6-header.h (module 'internet'): uint8_t ns3::Ipv6Header::GetNextHeader() const [member function]
    cls.add_method('GetNextHeader', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## ipv6-header.h (module 'internet'): uint16_t ns3::Ipv6Header::GetPayloadLength() const [member function]
    cls.add_method('GetPayloadLength', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## ipv6-header.h (module 'internet'): uint32_t ns3::Ipv6Header::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## ipv6-header.h (module 'internet'): ns3::Ipv6Address ns3::Ipv6Header::GetSourceAddress() const [member function]
    cls.add_method('GetSourceAddress', 
                   'ns3::Ipv6Address', 
                   [], 
                   is_const=True)
    ## ipv6-header.h (module 'internet'): uint8_t ns3::Ipv6Header::GetTrafficClass() const [member function]
    cls.add_method('GetTrafficClass', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## ipv6-header.h (module 'internet'): static ns3::TypeId ns3::Ipv6Header::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## ipv6-header.h (module 'internet'): void ns3::Ipv6Header::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## ipv6-header.h (module 'internet'): void ns3::Ipv6Header::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True, is_virtual=True)
    ## ipv6-header.h (module 'internet'): void ns3::Ipv6Header::SetDestinationAddress(ns3::Ipv6Address dst) [member function]
    cls.add_method('SetDestinationAddress', 
                   'void', 
                   [param('ns3::Ipv6Address', 'dst')])
    ## ipv6-header.h (module 'internet'): void ns3::Ipv6Header::SetFlowLabel(uint32_t flow) [member function]
    cls.add_method('SetFlowLabel', 
                   'void', 
                   [param('uint32_t', 'flow')])
    ## ipv6-header.h (module 'internet'): void ns3::Ipv6Header::SetHopLimit(uint8_t limit) [member function]
    cls.add_method('SetHopLimit', 
                   'void', 
                   [param('uint8_t', 'limit')])
    ## ipv6-header.h (module 'internet'): void ns3::Ipv6Header::SetNextHeader(uint8_t next) [member function]
    cls.add_method('SetNextHeader', 
                   'void', 
                   [param('uint8_t', 'next')])
    ## ipv6-header.h (module 'internet'): void ns3::Ipv6Header::SetPayloadLength(uint16_t len) [member function]
    cls.add_method('SetPayloadLength', 
                   'void', 
                   [param('uint16_t', 'len')])
    ## ipv6-header.h (module 'internet'): void ns3::Ipv6Header::SetSourceAddress(ns3::Ipv6Address src) [member function]
    cls.add_method('SetSourceAddress', 
                   'void', 
                   [param('ns3::Ipv6Address', 'src')])
    ## ipv6-header.h (module 'internet'): void ns3::Ipv6Header::SetTrafficClass(uint8_t traffic) [member function]
    cls.add_method('SetTrafficClass', 
                   'void', 
                   [param('uint8_t', 'traffic')])
    return

def register_Ns3LogNormalVariable_methods(root_module, cls):
    ## random-variable.h (module 'core'): ns3::LogNormalVariable::LogNormalVariable(ns3::LogNormalVariable const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::LogNormalVariable const &', 'arg0')])
    ## random-variable.h (module 'core'): ns3::LogNormalVariable::LogNormalVariable(double mu, double sigma) [constructor]
    cls.add_constructor([param('double', 'mu'), param('double', 'sigma')])
    return

def register_Ns3NormalVariable_methods(root_module, cls):
    ## random-variable.h (module 'core'): ns3::NormalVariable::NormalVariable(ns3::NormalVariable const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::NormalVariable const &', 'arg0')])
    ## random-variable.h (module 'core'): ns3::NormalVariable::NormalVariable() [constructor]
    cls.add_constructor([])
    ## random-variable.h (module 'core'): ns3::NormalVariable::NormalVariable(double m, double v) [constructor]
    cls.add_constructor([param('double', 'm'), param('double', 'v')])
    ## random-variable.h (module 'core'): ns3::NormalVariable::NormalVariable(double m, double v, double b) [constructor]
    cls.add_constructor([param('double', 'm'), param('double', 'v'), param('double', 'b')])
    return

def register_Ns3Object_methods(root_module, cls):
    ## object.h (module 'core'): ns3::Object::Object() [constructor]
    cls.add_constructor([])
    ## object.h (module 'core'): void ns3::Object::AggregateObject(ns3::Ptr<ns3::Object> other) [member function]
    cls.add_method('AggregateObject', 
                   'void', 
                   [param('ns3::Ptr< ns3::Object >', 'other')])
    ## object.h (module 'core'): void ns3::Object::Dispose() [member function]
    cls.add_method('Dispose', 
                   'void', 
                   [])
    ## object.h (module 'core'): ns3::Object::AggregateIterator ns3::Object::GetAggregateIterator() const [member function]
    cls.add_method('GetAggregateIterator', 
                   'ns3::Object::AggregateIterator', 
                   [], 
                   is_const=True)
    ## object.h (module 'core'): ns3::TypeId ns3::Object::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## object.h (module 'core'): static ns3::TypeId ns3::Object::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## object.h (module 'core'): void ns3::Object::Start() [member function]
    cls.add_method('Start', 
                   'void', 
                   [])
    ## object.h (module 'core'): ns3::Object::Object(ns3::Object const & o) [copy constructor]
    cls.add_constructor([param('ns3::Object const &', 'o')], 
                        visibility='protected')
    ## object.h (module 'core'): void ns3::Object::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## object.h (module 'core'): void ns3::Object::DoStart() [member function]
    cls.add_method('DoStart', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## object.h (module 'core'): void ns3::Object::NotifyNewAggregate() [member function]
    cls.add_method('NotifyNewAggregate', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    return

def register_Ns3ObjectAggregateIterator_methods(root_module, cls):
    ## object.h (module 'core'): ns3::Object::AggregateIterator::AggregateIterator(ns3::Object::AggregateIterator const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Object::AggregateIterator const &', 'arg0')])
    ## object.h (module 'core'): ns3::Object::AggregateIterator::AggregateIterator() [constructor]
    cls.add_constructor([])
    ## object.h (module 'core'): bool ns3::Object::AggregateIterator::HasNext() const [member function]
    cls.add_method('HasNext', 
                   'bool', 
                   [], 
                   is_const=True)
    ## object.h (module 'core'): ns3::Ptr<ns3::Object const> ns3::Object::AggregateIterator::Next() [member function]
    cls.add_method('Next', 
                   'ns3::Ptr< ns3::Object const >', 
                   [])
    return

def register_Ns3ParetoVariable_methods(root_module, cls):
    ## random-variable.h (module 'core'): ns3::ParetoVariable::ParetoVariable(ns3::ParetoVariable const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::ParetoVariable const &', 'arg0')])
    ## random-variable.h (module 'core'): ns3::ParetoVariable::ParetoVariable() [constructor]
    cls.add_constructor([])
    ## random-variable.h (module 'core'): ns3::ParetoVariable::ParetoVariable(double m) [constructor]
    cls.add_constructor([param('double', 'm')])
    ## random-variable.h (module 'core'): ns3::ParetoVariable::ParetoVariable(double m, double s) [constructor]
    cls.add_constructor([param('double', 'm'), param('double', 's')])
    ## random-variable.h (module 'core'): ns3::ParetoVariable::ParetoVariable(double m, double s, double b) [constructor]
    cls.add_constructor([param('double', 'm'), param('double', 's'), param('double', 'b')])
    ## random-variable.h (module 'core'): ns3::ParetoVariable::ParetoVariable(std::pair<double,double> params) [constructor]
    cls.add_constructor([param('std::pair< double, double >', 'params')])
    ## random-variable.h (module 'core'): ns3::ParetoVariable::ParetoVariable(std::pair<double,double> params, double b) [constructor]
    cls.add_constructor([param('std::pair< double, double >', 'params'), param('double', 'b')])
    return

def register_Ns3RandomVariableStream_methods(root_module, cls):
    ## random-variable-stream.h (module 'core'): static ns3::TypeId ns3::RandomVariableStream::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## random-variable-stream.h (module 'core'): ns3::RandomVariableStream::RandomVariableStream() [constructor]
    cls.add_constructor([])
    ## random-variable-stream.h (module 'core'): void ns3::RandomVariableStream::SetStream(int64_t stream) [member function]
    cls.add_method('SetStream', 
                   'void', 
                   [param('int64_t', 'stream')])
    ## random-variable-stream.h (module 'core'): int64_t ns3::RandomVariableStream::GetStream() const [member function]
    cls.add_method('GetStream', 
                   'int64_t', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): void ns3::RandomVariableStream::SetAntithetic(bool isAntithetic) [member function]
    cls.add_method('SetAntithetic', 
                   'void', 
                   [param('bool', 'isAntithetic')])
    ## random-variable-stream.h (module 'core'): bool ns3::RandomVariableStream::IsAntithetic() const [member function]
    cls.add_method('IsAntithetic', 
                   'bool', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::RandomVariableStream::GetValue() [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [], 
                   is_pure_virtual=True, is_virtual=True)
    ## random-variable-stream.h (module 'core'): uint32_t ns3::RandomVariableStream::GetInteger() [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [], 
                   is_pure_virtual=True, is_virtual=True)
    ## random-variable-stream.h (module 'core'): ns3::RngStream * ns3::RandomVariableStream::Peek() const [member function]
    cls.add_method('Peek', 
                   'ns3::RngStream *', 
                   [], 
                   is_const=True, visibility='protected')
    return

def register_Ns3SequentialRandomVariable_methods(root_module, cls):
    ## random-variable-stream.h (module 'core'): static ns3::TypeId ns3::SequentialRandomVariable::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## random-variable-stream.h (module 'core'): ns3::SequentialRandomVariable::SequentialRandomVariable() [constructor]
    cls.add_constructor([])
    ## random-variable-stream.h (module 'core'): double ns3::SequentialRandomVariable::GetMin() const [member function]
    cls.add_method('GetMin', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::SequentialRandomVariable::GetMax() const [member function]
    cls.add_method('GetMax', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): ns3::Ptr<ns3::RandomVariableStream> ns3::SequentialRandomVariable::GetIncrement() const [member function]
    cls.add_method('GetIncrement', 
                   'ns3::Ptr< ns3::RandomVariableStream >', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): uint32_t ns3::SequentialRandomVariable::GetConsecutive() const [member function]
    cls.add_method('GetConsecutive', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::SequentialRandomVariable::GetValue() [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [], 
                   is_virtual=True)
    ## random-variable-stream.h (module 'core'): uint32_t ns3::SequentialRandomVariable::GetInteger() [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [], 
                   is_virtual=True)
    return

def register_Ns3SimpleRefCount__Ns3AttributeAccessor_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeAccessor__gt___methods(root_module, cls):
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::AttributeAccessor, ns3::empty, ns3::DefaultDeleter<ns3::AttributeAccessor> >::SimpleRefCount() [constructor]
    cls.add_constructor([])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::AttributeAccessor, ns3::empty, ns3::DefaultDeleter<ns3::AttributeAccessor> >::SimpleRefCount(ns3::SimpleRefCount<ns3::AttributeAccessor, ns3::empty, ns3::DefaultDeleter<ns3::AttributeAccessor> > const & o) [copy constructor]
    cls.add_constructor([param('ns3::SimpleRefCount< ns3::AttributeAccessor, ns3::empty, ns3::DefaultDeleter< ns3::AttributeAccessor > > const &', 'o')])
    ## simple-ref-count.h (module 'core'): static void ns3::SimpleRefCount<ns3::AttributeAccessor, ns3::empty, ns3::DefaultDeleter<ns3::AttributeAccessor> >::Cleanup() [member function]
    cls.add_method('Cleanup', 
                   'void', 
                   [], 
                   is_static=True)
    return

def register_Ns3SimpleRefCount__Ns3AttributeChecker_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeChecker__gt___methods(root_module, cls):
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::AttributeChecker, ns3::empty, ns3::DefaultDeleter<ns3::AttributeChecker> >::SimpleRefCount() [constructor]
    cls.add_constructor([])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::AttributeChecker, ns3::empty, ns3::DefaultDeleter<ns3::AttributeChecker> >::SimpleRefCount(ns3::SimpleRefCount<ns3::AttributeChecker, ns3::empty, ns3::DefaultDeleter<ns3::AttributeChecker> > const & o) [copy constructor]
    cls.add_constructor([param('ns3::SimpleRefCount< ns3::AttributeChecker, ns3::empty, ns3::DefaultDeleter< ns3::AttributeChecker > > const &', 'o')])
    ## simple-ref-count.h (module 'core'): static void ns3::SimpleRefCount<ns3::AttributeChecker, ns3::empty, ns3::DefaultDeleter<ns3::AttributeChecker> >::Cleanup() [member function]
    cls.add_method('Cleanup', 
                   'void', 
                   [], 
                   is_static=True)
    return

def register_Ns3SimpleRefCount__Ns3AttributeValue_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeValue__gt___methods(root_module, cls):
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::AttributeValue, ns3::empty, ns3::DefaultDeleter<ns3::AttributeValue> >::SimpleRefCount() [constructor]
    cls.add_constructor([])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::AttributeValue, ns3::empty, ns3::DefaultDeleter<ns3::AttributeValue> >::SimpleRefCount(ns3::SimpleRefCount<ns3::AttributeValue, ns3::empty, ns3::DefaultDeleter<ns3::AttributeValue> > const & o) [copy constructor]
    cls.add_constructor([param('ns3::SimpleRefCount< ns3::AttributeValue, ns3::empty, ns3::DefaultDeleter< ns3::AttributeValue > > const &', 'o')])
    ## simple-ref-count.h (module 'core'): static void ns3::SimpleRefCount<ns3::AttributeValue, ns3::empty, ns3::DefaultDeleter<ns3::AttributeValue> >::Cleanup() [member function]
    cls.add_method('Cleanup', 
                   'void', 
                   [], 
                   is_static=True)
    return

def register_Ns3SimpleRefCount__Ns3CallbackImplBase_Ns3Empty_Ns3DefaultDeleter__lt__ns3CallbackImplBase__gt___methods(root_module, cls):
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::CallbackImplBase, ns3::empty, ns3::DefaultDeleter<ns3::CallbackImplBase> >::SimpleRefCount() [constructor]
    cls.add_constructor([])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::CallbackImplBase, ns3::empty, ns3::DefaultDeleter<ns3::CallbackImplBase> >::SimpleRefCount(ns3::SimpleRefCount<ns3::CallbackImplBase, ns3::empty, ns3::DefaultDeleter<ns3::CallbackImplBase> > const & o) [copy constructor]
    cls.add_constructor([param('ns3::SimpleRefCount< ns3::CallbackImplBase, ns3::empty, ns3::DefaultDeleter< ns3::CallbackImplBase > > const &', 'o')])
    ## simple-ref-count.h (module 'core'): static void ns3::SimpleRefCount<ns3::CallbackImplBase, ns3::empty, ns3::DefaultDeleter<ns3::CallbackImplBase> >::Cleanup() [member function]
    cls.add_method('Cleanup', 
                   'void', 
                   [], 
                   is_static=True)
    return

def register_Ns3SimpleRefCount__Ns3EventImpl_Ns3Empty_Ns3DefaultDeleter__lt__ns3EventImpl__gt___methods(root_module, cls):
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::EventImpl, ns3::empty, ns3::DefaultDeleter<ns3::EventImpl> >::SimpleRefCount() [constructor]
    cls.add_constructor([])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::EventImpl, ns3::empty, ns3::DefaultDeleter<ns3::EventImpl> >::SimpleRefCount(ns3::SimpleRefCount<ns3::EventImpl, ns3::empty, ns3::DefaultDeleter<ns3::EventImpl> > const & o) [copy constructor]
    cls.add_constructor([param('ns3::SimpleRefCount< ns3::EventImpl, ns3::empty, ns3::DefaultDeleter< ns3::EventImpl > > const &', 'o')])
    ## simple-ref-count.h (module 'core'): static void ns3::SimpleRefCount<ns3::EventImpl, ns3::empty, ns3::DefaultDeleter<ns3::EventImpl> >::Cleanup() [member function]
    cls.add_method('Cleanup', 
                   'void', 
                   [], 
                   is_static=True)
    return

def register_Ns3SimpleRefCount__Ns3Ipv4MulticastRoute_Ns3Empty_Ns3DefaultDeleter__lt__ns3Ipv4MulticastRoute__gt___methods(root_module, cls):
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::Ipv4MulticastRoute, ns3::empty, ns3::DefaultDeleter<ns3::Ipv4MulticastRoute> >::SimpleRefCount() [constructor]
    cls.add_constructor([])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::Ipv4MulticastRoute, ns3::empty, ns3::DefaultDeleter<ns3::Ipv4MulticastRoute> >::SimpleRefCount(ns3::SimpleRefCount<ns3::Ipv4MulticastRoute, ns3::empty, ns3::DefaultDeleter<ns3::Ipv4MulticastRoute> > const & o) [copy constructor]
    cls.add_constructor([param('ns3::SimpleRefCount< ns3::Ipv4MulticastRoute, ns3::empty, ns3::DefaultDeleter< ns3::Ipv4MulticastRoute > > const &', 'o')])
    ## simple-ref-count.h (module 'core'): static void ns3::SimpleRefCount<ns3::Ipv4MulticastRoute, ns3::empty, ns3::DefaultDeleter<ns3::Ipv4MulticastRoute> >::Cleanup() [member function]
    cls.add_method('Cleanup', 
                   'void', 
                   [], 
                   is_static=True)
    return

def register_Ns3SimpleRefCount__Ns3Ipv4Route_Ns3Empty_Ns3DefaultDeleter__lt__ns3Ipv4Route__gt___methods(root_module, cls):
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::Ipv4Route, ns3::empty, ns3::DefaultDeleter<ns3::Ipv4Route> >::SimpleRefCount() [constructor]
    cls.add_constructor([])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::Ipv4Route, ns3::empty, ns3::DefaultDeleter<ns3::Ipv4Route> >::SimpleRefCount(ns3::SimpleRefCount<ns3::Ipv4Route, ns3::empty, ns3::DefaultDeleter<ns3::Ipv4Route> > const & o) [copy constructor]
    cls.add_constructor([param('ns3::SimpleRefCount< ns3::Ipv4Route, ns3::empty, ns3::DefaultDeleter< ns3::Ipv4Route > > const &', 'o')])
    ## simple-ref-count.h (module 'core'): static void ns3::SimpleRefCount<ns3::Ipv4Route, ns3::empty, ns3::DefaultDeleter<ns3::Ipv4Route> >::Cleanup() [member function]
    cls.add_method('Cleanup', 
                   'void', 
                   [], 
                   is_static=True)
    return

def register_Ns3SimpleRefCount__Ns3NixVector_Ns3Empty_Ns3DefaultDeleter__lt__ns3NixVector__gt___methods(root_module, cls):
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::NixVector, ns3::empty, ns3::DefaultDeleter<ns3::NixVector> >::SimpleRefCount() [constructor]
    cls.add_constructor([])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::NixVector, ns3::empty, ns3::DefaultDeleter<ns3::NixVector> >::SimpleRefCount(ns3::SimpleRefCount<ns3::NixVector, ns3::empty, ns3::DefaultDeleter<ns3::NixVector> > const & o) [copy constructor]
    cls.add_constructor([param('ns3::SimpleRefCount< ns3::NixVector, ns3::empty, ns3::DefaultDeleter< ns3::NixVector > > const &', 'o')])
    ## simple-ref-count.h (module 'core'): static void ns3::SimpleRefCount<ns3::NixVector, ns3::empty, ns3::DefaultDeleter<ns3::NixVector> >::Cleanup() [member function]
    cls.add_method('Cleanup', 
                   'void', 
                   [], 
                   is_static=True)
    return

def register_Ns3SimpleRefCount__Ns3OutputStreamWrapper_Ns3Empty_Ns3DefaultDeleter__lt__ns3OutputStreamWrapper__gt___methods(root_module, cls):
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::OutputStreamWrapper, ns3::empty, ns3::DefaultDeleter<ns3::OutputStreamWrapper> >::SimpleRefCount() [constructor]
    cls.add_constructor([])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::OutputStreamWrapper, ns3::empty, ns3::DefaultDeleter<ns3::OutputStreamWrapper> >::SimpleRefCount(ns3::SimpleRefCount<ns3::OutputStreamWrapper, ns3::empty, ns3::DefaultDeleter<ns3::OutputStreamWrapper> > const & o) [copy constructor]
    cls.add_constructor([param('ns3::SimpleRefCount< ns3::OutputStreamWrapper, ns3::empty, ns3::DefaultDeleter< ns3::OutputStreamWrapper > > const &', 'o')])
    ## simple-ref-count.h (module 'core'): static void ns3::SimpleRefCount<ns3::OutputStreamWrapper, ns3::empty, ns3::DefaultDeleter<ns3::OutputStreamWrapper> >::Cleanup() [member function]
    cls.add_method('Cleanup', 
                   'void', 
                   [], 
                   is_static=True)
    return

def register_Ns3SimpleRefCount__Ns3Packet_Ns3Empty_Ns3DefaultDeleter__lt__ns3Packet__gt___methods(root_module, cls):
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::Packet, ns3::empty, ns3::DefaultDeleter<ns3::Packet> >::SimpleRefCount() [constructor]
    cls.add_constructor([])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::Packet, ns3::empty, ns3::DefaultDeleter<ns3::Packet> >::SimpleRefCount(ns3::SimpleRefCount<ns3::Packet, ns3::empty, ns3::DefaultDeleter<ns3::Packet> > const & o) [copy constructor]
    cls.add_constructor([param('ns3::SimpleRefCount< ns3::Packet, ns3::empty, ns3::DefaultDeleter< ns3::Packet > > const &', 'o')])
    ## simple-ref-count.h (module 'core'): static void ns3::SimpleRefCount<ns3::Packet, ns3::empty, ns3::DefaultDeleter<ns3::Packet> >::Cleanup() [member function]
    cls.add_method('Cleanup', 
                   'void', 
                   [], 
                   is_static=True)
    return

def register_Ns3SimpleRefCount__Ns3TraceSourceAccessor_Ns3Empty_Ns3DefaultDeleter__lt__ns3TraceSourceAccessor__gt___methods(root_module, cls):
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::TraceSourceAccessor, ns3::empty, ns3::DefaultDeleter<ns3::TraceSourceAccessor> >::SimpleRefCount() [constructor]
    cls.add_constructor([])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::TraceSourceAccessor, ns3::empty, ns3::DefaultDeleter<ns3::TraceSourceAccessor> >::SimpleRefCount(ns3::SimpleRefCount<ns3::TraceSourceAccessor, ns3::empty, ns3::DefaultDeleter<ns3::TraceSourceAccessor> > const & o) [copy constructor]
    cls.add_constructor([param('ns3::SimpleRefCount< ns3::TraceSourceAccessor, ns3::empty, ns3::DefaultDeleter< ns3::TraceSourceAccessor > > const &', 'o')])
    ## simple-ref-count.h (module 'core'): static void ns3::SimpleRefCount<ns3::TraceSourceAccessor, ns3::empty, ns3::DefaultDeleter<ns3::TraceSourceAccessor> >::Cleanup() [member function]
    cls.add_method('Cleanup', 
                   'void', 
                   [], 
                   is_static=True)
    return

def register_Ns3Socket_methods(root_module, cls):
    ## socket.h (module 'network'): ns3::Socket::Socket(ns3::Socket const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Socket const &', 'arg0')])
    ## socket.h (module 'network'): ns3::Socket::Socket() [constructor]
    cls.add_constructor([])
    ## socket.h (module 'network'): int ns3::Socket::Bind(ns3::Address const & address) [member function]
    cls.add_method('Bind', 
                   'int', 
                   [param('ns3::Address const &', 'address')], 
                   is_pure_virtual=True, is_virtual=True)
    ## socket.h (module 'network'): int ns3::Socket::Bind() [member function]
    cls.add_method('Bind', 
                   'int', 
                   [], 
                   is_pure_virtual=True, is_virtual=True)
    ## socket.h (module 'network'): int ns3::Socket::Bind6() [member function]
    cls.add_method('Bind6', 
                   'int', 
                   [], 
                   is_pure_virtual=True, is_virtual=True)
    ## socket.h (module 'network'): void ns3::Socket::BindToNetDevice(ns3::Ptr<ns3::NetDevice> netdevice) [member function]
    cls.add_method('BindToNetDevice', 
                   'void', 
                   [param('ns3::Ptr< ns3::NetDevice >', 'netdevice')], 
                   is_virtual=True)
    ## socket.h (module 'network'): int ns3::Socket::Close() [member function]
    cls.add_method('Close', 
                   'int', 
                   [], 
                   is_pure_virtual=True, is_virtual=True)
    ## socket.h (module 'network'): int ns3::Socket::Connect(ns3::Address const & address) [member function]
    cls.add_method('Connect', 
                   'int', 
                   [param('ns3::Address const &', 'address')], 
                   is_pure_virtual=True, is_virtual=True)
    ## socket.h (module 'network'): static ns3::Ptr<ns3::Socket> ns3::Socket::CreateSocket(ns3::Ptr<ns3::Node> node, ns3::TypeId tid) [member function]
    cls.add_method('CreateSocket', 
                   'ns3::Ptr< ns3::Socket >', 
                   [param('ns3::Ptr< ns3::Node >', 'node'), param('ns3::TypeId', 'tid')], 
                   is_static=True)
    ## socket.h (module 'network'): bool ns3::Socket::GetAllowBroadcast() const [member function]
    cls.add_method('GetAllowBroadcast', 
                   'bool', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## socket.h (module 'network'): ns3::Ptr<ns3::NetDevice> ns3::Socket::GetBoundNetDevice() [member function]
    cls.add_method('GetBoundNetDevice', 
                   'ns3::Ptr< ns3::NetDevice >', 
                   [])
    ## socket.h (module 'network'): ns3::Socket::SocketErrno ns3::Socket::GetErrno() const [member function]
    cls.add_method('GetErrno', 
                   'ns3::Socket::SocketErrno', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## socket.h (module 'network'): ns3::Ptr<ns3::Node> ns3::Socket::GetNode() const [member function]
    cls.add_method('GetNode', 
                   'ns3::Ptr< ns3::Node >', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## socket.h (module 'network'): uint32_t ns3::Socket::GetRxAvailable() const [member function]
    cls.add_method('GetRxAvailable', 
                   'uint32_t', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## socket.h (module 'network'): int ns3::Socket::GetSockName(ns3::Address & address) const [member function]
    cls.add_method('GetSockName', 
                   'int', 
                   [param('ns3::Address &', 'address')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## socket.h (module 'network'): ns3::Socket::SocketType ns3::Socket::GetSocketType() const [member function]
    cls.add_method('GetSocketType', 
                   'ns3::Socket::SocketType', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## socket.h (module 'network'): uint32_t ns3::Socket::GetTxAvailable() const [member function]
    cls.add_method('GetTxAvailable', 
                   'uint32_t', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## socket.h (module 'network'): static ns3::TypeId ns3::Socket::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## socket.h (module 'network'): bool ns3::Socket::IsRecvPktInfo() const [member function]
    cls.add_method('IsRecvPktInfo', 
                   'bool', 
                   [], 
                   is_const=True)
    ## socket.h (module 'network'): int ns3::Socket::Listen() [member function]
    cls.add_method('Listen', 
                   'int', 
                   [], 
                   is_pure_virtual=True, is_virtual=True)
    ## socket.h (module 'network'): ns3::Ptr<ns3::Packet> ns3::Socket::Recv(uint32_t maxSize, uint32_t flags) [member function]
    cls.add_method('Recv', 
                   'ns3::Ptr< ns3::Packet >', 
                   [param('uint32_t', 'maxSize'), param('uint32_t', 'flags')], 
                   is_pure_virtual=True, is_virtual=True)
    ## socket.h (module 'network'): ns3::Ptr<ns3::Packet> ns3::Socket::Recv() [member function]
    cls.add_method('Recv', 
                   'ns3::Ptr< ns3::Packet >', 
                   [])
    ## socket.h (module 'network'): int ns3::Socket::Recv(uint8_t * buf, uint32_t size, uint32_t flags) [member function]
    cls.add_method('Recv', 
                   'int', 
                   [param('uint8_t *', 'buf'), param('uint32_t', 'size'), param('uint32_t', 'flags')])
    ## socket.h (module 'network'): ns3::Ptr<ns3::Packet> ns3::Socket::RecvFrom(uint32_t maxSize, uint32_t flags, ns3::Address & fromAddress) [member function]
    cls.add_method('RecvFrom', 
                   'ns3::Ptr< ns3::Packet >', 
                   [param('uint32_t', 'maxSize'), param('uint32_t', 'flags'), param('ns3::Address &', 'fromAddress')], 
                   is_pure_virtual=True, is_virtual=True)
    ## socket.h (module 'network'): ns3::Ptr<ns3::Packet> ns3::Socket::RecvFrom(ns3::Address & fromAddress) [member function]
    cls.add_method('RecvFrom', 
                   'ns3::Ptr< ns3::Packet >', 
                   [param('ns3::Address &', 'fromAddress')])
    ## socket.h (module 'network'): int ns3::Socket::RecvFrom(uint8_t * buf, uint32_t size, uint32_t flags, ns3::Address & fromAddress) [member function]
    cls.add_method('RecvFrom', 
                   'int', 
                   [param('uint8_t *', 'buf'), param('uint32_t', 'size'), param('uint32_t', 'flags'), param('ns3::Address &', 'fromAddress')])
    ## socket.h (module 'network'): int ns3::Socket::Send(ns3::Ptr<ns3::Packet> p, uint32_t flags) [member function]
    cls.add_method('Send', 
                   'int', 
                   [param('ns3::Ptr< ns3::Packet >', 'p'), param('uint32_t', 'flags')], 
                   is_pure_virtual=True, is_virtual=True)
    ## socket.h (module 'network'): int ns3::Socket::Send(ns3::Ptr<ns3::Packet> p) [member function]
    cls.add_method('Send', 
                   'int', 
                   [param('ns3::Ptr< ns3::Packet >', 'p')])
    ## socket.h (module 'network'): int ns3::Socket::Send(uint8_t const * buf, uint32_t size, uint32_t flags) [member function]
    cls.add_method('Send', 
                   'int', 
                   [param('uint8_t const *', 'buf'), param('uint32_t', 'size'), param('uint32_t', 'flags')])
    ## socket.h (module 'network'): int ns3::Socket::SendTo(ns3::Ptr<ns3::Packet> p, uint32_t flags, ns3::Address const & toAddress) [member function]
    cls.add_method('SendTo', 
                   'int', 
                   [param('ns3::Ptr< ns3::Packet >', 'p'), param('uint32_t', 'flags'), param('ns3::Address const &', 'toAddress')], 
                   is_pure_virtual=True, is_virtual=True)
    ## socket.h (module 'network'): int ns3::Socket::SendTo(uint8_t const * buf, uint32_t size, uint32_t flags, ns3::Address const & address) [member function]
    cls.add_method('SendTo', 
                   'int', 
                   [param('uint8_t const *', 'buf'), param('uint32_t', 'size'), param('uint32_t', 'flags'), param('ns3::Address const &', 'address')])
    ## socket.h (module 'network'): void ns3::Socket::SetAcceptCallback(ns3::Callback<bool, ns3::Ptr<ns3::Socket>, ns3::Address const&, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> connectionRequest, ns3::Callback<void, ns3::Ptr<ns3::Socket>, ns3::Address const&, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> newConnectionCreated) [member function]
    cls.add_method('SetAcceptCallback', 
                   'void', 
                   [param('ns3::Callback< bool, ns3::Ptr< ns3::Socket >, ns3::Address const &, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'connectionRequest'), param('ns3::Callback< void, ns3::Ptr< ns3::Socket >, ns3::Address const &, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'newConnectionCreated')])
    ## socket.h (module 'network'): bool ns3::Socket::SetAllowBroadcast(bool allowBroadcast) [member function]
    cls.add_method('SetAllowBroadcast', 
                   'bool', 
                   [param('bool', 'allowBroadcast')], 
                   is_pure_virtual=True, is_virtual=True)
    ## socket.h (module 'network'): void ns3::Socket::SetCloseCallbacks(ns3::Callback<void, ns3::Ptr<ns3::Socket>, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> normalClose, ns3::Callback<void, ns3::Ptr<ns3::Socket>, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> errorClose) [member function]
    cls.add_method('SetCloseCallbacks', 
                   'void', 
                   [param('ns3::Callback< void, ns3::Ptr< ns3::Socket >, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'normalClose'), param('ns3::Callback< void, ns3::Ptr< ns3::Socket >, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'errorClose')])
    ## socket.h (module 'network'): void ns3::Socket::SetConnectCallback(ns3::Callback<void, ns3::Ptr<ns3::Socket>, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> connectionSucceeded, ns3::Callback<void, ns3::Ptr<ns3::Socket>, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> connectionFailed) [member function]
    cls.add_method('SetConnectCallback', 
                   'void', 
                   [param('ns3::Callback< void, ns3::Ptr< ns3::Socket >, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'connectionSucceeded'), param('ns3::Callback< void, ns3::Ptr< ns3::Socket >, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'connectionFailed')])
    ## socket.h (module 'network'): void ns3::Socket::SetDataSentCallback(ns3::Callback<void, ns3::Ptr<ns3::Socket>, unsigned int, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> dataSent) [member function]
    cls.add_method('SetDataSentCallback', 
                   'void', 
                   [param('ns3::Callback< void, ns3::Ptr< ns3::Socket >, unsigned int, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'dataSent')])
    ## socket.h (module 'network'): void ns3::Socket::SetRecvCallback(ns3::Callback<void, ns3::Ptr<ns3::Socket>, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> arg0) [member function]
    cls.add_method('SetRecvCallback', 
                   'void', 
                   [param('ns3::Callback< void, ns3::Ptr< ns3::Socket >, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'arg0')])
    ## socket.h (module 'network'): void ns3::Socket::SetRecvPktInfo(bool flag) [member function]
    cls.add_method('SetRecvPktInfo', 
                   'void', 
                   [param('bool', 'flag')])
    ## socket.h (module 'network'): void ns3::Socket::SetSendCallback(ns3::Callback<void, ns3::Ptr<ns3::Socket>, unsigned int, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> sendCb) [member function]
    cls.add_method('SetSendCallback', 
                   'void', 
                   [param('ns3::Callback< void, ns3::Ptr< ns3::Socket >, unsigned int, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'sendCb')])
    ## socket.h (module 'network'): int ns3::Socket::ShutdownRecv() [member function]
    cls.add_method('ShutdownRecv', 
                   'int', 
                   [], 
                   is_pure_virtual=True, is_virtual=True)
    ## socket.h (module 'network'): int ns3::Socket::ShutdownSend() [member function]
    cls.add_method('ShutdownSend', 
                   'int', 
                   [], 
                   is_pure_virtual=True, is_virtual=True)
    ## socket.h (module 'network'): void ns3::Socket::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## socket.h (module 'network'): void ns3::Socket::NotifyConnectionFailed() [member function]
    cls.add_method('NotifyConnectionFailed', 
                   'void', 
                   [], 
                   visibility='protected')
    ## socket.h (module 'network'): bool ns3::Socket::NotifyConnectionRequest(ns3::Address const & from) [member function]
    cls.add_method('NotifyConnectionRequest', 
                   'bool', 
                   [param('ns3::Address const &', 'from')], 
                   visibility='protected')
    ## socket.h (module 'network'): void ns3::Socket::NotifyConnectionSucceeded() [member function]
    cls.add_method('NotifyConnectionSucceeded', 
                   'void', 
                   [], 
                   visibility='protected')
    ## socket.h (module 'network'): void ns3::Socket::NotifyDataRecv() [member function]
    cls.add_method('NotifyDataRecv', 
                   'void', 
                   [], 
                   visibility='protected')
    ## socket.h (module 'network'): void ns3::Socket::NotifyDataSent(uint32_t size) [member function]
    cls.add_method('NotifyDataSent', 
                   'void', 
                   [param('uint32_t', 'size')], 
                   visibility='protected')
    ## socket.h (module 'network'): void ns3::Socket::NotifyErrorClose() [member function]
    cls.add_method('NotifyErrorClose', 
                   'void', 
                   [], 
                   visibility='protected')
    ## socket.h (module 'network'): void ns3::Socket::NotifyNewConnectionCreated(ns3::Ptr<ns3::Socket> socket, ns3::Address const & from) [member function]
    cls.add_method('NotifyNewConnectionCreated', 
                   'void', 
                   [param('ns3::Ptr< ns3::Socket >', 'socket'), param('ns3::Address const &', 'from')], 
                   visibility='protected')
    ## socket.h (module 'network'): void ns3::Socket::NotifyNormalClose() [member function]
    cls.add_method('NotifyNormalClose', 
                   'void', 
                   [], 
                   visibility='protected')
    ## socket.h (module 'network'): void ns3::Socket::NotifySend(uint32_t spaceAvailable) [member function]
    cls.add_method('NotifySend', 
                   'void', 
                   [param('uint32_t', 'spaceAvailable')], 
                   visibility='protected')
    return

def register_Ns3SocketAddressTag_methods(root_module, cls):
    ## socket.h (module 'network'): ns3::SocketAddressTag::SocketAddressTag(ns3::SocketAddressTag const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::SocketAddressTag const &', 'arg0')])
    ## socket.h (module 'network'): ns3::SocketAddressTag::SocketAddressTag() [constructor]
    cls.add_constructor([])
    ## socket.h (module 'network'): void ns3::SocketAddressTag::Deserialize(ns3::TagBuffer i) [member function]
    cls.add_method('Deserialize', 
                   'void', 
                   [param('ns3::TagBuffer', 'i')], 
                   is_virtual=True)
    ## socket.h (module 'network'): ns3::Address ns3::SocketAddressTag::GetAddress() const [member function]
    cls.add_method('GetAddress', 
                   'ns3::Address', 
                   [], 
                   is_const=True)
    ## socket.h (module 'network'): ns3::TypeId ns3::SocketAddressTag::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## socket.h (module 'network'): uint32_t ns3::SocketAddressTag::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## socket.h (module 'network'): static ns3::TypeId ns3::SocketAddressTag::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## socket.h (module 'network'): void ns3::SocketAddressTag::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## socket.h (module 'network'): void ns3::SocketAddressTag::Serialize(ns3::TagBuffer i) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::TagBuffer', 'i')], 
                   is_const=True, is_virtual=True)
    ## socket.h (module 'network'): void ns3::SocketAddressTag::SetAddress(ns3::Address addr) [member function]
    cls.add_method('SetAddress', 
                   'void', 
                   [param('ns3::Address', 'addr')])
    return

def register_Ns3SocketIpTtlTag_methods(root_module, cls):
    ## socket.h (module 'network'): ns3::SocketIpTtlTag::SocketIpTtlTag(ns3::SocketIpTtlTag const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::SocketIpTtlTag const &', 'arg0')])
    ## socket.h (module 'network'): ns3::SocketIpTtlTag::SocketIpTtlTag() [constructor]
    cls.add_constructor([])
    ## socket.h (module 'network'): void ns3::SocketIpTtlTag::Deserialize(ns3::TagBuffer i) [member function]
    cls.add_method('Deserialize', 
                   'void', 
                   [param('ns3::TagBuffer', 'i')], 
                   is_virtual=True)
    ## socket.h (module 'network'): ns3::TypeId ns3::SocketIpTtlTag::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## socket.h (module 'network'): uint32_t ns3::SocketIpTtlTag::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## socket.h (module 'network'): uint8_t ns3::SocketIpTtlTag::GetTtl() const [member function]
    cls.add_method('GetTtl', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## socket.h (module 'network'): static ns3::TypeId ns3::SocketIpTtlTag::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## socket.h (module 'network'): void ns3::SocketIpTtlTag::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## socket.h (module 'network'): void ns3::SocketIpTtlTag::Serialize(ns3::TagBuffer i) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::TagBuffer', 'i')], 
                   is_const=True, is_virtual=True)
    ## socket.h (module 'network'): void ns3::SocketIpTtlTag::SetTtl(uint8_t ttl) [member function]
    cls.add_method('SetTtl', 
                   'void', 
                   [param('uint8_t', 'ttl')])
    return

def register_Ns3SocketSetDontFragmentTag_methods(root_module, cls):
    ## socket.h (module 'network'): ns3::SocketSetDontFragmentTag::SocketSetDontFragmentTag(ns3::SocketSetDontFragmentTag const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::SocketSetDontFragmentTag const &', 'arg0')])
    ## socket.h (module 'network'): ns3::SocketSetDontFragmentTag::SocketSetDontFragmentTag() [constructor]
    cls.add_constructor([])
    ## socket.h (module 'network'): void ns3::SocketSetDontFragmentTag::Deserialize(ns3::TagBuffer i) [member function]
    cls.add_method('Deserialize', 
                   'void', 
                   [param('ns3::TagBuffer', 'i')], 
                   is_virtual=True)
    ## socket.h (module 'network'): void ns3::SocketSetDontFragmentTag::Disable() [member function]
    cls.add_method('Disable', 
                   'void', 
                   [])
    ## socket.h (module 'network'): void ns3::SocketSetDontFragmentTag::Enable() [member function]
    cls.add_method('Enable', 
                   'void', 
                   [])
    ## socket.h (module 'network'): ns3::TypeId ns3::SocketSetDontFragmentTag::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## socket.h (module 'network'): uint32_t ns3::SocketSetDontFragmentTag::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## socket.h (module 'network'): static ns3::TypeId ns3::SocketSetDontFragmentTag::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## socket.h (module 'network'): bool ns3::SocketSetDontFragmentTag::IsEnabled() const [member function]
    cls.add_method('IsEnabled', 
                   'bool', 
                   [], 
                   is_const=True)
    ## socket.h (module 'network'): void ns3::SocketSetDontFragmentTag::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## socket.h (module 'network'): void ns3::SocketSetDontFragmentTag::Serialize(ns3::TagBuffer i) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::TagBuffer', 'i')], 
                   is_const=True, is_virtual=True)
    return

def register_Ns3Time_methods(root_module, cls):
    cls.add_binary_comparison_operator('!=')
    cls.add_inplace_numeric_operator('+=', param('ns3::Time const &', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::Time'], root_module['ns3::Time'], param('ns3::Time const &', 'right'))
    cls.add_binary_numeric_operator('-', root_module['ns3::Time'], root_module['ns3::Time'], param('ns3::Time const &', 'right'))
    cls.add_binary_comparison_operator('<')
    cls.add_binary_comparison_operator('>')
    cls.add_inplace_numeric_operator('-=', param('ns3::Time const &', 'right'))
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('<=')
    cls.add_binary_comparison_operator('==')
    cls.add_binary_comparison_operator('>=')
    ## nstime.h (module 'core'): ns3::Time::Time() [constructor]
    cls.add_constructor([])
    ## nstime.h (module 'core'): ns3::Time::Time(ns3::Time const & o) [copy constructor]
    cls.add_constructor([param('ns3::Time const &', 'o')])
    ## nstime.h (module 'core'): ns3::Time::Time(double v) [constructor]
    cls.add_constructor([param('double', 'v')])
    ## nstime.h (module 'core'): ns3::Time::Time(int v) [constructor]
    cls.add_constructor([param('int', 'v')])
    ## nstime.h (module 'core'): ns3::Time::Time(long int v) [constructor]
    cls.add_constructor([param('long int', 'v')])
    ## nstime.h (module 'core'): ns3::Time::Time(long long int v) [constructor]
    cls.add_constructor([param('long long int', 'v')])
    ## nstime.h (module 'core'): ns3::Time::Time(unsigned int v) [constructor]
    cls.add_constructor([param('unsigned int', 'v')])
    ## nstime.h (module 'core'): ns3::Time::Time(long unsigned int v) [constructor]
    cls.add_constructor([param('long unsigned int', 'v')])
    ## nstime.h (module 'core'): ns3::Time::Time(long long unsigned int v) [constructor]
    cls.add_constructor([param('long long unsigned int', 'v')])
    ## nstime.h (module 'core'): ns3::Time::Time(std::string const & s) [constructor]
    cls.add_constructor([param('std::string const &', 's')])
    ## nstime.h (module 'core'): ns3::Time::Time(ns3::int64x64_t const & value) [constructor]
    cls.add_constructor([param('ns3::int64x64_t const &', 'value')])
    ## nstime.h (module 'core'): int ns3::Time::Compare(ns3::Time const & o) const [member function]
    cls.add_method('Compare', 
                   'int', 
                   [param('ns3::Time const &', 'o')], 
                   is_const=True)
    ## nstime.h (module 'core'): static ns3::Time ns3::Time::From(ns3::int64x64_t const & from, ns3::Time::Unit timeUnit) [member function]
    cls.add_method('From', 
                   'ns3::Time', 
                   [param('ns3::int64x64_t const &', 'from'), param('ns3::Time::Unit', 'timeUnit')], 
                   is_static=True)
    ## nstime.h (module 'core'): static ns3::Time ns3::Time::From(ns3::int64x64_t const & value) [member function]
    cls.add_method('From', 
                   'ns3::Time', 
                   [param('ns3::int64x64_t const &', 'value')], 
                   is_static=True)
    ## nstime.h (module 'core'): static ns3::Time ns3::Time::FromDouble(double value, ns3::Time::Unit timeUnit) [member function]
    cls.add_method('FromDouble', 
                   'ns3::Time', 
                   [param('double', 'value'), param('ns3::Time::Unit', 'timeUnit')], 
                   is_static=True)
    ## nstime.h (module 'core'): static ns3::Time ns3::Time::FromInteger(uint64_t value, ns3::Time::Unit timeUnit) [member function]
    cls.add_method('FromInteger', 
                   'ns3::Time', 
                   [param('uint64_t', 'value'), param('ns3::Time::Unit', 'timeUnit')], 
                   is_static=True)
    ## nstime.h (module 'core'): double ns3::Time::GetDouble() const [member function]
    cls.add_method('GetDouble', 
                   'double', 
                   [], 
                   is_const=True)
    ## nstime.h (module 'core'): int64_t ns3::Time::GetFemtoSeconds() const [member function]
    cls.add_method('GetFemtoSeconds', 
                   'int64_t', 
                   [], 
                   is_const=True)
    ## nstime.h (module 'core'): int64_t ns3::Time::GetInteger() const [member function]
    cls.add_method('GetInteger', 
                   'int64_t', 
                   [], 
                   is_const=True)
    ## nstime.h (module 'core'): int64_t ns3::Time::GetMicroSeconds() const [member function]
    cls.add_method('GetMicroSeconds', 
                   'int64_t', 
                   [], 
                   is_const=True)
    ## nstime.h (module 'core'): int64_t ns3::Time::GetMilliSeconds() const [member function]
    cls.add_method('GetMilliSeconds', 
                   'int64_t', 
                   [], 
                   is_const=True)
    ## nstime.h (module 'core'): int64_t ns3::Time::GetNanoSeconds() const [member function]
    cls.add_method('GetNanoSeconds', 
                   'int64_t', 
                   [], 
                   is_const=True)
    ## nstime.h (module 'core'): int64_t ns3::Time::GetPicoSeconds() const [member function]
    cls.add_method('GetPicoSeconds', 
                   'int64_t', 
                   [], 
                   is_const=True)
    ## nstime.h (module 'core'): static ns3::Time::Unit ns3::Time::GetResolution() [member function]
    cls.add_method('GetResolution', 
                   'ns3::Time::Unit', 
                   [], 
                   is_static=True)
    ## nstime.h (module 'core'): double ns3::Time::GetSeconds() const [member function]
    cls.add_method('GetSeconds', 
                   'double', 
                   [], 
                   is_const=True)
    ## nstime.h (module 'core'): int64_t ns3::Time::GetTimeStep() const [member function]
    cls.add_method('GetTimeStep', 
                   'int64_t', 
                   [], 
                   is_const=True)
    ## nstime.h (module 'core'): bool ns3::Time::IsNegative() const [member function]
    cls.add_method('IsNegative', 
                   'bool', 
                   [], 
                   is_const=True)
    ## nstime.h (module 'core'): bool ns3::Time::IsPositive() const [member function]
    cls.add_method('IsPositive', 
                   'bool', 
                   [], 
                   is_const=True)
    ## nstime.h (module 'core'): bool ns3::Time::IsStrictlyNegative() const [member function]
    cls.add_method('IsStrictlyNegative', 
                   'bool', 
                   [], 
                   is_const=True)
    ## nstime.h (module 'core'): bool ns3::Time::IsStrictlyPositive() const [member function]
    cls.add_method('IsStrictlyPositive', 
                   'bool', 
                   [], 
                   is_const=True)
    ## nstime.h (module 'core'): bool ns3::Time::IsZero() const [member function]
    cls.add_method('IsZero', 
                   'bool', 
                   [], 
                   is_const=True)
    ## nstime.h (module 'core'): static void ns3::Time::SetResolution(ns3::Time::Unit resolution) [member function]
    cls.add_method('SetResolution', 
                   'void', 
                   [param('ns3::Time::Unit', 'resolution')], 
                   is_static=True)
    ## nstime.h (module 'core'): ns3::int64x64_t ns3::Time::To(ns3::Time::Unit timeUnit) const [member function]
    cls.add_method('To', 
                   'ns3::int64x64_t', 
                   [param('ns3::Time::Unit', 'timeUnit')], 
                   is_const=True)
    ## nstime.h (module 'core'): double ns3::Time::ToDouble(ns3::Time::Unit timeUnit) const [member function]
    cls.add_method('ToDouble', 
                   'double', 
                   [param('ns3::Time::Unit', 'timeUnit')], 
                   is_const=True)
    ## nstime.h (module 'core'): int64_t ns3::Time::ToInteger(ns3::Time::Unit timeUnit) const [member function]
    cls.add_method('ToInteger', 
                   'int64_t', 
                   [param('ns3::Time::Unit', 'timeUnit')], 
                   is_const=True)
    return

def register_Ns3TraceSourceAccessor_methods(root_module, cls):
    ## trace-source-accessor.h (module 'core'): ns3::TraceSourceAccessor::TraceSourceAccessor(ns3::TraceSourceAccessor const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::TraceSourceAccessor const &', 'arg0')])
    ## trace-source-accessor.h (module 'core'): ns3::TraceSourceAccessor::TraceSourceAccessor() [constructor]
    cls.add_constructor([])
    ## trace-source-accessor.h (module 'core'): bool ns3::TraceSourceAccessor::Connect(ns3::ObjectBase * obj, std::string context, ns3::CallbackBase const & cb) const [member function]
    cls.add_method('Connect', 
                   'bool', 
                   [param('ns3::ObjectBase *', 'obj', transfer_ownership=False), param('std::string', 'context'), param('ns3::CallbackBase const &', 'cb')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## trace-source-accessor.h (module 'core'): bool ns3::TraceSourceAccessor::ConnectWithoutContext(ns3::ObjectBase * obj, ns3::CallbackBase const & cb) const [member function]
    cls.add_method('ConnectWithoutContext', 
                   'bool', 
                   [param('ns3::ObjectBase *', 'obj', transfer_ownership=False), param('ns3::CallbackBase const &', 'cb')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## trace-source-accessor.h (module 'core'): bool ns3::TraceSourceAccessor::Disconnect(ns3::ObjectBase * obj, std::string context, ns3::CallbackBase const & cb) const [member function]
    cls.add_method('Disconnect', 
                   'bool', 
                   [param('ns3::ObjectBase *', 'obj', transfer_ownership=False), param('std::string', 'context'), param('ns3::CallbackBase const &', 'cb')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## trace-source-accessor.h (module 'core'): bool ns3::TraceSourceAccessor::DisconnectWithoutContext(ns3::ObjectBase * obj, ns3::CallbackBase const & cb) const [member function]
    cls.add_method('DisconnectWithoutContext', 
                   'bool', 
                   [param('ns3::ObjectBase *', 'obj', transfer_ownership=False), param('ns3::CallbackBase const &', 'cb')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    return

def register_Ns3Trailer_methods(root_module, cls):
    cls.add_output_stream_operator()
    ## trailer.h (module 'network'): ns3::Trailer::Trailer() [constructor]
    cls.add_constructor([])
    ## trailer.h (module 'network'): ns3::Trailer::Trailer(ns3::Trailer const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Trailer const &', 'arg0')])
    ## trailer.h (module 'network'): uint32_t ns3::Trailer::Deserialize(ns3::Buffer::Iterator end) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'end')], 
                   is_pure_virtual=True, is_virtual=True)
    ## trailer.h (module 'network'): uint32_t ns3::Trailer::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## trailer.h (module 'network'): static ns3::TypeId ns3::Trailer::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## trailer.h (module 'network'): void ns3::Trailer::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## trailer.h (module 'network'): void ns3::Trailer::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    return

def register_Ns3TriangularRandomVariable_methods(root_module, cls):
    ## random-variable-stream.h (module 'core'): static ns3::TypeId ns3::TriangularRandomVariable::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## random-variable-stream.h (module 'core'): ns3::TriangularRandomVariable::TriangularRandomVariable() [constructor]
    cls.add_constructor([])
    ## random-variable-stream.h (module 'core'): double ns3::TriangularRandomVariable::GetMean() const [member function]
    cls.add_method('GetMean', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::TriangularRandomVariable::GetMin() const [member function]
    cls.add_method('GetMin', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::TriangularRandomVariable::GetMax() const [member function]
    cls.add_method('GetMax', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::TriangularRandomVariable::GetValue(double mean, double min, double max) [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [param('double', 'mean'), param('double', 'min'), param('double', 'max')])
    ## random-variable-stream.h (module 'core'): uint32_t ns3::TriangularRandomVariable::GetInteger(uint32_t mean, uint32_t min, uint32_t max) [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [param('uint32_t', 'mean'), param('uint32_t', 'min'), param('uint32_t', 'max')])
    ## random-variable-stream.h (module 'core'): double ns3::TriangularRandomVariable::GetValue() [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [], 
                   is_virtual=True)
    ## random-variable-stream.h (module 'core'): uint32_t ns3::TriangularRandomVariable::GetInteger() [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [], 
                   is_virtual=True)
    return

def register_Ns3UniformRandomVariable_methods(root_module, cls):
    ## random-variable-stream.h (module 'core'): static ns3::TypeId ns3::UniformRandomVariable::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## random-variable-stream.h (module 'core'): ns3::UniformRandomVariable::UniformRandomVariable() [constructor]
    cls.add_constructor([])
    ## random-variable-stream.h (module 'core'): double ns3::UniformRandomVariable::GetMin() const [member function]
    cls.add_method('GetMin', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::UniformRandomVariable::GetMax() const [member function]
    cls.add_method('GetMax', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::UniformRandomVariable::GetValue(double min, double max) [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [param('double', 'min'), param('double', 'max')])
    ## random-variable-stream.h (module 'core'): uint32_t ns3::UniformRandomVariable::GetInteger(uint32_t min, uint32_t max) [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [param('uint32_t', 'min'), param('uint32_t', 'max')])
    ## random-variable-stream.h (module 'core'): double ns3::UniformRandomVariable::GetValue() [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [], 
                   is_virtual=True)
    ## random-variable-stream.h (module 'core'): uint32_t ns3::UniformRandomVariable::GetInteger() [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [], 
                   is_virtual=True)
    return

def register_Ns3WeibullRandomVariable_methods(root_module, cls):
    ## random-variable-stream.h (module 'core'): static ns3::TypeId ns3::WeibullRandomVariable::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## random-variable-stream.h (module 'core'): ns3::WeibullRandomVariable::WeibullRandomVariable() [constructor]
    cls.add_constructor([])
    ## random-variable-stream.h (module 'core'): double ns3::WeibullRandomVariable::GetScale() const [member function]
    cls.add_method('GetScale', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::WeibullRandomVariable::GetShape() const [member function]
    cls.add_method('GetShape', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::WeibullRandomVariable::GetBound() const [member function]
    cls.add_method('GetBound', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::WeibullRandomVariable::GetValue(double scale, double shape, double bound) [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [param('double', 'scale'), param('double', 'shape'), param('double', 'bound')])
    ## random-variable-stream.h (module 'core'): uint32_t ns3::WeibullRandomVariable::GetInteger(uint32_t scale, uint32_t shape, uint32_t bound) [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [param('uint32_t', 'scale'), param('uint32_t', 'shape'), param('uint32_t', 'bound')])
    ## random-variable-stream.h (module 'core'): double ns3::WeibullRandomVariable::GetValue() [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [], 
                   is_virtual=True)
    ## random-variable-stream.h (module 'core'): uint32_t ns3::WeibullRandomVariable::GetInteger() [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [], 
                   is_virtual=True)
    return

def register_Ns3WifiMacHeader_methods(root_module, cls):
    ## wifi-mac-header.h (module 'wifi'): ns3::WifiMacHeader::WifiMacHeader(ns3::WifiMacHeader const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::WifiMacHeader const &', 'arg0')])
    ## wifi-mac-header.h (module 'wifi'): ns3::WifiMacHeader::WifiMacHeader() [constructor]
    cls.add_constructor([])
    ## wifi-mac-header.h (module 'wifi'): uint32_t ns3::WifiMacHeader::Deserialize(ns3::Buffer::Iterator start) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_virtual=True)
    ## wifi-mac-header.h (module 'wifi'): ns3::Mac48Address ns3::WifiMacHeader::GetAddr1() const [member function]
    cls.add_method('GetAddr1', 
                   'ns3::Mac48Address', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): ns3::Mac48Address ns3::WifiMacHeader::GetAddr2() const [member function]
    cls.add_method('GetAddr2', 
                   'ns3::Mac48Address', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): ns3::Mac48Address ns3::WifiMacHeader::GetAddr3() const [member function]
    cls.add_method('GetAddr3', 
                   'ns3::Mac48Address', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): ns3::Mac48Address ns3::WifiMacHeader::GetAddr4() const [member function]
    cls.add_method('GetAddr4', 
                   'ns3::Mac48Address', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): ns3::Time ns3::WifiMacHeader::GetDuration() const [member function]
    cls.add_method('GetDuration', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): uint16_t ns3::WifiMacHeader::GetFragmentNumber() const [member function]
    cls.add_method('GetFragmentNumber', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): ns3::TypeId ns3::WifiMacHeader::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## wifi-mac-header.h (module 'wifi'): ns3::WifiMacHeader::QosAckPolicy ns3::WifiMacHeader::GetQosAckPolicy() const [member function]
    cls.add_method('GetQosAckPolicy', 
                   'ns3::WifiMacHeader::QosAckPolicy', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): uint8_t ns3::WifiMacHeader::GetQosTid() const [member function]
    cls.add_method('GetQosTid', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): uint8_t ns3::WifiMacHeader::GetQosTxopLimit() const [member function]
    cls.add_method('GetQosTxopLimit', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): uint16_t ns3::WifiMacHeader::GetRawDuration() const [member function]
    cls.add_method('GetRawDuration', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): uint16_t ns3::WifiMacHeader::GetSequenceControl() const [member function]
    cls.add_method('GetSequenceControl', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): uint16_t ns3::WifiMacHeader::GetSequenceNumber() const [member function]
    cls.add_method('GetSequenceNumber', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): uint32_t ns3::WifiMacHeader::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## wifi-mac-header.h (module 'wifi'): uint32_t ns3::WifiMacHeader::GetSize() const [member function]
    cls.add_method('GetSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): ns3::WifiMacType ns3::WifiMacHeader::GetType() const [member function]
    cls.add_method('GetType', 
                   'ns3::WifiMacType', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): static ns3::TypeId ns3::WifiMacHeader::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## wifi-mac-header.h (module 'wifi'): char const * ns3::WifiMacHeader::GetTypeString() const [member function]
    cls.add_method('GetTypeString', 
                   'char const *', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsAck() const [member function]
    cls.add_method('IsAck', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsAction() const [member function]
    cls.add_method('IsAction', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsAssocReq() const [member function]
    cls.add_method('IsAssocReq', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsAssocResp() const [member function]
    cls.add_method('IsAssocResp', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsAuthentication() const [member function]
    cls.add_method('IsAuthentication', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsBeacon() const [member function]
    cls.add_method('IsBeacon', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsBlockAck() const [member function]
    cls.add_method('IsBlockAck', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsBlockAckReq() const [member function]
    cls.add_method('IsBlockAckReq', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsCfpoll() const [member function]
    cls.add_method('IsCfpoll', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsCtl() const [member function]
    cls.add_method('IsCtl', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsCts() const [member function]
    cls.add_method('IsCts', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsData() const [member function]
    cls.add_method('IsData', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsDeauthentication() const [member function]
    cls.add_method('IsDeauthentication', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsDisassociation() const [member function]
    cls.add_method('IsDisassociation', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsFromDs() const [member function]
    cls.add_method('IsFromDs', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsMgt() const [member function]
    cls.add_method('IsMgt', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsMoreFragments() const [member function]
    cls.add_method('IsMoreFragments', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsMultihopAction() const [member function]
    cls.add_method('IsMultihopAction', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsProbeReq() const [member function]
    cls.add_method('IsProbeReq', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsProbeResp() const [member function]
    cls.add_method('IsProbeResp', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsQosAck() const [member function]
    cls.add_method('IsQosAck', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsQosAmsdu() const [member function]
    cls.add_method('IsQosAmsdu', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsQosBlockAck() const [member function]
    cls.add_method('IsQosBlockAck', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsQosData() const [member function]
    cls.add_method('IsQosData', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsQosEosp() const [member function]
    cls.add_method('IsQosEosp', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsQosNoAck() const [member function]
    cls.add_method('IsQosNoAck', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsReassocReq() const [member function]
    cls.add_method('IsReassocReq', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsReassocResp() const [member function]
    cls.add_method('IsReassocResp', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsRetry() const [member function]
    cls.add_method('IsRetry', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsRts() const [member function]
    cls.add_method('IsRts', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsToDs() const [member function]
    cls.add_method('IsToDs', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True, is_virtual=True)
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetAction() [member function]
    cls.add_method('SetAction', 
                   'void', 
                   [])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetAddr1(ns3::Mac48Address address) [member function]
    cls.add_method('SetAddr1', 
                   'void', 
                   [param('ns3::Mac48Address', 'address')])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetAddr2(ns3::Mac48Address address) [member function]
    cls.add_method('SetAddr2', 
                   'void', 
                   [param('ns3::Mac48Address', 'address')])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetAddr3(ns3::Mac48Address address) [member function]
    cls.add_method('SetAddr3', 
                   'void', 
                   [param('ns3::Mac48Address', 'address')])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetAddr4(ns3::Mac48Address address) [member function]
    cls.add_method('SetAddr4', 
                   'void', 
                   [param('ns3::Mac48Address', 'address')])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetAssocReq() [member function]
    cls.add_method('SetAssocReq', 
                   'void', 
                   [])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetAssocResp() [member function]
    cls.add_method('SetAssocResp', 
                   'void', 
                   [])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetBeacon() [member function]
    cls.add_method('SetBeacon', 
                   'void', 
                   [])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetBlockAck() [member function]
    cls.add_method('SetBlockAck', 
                   'void', 
                   [])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetBlockAckReq() [member function]
    cls.add_method('SetBlockAckReq', 
                   'void', 
                   [])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetDsFrom() [member function]
    cls.add_method('SetDsFrom', 
                   'void', 
                   [])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetDsNotFrom() [member function]
    cls.add_method('SetDsNotFrom', 
                   'void', 
                   [])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetDsNotTo() [member function]
    cls.add_method('SetDsNotTo', 
                   'void', 
                   [])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetDsTo() [member function]
    cls.add_method('SetDsTo', 
                   'void', 
                   [])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetDuration(ns3::Time duration) [member function]
    cls.add_method('SetDuration', 
                   'void', 
                   [param('ns3::Time', 'duration')])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetFragmentNumber(uint8_t frag) [member function]
    cls.add_method('SetFragmentNumber', 
                   'void', 
                   [param('uint8_t', 'frag')])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetId(uint16_t id) [member function]
    cls.add_method('SetId', 
                   'void', 
                   [param('uint16_t', 'id')])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetMoreFragments() [member function]
    cls.add_method('SetMoreFragments', 
                   'void', 
                   [])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetMultihopAction() [member function]
    cls.add_method('SetMultihopAction', 
                   'void', 
                   [])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetNoMoreFragments() [member function]
    cls.add_method('SetNoMoreFragments', 
                   'void', 
                   [])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetNoRetry() [member function]
    cls.add_method('SetNoRetry', 
                   'void', 
                   [])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetProbeReq() [member function]
    cls.add_method('SetProbeReq', 
                   'void', 
                   [])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetProbeResp() [member function]
    cls.add_method('SetProbeResp', 
                   'void', 
                   [])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetQosAckPolicy(ns3::WifiMacHeader::QosAckPolicy arg0) [member function]
    cls.add_method('SetQosAckPolicy', 
                   'void', 
                   [param('ns3::WifiMacHeader::QosAckPolicy', 'arg0')])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetQosAmsdu() [member function]
    cls.add_method('SetQosAmsdu', 
                   'void', 
                   [])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetQosBlockAck() [member function]
    cls.add_method('SetQosBlockAck', 
                   'void', 
                   [])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetQosEosp() [member function]
    cls.add_method('SetQosEosp', 
                   'void', 
                   [])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetQosNoAck() [member function]
    cls.add_method('SetQosNoAck', 
                   'void', 
                   [])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetQosNoAmsdu() [member function]
    cls.add_method('SetQosNoAmsdu', 
                   'void', 
                   [])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetQosNoEosp() [member function]
    cls.add_method('SetQosNoEosp', 
                   'void', 
                   [])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetQosNormalAck() [member function]
    cls.add_method('SetQosNormalAck', 
                   'void', 
                   [])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetQosTid(uint8_t tid) [member function]
    cls.add_method('SetQosTid', 
                   'void', 
                   [param('uint8_t', 'tid')])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetQosTxopLimit(uint8_t txop) [member function]
    cls.add_method('SetQosTxopLimit', 
                   'void', 
                   [param('uint8_t', 'txop')])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetRawDuration(uint16_t duration) [member function]
    cls.add_method('SetRawDuration', 
                   'void', 
                   [param('uint16_t', 'duration')])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetRetry() [member function]
    cls.add_method('SetRetry', 
                   'void', 
                   [])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetSequenceNumber(uint16_t seq) [member function]
    cls.add_method('SetSequenceNumber', 
                   'void', 
                   [param('uint16_t', 'seq')])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetType(ns3::WifiMacType type) [member function]
    cls.add_method('SetType', 
                   'void', 
                   [param('ns3::WifiMacType', 'type')])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetTypeData() [member function]
    cls.add_method('SetTypeData', 
                   'void', 
                   [])
    return

def register_Ns3ZetaRandomVariable_methods(root_module, cls):
    ## random-variable-stream.h (module 'core'): static ns3::TypeId ns3::ZetaRandomVariable::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## random-variable-stream.h (module 'core'): ns3::ZetaRandomVariable::ZetaRandomVariable() [constructor]
    cls.add_constructor([])
    ## random-variable-stream.h (module 'core'): double ns3::ZetaRandomVariable::GetAlpha() const [member function]
    cls.add_method('GetAlpha', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::ZetaRandomVariable::GetValue(double alpha) [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [param('double', 'alpha')])
    ## random-variable-stream.h (module 'core'): uint32_t ns3::ZetaRandomVariable::GetInteger(uint32_t alpha) [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [param('uint32_t', 'alpha')])
    ## random-variable-stream.h (module 'core'): double ns3::ZetaRandomVariable::GetValue() [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [], 
                   is_virtual=True)
    ## random-variable-stream.h (module 'core'): uint32_t ns3::ZetaRandomVariable::GetInteger() [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [], 
                   is_virtual=True)
    return

def register_Ns3ZipfRandomVariable_methods(root_module, cls):
    ## random-variable-stream.h (module 'core'): static ns3::TypeId ns3::ZipfRandomVariable::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## random-variable-stream.h (module 'core'): ns3::ZipfRandomVariable::ZipfRandomVariable() [constructor]
    cls.add_constructor([])
    ## random-variable-stream.h (module 'core'): uint32_t ns3::ZipfRandomVariable::GetN() const [member function]
    cls.add_method('GetN', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::ZipfRandomVariable::GetAlpha() const [member function]
    cls.add_method('GetAlpha', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::ZipfRandomVariable::GetValue(uint32_t n, double alpha) [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [param('uint32_t', 'n'), param('double', 'alpha')])
    ## random-variable-stream.h (module 'core'): uint32_t ns3::ZipfRandomVariable::GetInteger(uint32_t n, uint32_t alpha) [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [param('uint32_t', 'n'), param('uint32_t', 'alpha')])
    ## random-variable-stream.h (module 'core'): double ns3::ZipfRandomVariable::GetValue() [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [], 
                   is_virtual=True)
    ## random-variable-stream.h (module 'core'): uint32_t ns3::ZipfRandomVariable::GetInteger() [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [], 
                   is_virtual=True)
    return

def register_Ns3ArpCache_methods(root_module, cls):
    ## arp-cache.h (module 'internet'): ns3::ArpCache::ArpCache() [constructor]
    cls.add_constructor([])
    ## arp-cache.h (module 'internet'): ns3::ArpCache::Entry * ns3::ArpCache::Add(ns3::Ipv4Address to) [member function]
    cls.add_method('Add', 
                   'ns3::ArpCache::Entry *', 
                   [param('ns3::Ipv4Address', 'to')])
    ## arp-cache.h (module 'internet'): void ns3::ArpCache::Flush() [member function]
    cls.add_method('Flush', 
                   'void', 
                   [])
    ## arp-cache.h (module 'internet'): ns3::Time ns3::ArpCache::GetAliveTimeout() const [member function]
    cls.add_method('GetAliveTimeout', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## arp-cache.h (module 'internet'): ns3::Time ns3::ArpCache::GetDeadTimeout() const [member function]
    cls.add_method('GetDeadTimeout', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## arp-cache.h (module 'internet'): ns3::Ptr<ns3::NetDevice> ns3::ArpCache::GetDevice() const [member function]
    cls.add_method('GetDevice', 
                   'ns3::Ptr< ns3::NetDevice >', 
                   [], 
                   is_const=True)
    ## arp-cache.h (module 'internet'): ns3::Ptr<ns3::Ipv4Interface> ns3::ArpCache::GetInterface() const [member function]
    cls.add_method('GetInterface', 
                   'ns3::Ptr< ns3::Ipv4Interface >', 
                   [], 
                   is_const=True)
    ## arp-cache.h (module 'internet'): static ns3::TypeId ns3::ArpCache::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## arp-cache.h (module 'internet'): ns3::Time ns3::ArpCache::GetWaitReplyTimeout() const [member function]
    cls.add_method('GetWaitReplyTimeout', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## arp-cache.h (module 'internet'): ns3::ArpCache::Entry * ns3::ArpCache::Lookup(ns3::Ipv4Address destination) [member function]
    cls.add_method('Lookup', 
                   'ns3::ArpCache::Entry *', 
                   [param('ns3::Ipv4Address', 'destination')])
    ## arp-cache.h (module 'internet'): void ns3::ArpCache::SetAliveTimeout(ns3::Time aliveTimeout) [member function]
    cls.add_method('SetAliveTimeout', 
                   'void', 
                   [param('ns3::Time', 'aliveTimeout')])
    ## arp-cache.h (module 'internet'): void ns3::ArpCache::SetArpRequestCallback(ns3::Callback<void, ns3::Ptr<ns3::ArpCache const>, ns3::Ipv4Address, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> arpRequestCallback) [member function]
    cls.add_method('SetArpRequestCallback', 
                   'void', 
                   [param('ns3::Callback< void, ns3::Ptr< ns3::ArpCache const >, ns3::Ipv4Address, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'arpRequestCallback')])
    ## arp-cache.h (module 'internet'): void ns3::ArpCache::SetDeadTimeout(ns3::Time deadTimeout) [member function]
    cls.add_method('SetDeadTimeout', 
                   'void', 
                   [param('ns3::Time', 'deadTimeout')])
    ## arp-cache.h (module 'internet'): void ns3::ArpCache::SetDevice(ns3::Ptr<ns3::NetDevice> device, ns3::Ptr<ns3::Ipv4Interface> interface) [member function]
    cls.add_method('SetDevice', 
                   'void', 
                   [param('ns3::Ptr< ns3::NetDevice >', 'device'), param('ns3::Ptr< ns3::Ipv4Interface >', 'interface')])
    ## arp-cache.h (module 'internet'): void ns3::ArpCache::SetWaitReplyTimeout(ns3::Time waitReplyTimeout) [member function]
    cls.add_method('SetWaitReplyTimeout', 
                   'void', 
                   [param('ns3::Time', 'waitReplyTimeout')])
    ## arp-cache.h (module 'internet'): void ns3::ArpCache::StartWaitReplyTimer() [member function]
    cls.add_method('StartWaitReplyTimer', 
                   'void', 
                   [])
    ## arp-cache.h (module 'internet'): void ns3::ArpCache::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='private', is_virtual=True)
    return

def register_Ns3ArpCacheEntry_methods(root_module, cls):
    ## arp-cache.h (module 'internet'): ns3::ArpCache::Entry::Entry(ns3::ArpCache::Entry const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::ArpCache::Entry const &', 'arg0')])
    ## arp-cache.h (module 'internet'): ns3::ArpCache::Entry::Entry(ns3::ArpCache * arp) [constructor]
    cls.add_constructor([param('ns3::ArpCache *', 'arp')])
    ## arp-cache.h (module 'internet'): void ns3::ArpCache::Entry::ClearRetries() [member function]
    cls.add_method('ClearRetries', 
                   'void', 
                   [])
    ## arp-cache.h (module 'internet'): ns3::Ptr<ns3::Packet> ns3::ArpCache::Entry::DequeuePending() [member function]
    cls.add_method('DequeuePending', 
                   'ns3::Ptr< ns3::Packet >', 
                   [])
    ## arp-cache.h (module 'internet'): ns3::Ipv4Address ns3::ArpCache::Entry::GetIpv4Address() const [member function]
    cls.add_method('GetIpv4Address', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## arp-cache.h (module 'internet'): ns3::Address ns3::ArpCache::Entry::GetMacAddress() const [member function]
    cls.add_method('GetMacAddress', 
                   'ns3::Address', 
                   [], 
                   is_const=True)
    ## arp-cache.h (module 'internet'): uint32_t ns3::ArpCache::Entry::GetRetries() const [member function]
    cls.add_method('GetRetries', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## arp-cache.h (module 'internet'): void ns3::ArpCache::Entry::IncrementRetries() [member function]
    cls.add_method('IncrementRetries', 
                   'void', 
                   [])
    ## arp-cache.h (module 'internet'): bool ns3::ArpCache::Entry::IsAlive() [member function]
    cls.add_method('IsAlive', 
                   'bool', 
                   [])
    ## arp-cache.h (module 'internet'): bool ns3::ArpCache::Entry::IsDead() [member function]
    cls.add_method('IsDead', 
                   'bool', 
                   [])
    ## arp-cache.h (module 'internet'): bool ns3::ArpCache::Entry::IsExpired() const [member function]
    cls.add_method('IsExpired', 
                   'bool', 
                   [], 
                   is_const=True)
    ## arp-cache.h (module 'internet'): bool ns3::ArpCache::Entry::IsWaitReply() [member function]
    cls.add_method('IsWaitReply', 
                   'bool', 
                   [])
    ## arp-cache.h (module 'internet'): void ns3::ArpCache::Entry::MarkAlive(ns3::Address macAddress) [member function]
    cls.add_method('MarkAlive', 
                   'void', 
                   [param('ns3::Address', 'macAddress')])
    ## arp-cache.h (module 'internet'): void ns3::ArpCache::Entry::MarkDead() [member function]
    cls.add_method('MarkDead', 
                   'void', 
                   [])
    ## arp-cache.h (module 'internet'): void ns3::ArpCache::Entry::MarkWaitReply(ns3::Ptr<ns3::Packet> waiting) [member function]
    cls.add_method('MarkWaitReply', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet >', 'waiting')])
    ## arp-cache.h (module 'internet'): void ns3::ArpCache::Entry::SetIpv4Address(ns3::Ipv4Address destination) [member function]
    cls.add_method('SetIpv4Address', 
                   'void', 
                   [param('ns3::Ipv4Address', 'destination')])
    ## arp-cache.h (module 'internet'): bool ns3::ArpCache::Entry::UpdateWaitReply(ns3::Ptr<ns3::Packet> waiting) [member function]
    cls.add_method('UpdateWaitReply', 
                   'bool', 
                   [param('ns3::Ptr< ns3::Packet >', 'waiting')])
    return

def register_Ns3AttributeAccessor_methods(root_module, cls):
    ## attribute.h (module 'core'): ns3::AttributeAccessor::AttributeAccessor(ns3::AttributeAccessor const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::AttributeAccessor const &', 'arg0')])
    ## attribute.h (module 'core'): ns3::AttributeAccessor::AttributeAccessor() [constructor]
    cls.add_constructor([])
    ## attribute.h (module 'core'): bool ns3::AttributeAccessor::Get(ns3::ObjectBase const * object, ns3::AttributeValue & attribute) const [member function]
    cls.add_method('Get', 
                   'bool', 
                   [param('ns3::ObjectBase const *', 'object'), param('ns3::AttributeValue &', 'attribute')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## attribute.h (module 'core'): bool ns3::AttributeAccessor::HasGetter() const [member function]
    cls.add_method('HasGetter', 
                   'bool', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## attribute.h (module 'core'): bool ns3::AttributeAccessor::HasSetter() const [member function]
    cls.add_method('HasSetter', 
                   'bool', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## attribute.h (module 'core'): bool ns3::AttributeAccessor::Set(ns3::ObjectBase * object, ns3::AttributeValue const & value) const [member function]
    cls.add_method('Set', 
                   'bool', 
                   [param('ns3::ObjectBase *', 'object', transfer_ownership=False), param('ns3::AttributeValue const &', 'value')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    return

def register_Ns3AttributeChecker_methods(root_module, cls):
    ## attribute.h (module 'core'): ns3::AttributeChecker::AttributeChecker(ns3::AttributeChecker const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::AttributeChecker const &', 'arg0')])
    ## attribute.h (module 'core'): ns3::AttributeChecker::AttributeChecker() [constructor]
    cls.add_constructor([])
    ## attribute.h (module 'core'): bool ns3::AttributeChecker::Check(ns3::AttributeValue const & value) const [member function]
    cls.add_method('Check', 
                   'bool', 
                   [param('ns3::AttributeValue const &', 'value')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## attribute.h (module 'core'): bool ns3::AttributeChecker::Copy(ns3::AttributeValue const & source, ns3::AttributeValue & destination) const [member function]
    cls.add_method('Copy', 
                   'bool', 
                   [param('ns3::AttributeValue const &', 'source'), param('ns3::AttributeValue &', 'destination')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## attribute.h (module 'core'): ns3::Ptr<ns3::AttributeValue> ns3::AttributeChecker::Create() const [member function]
    cls.add_method('Create', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## attribute.h (module 'core'): ns3::Ptr<ns3::AttributeValue> ns3::AttributeChecker::CreateValidValue(ns3::AttributeValue const & value) const [member function]
    cls.add_method('CreateValidValue', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [param('ns3::AttributeValue const &', 'value')], 
                   is_const=True)
    ## attribute.h (module 'core'): std::string ns3::AttributeChecker::GetUnderlyingTypeInformation() const [member function]
    cls.add_method('GetUnderlyingTypeInformation', 
                   'std::string', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## attribute.h (module 'core'): std::string ns3::AttributeChecker::GetValueTypeName() const [member function]
    cls.add_method('GetValueTypeName', 
                   'std::string', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## attribute.h (module 'core'): bool ns3::AttributeChecker::HasUnderlyingTypeInformation() const [member function]
    cls.add_method('HasUnderlyingTypeInformation', 
                   'bool', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    return

def register_Ns3AttributeValue_methods(root_module, cls):
    ## attribute.h (module 'core'): ns3::AttributeValue::AttributeValue(ns3::AttributeValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::AttributeValue const &', 'arg0')])
    ## attribute.h (module 'core'): ns3::AttributeValue::AttributeValue() [constructor]
    cls.add_constructor([])
    ## attribute.h (module 'core'): ns3::Ptr<ns3::AttributeValue> ns3::AttributeValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## attribute.h (module 'core'): bool ns3::AttributeValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_pure_virtual=True, is_virtual=True)
    ## attribute.h (module 'core'): std::string ns3::AttributeValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    return

def register_Ns3CallbackChecker_methods(root_module, cls):
    ## callback.h (module 'core'): ns3::CallbackChecker::CallbackChecker() [constructor]
    cls.add_constructor([])
    ## callback.h (module 'core'): ns3::CallbackChecker::CallbackChecker(ns3::CallbackChecker const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::CallbackChecker const &', 'arg0')])
    return

def register_Ns3CallbackImplBase_methods(root_module, cls):
    ## callback.h (module 'core'): ns3::CallbackImplBase::CallbackImplBase() [constructor]
    cls.add_constructor([])
    ## callback.h (module 'core'): ns3::CallbackImplBase::CallbackImplBase(ns3::CallbackImplBase const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::CallbackImplBase const &', 'arg0')])
    ## callback.h (module 'core'): bool ns3::CallbackImplBase::IsEqual(ns3::Ptr<ns3::CallbackImplBase const> other) const [member function]
    cls.add_method('IsEqual', 
                   'bool', 
                   [param('ns3::Ptr< ns3::CallbackImplBase const >', 'other')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    return

def register_Ns3CallbackValue_methods(root_module, cls):
    ## callback.h (module 'core'): ns3::CallbackValue::CallbackValue(ns3::CallbackValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::CallbackValue const &', 'arg0')])
    ## callback.h (module 'core'): ns3::CallbackValue::CallbackValue() [constructor]
    cls.add_constructor([])
    ## callback.h (module 'core'): ns3::CallbackValue::CallbackValue(ns3::CallbackBase const & base) [constructor]
    cls.add_constructor([param('ns3::CallbackBase const &', 'base')])
    ## callback.h (module 'core'): ns3::Ptr<ns3::AttributeValue> ns3::CallbackValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## callback.h (module 'core'): bool ns3::CallbackValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## callback.h (module 'core'): std::string ns3::CallbackValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## callback.h (module 'core'): void ns3::CallbackValue::Set(ns3::CallbackBase base) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('ns3::CallbackBase', 'base')])
    return

def register_Ns3ConstantRandomVariable_methods(root_module, cls):
    ## random-variable-stream.h (module 'core'): static ns3::TypeId ns3::ConstantRandomVariable::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## random-variable-stream.h (module 'core'): ns3::ConstantRandomVariable::ConstantRandomVariable() [constructor]
    cls.add_constructor([])
    ## random-variable-stream.h (module 'core'): double ns3::ConstantRandomVariable::GetConstant() const [member function]
    cls.add_method('GetConstant', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::ConstantRandomVariable::GetValue(double constant) [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [param('double', 'constant')])
    ## random-variable-stream.h (module 'core'): uint32_t ns3::ConstantRandomVariable::GetInteger(uint32_t constant) [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [param('uint32_t', 'constant')])
    ## random-variable-stream.h (module 'core'): double ns3::ConstantRandomVariable::GetValue() [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [], 
                   is_virtual=True)
    ## random-variable-stream.h (module 'core'): uint32_t ns3::ConstantRandomVariable::GetInteger() [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [], 
                   is_virtual=True)
    return

def register_Ns3DeterministicRandomVariable_methods(root_module, cls):
    ## random-variable-stream.h (module 'core'): static ns3::TypeId ns3::DeterministicRandomVariable::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## random-variable-stream.h (module 'core'): ns3::DeterministicRandomVariable::DeterministicRandomVariable() [constructor]
    cls.add_constructor([])
    ## random-variable-stream.h (module 'core'): void ns3::DeterministicRandomVariable::SetValueArray(double * values, uint64_t length) [member function]
    cls.add_method('SetValueArray', 
                   'void', 
                   [param('double *', 'values'), param('uint64_t', 'length')])
    ## random-variable-stream.h (module 'core'): double ns3::DeterministicRandomVariable::GetValue() [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [], 
                   is_virtual=True)
    ## random-variable-stream.h (module 'core'): uint32_t ns3::DeterministicRandomVariable::GetInteger() [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [], 
                   is_virtual=True)
    return

def register_Ns3EmpiricalRandomVariable_methods(root_module, cls):
    ## random-variable-stream.h (module 'core'): ns3::EmpiricalRandomVariable::EmpiricalRandomVariable() [constructor]
    cls.add_constructor([])
    ## random-variable-stream.h (module 'core'): void ns3::EmpiricalRandomVariable::CDF(double v, double c) [member function]
    cls.add_method('CDF', 
                   'void', 
                   [param('double', 'v'), param('double', 'c')])
    ## random-variable-stream.h (module 'core'): uint32_t ns3::EmpiricalRandomVariable::GetInteger() [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [], 
                   is_virtual=True)
    ## random-variable-stream.h (module 'core'): static ns3::TypeId ns3::EmpiricalRandomVariable::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## random-variable-stream.h (module 'core'): double ns3::EmpiricalRandomVariable::GetValue() [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [], 
                   is_virtual=True)
    ## random-variable-stream.h (module 'core'): double ns3::EmpiricalRandomVariable::Interpolate(double arg0, double arg1, double arg2, double arg3, double arg4) [member function]
    cls.add_method('Interpolate', 
                   'double', 
                   [param('double', 'arg0'), param('double', 'arg1'), param('double', 'arg2'), param('double', 'arg3'), param('double', 'arg4')], 
                   visibility='private', is_virtual=True)
    ## random-variable-stream.h (module 'core'): void ns3::EmpiricalRandomVariable::Validate() [member function]
    cls.add_method('Validate', 
                   'void', 
                   [], 
                   visibility='private', is_virtual=True)
    return

def register_Ns3EmptyAttributeValue_methods(root_module, cls):
    ## attribute.h (module 'core'): ns3::EmptyAttributeValue::EmptyAttributeValue(ns3::EmptyAttributeValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::EmptyAttributeValue const &', 'arg0')])
    ## attribute.h (module 'core'): ns3::EmptyAttributeValue::EmptyAttributeValue() [constructor]
    cls.add_constructor([])
    ## attribute.h (module 'core'): ns3::Ptr<ns3::AttributeValue> ns3::EmptyAttributeValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, visibility='private', is_virtual=True)
    ## attribute.h (module 'core'): bool ns3::EmptyAttributeValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   visibility='private', is_virtual=True)
    ## attribute.h (module 'core'): std::string ns3::EmptyAttributeValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, visibility='private', is_virtual=True)
    return

def register_Ns3EnumChecker_methods(root_module, cls):
    ## enum.h (module 'core'): ns3::EnumChecker::EnumChecker(ns3::EnumChecker const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::EnumChecker const &', 'arg0')])
    ## enum.h (module 'core'): ns3::EnumChecker::EnumChecker() [constructor]
    cls.add_constructor([])
    ## enum.h (module 'core'): void ns3::EnumChecker::Add(int v, std::string name) [member function]
    cls.add_method('Add', 
                   'void', 
                   [param('int', 'v'), param('std::string', 'name')])
    ## enum.h (module 'core'): void ns3::EnumChecker::AddDefault(int v, std::string name) [member function]
    cls.add_method('AddDefault', 
                   'void', 
                   [param('int', 'v'), param('std::string', 'name')])
    ## enum.h (module 'core'): bool ns3::EnumChecker::Check(ns3::AttributeValue const & value) const [member function]
    cls.add_method('Check', 
                   'bool', 
                   [param('ns3::AttributeValue const &', 'value')], 
                   is_const=True, is_virtual=True)
    ## enum.h (module 'core'): bool ns3::EnumChecker::Copy(ns3::AttributeValue const & src, ns3::AttributeValue & dst) const [member function]
    cls.add_method('Copy', 
                   'bool', 
                   [param('ns3::AttributeValue const &', 'src'), param('ns3::AttributeValue &', 'dst')], 
                   is_const=True, is_virtual=True)
    ## enum.h (module 'core'): ns3::Ptr<ns3::AttributeValue> ns3::EnumChecker::Create() const [member function]
    cls.add_method('Create', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## enum.h (module 'core'): std::string ns3::EnumChecker::GetUnderlyingTypeInformation() const [member function]
    cls.add_method('GetUnderlyingTypeInformation', 
                   'std::string', 
                   [], 
                   is_const=True, is_virtual=True)
    ## enum.h (module 'core'): std::string ns3::EnumChecker::GetValueTypeName() const [member function]
    cls.add_method('GetValueTypeName', 
                   'std::string', 
                   [], 
                   is_const=True, is_virtual=True)
    ## enum.h (module 'core'): bool ns3::EnumChecker::HasUnderlyingTypeInformation() const [member function]
    cls.add_method('HasUnderlyingTypeInformation', 
                   'bool', 
                   [], 
                   is_const=True, is_virtual=True)
    return

def register_Ns3EnumValue_methods(root_module, cls):
    ## enum.h (module 'core'): ns3::EnumValue::EnumValue(ns3::EnumValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::EnumValue const &', 'arg0')])
    ## enum.h (module 'core'): ns3::EnumValue::EnumValue() [constructor]
    cls.add_constructor([])
    ## enum.h (module 'core'): ns3::EnumValue::EnumValue(int v) [constructor]
    cls.add_constructor([param('int', 'v')])
    ## enum.h (module 'core'): ns3::Ptr<ns3::AttributeValue> ns3::EnumValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## enum.h (module 'core'): bool ns3::EnumValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## enum.h (module 'core'): int ns3::EnumValue::Get() const [member function]
    cls.add_method('Get', 
                   'int', 
                   [], 
                   is_const=True)
    ## enum.h (module 'core'): std::string ns3::EnumValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## enum.h (module 'core'): void ns3::EnumValue::Set(int v) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('int', 'v')])
    return

def register_Ns3ErlangRandomVariable_methods(root_module, cls):
    ## random-variable-stream.h (module 'core'): static ns3::TypeId ns3::ErlangRandomVariable::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## random-variable-stream.h (module 'core'): ns3::ErlangRandomVariable::ErlangRandomVariable() [constructor]
    cls.add_constructor([])
    ## random-variable-stream.h (module 'core'): uint32_t ns3::ErlangRandomVariable::GetK() const [member function]
    cls.add_method('GetK', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::ErlangRandomVariable::GetLambda() const [member function]
    cls.add_method('GetLambda', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::ErlangRandomVariable::GetValue(uint32_t k, double lambda) [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [param('uint32_t', 'k'), param('double', 'lambda')])
    ## random-variable-stream.h (module 'core'): uint32_t ns3::ErlangRandomVariable::GetInteger(uint32_t k, uint32_t lambda) [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [param('uint32_t', 'k'), param('uint32_t', 'lambda')])
    ## random-variable-stream.h (module 'core'): double ns3::ErlangRandomVariable::GetValue() [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [], 
                   is_virtual=True)
    ## random-variable-stream.h (module 'core'): uint32_t ns3::ErlangRandomVariable::GetInteger() [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [], 
                   is_virtual=True)
    return

def register_Ns3EventImpl_methods(root_module, cls):
    ## event-impl.h (module 'core'): ns3::EventImpl::EventImpl(ns3::EventImpl const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::EventImpl const &', 'arg0')])
    ## event-impl.h (module 'core'): ns3::EventImpl::EventImpl() [constructor]
    cls.add_constructor([])
    ## event-impl.h (module 'core'): void ns3::EventImpl::Cancel() [member function]
    cls.add_method('Cancel', 
                   'void', 
                   [])
    ## event-impl.h (module 'core'): void ns3::EventImpl::Invoke() [member function]
    cls.add_method('Invoke', 
                   'void', 
                   [])
    ## event-impl.h (module 'core'): bool ns3::EventImpl::IsCancelled() [member function]
    cls.add_method('IsCancelled', 
                   'bool', 
                   [])
    ## event-impl.h (module 'core'): void ns3::EventImpl::Notify() [member function]
    cls.add_method('Notify', 
                   'void', 
                   [], 
                   is_pure_virtual=True, visibility='protected', is_virtual=True)
    return

def register_Ns3ExponentialRandomVariable_methods(root_module, cls):
    ## random-variable-stream.h (module 'core'): static ns3::TypeId ns3::ExponentialRandomVariable::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## random-variable-stream.h (module 'core'): ns3::ExponentialRandomVariable::ExponentialRandomVariable() [constructor]
    cls.add_constructor([])
    ## random-variable-stream.h (module 'core'): double ns3::ExponentialRandomVariable::GetMean() const [member function]
    cls.add_method('GetMean', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::ExponentialRandomVariable::GetBound() const [member function]
    cls.add_method('GetBound', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::ExponentialRandomVariable::GetValue(double mean, double bound) [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [param('double', 'mean'), param('double', 'bound')])
    ## random-variable-stream.h (module 'core'): uint32_t ns3::ExponentialRandomVariable::GetInteger(uint32_t mean, uint32_t bound) [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [param('uint32_t', 'mean'), param('uint32_t', 'bound')])
    ## random-variable-stream.h (module 'core'): double ns3::ExponentialRandomVariable::GetValue() [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [], 
                   is_virtual=True)
    ## random-variable-stream.h (module 'core'): uint32_t ns3::ExponentialRandomVariable::GetInteger() [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [], 
                   is_virtual=True)
    return

def register_Ns3GammaRandomVariable_methods(root_module, cls):
    ## random-variable-stream.h (module 'core'): static ns3::TypeId ns3::GammaRandomVariable::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## random-variable-stream.h (module 'core'): ns3::GammaRandomVariable::GammaRandomVariable() [constructor]
    cls.add_constructor([])
    ## random-variable-stream.h (module 'core'): double ns3::GammaRandomVariable::GetAlpha() const [member function]
    cls.add_method('GetAlpha', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::GammaRandomVariable::GetBeta() const [member function]
    cls.add_method('GetBeta', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::GammaRandomVariable::GetValue(double alpha, double beta) [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [param('double', 'alpha'), param('double', 'beta')])
    ## random-variable-stream.h (module 'core'): uint32_t ns3::GammaRandomVariable::GetInteger(uint32_t alpha, uint32_t beta) [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [param('uint32_t', 'alpha'), param('uint32_t', 'beta')])
    ## random-variable-stream.h (module 'core'): double ns3::GammaRandomVariable::GetValue() [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [], 
                   is_virtual=True)
    ## random-variable-stream.h (module 'core'): uint32_t ns3::GammaRandomVariable::GetInteger() [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [], 
                   is_virtual=True)
    return

def register_Ns3IpL4Protocol_methods(root_module, cls):
    ## ip-l4-protocol.h (module 'internet'): ns3::IpL4Protocol::IpL4Protocol() [constructor]
    cls.add_constructor([])
    ## ip-l4-protocol.h (module 'internet'): ns3::IpL4Protocol::IpL4Protocol(ns3::IpL4Protocol const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::IpL4Protocol const &', 'arg0')])
    ## ip-l4-protocol.h (module 'internet'): ns3::Callback<void,ns3::Ptr<ns3::Packet>,ns3::Ipv4Address,ns3::Ipv4Address,unsigned char,ns3::Ptr<ns3::Ipv4Route>,ns3::empty,ns3::empty,ns3::empty,ns3::empty> ns3::IpL4Protocol::GetDownTarget() const [member function]
    cls.add_method('GetDownTarget', 
                   'ns3::Callback< void, ns3::Ptr< ns3::Packet >, ns3::Ipv4Address, ns3::Ipv4Address, unsigned char, ns3::Ptr< ns3::Ipv4Route >, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## ip-l4-protocol.h (module 'internet'): ns3::Callback<void,ns3::Ptr<ns3::Packet>,ns3::Ipv6Address,ns3::Ipv6Address,unsigned char,ns3::Ptr<ns3::Ipv6Route>,ns3::empty,ns3::empty,ns3::empty,ns3::empty> ns3::IpL4Protocol::GetDownTarget6() const [member function]
    cls.add_method('GetDownTarget6', 
                   'ns3::Callback< void, ns3::Ptr< ns3::Packet >, ns3::Ipv6Address, ns3::Ipv6Address, unsigned char, ns3::Ptr< ns3::Ipv6Route >, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## ip-l4-protocol.h (module 'internet'): int ns3::IpL4Protocol::GetProtocolNumber() const [member function]
    cls.add_method('GetProtocolNumber', 
                   'int', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## ip-l4-protocol.h (module 'internet'): static ns3::TypeId ns3::IpL4Protocol::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## ip-l4-protocol.h (module 'internet'): ns3::IpL4Protocol::RxStatus ns3::IpL4Protocol::Receive(ns3::Ptr<ns3::Packet> p, ns3::Ipv4Header const & header, ns3::Ptr<ns3::Ipv4Interface> incomingInterface) [member function]
    cls.add_method('Receive', 
                   'ns3::IpL4Protocol::RxStatus', 
                   [param('ns3::Ptr< ns3::Packet >', 'p'), param('ns3::Ipv4Header const &', 'header'), param('ns3::Ptr< ns3::Ipv4Interface >', 'incomingInterface')], 
                   is_pure_virtual=True, is_virtual=True)
    ## ip-l4-protocol.h (module 'internet'): ns3::IpL4Protocol::RxStatus ns3::IpL4Protocol::Receive(ns3::Ptr<ns3::Packet> p, ns3::Ipv6Address & src, ns3::Ipv6Address & dst, ns3::Ptr<ns3::Ipv6Interface> incomingInterface) [member function]
    cls.add_method('Receive', 
                   'ns3::IpL4Protocol::RxStatus', 
                   [param('ns3::Ptr< ns3::Packet >', 'p'), param('ns3::Ipv6Address &', 'src'), param('ns3::Ipv6Address &', 'dst'), param('ns3::Ptr< ns3::Ipv6Interface >', 'incomingInterface')], 
                   is_pure_virtual=True, is_virtual=True)
    ## ip-l4-protocol.h (module 'internet'): void ns3::IpL4Protocol::ReceiveIcmp(ns3::Ipv4Address icmpSource, uint8_t icmpTtl, uint8_t icmpType, uint8_t icmpCode, uint32_t icmpInfo, ns3::Ipv4Address payloadSource, ns3::Ipv4Address payloadDestination, uint8_t const * payload) [member function]
    cls.add_method('ReceiveIcmp', 
                   'void', 
                   [param('ns3::Ipv4Address', 'icmpSource'), param('uint8_t', 'icmpTtl'), param('uint8_t', 'icmpType'), param('uint8_t', 'icmpCode'), param('uint32_t', 'icmpInfo'), param('ns3::Ipv4Address', 'payloadSource'), param('ns3::Ipv4Address', 'payloadDestination'), param('uint8_t const *', 'payload')], 
                   is_virtual=True)
    ## ip-l4-protocol.h (module 'internet'): void ns3::IpL4Protocol::ReceiveIcmp(ns3::Ipv6Address icmpSource, uint8_t icmpTtl, uint8_t icmpType, uint8_t icmpCode, uint32_t icmpInfo, ns3::Ipv6Address payloadSource, ns3::Ipv6Address payloadDestination, uint8_t const * payload) [member function]
    cls.add_method('ReceiveIcmp', 
                   'void', 
                   [param('ns3::Ipv6Address', 'icmpSource'), param('uint8_t', 'icmpTtl'), param('uint8_t', 'icmpType'), param('uint8_t', 'icmpCode'), param('uint32_t', 'icmpInfo'), param('ns3::Ipv6Address', 'payloadSource'), param('ns3::Ipv6Address', 'payloadDestination'), param('uint8_t const *', 'payload')], 
                   is_virtual=True)
    ## ip-l4-protocol.h (module 'internet'): void ns3::IpL4Protocol::SetDownTarget(ns3::Callback<void,ns3::Ptr<ns3::Packet>,ns3::Ipv4Address,ns3::Ipv4Address,unsigned char,ns3::Ptr<ns3::Ipv4Route>,ns3::empty,ns3::empty,ns3::empty,ns3::empty> cb) [member function]
    cls.add_method('SetDownTarget', 
                   'void', 
                   [param('ns3::Callback< void, ns3::Ptr< ns3::Packet >, ns3::Ipv4Address, ns3::Ipv4Address, unsigned char, ns3::Ptr< ns3::Ipv4Route >, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'cb')], 
                   is_pure_virtual=True, is_virtual=True)
    ## ip-l4-protocol.h (module 'internet'): void ns3::IpL4Protocol::SetDownTarget6(ns3::Callback<void,ns3::Ptr<ns3::Packet>,ns3::Ipv6Address,ns3::Ipv6Address,unsigned char,ns3::Ptr<ns3::Ipv6Route>,ns3::empty,ns3::empty,ns3::empty,ns3::empty> cb) [member function]
    cls.add_method('SetDownTarget6', 
                   'void', 
                   [param('ns3::Callback< void, ns3::Ptr< ns3::Packet >, ns3::Ipv6Address, ns3::Ipv6Address, unsigned char, ns3::Ptr< ns3::Ipv6Route >, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'cb')], 
                   is_pure_virtual=True, is_virtual=True)
    return

def register_Ns3Ipv4_methods(root_module, cls):
    ## ipv4.h (module 'internet'): ns3::Ipv4::Ipv4(ns3::Ipv4 const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Ipv4 const &', 'arg0')])
    ## ipv4.h (module 'internet'): ns3::Ipv4::Ipv4() [constructor]
    cls.add_constructor([])
    ## ipv4.h (module 'internet'): bool ns3::Ipv4::AddAddress(uint32_t interface, ns3::Ipv4InterfaceAddress address) [member function]
    cls.add_method('AddAddress', 
                   'bool', 
                   [param('uint32_t', 'interface'), param('ns3::Ipv4InterfaceAddress', 'address')], 
                   is_pure_virtual=True, is_virtual=True)
    ## ipv4.h (module 'internet'): uint32_t ns3::Ipv4::AddInterface(ns3::Ptr<ns3::NetDevice> device) [member function]
    cls.add_method('AddInterface', 
                   'uint32_t', 
                   [param('ns3::Ptr< ns3::NetDevice >', 'device')], 
                   is_pure_virtual=True, is_virtual=True)
    ## ipv4.h (module 'internet'): ns3::Ptr<ns3::Socket> ns3::Ipv4::CreateRawSocket() [member function]
    cls.add_method('CreateRawSocket', 
                   'ns3::Ptr< ns3::Socket >', 
                   [], 
                   is_pure_virtual=True, is_virtual=True)
    ## ipv4.h (module 'internet'): void ns3::Ipv4::DeleteRawSocket(ns3::Ptr<ns3::Socket> socket) [member function]
    cls.add_method('DeleteRawSocket', 
                   'void', 
                   [param('ns3::Ptr< ns3::Socket >', 'socket')], 
                   is_pure_virtual=True, is_virtual=True)
    ## ipv4.h (module 'internet'): ns3::Ipv4InterfaceAddress ns3::Ipv4::GetAddress(uint32_t interface, uint32_t addressIndex) const [member function]
    cls.add_method('GetAddress', 
                   'ns3::Ipv4InterfaceAddress', 
                   [param('uint32_t', 'interface'), param('uint32_t', 'addressIndex')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## ipv4.h (module 'internet'): int32_t ns3::Ipv4::GetInterfaceForAddress(ns3::Ipv4Address address) const [member function]
    cls.add_method('GetInterfaceForAddress', 
                   'int32_t', 
                   [param('ns3::Ipv4Address', 'address')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## ipv4.h (module 'internet'): int32_t ns3::Ipv4::GetInterfaceForDevice(ns3::Ptr<const ns3::NetDevice> device) const [member function]
    cls.add_method('GetInterfaceForDevice', 
                   'int32_t', 
                   [param('ns3::Ptr< ns3::NetDevice const >', 'device')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## ipv4.h (module 'internet'): int32_t ns3::Ipv4::GetInterfaceForPrefix(ns3::Ipv4Address address, ns3::Ipv4Mask mask) const [member function]
    cls.add_method('GetInterfaceForPrefix', 
                   'int32_t', 
                   [param('ns3::Ipv4Address', 'address'), param('ns3::Ipv4Mask', 'mask')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## ipv4.h (module 'internet'): uint16_t ns3::Ipv4::GetMetric(uint32_t interface) const [member function]
    cls.add_method('GetMetric', 
                   'uint16_t', 
                   [param('uint32_t', 'interface')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## ipv4.h (module 'internet'): uint16_t ns3::Ipv4::GetMtu(uint32_t interface) const [member function]
    cls.add_method('GetMtu', 
                   'uint16_t', 
                   [param('uint32_t', 'interface')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## ipv4.h (module 'internet'): uint32_t ns3::Ipv4::GetNAddresses(uint32_t interface) const [member function]
    cls.add_method('GetNAddresses', 
                   'uint32_t', 
                   [param('uint32_t', 'interface')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## ipv4.h (module 'internet'): uint32_t ns3::Ipv4::GetNInterfaces() const [member function]
    cls.add_method('GetNInterfaces', 
                   'uint32_t', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## ipv4.h (module 'internet'): ns3::Ptr<ns3::NetDevice> ns3::Ipv4::GetNetDevice(uint32_t interface) [member function]
    cls.add_method('GetNetDevice', 
                   'ns3::Ptr< ns3::NetDevice >', 
                   [param('uint32_t', 'interface')], 
                   is_pure_virtual=True, is_virtual=True)
    ## ipv4.h (module 'internet'): ns3::Ptr<ns3::IpL4Protocol> ns3::Ipv4::GetProtocol(int protocolNumber) const [member function]
    cls.add_method('GetProtocol', 
                   'ns3::Ptr< ns3::IpL4Protocol >', 
                   [param('int', 'protocolNumber')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## ipv4.h (module 'internet'): ns3::Ptr<ns3::Ipv4RoutingProtocol> ns3::Ipv4::GetRoutingProtocol() const [member function]
    cls.add_method('GetRoutingProtocol', 
                   'ns3::Ptr< ns3::Ipv4RoutingProtocol >', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## ipv4.h (module 'internet'): static ns3::TypeId ns3::Ipv4::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## ipv4.h (module 'internet'): void ns3::Ipv4::Insert(ns3::Ptr<ns3::IpL4Protocol> protocol) [member function]
    cls.add_method('Insert', 
                   'void', 
                   [param('ns3::Ptr< ns3::IpL4Protocol >', 'protocol')], 
                   is_pure_virtual=True, is_virtual=True)
    ## ipv4.h (module 'internet'): bool ns3::Ipv4::IsDestinationAddress(ns3::Ipv4Address address, uint32_t iif) const [member function]
    cls.add_method('IsDestinationAddress', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'address'), param('uint32_t', 'iif')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## ipv4.h (module 'internet'): bool ns3::Ipv4::IsForwarding(uint32_t interface) const [member function]
    cls.add_method('IsForwarding', 
                   'bool', 
                   [param('uint32_t', 'interface')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## ipv4.h (module 'internet'): bool ns3::Ipv4::IsUp(uint32_t interface) const [member function]
    cls.add_method('IsUp', 
                   'bool', 
                   [param('uint32_t', 'interface')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## ipv4.h (module 'internet'): bool ns3::Ipv4::RemoveAddress(uint32_t interface, uint32_t addressIndex) [member function]
    cls.add_method('RemoveAddress', 
                   'bool', 
                   [param('uint32_t', 'interface'), param('uint32_t', 'addressIndex')], 
                   is_pure_virtual=True, is_virtual=True)
    ## ipv4.h (module 'internet'): ns3::Ipv4Address ns3::Ipv4::SelectSourceAddress(ns3::Ptr<const ns3::NetDevice> device, ns3::Ipv4Address dst, ns3::Ipv4InterfaceAddress::InterfaceAddressScope_e scope) [member function]
    cls.add_method('SelectSourceAddress', 
                   'ns3::Ipv4Address', 
                   [param('ns3::Ptr< ns3::NetDevice const >', 'device'), param('ns3::Ipv4Address', 'dst'), param('ns3::Ipv4InterfaceAddress::InterfaceAddressScope_e', 'scope')], 
                   is_pure_virtual=True, is_virtual=True)
    ## ipv4.h (module 'internet'): void ns3::Ipv4::Send(ns3::Ptr<ns3::Packet> packet, ns3::Ipv4Address source, ns3::Ipv4Address destination, uint8_t protocol, ns3::Ptr<ns3::Ipv4Route> route) [member function]
    cls.add_method('Send', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet >', 'packet'), param('ns3::Ipv4Address', 'source'), param('ns3::Ipv4Address', 'destination'), param('uint8_t', 'protocol'), param('ns3::Ptr< ns3::Ipv4Route >', 'route')], 
                   is_pure_virtual=True, is_virtual=True)
    ## ipv4.h (module 'internet'): void ns3::Ipv4::SendWithHeader(ns3::Ptr<ns3::Packet> packet, ns3::Ipv4Header ipHeader, ns3::Ptr<ns3::Ipv4Route> route) [member function]
    cls.add_method('SendWithHeader', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet >', 'packet'), param('ns3::Ipv4Header', 'ipHeader'), param('ns3::Ptr< ns3::Ipv4Route >', 'route')], 
                   is_pure_virtual=True, is_virtual=True)
    ## ipv4.h (module 'internet'): void ns3::Ipv4::SetDown(uint32_t interface) [member function]
    cls.add_method('SetDown', 
                   'void', 
                   [param('uint32_t', 'interface')], 
                   is_pure_virtual=True, is_virtual=True)
    ## ipv4.h (module 'internet'): void ns3::Ipv4::SetForwarding(uint32_t interface, bool val) [member function]
    cls.add_method('SetForwarding', 
                   'void', 
                   [param('uint32_t', 'interface'), param('bool', 'val')], 
                   is_pure_virtual=True, is_virtual=True)
    ## ipv4.h (module 'internet'): void ns3::Ipv4::SetMetric(uint32_t interface, uint16_t metric) [member function]
    cls.add_method('SetMetric', 
                   'void', 
                   [param('uint32_t', 'interface'), param('uint16_t', 'metric')], 
                   is_pure_virtual=True, is_virtual=True)
    ## ipv4.h (module 'internet'): void ns3::Ipv4::SetRoutingProtocol(ns3::Ptr<ns3::Ipv4RoutingProtocol> routingProtocol) [member function]
    cls.add_method('SetRoutingProtocol', 
                   'void', 
                   [param('ns3::Ptr< ns3::Ipv4RoutingProtocol >', 'routingProtocol')], 
                   is_pure_virtual=True, is_virtual=True)
    ## ipv4.h (module 'internet'): void ns3::Ipv4::SetUp(uint32_t interface) [member function]
    cls.add_method('SetUp', 
                   'void', 
                   [param('uint32_t', 'interface')], 
                   is_pure_virtual=True, is_virtual=True)
    ## ipv4.h (module 'internet'): ns3::Ipv4::IF_ANY [variable]
    cls.add_static_attribute('IF_ANY', 'uint32_t const', is_const=True)
    ## ipv4.h (module 'internet'): bool ns3::Ipv4::GetIpForward() const [member function]
    cls.add_method('GetIpForward', 
                   'bool', 
                   [], 
                   is_pure_virtual=True, is_const=True, visibility='private', is_virtual=True)
    ## ipv4.h (module 'internet'): bool ns3::Ipv4::GetWeakEsModel() const [member function]
    cls.add_method('GetWeakEsModel', 
                   'bool', 
                   [], 
                   is_pure_virtual=True, is_const=True, visibility='private', is_virtual=True)
    ## ipv4.h (module 'internet'): void ns3::Ipv4::SetIpForward(bool forward) [member function]
    cls.add_method('SetIpForward', 
                   'void', 
                   [param('bool', 'forward')], 
                   is_pure_virtual=True, visibility='private', is_virtual=True)
    ## ipv4.h (module 'internet'): void ns3::Ipv4::SetWeakEsModel(bool model) [member function]
    cls.add_method('SetWeakEsModel', 
                   'void', 
                   [param('bool', 'model')], 
                   is_pure_virtual=True, visibility='private', is_virtual=True)
    return

def register_Ns3Ipv4AddressChecker_methods(root_module, cls):
    ## ipv4-address.h (module 'network'): ns3::Ipv4AddressChecker::Ipv4AddressChecker() [constructor]
    cls.add_constructor([])
    ## ipv4-address.h (module 'network'): ns3::Ipv4AddressChecker::Ipv4AddressChecker(ns3::Ipv4AddressChecker const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Ipv4AddressChecker const &', 'arg0')])
    return

def register_Ns3Ipv4AddressValue_methods(root_module, cls):
    ## ipv4-address.h (module 'network'): ns3::Ipv4AddressValue::Ipv4AddressValue() [constructor]
    cls.add_constructor([])
    ## ipv4-address.h (module 'network'): ns3::Ipv4AddressValue::Ipv4AddressValue(ns3::Ipv4AddressValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Ipv4AddressValue const &', 'arg0')])
    ## ipv4-address.h (module 'network'): ns3::Ipv4AddressValue::Ipv4AddressValue(ns3::Ipv4Address const & value) [constructor]
    cls.add_constructor([param('ns3::Ipv4Address const &', 'value')])
    ## ipv4-address.h (module 'network'): ns3::Ptr<ns3::AttributeValue> ns3::Ipv4AddressValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## ipv4-address.h (module 'network'): bool ns3::Ipv4AddressValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## ipv4-address.h (module 'network'): ns3::Ipv4Address ns3::Ipv4AddressValue::Get() const [member function]
    cls.add_method('Get', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): std::string ns3::Ipv4AddressValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## ipv4-address.h (module 'network'): void ns3::Ipv4AddressValue::Set(ns3::Ipv4Address const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('ns3::Ipv4Address const &', 'value')])
    return

def register_Ns3Ipv4Interface_methods(root_module, cls):
    ## ipv4-interface.h (module 'internet'): ns3::Ipv4Interface::Ipv4Interface(ns3::Ipv4Interface const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Ipv4Interface const &', 'arg0')])
    ## ipv4-interface.h (module 'internet'): ns3::Ipv4Interface::Ipv4Interface() [constructor]
    cls.add_constructor([])
    ## ipv4-interface.h (module 'internet'): bool ns3::Ipv4Interface::AddAddress(ns3::Ipv4InterfaceAddress address) [member function]
    cls.add_method('AddAddress', 
                   'bool', 
                   [param('ns3::Ipv4InterfaceAddress', 'address')])
    ## ipv4-interface.h (module 'internet'): ns3::Ipv4InterfaceAddress ns3::Ipv4Interface::GetAddress(uint32_t index) const [member function]
    cls.add_method('GetAddress', 
                   'ns3::Ipv4InterfaceAddress', 
                   [param('uint32_t', 'index')], 
                   is_const=True)
    ## ipv4-interface.h (module 'internet'): ns3::Ptr<ns3::ArpCache> ns3::Ipv4Interface::GetArpCache() const [member function]
    cls.add_method('GetArpCache', 
                   'ns3::Ptr< ns3::ArpCache >', 
                   [], 
                   is_const=True)
    ## ipv4-interface.h (module 'internet'): ns3::Ptr<ns3::NetDevice> ns3::Ipv4Interface::GetDevice() const [member function]
    cls.add_method('GetDevice', 
                   'ns3::Ptr< ns3::NetDevice >', 
                   [], 
                   is_const=True)
    ## ipv4-interface.h (module 'internet'): uint16_t ns3::Ipv4Interface::GetMetric() const [member function]
    cls.add_method('GetMetric', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## ipv4-interface.h (module 'internet'): uint32_t ns3::Ipv4Interface::GetNAddresses() const [member function]
    cls.add_method('GetNAddresses', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## ipv4-interface.h (module 'internet'): static ns3::TypeId ns3::Ipv4Interface::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## ipv4-interface.h (module 'internet'): bool ns3::Ipv4Interface::IsDown() const [member function]
    cls.add_method('IsDown', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv4-interface.h (module 'internet'): bool ns3::Ipv4Interface::IsForwarding() const [member function]
    cls.add_method('IsForwarding', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv4-interface.h (module 'internet'): bool ns3::Ipv4Interface::IsUp() const [member function]
    cls.add_method('IsUp', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv4-interface.h (module 'internet'): ns3::Ipv4InterfaceAddress ns3::Ipv4Interface::RemoveAddress(uint32_t index) [member function]
    cls.add_method('RemoveAddress', 
                   'ns3::Ipv4InterfaceAddress', 
                   [param('uint32_t', 'index')])
    ## ipv4-interface.h (module 'internet'): void ns3::Ipv4Interface::Send(ns3::Ptr<ns3::Packet> p, ns3::Ipv4Address dest) [member function]
    cls.add_method('Send', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet >', 'p'), param('ns3::Ipv4Address', 'dest')])
    ## ipv4-interface.h (module 'internet'): void ns3::Ipv4Interface::SetArpCache(ns3::Ptr<ns3::ArpCache> arg0) [member function]
    cls.add_method('SetArpCache', 
                   'void', 
                   [param('ns3::Ptr< ns3::ArpCache >', 'arg0')])
    ## ipv4-interface.h (module 'internet'): void ns3::Ipv4Interface::SetDevice(ns3::Ptr<ns3::NetDevice> device) [member function]
    cls.add_method('SetDevice', 
                   'void', 
                   [param('ns3::Ptr< ns3::NetDevice >', 'device')])
    ## ipv4-interface.h (module 'internet'): void ns3::Ipv4Interface::SetDown() [member function]
    cls.add_method('SetDown', 
                   'void', 
                   [])
    ## ipv4-interface.h (module 'internet'): void ns3::Ipv4Interface::SetForwarding(bool val) [member function]
    cls.add_method('SetForwarding', 
                   'void', 
                   [param('bool', 'val')])
    ## ipv4-interface.h (module 'internet'): void ns3::Ipv4Interface::SetMetric(uint16_t metric) [member function]
    cls.add_method('SetMetric', 
                   'void', 
                   [param('uint16_t', 'metric')])
    ## ipv4-interface.h (module 'internet'): void ns3::Ipv4Interface::SetNode(ns3::Ptr<ns3::Node> node) [member function]
    cls.add_method('SetNode', 
                   'void', 
                   [param('ns3::Ptr< ns3::Node >', 'node')])
    ## ipv4-interface.h (module 'internet'): void ns3::Ipv4Interface::SetUp() [member function]
    cls.add_method('SetUp', 
                   'void', 
                   [])
    ## ipv4-interface.h (module 'internet'): void ns3::Ipv4Interface::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    return

def register_Ns3Ipv4L3Protocol_methods(root_module, cls):
    ## ipv4-l3-protocol.h (module 'internet'): ns3::Ipv4L3Protocol::Ipv4L3Protocol() [constructor]
    cls.add_constructor([])
    ## ipv4-l3-protocol.h (module 'internet'): bool ns3::Ipv4L3Protocol::AddAddress(uint32_t i, ns3::Ipv4InterfaceAddress address) [member function]
    cls.add_method('AddAddress', 
                   'bool', 
                   [param('uint32_t', 'i'), param('ns3::Ipv4InterfaceAddress', 'address')], 
                   is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): uint32_t ns3::Ipv4L3Protocol::AddInterface(ns3::Ptr<ns3::NetDevice> device) [member function]
    cls.add_method('AddInterface', 
                   'uint32_t', 
                   [param('ns3::Ptr< ns3::NetDevice >', 'device')], 
                   is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): ns3::Ptr<ns3::Socket> ns3::Ipv4L3Protocol::CreateRawSocket() [member function]
    cls.add_method('CreateRawSocket', 
                   'ns3::Ptr< ns3::Socket >', 
                   [], 
                   is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): void ns3::Ipv4L3Protocol::DeleteRawSocket(ns3::Ptr<ns3::Socket> socket) [member function]
    cls.add_method('DeleteRawSocket', 
                   'void', 
                   [param('ns3::Ptr< ns3::Socket >', 'socket')], 
                   is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): ns3::Ipv4InterfaceAddress ns3::Ipv4L3Protocol::GetAddress(uint32_t interfaceIndex, uint32_t addressIndex) const [member function]
    cls.add_method('GetAddress', 
                   'ns3::Ipv4InterfaceAddress', 
                   [param('uint32_t', 'interfaceIndex'), param('uint32_t', 'addressIndex')], 
                   is_const=True, is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): ns3::Ptr<ns3::Ipv4Interface> ns3::Ipv4L3Protocol::GetInterface(uint32_t i) const [member function]
    cls.add_method('GetInterface', 
                   'ns3::Ptr< ns3::Ipv4Interface >', 
                   [param('uint32_t', 'i')], 
                   is_const=True)
    ## ipv4-l3-protocol.h (module 'internet'): int32_t ns3::Ipv4L3Protocol::GetInterfaceForAddress(ns3::Ipv4Address addr) const [member function]
    cls.add_method('GetInterfaceForAddress', 
                   'int32_t', 
                   [param('ns3::Ipv4Address', 'addr')], 
                   is_const=True, is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): int32_t ns3::Ipv4L3Protocol::GetInterfaceForDevice(ns3::Ptr<const ns3::NetDevice> device) const [member function]
    cls.add_method('GetInterfaceForDevice', 
                   'int32_t', 
                   [param('ns3::Ptr< ns3::NetDevice const >', 'device')], 
                   is_const=True, is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): int32_t ns3::Ipv4L3Protocol::GetInterfaceForPrefix(ns3::Ipv4Address addr, ns3::Ipv4Mask mask) const [member function]
    cls.add_method('GetInterfaceForPrefix', 
                   'int32_t', 
                   [param('ns3::Ipv4Address', 'addr'), param('ns3::Ipv4Mask', 'mask')], 
                   is_const=True, is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): uint16_t ns3::Ipv4L3Protocol::GetMetric(uint32_t i) const [member function]
    cls.add_method('GetMetric', 
                   'uint16_t', 
                   [param('uint32_t', 'i')], 
                   is_const=True, is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): uint16_t ns3::Ipv4L3Protocol::GetMtu(uint32_t i) const [member function]
    cls.add_method('GetMtu', 
                   'uint16_t', 
                   [param('uint32_t', 'i')], 
                   is_const=True, is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): uint32_t ns3::Ipv4L3Protocol::GetNAddresses(uint32_t interface) const [member function]
    cls.add_method('GetNAddresses', 
                   'uint32_t', 
                   [param('uint32_t', 'interface')], 
                   is_const=True, is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): uint32_t ns3::Ipv4L3Protocol::GetNInterfaces() const [member function]
    cls.add_method('GetNInterfaces', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): ns3::Ptr<ns3::NetDevice> ns3::Ipv4L3Protocol::GetNetDevice(uint32_t i) [member function]
    cls.add_method('GetNetDevice', 
                   'ns3::Ptr< ns3::NetDevice >', 
                   [param('uint32_t', 'i')], 
                   is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): ns3::Ptr<ns3::IpL4Protocol> ns3::Ipv4L3Protocol::GetProtocol(int protocolNumber) const [member function]
    cls.add_method('GetProtocol', 
                   'ns3::Ptr< ns3::IpL4Protocol >', 
                   [param('int', 'protocolNumber')], 
                   is_const=True, is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): ns3::Ptr<ns3::Ipv4RoutingProtocol> ns3::Ipv4L3Protocol::GetRoutingProtocol() const [member function]
    cls.add_method('GetRoutingProtocol', 
                   'ns3::Ptr< ns3::Ipv4RoutingProtocol >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): static ns3::TypeId ns3::Ipv4L3Protocol::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## ipv4-l3-protocol.h (module 'internet'): void ns3::Ipv4L3Protocol::Insert(ns3::Ptr<ns3::IpL4Protocol> protocol) [member function]
    cls.add_method('Insert', 
                   'void', 
                   [param('ns3::Ptr< ns3::IpL4Protocol >', 'protocol')], 
                   is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): bool ns3::Ipv4L3Protocol::IsDestinationAddress(ns3::Ipv4Address address, uint32_t iif) const [member function]
    cls.add_method('IsDestinationAddress', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'address'), param('uint32_t', 'iif')], 
                   is_const=True, is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): bool ns3::Ipv4L3Protocol::IsForwarding(uint32_t i) const [member function]
    cls.add_method('IsForwarding', 
                   'bool', 
                   [param('uint32_t', 'i')], 
                   is_const=True, is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): bool ns3::Ipv4L3Protocol::IsUp(uint32_t i) const [member function]
    cls.add_method('IsUp', 
                   'bool', 
                   [param('uint32_t', 'i')], 
                   is_const=True, is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): void ns3::Ipv4L3Protocol::Receive(ns3::Ptr<ns3::NetDevice> device, ns3::Ptr<ns3::Packet const> p, uint16_t protocol, ns3::Address const & from, ns3::Address const & to, ns3::NetDevice::PacketType packetType) [member function]
    cls.add_method('Receive', 
                   'void', 
                   [param('ns3::Ptr< ns3::NetDevice >', 'device'), param('ns3::Ptr< ns3::Packet const >', 'p'), param('uint16_t', 'protocol'), param('ns3::Address const &', 'from'), param('ns3::Address const &', 'to'), param('ns3::NetDevice::PacketType', 'packetType')])
    ## ipv4-l3-protocol.h (module 'internet'): void ns3::Ipv4L3Protocol::Remove(ns3::Ptr<ns3::IpL4Protocol> protocol) [member function]
    cls.add_method('Remove', 
                   'void', 
                   [param('ns3::Ptr< ns3::IpL4Protocol >', 'protocol')])
    ## ipv4-l3-protocol.h (module 'internet'): bool ns3::Ipv4L3Protocol::RemoveAddress(uint32_t interfaceIndex, uint32_t addressIndex) [member function]
    cls.add_method('RemoveAddress', 
                   'bool', 
                   [param('uint32_t', 'interfaceIndex'), param('uint32_t', 'addressIndex')], 
                   is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): ns3::Ipv4Address ns3::Ipv4L3Protocol::SelectSourceAddress(ns3::Ptr<const ns3::NetDevice> device, ns3::Ipv4Address dst, ns3::Ipv4InterfaceAddress::InterfaceAddressScope_e scope) [member function]
    cls.add_method('SelectSourceAddress', 
                   'ns3::Ipv4Address', 
                   [param('ns3::Ptr< ns3::NetDevice const >', 'device'), param('ns3::Ipv4Address', 'dst'), param('ns3::Ipv4InterfaceAddress::InterfaceAddressScope_e', 'scope')], 
                   is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): void ns3::Ipv4L3Protocol::Send(ns3::Ptr<ns3::Packet> packet, ns3::Ipv4Address source, ns3::Ipv4Address destination, uint8_t protocol, ns3::Ptr<ns3::Ipv4Route> route) [member function]
    cls.add_method('Send', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet >', 'packet'), param('ns3::Ipv4Address', 'source'), param('ns3::Ipv4Address', 'destination'), param('uint8_t', 'protocol'), param('ns3::Ptr< ns3::Ipv4Route >', 'route')], 
                   is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): void ns3::Ipv4L3Protocol::SendWithHeader(ns3::Ptr<ns3::Packet> packet, ns3::Ipv4Header ipHeader, ns3::Ptr<ns3::Ipv4Route> route) [member function]
    cls.add_method('SendWithHeader', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet >', 'packet'), param('ns3::Ipv4Header', 'ipHeader'), param('ns3::Ptr< ns3::Ipv4Route >', 'route')], 
                   is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): void ns3::Ipv4L3Protocol::SetDefaultTtl(uint8_t ttl) [member function]
    cls.add_method('SetDefaultTtl', 
                   'void', 
                   [param('uint8_t', 'ttl')])
    ## ipv4-l3-protocol.h (module 'internet'): void ns3::Ipv4L3Protocol::SetDown(uint32_t i) [member function]
    cls.add_method('SetDown', 
                   'void', 
                   [param('uint32_t', 'i')], 
                   is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): void ns3::Ipv4L3Protocol::SetForwarding(uint32_t i, bool val) [member function]
    cls.add_method('SetForwarding', 
                   'void', 
                   [param('uint32_t', 'i'), param('bool', 'val')], 
                   is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): void ns3::Ipv4L3Protocol::SetMetric(uint32_t i, uint16_t metric) [member function]
    cls.add_method('SetMetric', 
                   'void', 
                   [param('uint32_t', 'i'), param('uint16_t', 'metric')], 
                   is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): void ns3::Ipv4L3Protocol::SetNode(ns3::Ptr<ns3::Node> node) [member function]
    cls.add_method('SetNode', 
                   'void', 
                   [param('ns3::Ptr< ns3::Node >', 'node')])
    ## ipv4-l3-protocol.h (module 'internet'): void ns3::Ipv4L3Protocol::SetRoutingProtocol(ns3::Ptr<ns3::Ipv4RoutingProtocol> routingProtocol) [member function]
    cls.add_method('SetRoutingProtocol', 
                   'void', 
                   [param('ns3::Ptr< ns3::Ipv4RoutingProtocol >', 'routingProtocol')], 
                   is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): void ns3::Ipv4L3Protocol::SetUp(uint32_t i) [member function]
    cls.add_method('SetUp', 
                   'void', 
                   [param('uint32_t', 'i')], 
                   is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): ns3::Ipv4L3Protocol::PROT_NUMBER [variable]
    cls.add_static_attribute('PROT_NUMBER', 'uint16_t const', is_const=True)
    ## ipv4-l3-protocol.h (module 'internet'): void ns3::Ipv4L3Protocol::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): void ns3::Ipv4L3Protocol::NotifyNewAggregate() [member function]
    cls.add_method('NotifyNewAggregate', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): bool ns3::Ipv4L3Protocol::GetIpForward() const [member function]
    cls.add_method('GetIpForward', 
                   'bool', 
                   [], 
                   is_const=True, visibility='private', is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): bool ns3::Ipv4L3Protocol::GetWeakEsModel() const [member function]
    cls.add_method('GetWeakEsModel', 
                   'bool', 
                   [], 
                   is_const=True, visibility='private', is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): void ns3::Ipv4L3Protocol::SetIpForward(bool forward) [member function]
    cls.add_method('SetIpForward', 
                   'void', 
                   [param('bool', 'forward')], 
                   visibility='private', is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): void ns3::Ipv4L3Protocol::SetWeakEsModel(bool model) [member function]
    cls.add_method('SetWeakEsModel', 
                   'void', 
                   [param('bool', 'model')], 
                   visibility='private', is_virtual=True)
    return

def register_Ns3Ipv4MaskChecker_methods(root_module, cls):
    ## ipv4-address.h (module 'network'): ns3::Ipv4MaskChecker::Ipv4MaskChecker() [constructor]
    cls.add_constructor([])
    ## ipv4-address.h (module 'network'): ns3::Ipv4MaskChecker::Ipv4MaskChecker(ns3::Ipv4MaskChecker const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Ipv4MaskChecker const &', 'arg0')])
    return

def register_Ns3Ipv4MaskValue_methods(root_module, cls):
    ## ipv4-address.h (module 'network'): ns3::Ipv4MaskValue::Ipv4MaskValue() [constructor]
    cls.add_constructor([])
    ## ipv4-address.h (module 'network'): ns3::Ipv4MaskValue::Ipv4MaskValue(ns3::Ipv4MaskValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Ipv4MaskValue const &', 'arg0')])
    ## ipv4-address.h (module 'network'): ns3::Ipv4MaskValue::Ipv4MaskValue(ns3::Ipv4Mask const & value) [constructor]
    cls.add_constructor([param('ns3::Ipv4Mask const &', 'value')])
    ## ipv4-address.h (module 'network'): ns3::Ptr<ns3::AttributeValue> ns3::Ipv4MaskValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## ipv4-address.h (module 'network'): bool ns3::Ipv4MaskValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## ipv4-address.h (module 'network'): ns3::Ipv4Mask ns3::Ipv4MaskValue::Get() const [member function]
    cls.add_method('Get', 
                   'ns3::Ipv4Mask', 
                   [], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): std::string ns3::Ipv4MaskValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## ipv4-address.h (module 'network'): void ns3::Ipv4MaskValue::Set(ns3::Ipv4Mask const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('ns3::Ipv4Mask const &', 'value')])
    return

def register_Ns3Ipv4MulticastRoute_methods(root_module, cls):
    ## ipv4-route.h (module 'internet'): ns3::Ipv4MulticastRoute::Ipv4MulticastRoute(ns3::Ipv4MulticastRoute const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Ipv4MulticastRoute const &', 'arg0')])
    ## ipv4-route.h (module 'internet'): ns3::Ipv4MulticastRoute::Ipv4MulticastRoute() [constructor]
    cls.add_constructor([])
    ## ipv4-route.h (module 'internet'): ns3::Ipv4Address ns3::Ipv4MulticastRoute::GetGroup() const [member function]
    cls.add_method('GetGroup', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## ipv4-route.h (module 'internet'): ns3::Ipv4Address ns3::Ipv4MulticastRoute::GetOrigin() const [member function]
    cls.add_method('GetOrigin', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## ipv4-route.h (module 'internet'): uint32_t ns3::Ipv4MulticastRoute::GetOutputTtl(uint32_t oif) [member function]
    cls.add_method('GetOutputTtl', 
                   'uint32_t', 
                   [param('uint32_t', 'oif')], 
                   deprecated=True)
    ## ipv4-route.h (module 'internet'): std::map<unsigned int, unsigned int, std::less<unsigned int>, std::allocator<std::pair<unsigned int const, unsigned int> > > ns3::Ipv4MulticastRoute::GetOutputTtlMap() const [member function]
    cls.add_method('GetOutputTtlMap', 
                   'std::map< unsigned int, unsigned int >', 
                   [], 
                   is_const=True)
    ## ipv4-route.h (module 'internet'): uint32_t ns3::Ipv4MulticastRoute::GetParent() const [member function]
    cls.add_method('GetParent', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## ipv4-route.h (module 'internet'): void ns3::Ipv4MulticastRoute::SetGroup(ns3::Ipv4Address const group) [member function]
    cls.add_method('SetGroup', 
                   'void', 
                   [param('ns3::Ipv4Address const', 'group')])
    ## ipv4-route.h (module 'internet'): void ns3::Ipv4MulticastRoute::SetOrigin(ns3::Ipv4Address const origin) [member function]
    cls.add_method('SetOrigin', 
                   'void', 
                   [param('ns3::Ipv4Address const', 'origin')])
    ## ipv4-route.h (module 'internet'): void ns3::Ipv4MulticastRoute::SetOutputTtl(uint32_t oif, uint32_t ttl) [member function]
    cls.add_method('SetOutputTtl', 
                   'void', 
                   [param('uint32_t', 'oif'), param('uint32_t', 'ttl')])
    ## ipv4-route.h (module 'internet'): void ns3::Ipv4MulticastRoute::SetParent(uint32_t iif) [member function]
    cls.add_method('SetParent', 
                   'void', 
                   [param('uint32_t', 'iif')])
    ## ipv4-route.h (module 'internet'): ns3::Ipv4MulticastRoute::MAX_INTERFACES [variable]
    cls.add_static_attribute('MAX_INTERFACES', 'uint32_t const', is_const=True)
    ## ipv4-route.h (module 'internet'): ns3::Ipv4MulticastRoute::MAX_TTL [variable]
    cls.add_static_attribute('MAX_TTL', 'uint32_t const', is_const=True)
    return

def register_Ns3Ipv4Route_methods(root_module, cls):
    cls.add_output_stream_operator()
    ## ipv4-route.h (module 'internet'): ns3::Ipv4Route::Ipv4Route(ns3::Ipv4Route const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Ipv4Route const &', 'arg0')])
    ## ipv4-route.h (module 'internet'): ns3::Ipv4Route::Ipv4Route() [constructor]
    cls.add_constructor([])
    ## ipv4-route.h (module 'internet'): ns3::Ipv4Address ns3::Ipv4Route::GetDestination() const [member function]
    cls.add_method('GetDestination', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## ipv4-route.h (module 'internet'): ns3::Ipv4Address ns3::Ipv4Route::GetGateway() const [member function]
    cls.add_method('GetGateway', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## ipv4-route.h (module 'internet'): ns3::Ptr<ns3::NetDevice> ns3::Ipv4Route::GetOutputDevice() const [member function]
    cls.add_method('GetOutputDevice', 
                   'ns3::Ptr< ns3::NetDevice >', 
                   [], 
                   is_const=True)
    ## ipv4-route.h (module 'internet'): ns3::Ipv4Address ns3::Ipv4Route::GetSource() const [member function]
    cls.add_method('GetSource', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## ipv4-route.h (module 'internet'): void ns3::Ipv4Route::SetDestination(ns3::Ipv4Address dest) [member function]
    cls.add_method('SetDestination', 
                   'void', 
                   [param('ns3::Ipv4Address', 'dest')])
    ## ipv4-route.h (module 'internet'): void ns3::Ipv4Route::SetGateway(ns3::Ipv4Address gw) [member function]
    cls.add_method('SetGateway', 
                   'void', 
                   [param('ns3::Ipv4Address', 'gw')])
    ## ipv4-route.h (module 'internet'): void ns3::Ipv4Route::SetOutputDevice(ns3::Ptr<ns3::NetDevice> outputDevice) [member function]
    cls.add_method('SetOutputDevice', 
                   'void', 
                   [param('ns3::Ptr< ns3::NetDevice >', 'outputDevice')])
    ## ipv4-route.h (module 'internet'): void ns3::Ipv4Route::SetSource(ns3::Ipv4Address src) [member function]
    cls.add_method('SetSource', 
                   'void', 
                   [param('ns3::Ipv4Address', 'src')])
    return

def register_Ns3Ipv4RoutingProtocol_methods(root_module, cls):
    ## ipv4-routing-protocol.h (module 'internet'): ns3::Ipv4RoutingProtocol::Ipv4RoutingProtocol() [constructor]
    cls.add_constructor([])
    ## ipv4-routing-protocol.h (module 'internet'): ns3::Ipv4RoutingProtocol::Ipv4RoutingProtocol(ns3::Ipv4RoutingProtocol const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Ipv4RoutingProtocol const &', 'arg0')])
    ## ipv4-routing-protocol.h (module 'internet'): static ns3::TypeId ns3::Ipv4RoutingProtocol::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## ipv4-routing-protocol.h (module 'internet'): void ns3::Ipv4RoutingProtocol::NotifyAddAddress(uint32_t interface, ns3::Ipv4InterfaceAddress address) [member function]
    cls.add_method('NotifyAddAddress', 
                   'void', 
                   [param('uint32_t', 'interface'), param('ns3::Ipv4InterfaceAddress', 'address')], 
                   is_pure_virtual=True, is_virtual=True)
    ## ipv4-routing-protocol.h (module 'internet'): void ns3::Ipv4RoutingProtocol::NotifyInterfaceDown(uint32_t interface) [member function]
    cls.add_method('NotifyInterfaceDown', 
                   'void', 
                   [param('uint32_t', 'interface')], 
                   is_pure_virtual=True, is_virtual=True)
    ## ipv4-routing-protocol.h (module 'internet'): void ns3::Ipv4RoutingProtocol::NotifyInterfaceUp(uint32_t interface) [member function]
    cls.add_method('NotifyInterfaceUp', 
                   'void', 
                   [param('uint32_t', 'interface')], 
                   is_pure_virtual=True, is_virtual=True)
    ## ipv4-routing-protocol.h (module 'internet'): void ns3::Ipv4RoutingProtocol::NotifyRemoveAddress(uint32_t interface, ns3::Ipv4InterfaceAddress address) [member function]
    cls.add_method('NotifyRemoveAddress', 
                   'void', 
                   [param('uint32_t', 'interface'), param('ns3::Ipv4InterfaceAddress', 'address')], 
                   is_pure_virtual=True, is_virtual=True)
    ## ipv4-routing-protocol.h (module 'internet'): void ns3::Ipv4RoutingProtocol::PrintRoutingTable(ns3::Ptr<ns3::OutputStreamWrapper> stream) const [member function]
    cls.add_method('PrintRoutingTable', 
                   'void', 
                   [param('ns3::Ptr< ns3::OutputStreamWrapper >', 'stream')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## ipv4-routing-protocol.h (module 'internet'): bool ns3::Ipv4RoutingProtocol::RouteInput(ns3::Ptr<ns3::Packet const> p, ns3::Ipv4Header const & header, ns3::Ptr<const ns3::NetDevice> idev, ns3::Callback<void, ns3::Ptr<ns3::Ipv4Route>, ns3::Ptr<ns3::Packet const>, ns3::Ipv4Header const&, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ucb, ns3::Callback<void,ns3::Ptr<ns3::Ipv4MulticastRoute>,ns3::Ptr<const ns3::Packet>,const ns3::Ipv4Header&,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty> mcb, ns3::Callback<void,ns3::Ptr<const ns3::Packet>,const ns3::Ipv4Header&,unsigned int,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty> lcb, ns3::Callback<void, ns3::Ptr<ns3::Packet const>, ns3::Ipv4Header const&, ns3::Socket::SocketErrno, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ecb) [member function]
    cls.add_method('RouteInput', 
                   'bool', 
                   [param('ns3::Ptr< ns3::Packet const >', 'p'), param('ns3::Ipv4Header const &', 'header'), param('ns3::Ptr< ns3::NetDevice const >', 'idev'), param('ns3::Callback< void, ns3::Ptr< ns3::Ipv4Route >, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'ucb'), param('ns3::Callback< void, ns3::Ptr< ns3::Ipv4MulticastRoute >, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'mcb'), param('ns3::Callback< void, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, unsigned int, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'lcb'), param('ns3::Callback< void, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, ns3::Socket::SocketErrno, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'ecb')], 
                   is_pure_virtual=True, is_virtual=True)
    ## ipv4-routing-protocol.h (module 'internet'): ns3::Ptr<ns3::Ipv4Route> ns3::Ipv4RoutingProtocol::RouteOutput(ns3::Ptr<ns3::Packet> p, ns3::Ipv4Header const & header, ns3::Ptr<ns3::NetDevice> oif, ns3::Socket::SocketErrno & sockerr) [member function]
    cls.add_method('RouteOutput', 
                   'ns3::Ptr< ns3::Ipv4Route >', 
                   [param('ns3::Ptr< ns3::Packet >', 'p'), param('ns3::Ipv4Header const &', 'header'), param('ns3::Ptr< ns3::NetDevice >', 'oif'), param('ns3::Socket::SocketErrno &', 'sockerr')], 
                   is_pure_virtual=True, is_virtual=True)
    ## ipv4-routing-protocol.h (module 'internet'): void ns3::Ipv4RoutingProtocol::SetIpv4(ns3::Ptr<ns3::Ipv4> ipv4) [member function]
    cls.add_method('SetIpv4', 
                   'void', 
                   [param('ns3::Ptr< ns3::Ipv4 >', 'ipv4')], 
                   is_pure_virtual=True, is_virtual=True)
    return

def register_Ns3Ipv4StaticRouting_methods(root_module, cls):
    ## ipv4-static-routing.h (module 'internet'): ns3::Ipv4StaticRouting::Ipv4StaticRouting(ns3::Ipv4StaticRouting const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Ipv4StaticRouting const &', 'arg0')])
    ## ipv4-static-routing.h (module 'internet'): ns3::Ipv4StaticRouting::Ipv4StaticRouting() [constructor]
    cls.add_constructor([])
    ## ipv4-static-routing.h (module 'internet'): void ns3::Ipv4StaticRouting::AddHostRouteTo(ns3::Ipv4Address dest, ns3::Ipv4Address nextHop, uint32_t interface, uint32_t metric=0) [member function]
    cls.add_method('AddHostRouteTo', 
                   'void', 
                   [param('ns3::Ipv4Address', 'dest'), param('ns3::Ipv4Address', 'nextHop'), param('uint32_t', 'interface'), param('uint32_t', 'metric', default_value='0')])
    ## ipv4-static-routing.h (module 'internet'): void ns3::Ipv4StaticRouting::AddHostRouteTo(ns3::Ipv4Address dest, uint32_t interface, uint32_t metric=0) [member function]
    cls.add_method('AddHostRouteTo', 
                   'void', 
                   [param('ns3::Ipv4Address', 'dest'), param('uint32_t', 'interface'), param('uint32_t', 'metric', default_value='0')])
    ## ipv4-static-routing.h (module 'internet'): void ns3::Ipv4StaticRouting::AddMulticastRoute(ns3::Ipv4Address origin, ns3::Ipv4Address group, uint32_t inputInterface, std::vector<unsigned int, std::allocator<unsigned int> > outputInterfaces) [member function]
    cls.add_method('AddMulticastRoute', 
                   'void', 
                   [param('ns3::Ipv4Address', 'origin'), param('ns3::Ipv4Address', 'group'), param('uint32_t', 'inputInterface'), param('std::vector< unsigned int >', 'outputInterfaces')])
    ## ipv4-static-routing.h (module 'internet'): void ns3::Ipv4StaticRouting::AddNetworkRouteTo(ns3::Ipv4Address network, ns3::Ipv4Mask networkMask, ns3::Ipv4Address nextHop, uint32_t interface, uint32_t metric=0) [member function]
    cls.add_method('AddNetworkRouteTo', 
                   'void', 
                   [param('ns3::Ipv4Address', 'network'), param('ns3::Ipv4Mask', 'networkMask'), param('ns3::Ipv4Address', 'nextHop'), param('uint32_t', 'interface'), param('uint32_t', 'metric', default_value='0')])
    ## ipv4-static-routing.h (module 'internet'): void ns3::Ipv4StaticRouting::AddNetworkRouteTo(ns3::Ipv4Address network, ns3::Ipv4Mask networkMask, uint32_t interface, uint32_t metric=0) [member function]
    cls.add_method('AddNetworkRouteTo', 
                   'void', 
                   [param('ns3::Ipv4Address', 'network'), param('ns3::Ipv4Mask', 'networkMask'), param('uint32_t', 'interface'), param('uint32_t', 'metric', default_value='0')])
    ## ipv4-static-routing.h (module 'internet'): ns3::Ipv4RoutingTableEntry ns3::Ipv4StaticRouting::GetDefaultRoute() [member function]
    cls.add_method('GetDefaultRoute', 
                   'ns3::Ipv4RoutingTableEntry', 
                   [])
    ## ipv4-static-routing.h (module 'internet'): uint32_t ns3::Ipv4StaticRouting::GetMetric(uint32_t index) const [member function]
    cls.add_method('GetMetric', 
                   'uint32_t', 
                   [param('uint32_t', 'index')], 
                   is_const=True)
    ## ipv4-static-routing.h (module 'internet'): ns3::Ipv4MulticastRoutingTableEntry ns3::Ipv4StaticRouting::GetMulticastRoute(uint32_t i) const [member function]
    cls.add_method('GetMulticastRoute', 
                   'ns3::Ipv4MulticastRoutingTableEntry', 
                   [param('uint32_t', 'i')], 
                   is_const=True)
    ## ipv4-static-routing.h (module 'internet'): uint32_t ns3::Ipv4StaticRouting::GetNMulticastRoutes() const [member function]
    cls.add_method('GetNMulticastRoutes', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## ipv4-static-routing.h (module 'internet'): uint32_t ns3::Ipv4StaticRouting::GetNRoutes() const [member function]
    cls.add_method('GetNRoutes', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## ipv4-static-routing.h (module 'internet'): ns3::Ipv4RoutingTableEntry ns3::Ipv4StaticRouting::GetRoute(uint32_t i) const [member function]
    cls.add_method('GetRoute', 
                   'ns3::Ipv4RoutingTableEntry', 
                   [param('uint32_t', 'i')], 
                   is_const=True)
    ## ipv4-static-routing.h (module 'internet'): static ns3::TypeId ns3::Ipv4StaticRouting::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## ipv4-static-routing.h (module 'internet'): void ns3::Ipv4StaticRouting::NotifyAddAddress(uint32_t interface, ns3::Ipv4InterfaceAddress address) [member function]
    cls.add_method('NotifyAddAddress', 
                   'void', 
                   [param('uint32_t', 'interface'), param('ns3::Ipv4InterfaceAddress', 'address')], 
                   is_virtual=True)
    ## ipv4-static-routing.h (module 'internet'): void ns3::Ipv4StaticRouting::NotifyInterfaceDown(uint32_t interface) [member function]
    cls.add_method('NotifyInterfaceDown', 
                   'void', 
                   [param('uint32_t', 'interface')], 
                   is_virtual=True)
    ## ipv4-static-routing.h (module 'internet'): void ns3::Ipv4StaticRouting::NotifyInterfaceUp(uint32_t interface) [member function]
    cls.add_method('NotifyInterfaceUp', 
                   'void', 
                   [param('uint32_t', 'interface')], 
                   is_virtual=True)
    ## ipv4-static-routing.h (module 'internet'): void ns3::Ipv4StaticRouting::NotifyRemoveAddress(uint32_t interface, ns3::Ipv4InterfaceAddress address) [member function]
    cls.add_method('NotifyRemoveAddress', 
                   'void', 
                   [param('uint32_t', 'interface'), param('ns3::Ipv4InterfaceAddress', 'address')], 
                   is_virtual=True)
    ## ipv4-static-routing.h (module 'internet'): void ns3::Ipv4StaticRouting::PrintRoutingTable(ns3::Ptr<ns3::OutputStreamWrapper> stream) const [member function]
    cls.add_method('PrintRoutingTable', 
                   'void', 
                   [param('ns3::Ptr< ns3::OutputStreamWrapper >', 'stream')], 
                   is_const=True, is_virtual=True)
    ## ipv4-static-routing.h (module 'internet'): bool ns3::Ipv4StaticRouting::RemoveMulticastRoute(ns3::Ipv4Address origin, ns3::Ipv4Address group, uint32_t inputInterface) [member function]
    cls.add_method('RemoveMulticastRoute', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'origin'), param('ns3::Ipv4Address', 'group'), param('uint32_t', 'inputInterface')])
    ## ipv4-static-routing.h (module 'internet'): void ns3::Ipv4StaticRouting::RemoveMulticastRoute(uint32_t index) [member function]
    cls.add_method('RemoveMulticastRoute', 
                   'void', 
                   [param('uint32_t', 'index')])
    ## ipv4-static-routing.h (module 'internet'): void ns3::Ipv4StaticRouting::RemoveRoute(uint32_t i) [member function]
    cls.add_method('RemoveRoute', 
                   'void', 
                   [param('uint32_t', 'i')])
    ## ipv4-static-routing.h (module 'internet'): bool ns3::Ipv4StaticRouting::RouteInput(ns3::Ptr<ns3::Packet const> p, ns3::Ipv4Header const & header, ns3::Ptr<const ns3::NetDevice> idev, ns3::Callback<void, ns3::Ptr<ns3::Ipv4Route>, ns3::Ptr<ns3::Packet const>, ns3::Ipv4Header const&, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ucb, ns3::Callback<void,ns3::Ptr<ns3::Ipv4MulticastRoute>,ns3::Ptr<const ns3::Packet>,const ns3::Ipv4Header&,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty> mcb, ns3::Callback<void,ns3::Ptr<const ns3::Packet>,const ns3::Ipv4Header&,unsigned int,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty> lcb, ns3::Callback<void, ns3::Ptr<ns3::Packet const>, ns3::Ipv4Header const&, ns3::Socket::SocketErrno, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ecb) [member function]
    cls.add_method('RouteInput', 
                   'bool', 
                   [param('ns3::Ptr< ns3::Packet const >', 'p'), param('ns3::Ipv4Header const &', 'header'), param('ns3::Ptr< ns3::NetDevice const >', 'idev'), param('ns3::Callback< void, ns3::Ptr< ns3::Ipv4Route >, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'ucb'), param('ns3::Callback< void, ns3::Ptr< ns3::Ipv4MulticastRoute >, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'mcb'), param('ns3::Callback< void, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, unsigned int, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'lcb'), param('ns3::Callback< void, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, ns3::Socket::SocketErrno, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'ecb')], 
                   is_virtual=True)
    ## ipv4-static-routing.h (module 'internet'): ns3::Ptr<ns3::Ipv4Route> ns3::Ipv4StaticRouting::RouteOutput(ns3::Ptr<ns3::Packet> p, ns3::Ipv4Header const & header, ns3::Ptr<ns3::NetDevice> oif, ns3::Socket::SocketErrno & sockerr) [member function]
    cls.add_method('RouteOutput', 
                   'ns3::Ptr< ns3::Ipv4Route >', 
                   [param('ns3::Ptr< ns3::Packet >', 'p'), param('ns3::Ipv4Header const &', 'header'), param('ns3::Ptr< ns3::NetDevice >', 'oif'), param('ns3::Socket::SocketErrno &', 'sockerr')], 
                   is_virtual=True)
    ## ipv4-static-routing.h (module 'internet'): void ns3::Ipv4StaticRouting::SetDefaultMulticastRoute(uint32_t outputInterface) [member function]
    cls.add_method('SetDefaultMulticastRoute', 
                   'void', 
                   [param('uint32_t', 'outputInterface')])
    ## ipv4-static-routing.h (module 'internet'): void ns3::Ipv4StaticRouting::SetDefaultRoute(ns3::Ipv4Address nextHop, uint32_t interface, uint32_t metric=0) [member function]
    cls.add_method('SetDefaultRoute', 
                   'void', 
                   [param('ns3::Ipv4Address', 'nextHop'), param('uint32_t', 'interface'), param('uint32_t', 'metric', default_value='0')])
    ## ipv4-static-routing.h (module 'internet'): void ns3::Ipv4StaticRouting::SetIpv4(ns3::Ptr<ns3::Ipv4> ipv4) [member function]
    cls.add_method('SetIpv4', 
                   'void', 
                   [param('ns3::Ptr< ns3::Ipv4 >', 'ipv4')], 
                   is_virtual=True)
    ## ipv4-static-routing.h (module 'internet'): void ns3::Ipv4StaticRouting::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    return

def register_Ns3Ipv6AddressChecker_methods(root_module, cls):
    ## ipv6-address.h (module 'network'): ns3::Ipv6AddressChecker::Ipv6AddressChecker() [constructor]
    cls.add_constructor([])
    ## ipv6-address.h (module 'network'): ns3::Ipv6AddressChecker::Ipv6AddressChecker(ns3::Ipv6AddressChecker const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Ipv6AddressChecker const &', 'arg0')])
    return

def register_Ns3Ipv6AddressValue_methods(root_module, cls):
    ## ipv6-address.h (module 'network'): ns3::Ipv6AddressValue::Ipv6AddressValue() [constructor]
    cls.add_constructor([])
    ## ipv6-address.h (module 'network'): ns3::Ipv6AddressValue::Ipv6AddressValue(ns3::Ipv6AddressValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Ipv6AddressValue const &', 'arg0')])
    ## ipv6-address.h (module 'network'): ns3::Ipv6AddressValue::Ipv6AddressValue(ns3::Ipv6Address const & value) [constructor]
    cls.add_constructor([param('ns3::Ipv6Address const &', 'value')])
    ## ipv6-address.h (module 'network'): ns3::Ptr<ns3::AttributeValue> ns3::Ipv6AddressValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## ipv6-address.h (module 'network'): bool ns3::Ipv6AddressValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## ipv6-address.h (module 'network'): ns3::Ipv6Address ns3::Ipv6AddressValue::Get() const [member function]
    cls.add_method('Get', 
                   'ns3::Ipv6Address', 
                   [], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): std::string ns3::Ipv6AddressValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## ipv6-address.h (module 'network'): void ns3::Ipv6AddressValue::Set(ns3::Ipv6Address const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('ns3::Ipv6Address const &', 'value')])
    return

def register_Ns3Ipv6Interface_methods(root_module, cls):
    ## ipv6-interface.h (module 'internet'): ns3::Ipv6Interface::Ipv6Interface(ns3::Ipv6Interface const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Ipv6Interface const &', 'arg0')])
    ## ipv6-interface.h (module 'internet'): ns3::Ipv6Interface::Ipv6Interface() [constructor]
    cls.add_constructor([])
    ## ipv6-interface.h (module 'internet'): bool ns3::Ipv6Interface::AddAddress(ns3::Ipv6InterfaceAddress iface) [member function]
    cls.add_method('AddAddress', 
                   'bool', 
                   [param('ns3::Ipv6InterfaceAddress', 'iface')])
    ## ipv6-interface.h (module 'internet'): ns3::Ipv6InterfaceAddress ns3::Ipv6Interface::GetAddress(uint32_t index) const [member function]
    cls.add_method('GetAddress', 
                   'ns3::Ipv6InterfaceAddress', 
                   [param('uint32_t', 'index')], 
                   is_const=True)
    ## ipv6-interface.h (module 'internet'): ns3::Ipv6InterfaceAddress ns3::Ipv6Interface::GetAddressMatchingDestination(ns3::Ipv6Address dst) [member function]
    cls.add_method('GetAddressMatchingDestination', 
                   'ns3::Ipv6InterfaceAddress', 
                   [param('ns3::Ipv6Address', 'dst')])
    ## ipv6-interface.h (module 'internet'): uint16_t ns3::Ipv6Interface::GetBaseReachableTime() const [member function]
    cls.add_method('GetBaseReachableTime', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## ipv6-interface.h (module 'internet'): uint8_t ns3::Ipv6Interface::GetCurHopLimit() const [member function]
    cls.add_method('GetCurHopLimit', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## ipv6-interface.h (module 'internet'): ns3::Ptr<ns3::NetDevice> ns3::Ipv6Interface::GetDevice() const [member function]
    cls.add_method('GetDevice', 
                   'ns3::Ptr< ns3::NetDevice >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## ipv6-interface.h (module 'internet'): ns3::Ipv6InterfaceAddress ns3::Ipv6Interface::GetLinkLocalAddress() const [member function]
    cls.add_method('GetLinkLocalAddress', 
                   'ns3::Ipv6InterfaceAddress', 
                   [], 
                   is_const=True)
    ## ipv6-interface.h (module 'internet'): uint16_t ns3::Ipv6Interface::GetMetric() const [member function]
    cls.add_method('GetMetric', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## ipv6-interface.h (module 'internet'): uint32_t ns3::Ipv6Interface::GetNAddresses() const [member function]
    cls.add_method('GetNAddresses', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## ipv6-interface.h (module 'internet'): uint16_t ns3::Ipv6Interface::GetReachableTime() const [member function]
    cls.add_method('GetReachableTime', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## ipv6-interface.h (module 'internet'): uint16_t ns3::Ipv6Interface::GetRetransTimer() const [member function]
    cls.add_method('GetRetransTimer', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## ipv6-interface.h (module 'internet'): static ns3::TypeId ns3::Ipv6Interface::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## ipv6-interface.h (module 'internet'): bool ns3::Ipv6Interface::IsDown() const [member function]
    cls.add_method('IsDown', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv6-interface.h (module 'internet'): bool ns3::Ipv6Interface::IsForwarding() const [member function]
    cls.add_method('IsForwarding', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv6-interface.h (module 'internet'): bool ns3::Ipv6Interface::IsUp() const [member function]
    cls.add_method('IsUp', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv6-interface.h (module 'internet'): ns3::Ipv6InterfaceAddress ns3::Ipv6Interface::RemoveAddress(uint32_t index) [member function]
    cls.add_method('RemoveAddress', 
                   'ns3::Ipv6InterfaceAddress', 
                   [param('uint32_t', 'index')])
    ## ipv6-interface.h (module 'internet'): void ns3::Ipv6Interface::Send(ns3::Ptr<ns3::Packet> p, ns3::Ipv6Address dest) [member function]
    cls.add_method('Send', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet >', 'p'), param('ns3::Ipv6Address', 'dest')])
    ## ipv6-interface.h (module 'internet'): void ns3::Ipv6Interface::SetBaseReachableTime(uint16_t baseReachableTime) [member function]
    cls.add_method('SetBaseReachableTime', 
                   'void', 
                   [param('uint16_t', 'baseReachableTime')])
    ## ipv6-interface.h (module 'internet'): void ns3::Ipv6Interface::SetCurHopLimit(uint8_t curHopLimit) [member function]
    cls.add_method('SetCurHopLimit', 
                   'void', 
                   [param('uint8_t', 'curHopLimit')])
    ## ipv6-interface.h (module 'internet'): void ns3::Ipv6Interface::SetDevice(ns3::Ptr<ns3::NetDevice> device) [member function]
    cls.add_method('SetDevice', 
                   'void', 
                   [param('ns3::Ptr< ns3::NetDevice >', 'device')])
    ## ipv6-interface.h (module 'internet'): void ns3::Ipv6Interface::SetDown() [member function]
    cls.add_method('SetDown', 
                   'void', 
                   [])
    ## ipv6-interface.h (module 'internet'): void ns3::Ipv6Interface::SetForwarding(bool forward) [member function]
    cls.add_method('SetForwarding', 
                   'void', 
                   [param('bool', 'forward')])
    ## ipv6-interface.h (module 'internet'): void ns3::Ipv6Interface::SetMetric(uint16_t metric) [member function]
    cls.add_method('SetMetric', 
                   'void', 
                   [param('uint16_t', 'metric')])
    ## ipv6-interface.h (module 'internet'): void ns3::Ipv6Interface::SetNode(ns3::Ptr<ns3::Node> node) [member function]
    cls.add_method('SetNode', 
                   'void', 
                   [param('ns3::Ptr< ns3::Node >', 'node')])
    ## ipv6-interface.h (module 'internet'): void ns3::Ipv6Interface::SetNsDadUid(ns3::Ipv6Address address, uint32_t uid) [member function]
    cls.add_method('SetNsDadUid', 
                   'void', 
                   [param('ns3::Ipv6Address', 'address'), param('uint32_t', 'uid')])
    ## ipv6-interface.h (module 'internet'): void ns3::Ipv6Interface::SetReachableTime(uint16_t reachableTime) [member function]
    cls.add_method('SetReachableTime', 
                   'void', 
                   [param('uint16_t', 'reachableTime')])
    ## ipv6-interface.h (module 'internet'): void ns3::Ipv6Interface::SetRetransTimer(uint16_t retransTimer) [member function]
    cls.add_method('SetRetransTimer', 
                   'void', 
                   [param('uint16_t', 'retransTimer')])
    ## ipv6-interface.h (module 'internet'): void ns3::Ipv6Interface::SetState(ns3::Ipv6Address address, ns3::Ipv6InterfaceAddress::State_e state) [member function]
    cls.add_method('SetState', 
                   'void', 
                   [param('ns3::Ipv6Address', 'address'), param('ns3::Ipv6InterfaceAddress::State_e', 'state')])
    ## ipv6-interface.h (module 'internet'): void ns3::Ipv6Interface::SetUp() [member function]
    cls.add_method('SetUp', 
                   'void', 
                   [])
    ## ipv6-interface.h (module 'internet'): void ns3::Ipv6Interface::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    return

def register_Ns3Ipv6PrefixChecker_methods(root_module, cls):
    ## ipv6-address.h (module 'network'): ns3::Ipv6PrefixChecker::Ipv6PrefixChecker() [constructor]
    cls.add_constructor([])
    ## ipv6-address.h (module 'network'): ns3::Ipv6PrefixChecker::Ipv6PrefixChecker(ns3::Ipv6PrefixChecker const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Ipv6PrefixChecker const &', 'arg0')])
    return

def register_Ns3Ipv6PrefixValue_methods(root_module, cls):
    ## ipv6-address.h (module 'network'): ns3::Ipv6PrefixValue::Ipv6PrefixValue() [constructor]
    cls.add_constructor([])
    ## ipv6-address.h (module 'network'): ns3::Ipv6PrefixValue::Ipv6PrefixValue(ns3::Ipv6PrefixValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Ipv6PrefixValue const &', 'arg0')])
    ## ipv6-address.h (module 'network'): ns3::Ipv6PrefixValue::Ipv6PrefixValue(ns3::Ipv6Prefix const & value) [constructor]
    cls.add_constructor([param('ns3::Ipv6Prefix const &', 'value')])
    ## ipv6-address.h (module 'network'): ns3::Ptr<ns3::AttributeValue> ns3::Ipv6PrefixValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## ipv6-address.h (module 'network'): bool ns3::Ipv6PrefixValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## ipv6-address.h (module 'network'): ns3::Ipv6Prefix ns3::Ipv6PrefixValue::Get() const [member function]
    cls.add_method('Get', 
                   'ns3::Ipv6Prefix', 
                   [], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): std::string ns3::Ipv6PrefixValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## ipv6-address.h (module 'network'): void ns3::Ipv6PrefixValue::Set(ns3::Ipv6Prefix const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('ns3::Ipv6Prefix const &', 'value')])
    return

def register_Ns3LogNormalRandomVariable_methods(root_module, cls):
    ## random-variable-stream.h (module 'core'): static ns3::TypeId ns3::LogNormalRandomVariable::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## random-variable-stream.h (module 'core'): ns3::LogNormalRandomVariable::LogNormalRandomVariable() [constructor]
    cls.add_constructor([])
    ## random-variable-stream.h (module 'core'): double ns3::LogNormalRandomVariable::GetMu() const [member function]
    cls.add_method('GetMu', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::LogNormalRandomVariable::GetSigma() const [member function]
    cls.add_method('GetSigma', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::LogNormalRandomVariable::GetValue(double mu, double sigma) [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [param('double', 'mu'), param('double', 'sigma')])
    ## random-variable-stream.h (module 'core'): uint32_t ns3::LogNormalRandomVariable::GetInteger(uint32_t mu, uint32_t sigma) [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [param('uint32_t', 'mu'), param('uint32_t', 'sigma')])
    ## random-variable-stream.h (module 'core'): double ns3::LogNormalRandomVariable::GetValue() [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [], 
                   is_virtual=True)
    ## random-variable-stream.h (module 'core'): uint32_t ns3::LogNormalRandomVariable::GetInteger() [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [], 
                   is_virtual=True)
    return

def register_Ns3Mac48AddressChecker_methods(root_module, cls):
    ## mac48-address.h (module 'network'): ns3::Mac48AddressChecker::Mac48AddressChecker() [constructor]
    cls.add_constructor([])
    ## mac48-address.h (module 'network'): ns3::Mac48AddressChecker::Mac48AddressChecker(ns3::Mac48AddressChecker const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Mac48AddressChecker const &', 'arg0')])
    return

def register_Ns3Mac48AddressValue_methods(root_module, cls):
    ## mac48-address.h (module 'network'): ns3::Mac48AddressValue::Mac48AddressValue() [constructor]
    cls.add_constructor([])
    ## mac48-address.h (module 'network'): ns3::Mac48AddressValue::Mac48AddressValue(ns3::Mac48AddressValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Mac48AddressValue const &', 'arg0')])
    ## mac48-address.h (module 'network'): ns3::Mac48AddressValue::Mac48AddressValue(ns3::Mac48Address const & value) [constructor]
    cls.add_constructor([param('ns3::Mac48Address const &', 'value')])
    ## mac48-address.h (module 'network'): ns3::Ptr<ns3::AttributeValue> ns3::Mac48AddressValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## mac48-address.h (module 'network'): bool ns3::Mac48AddressValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## mac48-address.h (module 'network'): ns3::Mac48Address ns3::Mac48AddressValue::Get() const [member function]
    cls.add_method('Get', 
                   'ns3::Mac48Address', 
                   [], 
                   is_const=True)
    ## mac48-address.h (module 'network'): std::string ns3::Mac48AddressValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## mac48-address.h (module 'network'): void ns3::Mac48AddressValue::Set(ns3::Mac48Address const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('ns3::Mac48Address const &', 'value')])
    return

def register_Ns3NetDevice_methods(root_module, cls):
    ## net-device.h (module 'network'): ns3::NetDevice::NetDevice() [constructor]
    cls.add_constructor([])
    ## net-device.h (module 'network'): ns3::NetDevice::NetDevice(ns3::NetDevice const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::NetDevice const &', 'arg0')])
    ## net-device.h (module 'network'): void ns3::NetDevice::AddLinkChangeCallback(ns3::Callback<void,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty> callback) [member function]
    cls.add_method('AddLinkChangeCallback', 
                   'void', 
                   [param('ns3::Callback< void, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'callback')], 
                   is_pure_virtual=True, is_virtual=True)
    ## net-device.h (module 'network'): ns3::Address ns3::NetDevice::GetAddress() const [member function]
    cls.add_method('GetAddress', 
                   'ns3::Address', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## net-device.h (module 'network'): ns3::Address ns3::NetDevice::GetBroadcast() const [member function]
    cls.add_method('GetBroadcast', 
                   'ns3::Address', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## net-device.h (module 'network'): ns3::Ptr<ns3::Channel> ns3::NetDevice::GetChannel() const [member function]
    cls.add_method('GetChannel', 
                   'ns3::Ptr< ns3::Channel >', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## net-device.h (module 'network'): uint32_t ns3::NetDevice::GetIfIndex() const [member function]
    cls.add_method('GetIfIndex', 
                   'uint32_t', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## net-device.h (module 'network'): uint16_t ns3::NetDevice::GetMtu() const [member function]
    cls.add_method('GetMtu', 
                   'uint16_t', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## net-device.h (module 'network'): ns3::Address ns3::NetDevice::GetMulticast(ns3::Ipv4Address multicastGroup) const [member function]
    cls.add_method('GetMulticast', 
                   'ns3::Address', 
                   [param('ns3::Ipv4Address', 'multicastGroup')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## net-device.h (module 'network'): ns3::Address ns3::NetDevice::GetMulticast(ns3::Ipv6Address addr) const [member function]
    cls.add_method('GetMulticast', 
                   'ns3::Address', 
                   [param('ns3::Ipv6Address', 'addr')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## net-device.h (module 'network'): ns3::Ptr<ns3::Node> ns3::NetDevice::GetNode() const [member function]
    cls.add_method('GetNode', 
                   'ns3::Ptr< ns3::Node >', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## net-device.h (module 'network'): static ns3::TypeId ns3::NetDevice::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## net-device.h (module 'network'): bool ns3::NetDevice::IsBridge() const [member function]
    cls.add_method('IsBridge', 
                   'bool', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## net-device.h (module 'network'): bool ns3::NetDevice::IsBroadcast() const [member function]
    cls.add_method('IsBroadcast', 
                   'bool', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## net-device.h (module 'network'): bool ns3::NetDevice::IsLinkUp() const [member function]
    cls.add_method('IsLinkUp', 
                   'bool', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## net-device.h (module 'network'): bool ns3::NetDevice::IsMulticast() const [member function]
    cls.add_method('IsMulticast', 
                   'bool', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## net-device.h (module 'network'): bool ns3::NetDevice::IsPointToPoint() const [member function]
    cls.add_method('IsPointToPoint', 
                   'bool', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## net-device.h (module 'network'): bool ns3::NetDevice::NeedsArp() const [member function]
    cls.add_method('NeedsArp', 
                   'bool', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## net-device.h (module 'network'): bool ns3::NetDevice::Send(ns3::Ptr<ns3::Packet> packet, ns3::Address const & dest, uint16_t protocolNumber) [member function]
    cls.add_method('Send', 
                   'bool', 
                   [param('ns3::Ptr< ns3::Packet >', 'packet'), param('ns3::Address const &', 'dest'), param('uint16_t', 'protocolNumber')], 
                   is_pure_virtual=True, is_virtual=True)
    ## net-device.h (module 'network'): bool ns3::NetDevice::SendFrom(ns3::Ptr<ns3::Packet> packet, ns3::Address const & source, ns3::Address const & dest, uint16_t protocolNumber) [member function]
    cls.add_method('SendFrom', 
                   'bool', 
                   [param('ns3::Ptr< ns3::Packet >', 'packet'), param('ns3::Address const &', 'source'), param('ns3::Address const &', 'dest'), param('uint16_t', 'protocolNumber')], 
                   is_pure_virtual=True, is_virtual=True)
    ## net-device.h (module 'network'): void ns3::NetDevice::SetAddress(ns3::Address address) [member function]
    cls.add_method('SetAddress', 
                   'void', 
                   [param('ns3::Address', 'address')], 
                   is_pure_virtual=True, is_virtual=True)
    ## net-device.h (module 'network'): void ns3::NetDevice::SetIfIndex(uint32_t const index) [member function]
    cls.add_method('SetIfIndex', 
                   'void', 
                   [param('uint32_t const', 'index')], 
                   is_pure_virtual=True, is_virtual=True)
    ## net-device.h (module 'network'): bool ns3::NetDevice::SetMtu(uint16_t const mtu) [member function]
    cls.add_method('SetMtu', 
                   'bool', 
                   [param('uint16_t const', 'mtu')], 
                   is_pure_virtual=True, is_virtual=True)
    ## net-device.h (module 'network'): void ns3::NetDevice::SetNode(ns3::Ptr<ns3::Node> node) [member function]
    cls.add_method('SetNode', 
                   'void', 
                   [param('ns3::Ptr< ns3::Node >', 'node')], 
                   is_pure_virtual=True, is_virtual=True)
    ## net-device.h (module 'network'): void ns3::NetDevice::SetPromiscReceiveCallback(ns3::Callback<bool,ns3::Ptr<ns3::NetDevice>,ns3::Ptr<const ns3::Packet>,short unsigned int,const ns3::Address&,const ns3::Address&,ns3::NetDevice::PacketType,ns3::empty,ns3::empty,ns3::empty> cb) [member function]
    cls.add_method('SetPromiscReceiveCallback', 
                   'void', 
                   [param('ns3::Callback< bool, ns3::Ptr< ns3::NetDevice >, ns3::Ptr< ns3::Packet const >, short unsigned int, ns3::Address const &, ns3::Address const &, ns3::NetDevice::PacketType, ns3::empty, ns3::empty, ns3::empty >', 'cb')], 
                   is_pure_virtual=True, is_virtual=True)
    ## net-device.h (module 'network'): void ns3::NetDevice::SetReceiveCallback(ns3::Callback<bool,ns3::Ptr<ns3::NetDevice>,ns3::Ptr<const ns3::Packet>,short unsigned int,const ns3::Address&,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty> cb) [member function]
    cls.add_method('SetReceiveCallback', 
                   'void', 
                   [param('ns3::Callback< bool, ns3::Ptr< ns3::NetDevice >, ns3::Ptr< ns3::Packet const >, short unsigned int, ns3::Address const &, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'cb')], 
                   is_pure_virtual=True, is_virtual=True)
    ## net-device.h (module 'network'): bool ns3::NetDevice::SupportsSendFrom() const [member function]
    cls.add_method('SupportsSendFrom', 
                   'bool', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    return

def register_Ns3NixVector_methods(root_module, cls):
    cls.add_output_stream_operator()
    ## nix-vector.h (module 'network'): ns3::NixVector::NixVector() [constructor]
    cls.add_constructor([])
    ## nix-vector.h (module 'network'): ns3::NixVector::NixVector(ns3::NixVector const & o) [copy constructor]
    cls.add_constructor([param('ns3::NixVector const &', 'o')])
    ## nix-vector.h (module 'network'): void ns3::NixVector::AddNeighborIndex(uint32_t newBits, uint32_t numberOfBits) [member function]
    cls.add_method('AddNeighborIndex', 
                   'void', 
                   [param('uint32_t', 'newBits'), param('uint32_t', 'numberOfBits')])
    ## nix-vector.h (module 'network'): uint32_t ns3::NixVector::BitCount(uint32_t numberOfNeighbors) const [member function]
    cls.add_method('BitCount', 
                   'uint32_t', 
                   [param('uint32_t', 'numberOfNeighbors')], 
                   is_const=True)
    ## nix-vector.h (module 'network'): ns3::Ptr<ns3::NixVector> ns3::NixVector::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::NixVector >', 
                   [], 
                   is_const=True)
    ## nix-vector.h (module 'network'): uint32_t ns3::NixVector::Deserialize(uint32_t const * buffer, uint32_t size) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('uint32_t const *', 'buffer'), param('uint32_t', 'size')])
    ## nix-vector.h (module 'network'): uint32_t ns3::NixVector::ExtractNeighborIndex(uint32_t numberOfBits) [member function]
    cls.add_method('ExtractNeighborIndex', 
                   'uint32_t', 
                   [param('uint32_t', 'numberOfBits')])
    ## nix-vector.h (module 'network'): uint32_t ns3::NixVector::GetRemainingBits() [member function]
    cls.add_method('GetRemainingBits', 
                   'uint32_t', 
                   [])
    ## nix-vector.h (module 'network'): uint32_t ns3::NixVector::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## nix-vector.h (module 'network'): uint32_t ns3::NixVector::Serialize(uint32_t * buffer, uint32_t maxSize) const [member function]
    cls.add_method('Serialize', 
                   'uint32_t', 
                   [param('uint32_t *', 'buffer'), param('uint32_t', 'maxSize')], 
                   is_const=True)
    return

def register_Ns3Node_methods(root_module, cls):
    ## node.h (module 'network'): ns3::Node::Node(ns3::Node const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Node const &', 'arg0')])
    ## node.h (module 'network'): ns3::Node::Node() [constructor]
    cls.add_constructor([])
    ## node.h (module 'network'): ns3::Node::Node(uint32_t systemId) [constructor]
    cls.add_constructor([param('uint32_t', 'systemId')])
    ## node.h (module 'network'): uint32_t ns3::Node::AddApplication(ns3::Ptr<ns3::Application> application) [member function]
    cls.add_method('AddApplication', 
                   'uint32_t', 
                   [param('ns3::Ptr< ns3::Application >', 'application')])
    ## node.h (module 'network'): uint32_t ns3::Node::AddDevice(ns3::Ptr<ns3::NetDevice> device) [member function]
    cls.add_method('AddDevice', 
                   'uint32_t', 
                   [param('ns3::Ptr< ns3::NetDevice >', 'device')])
    ## node.h (module 'network'): static bool ns3::Node::ChecksumEnabled() [member function]
    cls.add_method('ChecksumEnabled', 
                   'bool', 
                   [], 
                   is_static=True)
    ## node.h (module 'network'): ns3::Ptr<ns3::Application> ns3::Node::GetApplication(uint32_t index) const [member function]
    cls.add_method('GetApplication', 
                   'ns3::Ptr< ns3::Application >', 
                   [param('uint32_t', 'index')], 
                   is_const=True)
    ## node.h (module 'network'): ns3::Ptr<ns3::NetDevice> ns3::Node::GetDevice(uint32_t index) const [member function]
    cls.add_method('GetDevice', 
                   'ns3::Ptr< ns3::NetDevice >', 
                   [param('uint32_t', 'index')], 
                   is_const=True)
    ## node.h (module 'network'): uint32_t ns3::Node::GetId() const [member function]
    cls.add_method('GetId', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## node.h (module 'network'): uint32_t ns3::Node::GetNApplications() const [member function]
    cls.add_method('GetNApplications', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## node.h (module 'network'): uint32_t ns3::Node::GetNDevices() const [member function]
    cls.add_method('GetNDevices', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## node.h (module 'network'): uint32_t ns3::Node::GetSystemId() const [member function]
    cls.add_method('GetSystemId', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## node.h (module 'network'): static ns3::TypeId ns3::Node::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## node.h (module 'network'): void ns3::Node::RegisterDeviceAdditionListener(ns3::Callback<void,ns3::Ptr<ns3::NetDevice>,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty> listener) [member function]
    cls.add_method('RegisterDeviceAdditionListener', 
                   'void', 
                   [param('ns3::Callback< void, ns3::Ptr< ns3::NetDevice >, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'listener')])
    ## node.h (module 'network'): void ns3::Node::RegisterProtocolHandler(ns3::Callback<void, ns3::Ptr<ns3::NetDevice>, ns3::Ptr<ns3::Packet const>, unsigned short, ns3::Address const&, ns3::Address const&, ns3::NetDevice::PacketType, ns3::empty, ns3::empty, ns3::empty> handler, uint16_t protocolType, ns3::Ptr<ns3::NetDevice> device, bool promiscuous=false) [member function]
    cls.add_method('RegisterProtocolHandler', 
                   'void', 
                   [param('ns3::Callback< void, ns3::Ptr< ns3::NetDevice >, ns3::Ptr< ns3::Packet const >, unsigned short, ns3::Address const &, ns3::Address const &, ns3::NetDevice::PacketType, ns3::empty, ns3::empty, ns3::empty >', 'handler'), param('uint16_t', 'protocolType'), param('ns3::Ptr< ns3::NetDevice >', 'device'), param('bool', 'promiscuous', default_value='false')])
    ## node.h (module 'network'): void ns3::Node::UnregisterDeviceAdditionListener(ns3::Callback<void,ns3::Ptr<ns3::NetDevice>,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty> listener) [member function]
    cls.add_method('UnregisterDeviceAdditionListener', 
                   'void', 
                   [param('ns3::Callback< void, ns3::Ptr< ns3::NetDevice >, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'listener')])
    ## node.h (module 'network'): void ns3::Node::UnregisterProtocolHandler(ns3::Callback<void, ns3::Ptr<ns3::NetDevice>, ns3::Ptr<ns3::Packet const>, unsigned short, ns3::Address const&, ns3::Address const&, ns3::NetDevice::PacketType, ns3::empty, ns3::empty, ns3::empty> handler) [member function]
    cls.add_method('UnregisterProtocolHandler', 
                   'void', 
                   [param('ns3::Callback< void, ns3::Ptr< ns3::NetDevice >, ns3::Ptr< ns3::Packet const >, unsigned short, ns3::Address const &, ns3::Address const &, ns3::NetDevice::PacketType, ns3::empty, ns3::empty, ns3::empty >', 'handler')])
    ## node.h (module 'network'): void ns3::Node::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## node.h (module 'network'): void ns3::Node::DoStart() [member function]
    cls.add_method('DoStart', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    return

def register_Ns3NormalRandomVariable_methods(root_module, cls):
    ## random-variable-stream.h (module 'core'): ns3::NormalRandomVariable::INFINITE_VALUE [variable]
    cls.add_static_attribute('INFINITE_VALUE', 'double const', is_const=True)
    ## random-variable-stream.h (module 'core'): static ns3::TypeId ns3::NormalRandomVariable::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## random-variable-stream.h (module 'core'): ns3::NormalRandomVariable::NormalRandomVariable() [constructor]
    cls.add_constructor([])
    ## random-variable-stream.h (module 'core'): double ns3::NormalRandomVariable::GetMean() const [member function]
    cls.add_method('GetMean', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::NormalRandomVariable::GetVariance() const [member function]
    cls.add_method('GetVariance', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::NormalRandomVariable::GetBound() const [member function]
    cls.add_method('GetBound', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::NormalRandomVariable::GetValue(double mean, double variance, double bound=ns3::NormalRandomVariable::INFINITE_VALUE) [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [param('double', 'mean'), param('double', 'variance'), param('double', 'bound', default_value='ns3::NormalRandomVariable::INFINITE_VALUE')])
    ## random-variable-stream.h (module 'core'): uint32_t ns3::NormalRandomVariable::GetInteger(uint32_t mean, uint32_t variance, uint32_t bound) [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [param('uint32_t', 'mean'), param('uint32_t', 'variance'), param('uint32_t', 'bound')])
    ## random-variable-stream.h (module 'core'): double ns3::NormalRandomVariable::GetValue() [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [], 
                   is_virtual=True)
    ## random-variable-stream.h (module 'core'): uint32_t ns3::NormalRandomVariable::GetInteger() [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [], 
                   is_virtual=True)
    return

def register_Ns3ObjectFactoryChecker_methods(root_module, cls):
    ## object-factory.h (module 'core'): ns3::ObjectFactoryChecker::ObjectFactoryChecker() [constructor]
    cls.add_constructor([])
    ## object-factory.h (module 'core'): ns3::ObjectFactoryChecker::ObjectFactoryChecker(ns3::ObjectFactoryChecker const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::ObjectFactoryChecker const &', 'arg0')])
    return

def register_Ns3ObjectFactoryValue_methods(root_module, cls):
    ## object-factory.h (module 'core'): ns3::ObjectFactoryValue::ObjectFactoryValue() [constructor]
    cls.add_constructor([])
    ## object-factory.h (module 'core'): ns3::ObjectFactoryValue::ObjectFactoryValue(ns3::ObjectFactoryValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::ObjectFactoryValue const &', 'arg0')])
    ## object-factory.h (module 'core'): ns3::ObjectFactoryValue::ObjectFactoryValue(ns3::ObjectFactory const & value) [constructor]
    cls.add_constructor([param('ns3::ObjectFactory const &', 'value')])
    ## object-factory.h (module 'core'): ns3::Ptr<ns3::AttributeValue> ns3::ObjectFactoryValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## object-factory.h (module 'core'): bool ns3::ObjectFactoryValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## object-factory.h (module 'core'): ns3::ObjectFactory ns3::ObjectFactoryValue::Get() const [member function]
    cls.add_method('Get', 
                   'ns3::ObjectFactory', 
                   [], 
                   is_const=True)
    ## object-factory.h (module 'core'): std::string ns3::ObjectFactoryValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## object-factory.h (module 'core'): void ns3::ObjectFactoryValue::Set(ns3::ObjectFactory const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('ns3::ObjectFactory const &', 'value')])
    return

def register_Ns3OutputStreamWrapper_methods(root_module, cls):
    ## output-stream-wrapper.h (module 'network'): ns3::OutputStreamWrapper::OutputStreamWrapper(ns3::OutputStreamWrapper const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::OutputStreamWrapper const &', 'arg0')])
    ## output-stream-wrapper.h (module 'network'): ns3::OutputStreamWrapper::OutputStreamWrapper(std::string filename, std::_Ios_Openmode filemode) [constructor]
    cls.add_constructor([param('std::string', 'filename'), param('std::_Ios_Openmode', 'filemode')])
    ## output-stream-wrapper.h (module 'network'): ns3::OutputStreamWrapper::OutputStreamWrapper(std::ostream * os) [constructor]
    cls.add_constructor([param('std::ostream *', 'os')])
    ## output-stream-wrapper.h (module 'network'): std::ostream * ns3::OutputStreamWrapper::GetStream() [member function]
    cls.add_method('GetStream', 
                   'std::ostream *', 
                   [])
    return

def register_Ns3Packet_methods(root_module, cls):
    cls.add_output_stream_operator()
    ## packet.h (module 'network'): ns3::Packet::Packet() [constructor]
    cls.add_constructor([])
    ## packet.h (module 'network'): ns3::Packet::Packet(ns3::Packet const & o) [copy constructor]
    cls.add_constructor([param('ns3::Packet const &', 'o')])
    ## packet.h (module 'network'): ns3::Packet::Packet(uint32_t size) [constructor]
    cls.add_constructor([param('uint32_t', 'size')])
    ## packet.h (module 'network'): ns3::Packet::Packet(uint8_t const * buffer, uint32_t size, bool magic) [constructor]
    cls.add_constructor([param('uint8_t const *', 'buffer'), param('uint32_t', 'size'), param('bool', 'magic')])
    ## packet.h (module 'network'): ns3::Packet::Packet(uint8_t const * buffer, uint32_t size) [constructor]
    cls.add_constructor([param('uint8_t const *', 'buffer'), param('uint32_t', 'size')])
    ## packet.h (module 'network'): void ns3::Packet::AddAtEnd(ns3::Ptr<ns3::Packet const> packet) [member function]
    cls.add_method('AddAtEnd', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet const >', 'packet')])
    ## packet.h (module 'network'): void ns3::Packet::AddByteTag(ns3::Tag const & tag) const [member function]
    cls.add_method('AddByteTag', 
                   'void', 
                   [param('ns3::Tag const &', 'tag')], 
                   is_const=True)
    ## packet.h (module 'network'): void ns3::Packet::AddHeader(ns3::Header const & header) [member function]
    cls.add_method('AddHeader', 
                   'void', 
                   [param('ns3::Header const &', 'header')])
    ## packet.h (module 'network'): void ns3::Packet::AddPacketTag(ns3::Tag const & tag) const [member function]
    cls.add_method('AddPacketTag', 
                   'void', 
                   [param('ns3::Tag const &', 'tag')], 
                   is_const=True)
    ## packet.h (module 'network'): void ns3::Packet::AddPaddingAtEnd(uint32_t size) [member function]
    cls.add_method('AddPaddingAtEnd', 
                   'void', 
                   [param('uint32_t', 'size')])
    ## packet.h (module 'network'): void ns3::Packet::AddTrailer(ns3::Trailer const & trailer) [member function]
    cls.add_method('AddTrailer', 
                   'void', 
                   [param('ns3::Trailer const &', 'trailer')])
    ## packet.h (module 'network'): ns3::PacketMetadata::ItemIterator ns3::Packet::BeginItem() const [member function]
    cls.add_method('BeginItem', 
                   'ns3::PacketMetadata::ItemIterator', 
                   [], 
                   is_const=True)
    ## packet.h (module 'network'): ns3::Ptr<ns3::Packet> ns3::Packet::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::Packet >', 
                   [], 
                   is_const=True)
    ## packet.h (module 'network'): uint32_t ns3::Packet::CopyData(uint8_t * buffer, uint32_t size) const [member function]
    cls.add_method('CopyData', 
                   'uint32_t', 
                   [param('uint8_t *', 'buffer'), param('uint32_t', 'size')], 
                   is_const=True)
    ## packet.h (module 'network'): void ns3::Packet::CopyData(std::ostream * os, uint32_t size) const [member function]
    cls.add_method('CopyData', 
                   'void', 
                   [param('std::ostream *', 'os'), param('uint32_t', 'size')], 
                   is_const=True)
    ## packet.h (module 'network'): ns3::Ptr<ns3::Packet> ns3::Packet::CreateFragment(uint32_t start, uint32_t length) const [member function]
    cls.add_method('CreateFragment', 
                   'ns3::Ptr< ns3::Packet >', 
                   [param('uint32_t', 'start'), param('uint32_t', 'length')], 
                   is_const=True)
    ## packet.h (module 'network'): static void ns3::Packet::EnableChecking() [member function]
    cls.add_method('EnableChecking', 
                   'void', 
                   [], 
                   is_static=True)
    ## packet.h (module 'network'): static void ns3::Packet::EnablePrinting() [member function]
    cls.add_method('EnablePrinting', 
                   'void', 
                   [], 
                   is_static=True)
    ## packet.h (module 'network'): bool ns3::Packet::FindFirstMatchingByteTag(ns3::Tag & tag) const [member function]
    cls.add_method('FindFirstMatchingByteTag', 
                   'bool', 
                   [param('ns3::Tag &', 'tag')], 
                   is_const=True)
    ## packet.h (module 'network'): ns3::ByteTagIterator ns3::Packet::GetByteTagIterator() const [member function]
    cls.add_method('GetByteTagIterator', 
                   'ns3::ByteTagIterator', 
                   [], 
                   is_const=True)
    ## packet.h (module 'network'): ns3::Ptr<ns3::NixVector> ns3::Packet::GetNixVector() const [member function]
    cls.add_method('GetNixVector', 
                   'ns3::Ptr< ns3::NixVector >', 
                   [], 
                   is_const=True)
    ## packet.h (module 'network'): ns3::PacketTagIterator ns3::Packet::GetPacketTagIterator() const [member function]
    cls.add_method('GetPacketTagIterator', 
                   'ns3::PacketTagIterator', 
                   [], 
                   is_const=True)
    ## packet.h (module 'network'): uint32_t ns3::Packet::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## packet.h (module 'network'): uint32_t ns3::Packet::GetSize() const [member function]
    cls.add_method('GetSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## packet.h (module 'network'): uint64_t ns3::Packet::GetUid() const [member function]
    cls.add_method('GetUid', 
                   'uint64_t', 
                   [], 
                   is_const=True)
    ## packet.h (module 'network'): uint8_t const * ns3::Packet::PeekData() const [member function]
    cls.add_method('PeekData', 
                   'uint8_t const *', 
                   [], 
                   deprecated=True, is_const=True)
    ## packet.h (module 'network'): uint32_t ns3::Packet::PeekHeader(ns3::Header & header) const [member function]
    cls.add_method('PeekHeader', 
                   'uint32_t', 
                   [param('ns3::Header &', 'header')], 
                   is_const=True)
    ## packet.h (module 'network'): bool ns3::Packet::PeekPacketTag(ns3::Tag & tag) const [member function]
    cls.add_method('PeekPacketTag', 
                   'bool', 
                   [param('ns3::Tag &', 'tag')], 
                   is_const=True)
    ## packet.h (module 'network'): uint32_t ns3::Packet::PeekTrailer(ns3::Trailer & trailer) [member function]
    cls.add_method('PeekTrailer', 
                   'uint32_t', 
                   [param('ns3::Trailer &', 'trailer')])
    ## packet.h (module 'network'): void ns3::Packet::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True)
    ## packet.h (module 'network'): void ns3::Packet::PrintByteTags(std::ostream & os) const [member function]
    cls.add_method('PrintByteTags', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True)
    ## packet.h (module 'network'): void ns3::Packet::PrintPacketTags(std::ostream & os) const [member function]
    cls.add_method('PrintPacketTags', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True)
    ## packet.h (module 'network'): void ns3::Packet::RemoveAllByteTags() [member function]
    cls.add_method('RemoveAllByteTags', 
                   'void', 
                   [])
    ## packet.h (module 'network'): void ns3::Packet::RemoveAllPacketTags() [member function]
    cls.add_method('RemoveAllPacketTags', 
                   'void', 
                   [])
    ## packet.h (module 'network'): void ns3::Packet::RemoveAtEnd(uint32_t size) [member function]
    cls.add_method('RemoveAtEnd', 
                   'void', 
                   [param('uint32_t', 'size')])
    ## packet.h (module 'network'): void ns3::Packet::RemoveAtStart(uint32_t size) [member function]
    cls.add_method('RemoveAtStart', 
                   'void', 
                   [param('uint32_t', 'size')])
    ## packet.h (module 'network'): uint32_t ns3::Packet::RemoveHeader(ns3::Header & header) [member function]
    cls.add_method('RemoveHeader', 
                   'uint32_t', 
                   [param('ns3::Header &', 'header')])
    ## packet.h (module 'network'): bool ns3::Packet::RemovePacketTag(ns3::Tag & tag) [member function]
    cls.add_method('RemovePacketTag', 
                   'bool', 
                   [param('ns3::Tag &', 'tag')])
    ## packet.h (module 'network'): uint32_t ns3::Packet::RemoveTrailer(ns3::Trailer & trailer) [member function]
    cls.add_method('RemoveTrailer', 
                   'uint32_t', 
                   [param('ns3::Trailer &', 'trailer')])
    ## packet.h (module 'network'): uint32_t ns3::Packet::Serialize(uint8_t * buffer, uint32_t maxSize) const [member function]
    cls.add_method('Serialize', 
                   'uint32_t', 
                   [param('uint8_t *', 'buffer'), param('uint32_t', 'maxSize')], 
                   is_const=True)
    ## packet.h (module 'network'): void ns3::Packet::SetNixVector(ns3::Ptr<ns3::NixVector> arg0) [member function]
    cls.add_method('SetNixVector', 
                   'void', 
                   [param('ns3::Ptr< ns3::NixVector >', 'arg0')])
    return

def register_Ns3ParetoRandomVariable_methods(root_module, cls):
    ## random-variable-stream.h (module 'core'): static ns3::TypeId ns3::ParetoRandomVariable::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## random-variable-stream.h (module 'core'): ns3::ParetoRandomVariable::ParetoRandomVariable() [constructor]
    cls.add_constructor([])
    ## random-variable-stream.h (module 'core'): double ns3::ParetoRandomVariable::GetMean() const [member function]
    cls.add_method('GetMean', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::ParetoRandomVariable::GetShape() const [member function]
    cls.add_method('GetShape', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::ParetoRandomVariable::GetBound() const [member function]
    cls.add_method('GetBound', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::ParetoRandomVariable::GetValue(double mean, double shape, double bound) [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [param('double', 'mean'), param('double', 'shape'), param('double', 'bound')])
    ## random-variable-stream.h (module 'core'): uint32_t ns3::ParetoRandomVariable::GetInteger(uint32_t mean, uint32_t shape, uint32_t bound) [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [param('uint32_t', 'mean'), param('uint32_t', 'shape'), param('uint32_t', 'bound')])
    ## random-variable-stream.h (module 'core'): double ns3::ParetoRandomVariable::GetValue() [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [], 
                   is_virtual=True)
    ## random-variable-stream.h (module 'core'): uint32_t ns3::ParetoRandomVariable::GetInteger() [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [], 
                   is_virtual=True)
    return

def register_Ns3RandomVariableChecker_methods(root_module, cls):
    ## random-variable.h (module 'core'): ns3::RandomVariableChecker::RandomVariableChecker() [constructor]
    cls.add_constructor([])
    ## random-variable.h (module 'core'): ns3::RandomVariableChecker::RandomVariableChecker(ns3::RandomVariableChecker const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::RandomVariableChecker const &', 'arg0')])
    return

def register_Ns3RandomVariableValue_methods(root_module, cls):
    ## random-variable.h (module 'core'): ns3::RandomVariableValue::RandomVariableValue() [constructor]
    cls.add_constructor([])
    ## random-variable.h (module 'core'): ns3::RandomVariableValue::RandomVariableValue(ns3::RandomVariableValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::RandomVariableValue const &', 'arg0')])
    ## random-variable.h (module 'core'): ns3::RandomVariableValue::RandomVariableValue(ns3::RandomVariable const & value) [constructor]
    cls.add_constructor([param('ns3::RandomVariable const &', 'value')])
    ## random-variable.h (module 'core'): ns3::Ptr<ns3::AttributeValue> ns3::RandomVariableValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## random-variable.h (module 'core'): bool ns3::RandomVariableValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## random-variable.h (module 'core'): ns3::RandomVariable ns3::RandomVariableValue::Get() const [member function]
    cls.add_method('Get', 
                   'ns3::RandomVariable', 
                   [], 
                   is_const=True)
    ## random-variable.h (module 'core'): std::string ns3::RandomVariableValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## random-variable.h (module 'core'): void ns3::RandomVariableValue::Set(ns3::RandomVariable const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('ns3::RandomVariable const &', 'value')])
    return

def register_Ns3StringChecker_methods(root_module, cls):
    ## string.h (module 'core'): ns3::StringChecker::StringChecker() [constructor]
    cls.add_constructor([])
    ## string.h (module 'core'): ns3::StringChecker::StringChecker(ns3::StringChecker const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::StringChecker const &', 'arg0')])
    return

def register_Ns3StringValue_methods(root_module, cls):
    ## string.h (module 'core'): ns3::StringValue::StringValue() [constructor]
    cls.add_constructor([])
    ## string.h (module 'core'): ns3::StringValue::StringValue(ns3::StringValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::StringValue const &', 'arg0')])
    ## string.h (module 'core'): ns3::StringValue::StringValue(std::string const & value) [constructor]
    cls.add_constructor([param('std::string const &', 'value')])
    ## string.h (module 'core'): ns3::Ptr<ns3::AttributeValue> ns3::StringValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## string.h (module 'core'): bool ns3::StringValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## string.h (module 'core'): std::string ns3::StringValue::Get() const [member function]
    cls.add_method('Get', 
                   'std::string', 
                   [], 
                   is_const=True)
    ## string.h (module 'core'): std::string ns3::StringValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## string.h (module 'core'): void ns3::StringValue::Set(std::string const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('std::string const &', 'value')])
    return

def register_Ns3TimeChecker_methods(root_module, cls):
    ## nstime.h (module 'core'): ns3::TimeChecker::TimeChecker() [constructor]
    cls.add_constructor([])
    ## nstime.h (module 'core'): ns3::TimeChecker::TimeChecker(ns3::TimeChecker const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::TimeChecker const &', 'arg0')])
    return

def register_Ns3TimeValue_methods(root_module, cls):
    ## nstime.h (module 'core'): ns3::TimeValue::TimeValue() [constructor]
    cls.add_constructor([])
    ## nstime.h (module 'core'): ns3::TimeValue::TimeValue(ns3::TimeValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::TimeValue const &', 'arg0')])
    ## nstime.h (module 'core'): ns3::TimeValue::TimeValue(ns3::Time const & value) [constructor]
    cls.add_constructor([param('ns3::Time const &', 'value')])
    ## nstime.h (module 'core'): ns3::Ptr<ns3::AttributeValue> ns3::TimeValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## nstime.h (module 'core'): bool ns3::TimeValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## nstime.h (module 'core'): ns3::Time ns3::TimeValue::Get() const [member function]
    cls.add_method('Get', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## nstime.h (module 'core'): std::string ns3::TimeValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## nstime.h (module 'core'): void ns3::TimeValue::Set(ns3::Time const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('ns3::Time const &', 'value')])
    return

def register_Ns3TypeIdChecker_methods(root_module, cls):
    ## type-id.h (module 'core'): ns3::TypeIdChecker::TypeIdChecker() [constructor]
    cls.add_constructor([])
    ## type-id.h (module 'core'): ns3::TypeIdChecker::TypeIdChecker(ns3::TypeIdChecker const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::TypeIdChecker const &', 'arg0')])
    return

def register_Ns3TypeIdValue_methods(root_module, cls):
    ## type-id.h (module 'core'): ns3::TypeIdValue::TypeIdValue() [constructor]
    cls.add_constructor([])
    ## type-id.h (module 'core'): ns3::TypeIdValue::TypeIdValue(ns3::TypeIdValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::TypeIdValue const &', 'arg0')])
    ## type-id.h (module 'core'): ns3::TypeIdValue::TypeIdValue(ns3::TypeId const & value) [constructor]
    cls.add_constructor([param('ns3::TypeId const &', 'value')])
    ## type-id.h (module 'core'): ns3::Ptr<ns3::AttributeValue> ns3::TypeIdValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## type-id.h (module 'core'): bool ns3::TypeIdValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## type-id.h (module 'core'): ns3::TypeId ns3::TypeIdValue::Get() const [member function]
    cls.add_method('Get', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True)
    ## type-id.h (module 'core'): std::string ns3::TypeIdValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## type-id.h (module 'core'): void ns3::TypeIdValue::Set(ns3::TypeId const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('ns3::TypeId const &', 'value')])
    return

def register_Ns3UintegerValue_methods(root_module, cls):
    ## uinteger.h (module 'core'): ns3::UintegerValue::UintegerValue() [constructor]
    cls.add_constructor([])
    ## uinteger.h (module 'core'): ns3::UintegerValue::UintegerValue(ns3::UintegerValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::UintegerValue const &', 'arg0')])
    ## uinteger.h (module 'core'): ns3::UintegerValue::UintegerValue(uint64_t const & value) [constructor]
    cls.add_constructor([param('uint64_t const &', 'value')])
    ## uinteger.h (module 'core'): ns3::Ptr<ns3::AttributeValue> ns3::UintegerValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## uinteger.h (module 'core'): bool ns3::UintegerValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## uinteger.h (module 'core'): uint64_t ns3::UintegerValue::Get() const [member function]
    cls.add_method('Get', 
                   'uint64_t', 
                   [], 
                   is_const=True)
    ## uinteger.h (module 'core'): std::string ns3::UintegerValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## uinteger.h (module 'core'): void ns3::UintegerValue::Set(uint64_t const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('uint64_t const &', 'value')])
    return

def register_Ns3AddressChecker_methods(root_module, cls):
    ## address.h (module 'network'): ns3::AddressChecker::AddressChecker() [constructor]
    cls.add_constructor([])
    ## address.h (module 'network'): ns3::AddressChecker::AddressChecker(ns3::AddressChecker const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::AddressChecker const &', 'arg0')])
    return

def register_Ns3AddressValue_methods(root_module, cls):
    ## address.h (module 'network'): ns3::AddressValue::AddressValue() [constructor]
    cls.add_constructor([])
    ## address.h (module 'network'): ns3::AddressValue::AddressValue(ns3::AddressValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::AddressValue const &', 'arg0')])
    ## address.h (module 'network'): ns3::AddressValue::AddressValue(ns3::Address const & value) [constructor]
    cls.add_constructor([param('ns3::Address const &', 'value')])
    ## address.h (module 'network'): ns3::Ptr<ns3::AttributeValue> ns3::AddressValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## address.h (module 'network'): bool ns3::AddressValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## address.h (module 'network'): ns3::Address ns3::AddressValue::Get() const [member function]
    cls.add_method('Get', 
                   'ns3::Address', 
                   [], 
                   is_const=True)
    ## address.h (module 'network'): std::string ns3::AddressValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## address.h (module 'network'): void ns3::AddressValue::Set(ns3::Address const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('ns3::Address const &', 'value')])
    return

def register_Ns3Ipv4ListRouting_methods(root_module, cls):
    ## ipv4-list-routing.h (module 'internet'): ns3::Ipv4ListRouting::Ipv4ListRouting(ns3::Ipv4ListRouting const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Ipv4ListRouting const &', 'arg0')])
    ## ipv4-list-routing.h (module 'internet'): ns3::Ipv4ListRouting::Ipv4ListRouting() [constructor]
    cls.add_constructor([])
    ## ipv4-list-routing.h (module 'internet'): void ns3::Ipv4ListRouting::AddRoutingProtocol(ns3::Ptr<ns3::Ipv4RoutingProtocol> routingProtocol, int16_t priority) [member function]
    cls.add_method('AddRoutingProtocol', 
                   'void', 
                   [param('ns3::Ptr< ns3::Ipv4RoutingProtocol >', 'routingProtocol'), param('int16_t', 'priority')], 
                   is_virtual=True)
    ## ipv4-list-routing.h (module 'internet'): uint32_t ns3::Ipv4ListRouting::GetNRoutingProtocols() const [member function]
    cls.add_method('GetNRoutingProtocols', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## ipv4-list-routing.h (module 'internet'): ns3::Ptr<ns3::Ipv4RoutingProtocol> ns3::Ipv4ListRouting::GetRoutingProtocol(uint32_t index, int16_t & priority) const [member function]
    cls.add_method('GetRoutingProtocol', 
                   'ns3::Ptr< ns3::Ipv4RoutingProtocol >', 
                   [param('uint32_t', 'index'), param('int16_t &', 'priority', direction=2)], 
                   is_const=True, is_virtual=True)
    ## ipv4-list-routing.h (module 'internet'): static ns3::TypeId ns3::Ipv4ListRouting::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## ipv4-list-routing.h (module 'internet'): void ns3::Ipv4ListRouting::NotifyAddAddress(uint32_t interface, ns3::Ipv4InterfaceAddress address) [member function]
    cls.add_method('NotifyAddAddress', 
                   'void', 
                   [param('uint32_t', 'interface'), param('ns3::Ipv4InterfaceAddress', 'address')], 
                   is_virtual=True)
    ## ipv4-list-routing.h (module 'internet'): void ns3::Ipv4ListRouting::NotifyInterfaceDown(uint32_t interface) [member function]
    cls.add_method('NotifyInterfaceDown', 
                   'void', 
                   [param('uint32_t', 'interface')], 
                   is_virtual=True)
    ## ipv4-list-routing.h (module 'internet'): void ns3::Ipv4ListRouting::NotifyInterfaceUp(uint32_t interface) [member function]
    cls.add_method('NotifyInterfaceUp', 
                   'void', 
                   [param('uint32_t', 'interface')], 
                   is_virtual=True)
    ## ipv4-list-routing.h (module 'internet'): void ns3::Ipv4ListRouting::NotifyRemoveAddress(uint32_t interface, ns3::Ipv4InterfaceAddress address) [member function]
    cls.add_method('NotifyRemoveAddress', 
                   'void', 
                   [param('uint32_t', 'interface'), param('ns3::Ipv4InterfaceAddress', 'address')], 
                   is_virtual=True)
    ## ipv4-list-routing.h (module 'internet'): void ns3::Ipv4ListRouting::PrintRoutingTable(ns3::Ptr<ns3::OutputStreamWrapper> stream) const [member function]
    cls.add_method('PrintRoutingTable', 
                   'void', 
                   [param('ns3::Ptr< ns3::OutputStreamWrapper >', 'stream')], 
                   is_const=True, is_virtual=True)
    ## ipv4-list-routing.h (module 'internet'): bool ns3::Ipv4ListRouting::RouteInput(ns3::Ptr<ns3::Packet const> p, ns3::Ipv4Header const & header, ns3::Ptr<const ns3::NetDevice> idev, ns3::Callback<void, ns3::Ptr<ns3::Ipv4Route>, ns3::Ptr<ns3::Packet const>, ns3::Ipv4Header const&, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ucb, ns3::Callback<void,ns3::Ptr<ns3::Ipv4MulticastRoute>,ns3::Ptr<const ns3::Packet>,const ns3::Ipv4Header&,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty> mcb, ns3::Callback<void,ns3::Ptr<const ns3::Packet>,const ns3::Ipv4Header&,unsigned int,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty> lcb, ns3::Callback<void, ns3::Ptr<ns3::Packet const>, ns3::Ipv4Header const&, ns3::Socket::SocketErrno, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ecb) [member function]
    cls.add_method('RouteInput', 
                   'bool', 
                   [param('ns3::Ptr< ns3::Packet const >', 'p'), param('ns3::Ipv4Header const &', 'header'), param('ns3::Ptr< ns3::NetDevice const >', 'idev'), param('ns3::Callback< void, ns3::Ptr< ns3::Ipv4Route >, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'ucb'), param('ns3::Callback< void, ns3::Ptr< ns3::Ipv4MulticastRoute >, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'mcb'), param('ns3::Callback< void, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, unsigned int, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'lcb'), param('ns3::Callback< void, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, ns3::Socket::SocketErrno, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'ecb')], 
                   is_virtual=True)
    ## ipv4-list-routing.h (module 'internet'): ns3::Ptr<ns3::Ipv4Route> ns3::Ipv4ListRouting::RouteOutput(ns3::Ptr<ns3::Packet> p, ns3::Ipv4Header const & header, ns3::Ptr<ns3::NetDevice> oif, ns3::Socket::SocketErrno & sockerr) [member function]
    cls.add_method('RouteOutput', 
                   'ns3::Ptr< ns3::Ipv4Route >', 
                   [param('ns3::Ptr< ns3::Packet >', 'p'), param('ns3::Ipv4Header const &', 'header'), param('ns3::Ptr< ns3::NetDevice >', 'oif'), param('ns3::Socket::SocketErrno &', 'sockerr')], 
                   is_virtual=True)
    ## ipv4-list-routing.h (module 'internet'): void ns3::Ipv4ListRouting::SetIpv4(ns3::Ptr<ns3::Ipv4> ipv4) [member function]
    cls.add_method('SetIpv4', 
                   'void', 
                   [param('ns3::Ptr< ns3::Ipv4 >', 'ipv4')], 
                   is_virtual=True)
    ## ipv4-list-routing.h (module 'internet'): void ns3::Ipv4ListRouting::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## ipv4-list-routing.h (module 'internet'): void ns3::Ipv4ListRouting::DoStart() [member function]
    cls.add_method('DoStart', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    return

def register_Ns3AodvDuplicatePacketDetection_methods(root_module, cls):
    ## aodv-dpd.h (module 'aodv'): ns3::aodv::DuplicatePacketDetection::DuplicatePacketDetection(ns3::aodv::DuplicatePacketDetection const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::aodv::DuplicatePacketDetection const &', 'arg0')])
    ## aodv-dpd.h (module 'aodv'): ns3::aodv::DuplicatePacketDetection::DuplicatePacketDetection(ns3::Time lifetime) [constructor]
    cls.add_constructor([param('ns3::Time', 'lifetime')])
    ## aodv-dpd.h (module 'aodv'): ns3::Time ns3::aodv::DuplicatePacketDetection::GetLifetime() const [member function]
    cls.add_method('GetLifetime', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## aodv-dpd.h (module 'aodv'): bool ns3::aodv::DuplicatePacketDetection::IsDuplicate(ns3::Ptr<ns3::Packet const> p, ns3::Ipv4Header const & header) [member function]
    cls.add_method('IsDuplicate', 
                   'bool', 
                   [param('ns3::Ptr< ns3::Packet const >', 'p'), param('ns3::Ipv4Header const &', 'header')])
    ## aodv-dpd.h (module 'aodv'): void ns3::aodv::DuplicatePacketDetection::SetLifetime(ns3::Time lifetime) [member function]
    cls.add_method('SetLifetime', 
                   'void', 
                   [param('ns3::Time', 'lifetime')])
    return

def register_Ns3AodvIdCache_methods(root_module, cls):
    ## aodv-id-cache.h (module 'aodv'): ns3::aodv::IdCache::IdCache(ns3::aodv::IdCache const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::aodv::IdCache const &', 'arg0')])
    ## aodv-id-cache.h (module 'aodv'): ns3::aodv::IdCache::IdCache(ns3::Time lifetime) [constructor]
    cls.add_constructor([param('ns3::Time', 'lifetime')])
    ## aodv-id-cache.h (module 'aodv'): ns3::Time ns3::aodv::IdCache::GetLifeTime() const [member function]
    cls.add_method('GetLifeTime', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## aodv-id-cache.h (module 'aodv'): uint32_t ns3::aodv::IdCache::GetSize() [member function]
    cls.add_method('GetSize', 
                   'uint32_t', 
                   [])
    ## aodv-id-cache.h (module 'aodv'): bool ns3::aodv::IdCache::IsDuplicate(ns3::Ipv4Address addr, uint32_t id) [member function]
    cls.add_method('IsDuplicate', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'addr'), param('uint32_t', 'id')])
    ## aodv-id-cache.h (module 'aodv'): void ns3::aodv::IdCache::Purge() [member function]
    cls.add_method('Purge', 
                   'void', 
                   [])
    ## aodv-id-cache.h (module 'aodv'): void ns3::aodv::IdCache::SetLifetime(ns3::Time lifetime) [member function]
    cls.add_method('SetLifetime', 
                   'void', 
                   [param('ns3::Time', 'lifetime')])
    return

def register_Ns3AodvNeighbors_methods(root_module, cls):
    ## aodv-neighbor.h (module 'aodv'): ns3::aodv::Neighbors::Neighbors(ns3::aodv::Neighbors const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::aodv::Neighbors const &', 'arg0')])
    ## aodv-neighbor.h (module 'aodv'): ns3::aodv::Neighbors::Neighbors(ns3::Time delay) [constructor]
    cls.add_constructor([param('ns3::Time', 'delay')])
    ## aodv-neighbor.h (module 'aodv'): void ns3::aodv::Neighbors::AddArpCache(ns3::Ptr<ns3::ArpCache> arg0) [member function]
    cls.add_method('AddArpCache', 
                   'void', 
                   [param('ns3::Ptr< ns3::ArpCache >', 'arg0')])
    ## aodv-neighbor.h (module 'aodv'): void ns3::aodv::Neighbors::Clear() [member function]
    cls.add_method('Clear', 
                   'void', 
                   [])
    ## aodv-neighbor.h (module 'aodv'): void ns3::aodv::Neighbors::DelArpCache(ns3::Ptr<ns3::ArpCache> arg0) [member function]
    cls.add_method('DelArpCache', 
                   'void', 
                   [param('ns3::Ptr< ns3::ArpCache >', 'arg0')])
    ## aodv-neighbor.h (module 'aodv'): ns3::Callback<void, ns3::Ipv4Address, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ns3::aodv::Neighbors::GetCallback() const [member function]
    cls.add_method('GetCallback', 
                   'ns3::Callback< void, ns3::Ipv4Address, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 
                   [], 
                   is_const=True)
    ## aodv-neighbor.h (module 'aodv'): ns3::Time ns3::aodv::Neighbors::GetExpireTime(ns3::Ipv4Address addr) [member function]
    cls.add_method('GetExpireTime', 
                   'ns3::Time', 
                   [param('ns3::Ipv4Address', 'addr')])
    ## aodv-neighbor.h (module 'aodv'): ns3::Callback<void, ns3::WifiMacHeader const&, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ns3::aodv::Neighbors::GetTxErrorCallback() const [member function]
    cls.add_method('GetTxErrorCallback', 
                   'ns3::Callback< void, ns3::WifiMacHeader const &, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 
                   [], 
                   is_const=True)
    ## aodv-neighbor.h (module 'aodv'): bool ns3::aodv::Neighbors::IsNeighbor(ns3::Ipv4Address addr) [member function]
    cls.add_method('IsNeighbor', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'addr')])
    ## aodv-neighbor.h (module 'aodv'): void ns3::aodv::Neighbors::Purge() [member function]
    cls.add_method('Purge', 
                   'void', 
                   [])
    ## aodv-neighbor.h (module 'aodv'): void ns3::aodv::Neighbors::ScheduleTimer() [member function]
    cls.add_method('ScheduleTimer', 
                   'void', 
                   [])
    ## aodv-neighbor.h (module 'aodv'): void ns3::aodv::Neighbors::SetCallback(ns3::Callback<void, ns3::Ipv4Address, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> cb) [member function]
    cls.add_method('SetCallback', 
                   'void', 
                   [param('ns3::Callback< void, ns3::Ipv4Address, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'cb')])
    ## aodv-neighbor.h (module 'aodv'): void ns3::aodv::Neighbors::Update(ns3::Ipv4Address addr, ns3::Time expire) [member function]
    cls.add_method('Update', 
                   'void', 
                   [param('ns3::Ipv4Address', 'addr'), param('ns3::Time', 'expire')])
    return

def register_Ns3AodvNeighborsNeighbor_methods(root_module, cls):
    ## aodv-neighbor.h (module 'aodv'): ns3::aodv::Neighbors::Neighbor::Neighbor(ns3::aodv::Neighbors::Neighbor const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::aodv::Neighbors::Neighbor const &', 'arg0')])
    ## aodv-neighbor.h (module 'aodv'): ns3::aodv::Neighbors::Neighbor::Neighbor(ns3::Ipv4Address ip, ns3::Mac48Address mac, ns3::Time t) [constructor]
    cls.add_constructor([param('ns3::Ipv4Address', 'ip'), param('ns3::Mac48Address', 'mac'), param('ns3::Time', 't')])
    ## aodv-neighbor.h (module 'aodv'): ns3::aodv::Neighbors::Neighbor::close [variable]
    cls.add_instance_attribute('close', 'bool', is_const=False)
    ## aodv-neighbor.h (module 'aodv'): ns3::aodv::Neighbors::Neighbor::m_expireTime [variable]
    cls.add_instance_attribute('m_expireTime', 'ns3::Time', is_const=False)
    ## aodv-neighbor.h (module 'aodv'): ns3::aodv::Neighbors::Neighbor::m_hardwareAddress [variable]
    cls.add_instance_attribute('m_hardwareAddress', 'ns3::Mac48Address', is_const=False)
    ## aodv-neighbor.h (module 'aodv'): ns3::aodv::Neighbors::Neighbor::m_neighborAddress [variable]
    cls.add_instance_attribute('m_neighborAddress', 'ns3::Ipv4Address', is_const=False)
    return

def register_Ns3AodvQueueEntry_methods(root_module, cls):
    cls.add_binary_comparison_operator('==')
    ## aodv-rqueue.h (module 'aodv'): ns3::aodv::QueueEntry::QueueEntry(ns3::aodv::QueueEntry const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::aodv::QueueEntry const &', 'arg0')])
    ## aodv-rqueue.h (module 'aodv'): ns3::aodv::QueueEntry::QueueEntry(ns3::Ptr<ns3::Packet const> pa=0, ns3::Ipv4Header const & h=ns3::Ipv4Header(), ns3::Callback<void, ns3::Ptr<ns3::Ipv4Route>, ns3::Ptr<ns3::Packet const>, ns3::Ipv4Header const&, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ucb=ns3::Callback<void, ns3::Ptr<ns3::Ipv4Route>, ns3::Ptr<const ns3::Packet>, const ns3::Ipv4Header&, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty>(), ns3::Callback<void, ns3::Ptr<ns3::Packet const>, ns3::Ipv4Header const&, ns3::Socket::SocketErrno, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ecb=ns3::Callback<void, ns3::Ptr<const ns3::Packet>, const ns3::Ipv4Header&, ns3::Socket::SocketErrno, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty>(), ns3::Time exp=ns3::Simulator::Now( )) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::Packet const >', 'pa', default_value='0'), param('ns3::Ipv4Header const &', 'h', default_value='ns3::Ipv4Header()'), param('ns3::Callback< void, ns3::Ptr< ns3::Ipv4Route >, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'ucb', default_value='ns3::Callback<void, ns3::Ptr<ns3::Ipv4Route>, ns3::Ptr<const ns3::Packet>, const ns3::Ipv4Header&, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty>()'), param('ns3::Callback< void, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, ns3::Socket::SocketErrno, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'ecb', default_value='ns3::Callback<void, ns3::Ptr<const ns3::Packet>, const ns3::Ipv4Header&, ns3::Socket::SocketErrno, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty>()'), param('ns3::Time', 'exp', default_value='ns3::Simulator::Now( )')])
    ## aodv-rqueue.h (module 'aodv'): ns3::Callback<void, ns3::Ptr<ns3::Packet const>, ns3::Ipv4Header const&, ns3::Socket::SocketErrno, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ns3::aodv::QueueEntry::GetErrorCallback() const [member function]
    cls.add_method('GetErrorCallback', 
                   'ns3::Callback< void, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, ns3::Socket::SocketErrno, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 
                   [], 
                   is_const=True)
    ## aodv-rqueue.h (module 'aodv'): ns3::Time ns3::aodv::QueueEntry::GetExpireTime() const [member function]
    cls.add_method('GetExpireTime', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## aodv-rqueue.h (module 'aodv'): ns3::Ipv4Header ns3::aodv::QueueEntry::GetIpv4Header() const [member function]
    cls.add_method('GetIpv4Header', 
                   'ns3::Ipv4Header', 
                   [], 
                   is_const=True)
    ## aodv-rqueue.h (module 'aodv'): ns3::Ptr<ns3::Packet const> ns3::aodv::QueueEntry::GetPacket() const [member function]
    cls.add_method('GetPacket', 
                   'ns3::Ptr< ns3::Packet const >', 
                   [], 
                   is_const=True)
    ## aodv-rqueue.h (module 'aodv'): ns3::Callback<void, ns3::Ptr<ns3::Ipv4Route>, ns3::Ptr<ns3::Packet const>, ns3::Ipv4Header const&, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ns3::aodv::QueueEntry::GetUnicastForwardCallback() const [member function]
    cls.add_method('GetUnicastForwardCallback', 
                   'ns3::Callback< void, ns3::Ptr< ns3::Ipv4Route >, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 
                   [], 
                   is_const=True)
    ## aodv-rqueue.h (module 'aodv'): void ns3::aodv::QueueEntry::SetErrorCallback(ns3::Callback<void, ns3::Ptr<ns3::Packet const>, ns3::Ipv4Header const&, ns3::Socket::SocketErrno, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ecb) [member function]
    cls.add_method('SetErrorCallback', 
                   'void', 
                   [param('ns3::Callback< void, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, ns3::Socket::SocketErrno, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'ecb')])
    ## aodv-rqueue.h (module 'aodv'): void ns3::aodv::QueueEntry::SetExpireTime(ns3::Time exp) [member function]
    cls.add_method('SetExpireTime', 
                   'void', 
                   [param('ns3::Time', 'exp')])
    ## aodv-rqueue.h (module 'aodv'): void ns3::aodv::QueueEntry::SetIpv4Header(ns3::Ipv4Header h) [member function]
    cls.add_method('SetIpv4Header', 
                   'void', 
                   [param('ns3::Ipv4Header', 'h')])
    ## aodv-rqueue.h (module 'aodv'): void ns3::aodv::QueueEntry::SetPacket(ns3::Ptr<ns3::Packet const> p) [member function]
    cls.add_method('SetPacket', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet const >', 'p')])
    ## aodv-rqueue.h (module 'aodv'): void ns3::aodv::QueueEntry::SetUnicastForwardCallback(ns3::Callback<void, ns3::Ptr<ns3::Ipv4Route>, ns3::Ptr<ns3::Packet const>, ns3::Ipv4Header const&, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ucb) [member function]
    cls.add_method('SetUnicastForwardCallback', 
                   'void', 
                   [param('ns3::Callback< void, ns3::Ptr< ns3::Ipv4Route >, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'ucb')])
    return

def register_Ns3AodvRequestQueue_methods(root_module, cls):
    ## aodv-rqueue.h (module 'aodv'): ns3::aodv::RequestQueue::RequestQueue(ns3::aodv::RequestQueue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::aodv::RequestQueue const &', 'arg0')])
    ## aodv-rqueue.h (module 'aodv'): ns3::aodv::RequestQueue::RequestQueue(uint32_t maxLen, ns3::Time routeToQueueTimeout) [constructor]
    cls.add_constructor([param('uint32_t', 'maxLen'), param('ns3::Time', 'routeToQueueTimeout')])
    ## aodv-rqueue.h (module 'aodv'): bool ns3::aodv::RequestQueue::Dequeue(ns3::Ipv4Address dst, ns3::aodv::QueueEntry & entry) [member function]
    cls.add_method('Dequeue', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'dst'), param('ns3::aodv::QueueEntry &', 'entry')])
    ## aodv-rqueue.h (module 'aodv'): void ns3::aodv::RequestQueue::DropPacketWithDst(ns3::Ipv4Address dst) [member function]
    cls.add_method('DropPacketWithDst', 
                   'void', 
                   [param('ns3::Ipv4Address', 'dst')])
    ## aodv-rqueue.h (module 'aodv'): bool ns3::aodv::RequestQueue::Enqueue(ns3::aodv::QueueEntry & entry) [member function]
    cls.add_method('Enqueue', 
                   'bool', 
                   [param('ns3::aodv::QueueEntry &', 'entry')])
    ## aodv-rqueue.h (module 'aodv'): bool ns3::aodv::RequestQueue::Find(ns3::Ipv4Address dst) [member function]
    cls.add_method('Find', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'dst')])
    ## aodv-rqueue.h (module 'aodv'): uint32_t ns3::aodv::RequestQueue::GetMaxQueueLen() const [member function]
    cls.add_method('GetMaxQueueLen', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## aodv-rqueue.h (module 'aodv'): ns3::Time ns3::aodv::RequestQueue::GetQueueTimeout() const [member function]
    cls.add_method('GetQueueTimeout', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## aodv-rqueue.h (module 'aodv'): uint32_t ns3::aodv::RequestQueue::GetSize() [member function]
    cls.add_method('GetSize', 
                   'uint32_t', 
                   [])
    ## aodv-rqueue.h (module 'aodv'): void ns3::aodv::RequestQueue::SetMaxQueueLen(uint32_t len) [member function]
    cls.add_method('SetMaxQueueLen', 
                   'void', 
                   [param('uint32_t', 'len')])
    ## aodv-rqueue.h (module 'aodv'): void ns3::aodv::RequestQueue::SetQueueTimeout(ns3::Time t) [member function]
    cls.add_method('SetQueueTimeout', 
                   'void', 
                   [param('ns3::Time', 't')])
    return

def register_Ns3AodvRerrHeader_methods(root_module, cls):
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    ## aodv-packet.h (module 'aodv'): ns3::aodv::RerrHeader::RerrHeader(ns3::aodv::RerrHeader const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::aodv::RerrHeader const &', 'arg0')])
    ## aodv-packet.h (module 'aodv'): ns3::aodv::RerrHeader::RerrHeader() [constructor]
    cls.add_constructor([])
    ## aodv-packet.h (module 'aodv'): bool ns3::aodv::RerrHeader::AddUnDestination(ns3::Ipv4Address dst, uint32_t seqNo) [member function]
    cls.add_method('AddUnDestination', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'dst'), param('uint32_t', 'seqNo')])
    ## aodv-packet.h (module 'aodv'): void ns3::aodv::RerrHeader::Clear() [member function]
    cls.add_method('Clear', 
                   'void', 
                   [])
    ## aodv-packet.h (module 'aodv'): uint32_t ns3::aodv::RerrHeader::Deserialize(ns3::Buffer::Iterator start) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_virtual=True)
    ## aodv-packet.h (module 'aodv'): uint8_t ns3::aodv::RerrHeader::GetDestCount() const [member function]
    cls.add_method('GetDestCount', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## aodv-packet.h (module 'aodv'): ns3::TypeId ns3::aodv::RerrHeader::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## aodv-packet.h (module 'aodv'): bool ns3::aodv::RerrHeader::GetNoDelete() const [member function]
    cls.add_method('GetNoDelete', 
                   'bool', 
                   [], 
                   is_const=True)
    ## aodv-packet.h (module 'aodv'): uint32_t ns3::aodv::RerrHeader::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## aodv-packet.h (module 'aodv'): static ns3::TypeId ns3::aodv::RerrHeader::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## aodv-packet.h (module 'aodv'): void ns3::aodv::RerrHeader::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## aodv-packet.h (module 'aodv'): bool ns3::aodv::RerrHeader::RemoveUnDestination(std::pair<ns3::Ipv4Address,unsigned int> & un) [member function]
    cls.add_method('RemoveUnDestination', 
                   'bool', 
                   [param('std::pair< ns3::Ipv4Address, unsigned int > &', 'un')])
    ## aodv-packet.h (module 'aodv'): void ns3::aodv::RerrHeader::Serialize(ns3::Buffer::Iterator i) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'i')], 
                   is_const=True, is_virtual=True)
    ## aodv-packet.h (module 'aodv'): void ns3::aodv::RerrHeader::SetNoDelete(bool f) [member function]
    cls.add_method('SetNoDelete', 
                   'void', 
                   [param('bool', 'f')])
    return

def register_Ns3AodvRoutingProtocol_methods(root_module, cls):
    ## aodv-routing-protocol.h (module 'aodv'): ns3::aodv::RoutingProtocol::RoutingProtocol(ns3::aodv::RoutingProtocol const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::aodv::RoutingProtocol const &', 'arg0')])
    ## aodv-routing-protocol.h (module 'aodv'): ns3::aodv::RoutingProtocol::RoutingProtocol() [constructor]
    cls.add_constructor([])
    ## aodv-routing-protocol.h (module 'aodv'): void ns3::aodv::RoutingProtocol::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   is_virtual=True)
    ## aodv-routing-protocol.h (module 'aodv'): bool ns3::aodv::RoutingProtocol::GetBroadcastEnable() const [member function]
    cls.add_method('GetBroadcastEnable', 
                   'bool', 
                   [], 
                   is_const=True)
    ## aodv-routing-protocol.h (module 'aodv'): bool ns3::aodv::RoutingProtocol::GetDesinationOnlyFlag() const [member function]
    cls.add_method('GetDesinationOnlyFlag', 
                   'bool', 
                   [], 
                   is_const=True)
    ## aodv-routing-protocol.h (module 'aodv'): bool ns3::aodv::RoutingProtocol::GetGratuitousReplyFlag() const [member function]
    cls.add_method('GetGratuitousReplyFlag', 
                   'bool', 
                   [], 
                   is_const=True)
    ## aodv-routing-protocol.h (module 'aodv'): bool ns3::aodv::RoutingProtocol::GetHelloEnable() const [member function]
    cls.add_method('GetHelloEnable', 
                   'bool', 
                   [], 
                   is_const=True)
    ## aodv-routing-protocol.h (module 'aodv'): uint32_t ns3::aodv::RoutingProtocol::GetMaxQueueLen() const [member function]
    cls.add_method('GetMaxQueueLen', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## aodv-routing-protocol.h (module 'aodv'): ns3::Time ns3::aodv::RoutingProtocol::GetMaxQueueTime() const [member function]
    cls.add_method('GetMaxQueueTime', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## aodv-routing-protocol.h (module 'aodv'): uint32_t ns3::aodv::RoutingProtocol::GetRouteMetric(ns3::Ipv4Address destination) [member function]
    cls.add_method('GetRouteMetric', 
                   'uint32_t', 
                   [param('ns3::Ipv4Address', 'destination')])
    ## aodv-routing-protocol.h (module 'aodv'): static ns3::TypeId ns3::aodv::RoutingProtocol::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## aodv-routing-protocol.h (module 'aodv'): void ns3::aodv::RoutingProtocol::NotifyAddAddress(uint32_t interface, ns3::Ipv4InterfaceAddress address) [member function]
    cls.add_method('NotifyAddAddress', 
                   'void', 
                   [param('uint32_t', 'interface'), param('ns3::Ipv4InterfaceAddress', 'address')], 
                   is_virtual=True)
    ## aodv-routing-protocol.h (module 'aodv'): void ns3::aodv::RoutingProtocol::NotifyInterfaceDown(uint32_t interface) [member function]
    cls.add_method('NotifyInterfaceDown', 
                   'void', 
                   [param('uint32_t', 'interface')], 
                   is_virtual=True)
    ## aodv-routing-protocol.h (module 'aodv'): void ns3::aodv::RoutingProtocol::NotifyInterfaceUp(uint32_t interface) [member function]
    cls.add_method('NotifyInterfaceUp', 
                   'void', 
                   [param('uint32_t', 'interface')], 
                   is_virtual=True)
    ## aodv-routing-protocol.h (module 'aodv'): void ns3::aodv::RoutingProtocol::NotifyRemoveAddress(uint32_t interface, ns3::Ipv4InterfaceAddress address) [member function]
    cls.add_method('NotifyRemoveAddress', 
                   'void', 
                   [param('uint32_t', 'interface'), param('ns3::Ipv4InterfaceAddress', 'address')], 
                   is_virtual=True)
    ## aodv-routing-protocol.h (module 'aodv'): void ns3::aodv::RoutingProtocol::PrintRoutingTable(ns3::Ptr<ns3::OutputStreamWrapper> stream) const [member function]
    cls.add_method('PrintRoutingTable', 
                   'void', 
                   [param('ns3::Ptr< ns3::OutputStreamWrapper >', 'stream')], 
                   is_const=True, is_virtual=True)
    ## aodv-routing-protocol.h (module 'aodv'): bool ns3::aodv::RoutingProtocol::RouteInput(ns3::Ptr<ns3::Packet const> p, ns3::Ipv4Header const & header, ns3::Ptr<const ns3::NetDevice> idev, ns3::Callback<void, ns3::Ptr<ns3::Ipv4Route>, ns3::Ptr<ns3::Packet const>, ns3::Ipv4Header const&, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ucb, ns3::Callback<void,ns3::Ptr<ns3::Ipv4MulticastRoute>,ns3::Ptr<const ns3::Packet>,const ns3::Ipv4Header&,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty> mcb, ns3::Callback<void,ns3::Ptr<const ns3::Packet>,const ns3::Ipv4Header&,unsigned int,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty> lcb, ns3::Callback<void, ns3::Ptr<ns3::Packet const>, ns3::Ipv4Header const&, ns3::Socket::SocketErrno, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ecb) [member function]
    cls.add_method('RouteInput', 
                   'bool', 
                   [param('ns3::Ptr< ns3::Packet const >', 'p'), param('ns3::Ipv4Header const &', 'header'), param('ns3::Ptr< ns3::NetDevice const >', 'idev'), param('ns3::Callback< void, ns3::Ptr< ns3::Ipv4Route >, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'ucb'), param('ns3::Callback< void, ns3::Ptr< ns3::Ipv4MulticastRoute >, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'mcb'), param('ns3::Callback< void, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, unsigned int, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'lcb'), param('ns3::Callback< void, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, ns3::Socket::SocketErrno, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'ecb')], 
                   is_virtual=True)
    ## aodv-routing-protocol.h (module 'aodv'): ns3::Ptr<ns3::Ipv4Route> ns3::aodv::RoutingProtocol::RouteOutput(ns3::Ptr<ns3::Packet> p, ns3::Ipv4Header const & header, ns3::Ptr<ns3::NetDevice> oif, ns3::Socket::SocketErrno & sockerr) [member function]
    cls.add_method('RouteOutput', 
                   'ns3::Ptr< ns3::Ipv4Route >', 
                   [param('ns3::Ptr< ns3::Packet >', 'p'), param('ns3::Ipv4Header const &', 'header'), param('ns3::Ptr< ns3::NetDevice >', 'oif'), param('ns3::Socket::SocketErrno &', 'sockerr')], 
                   is_virtual=True)
    ## aodv-routing-protocol.h (module 'aodv'): void ns3::aodv::RoutingProtocol::SetBroadcastEnable(bool f) [member function]
    cls.add_method('SetBroadcastEnable', 
                   'void', 
                   [param('bool', 'f')])
    ## aodv-routing-protocol.h (module 'aodv'): void ns3::aodv::RoutingProtocol::SetDesinationOnlyFlag(bool f) [member function]
    cls.add_method('SetDesinationOnlyFlag', 
                   'void', 
                   [param('bool', 'f')])
    ## aodv-routing-protocol.h (module 'aodv'): void ns3::aodv::RoutingProtocol::SetGratuitousReplyFlag(bool f) [member function]
    cls.add_method('SetGratuitousReplyFlag', 
                   'void', 
                   [param('bool', 'f')])
    ## aodv-routing-protocol.h (module 'aodv'): void ns3::aodv::RoutingProtocol::SetHelloEnable(bool f) [member function]
    cls.add_method('SetHelloEnable', 
                   'void', 
                   [param('bool', 'f')])
    ## aodv-routing-protocol.h (module 'aodv'): void ns3::aodv::RoutingProtocol::SetIpv4(ns3::Ptr<ns3::Ipv4> ipv4) [member function]
    cls.add_method('SetIpv4', 
                   'void', 
                   [param('ns3::Ptr< ns3::Ipv4 >', 'ipv4')], 
                   is_virtual=True)
    ## aodv-routing-protocol.h (module 'aodv'): void ns3::aodv::RoutingProtocol::SetMaxQueueLen(uint32_t len) [member function]
    cls.add_method('SetMaxQueueLen', 
                   'void', 
                   [param('uint32_t', 'len')])
    ## aodv-routing-protocol.h (module 'aodv'): void ns3::aodv::RoutingProtocol::SetMaxQueueTime(ns3::Time t) [member function]
    cls.add_method('SetMaxQueueTime', 
                   'void', 
                   [param('ns3::Time', 't')])
    ## aodv-routing-protocol.h (module 'aodv'): ns3::aodv::RoutingProtocol::AODV_PORT [variable]
    cls.add_static_attribute('AODV_PORT', 'uint32_t const', is_const=True)
    return

def register_Ns3AodvRoutingTable_methods(root_module, cls):
    ## aodv-rtable.h (module 'aodv'): ns3::aodv::RoutingTable::RoutingTable(ns3::aodv::RoutingTable const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::aodv::RoutingTable const &', 'arg0')])
    ## aodv-rtable.h (module 'aodv'): ns3::aodv::RoutingTable::RoutingTable(ns3::Time t) [constructor]
    cls.add_constructor([param('ns3::Time', 't')])
    ## aodv-rtable.h (module 'aodv'): bool ns3::aodv::RoutingTable::AddRoute(ns3::aodv::RoutingTableEntry & r) [member function]
    cls.add_method('AddRoute', 
                   'bool', 
                   [param('ns3::aodv::RoutingTableEntry &', 'r')])
    ## aodv-rtable.h (module 'aodv'): void ns3::aodv::RoutingTable::Clear() [member function]
    cls.add_method('Clear', 
                   'void', 
                   [])
    ## aodv-rtable.h (module 'aodv'): void ns3::aodv::RoutingTable::DeleteAllRoutesFromInterface(ns3::Ipv4InterfaceAddress iface) [member function]
    cls.add_method('DeleteAllRoutesFromInterface', 
                   'void', 
                   [param('ns3::Ipv4InterfaceAddress', 'iface')])
    ## aodv-rtable.h (module 'aodv'): bool ns3::aodv::RoutingTable::DeleteRoute(ns3::Ipv4Address dst) [member function]
    cls.add_method('DeleteRoute', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'dst')])
    ## aodv-rtable.h (module 'aodv'): ns3::Time ns3::aodv::RoutingTable::GetBadLinkLifetime() const [member function]
    cls.add_method('GetBadLinkLifetime', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## aodv-rtable.h (module 'aodv'): void ns3::aodv::RoutingTable::GetListOfDestinationWithNextHop(ns3::Ipv4Address nextHop, std::map<ns3::Ipv4Address, unsigned int, std::less<ns3::Ipv4Address>, std::allocator<std::pair<ns3::Ipv4Address const, unsigned int> > > & unreachable) [member function]
    cls.add_method('GetListOfDestinationWithNextHop', 
                   'void', 
                   [param('ns3::Ipv4Address', 'nextHop'), param('std::map< ns3::Ipv4Address, unsigned int > &', 'unreachable')])
    ## aodv-rtable.h (module 'aodv'): void ns3::aodv::RoutingTable::InvalidateRoutesWithDst(std::map<ns3::Ipv4Address, unsigned int, std::less<ns3::Ipv4Address>, std::allocator<std::pair<ns3::Ipv4Address const, unsigned int> > > const & unreachable) [member function]
    cls.add_method('InvalidateRoutesWithDst', 
                   'void', 
                   [param('std::map< ns3::Ipv4Address, unsigned int > const &', 'unreachable')])
    ## aodv-rtable.h (module 'aodv'): bool ns3::aodv::RoutingTable::LookupRoute(ns3::Ipv4Address dst, ns3::aodv::RoutingTableEntry & rt) [member function]
    cls.add_method('LookupRoute', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'dst'), param('ns3::aodv::RoutingTableEntry &', 'rt')])
    ## aodv-rtable.h (module 'aodv'): bool ns3::aodv::RoutingTable::LookupValidRoute(ns3::Ipv4Address dst, ns3::aodv::RoutingTableEntry & rt) [member function]
    cls.add_method('LookupValidRoute', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'dst'), param('ns3::aodv::RoutingTableEntry &', 'rt')])
    ## aodv-rtable.h (module 'aodv'): bool ns3::aodv::RoutingTable::MarkLinkAsUnidirectional(ns3::Ipv4Address neighbor, ns3::Time blacklistTimeout) [member function]
    cls.add_method('MarkLinkAsUnidirectional', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'neighbor'), param('ns3::Time', 'blacklistTimeout')])
    ## aodv-rtable.h (module 'aodv'): void ns3::aodv::RoutingTable::Print(ns3::Ptr<ns3::OutputStreamWrapper> stream) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('ns3::Ptr< ns3::OutputStreamWrapper >', 'stream')], 
                   is_const=True)
    ## aodv-rtable.h (module 'aodv'): void ns3::aodv::RoutingTable::Purge() [member function]
    cls.add_method('Purge', 
                   'void', 
                   [])
    ## aodv-rtable.h (module 'aodv'): void ns3::aodv::RoutingTable::SetBadLinkLifetime(ns3::Time t) [member function]
    cls.add_method('SetBadLinkLifetime', 
                   'void', 
                   [param('ns3::Time', 't')])
    ## aodv-rtable.h (module 'aodv'): bool ns3::aodv::RoutingTable::SetEntryState(ns3::Ipv4Address dst, ns3::aodv::RouteFlags state) [member function]
    cls.add_method('SetEntryState', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'dst'), param('ns3::aodv::RouteFlags', 'state')])
    ## aodv-rtable.h (module 'aodv'): bool ns3::aodv::RoutingTable::Update(ns3::aodv::RoutingTableEntry & rt) [member function]
    cls.add_method('Update', 
                   'bool', 
                   [param('ns3::aodv::RoutingTableEntry &', 'rt')])
    return

def register_Ns3AodvRoutingTableEntry_methods(root_module, cls):
    ## aodv-rtable.h (module 'aodv'): ns3::aodv::RoutingTableEntry::RoutingTableEntry(ns3::aodv::RoutingTableEntry const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::aodv::RoutingTableEntry const &', 'arg0')])
    ## aodv-rtable.h (module 'aodv'): ns3::aodv::RoutingTableEntry::RoutingTableEntry(ns3::Ptr<ns3::NetDevice> dev=0, ns3::Ipv4Address dst=ns3::Ipv4Address(), bool vSeqNo=false, uint32_t m_seqNo=0, ns3::Ipv4InterfaceAddress iface=ns3::Ipv4InterfaceAddress(), uint16_t hops=0, ns3::Ipv4Address nextHop=ns3::Ipv4Address(), ns3::Time lifetime=ns3::Simulator::Now( )) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::NetDevice >', 'dev', default_value='0'), param('ns3::Ipv4Address', 'dst', default_value='ns3::Ipv4Address()'), param('bool', 'vSeqNo', default_value='false'), param('uint32_t', 'm_seqNo', default_value='0'), param('ns3::Ipv4InterfaceAddress', 'iface', default_value='ns3::Ipv4InterfaceAddress()'), param('uint16_t', 'hops', default_value='0'), param('ns3::Ipv4Address', 'nextHop', default_value='ns3::Ipv4Address()'), param('ns3::Time', 'lifetime', default_value='ns3::Simulator::Now( )')])
    ## aodv-rtable.h (module 'aodv'): void ns3::aodv::RoutingTableEntry::DeleteAllPrecursors() [member function]
    cls.add_method('DeleteAllPrecursors', 
                   'void', 
                   [])
    ## aodv-rtable.h (module 'aodv'): bool ns3::aodv::RoutingTableEntry::DeletePrecursor(ns3::Ipv4Address id) [member function]
    cls.add_method('DeletePrecursor', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'id')])
    ## aodv-rtable.h (module 'aodv'): ns3::Time ns3::aodv::RoutingTableEntry::GetBlacklistTimeout() const [member function]
    cls.add_method('GetBlacklistTimeout', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## aodv-rtable.h (module 'aodv'): ns3::Ipv4Address ns3::aodv::RoutingTableEntry::GetDestination() const [member function]
    cls.add_method('GetDestination', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## aodv-rtable.h (module 'aodv'): ns3::aodv::RouteFlags ns3::aodv::RoutingTableEntry::GetFlag() const [member function]
    cls.add_method('GetFlag', 
                   'ns3::aodv::RouteFlags', 
                   [], 
                   is_const=True)
    ## aodv-rtable.h (module 'aodv'): uint16_t ns3::aodv::RoutingTableEntry::GetHop() const [member function]
    cls.add_method('GetHop', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## aodv-rtable.h (module 'aodv'): ns3::Ipv4InterfaceAddress ns3::aodv::RoutingTableEntry::GetInterface() const [member function]
    cls.add_method('GetInterface', 
                   'ns3::Ipv4InterfaceAddress', 
                   [], 
                   is_const=True)
    ## aodv-rtable.h (module 'aodv'): ns3::Time ns3::aodv::RoutingTableEntry::GetLifeTime() const [member function]
    cls.add_method('GetLifeTime', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## aodv-rtable.h (module 'aodv'): ns3::Ipv4Address ns3::aodv::RoutingTableEntry::GetNextHop() const [member function]
    cls.add_method('GetNextHop', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## aodv-rtable.h (module 'aodv'): ns3::Ptr<ns3::NetDevice> ns3::aodv::RoutingTableEntry::GetOutputDevice() const [member function]
    cls.add_method('GetOutputDevice', 
                   'ns3::Ptr< ns3::NetDevice >', 
                   [], 
                   is_const=True)
    ## aodv-rtable.h (module 'aodv'): void ns3::aodv::RoutingTableEntry::GetPrecursors(std::vector<ns3::Ipv4Address, std::allocator<ns3::Ipv4Address> > & prec) const [member function]
    cls.add_method('GetPrecursors', 
                   'void', 
                   [param('std::vector< ns3::Ipv4Address > &', 'prec')], 
                   is_const=True)
    ## aodv-rtable.h (module 'aodv'): ns3::Ptr<ns3::Ipv4Route> ns3::aodv::RoutingTableEntry::GetRoute() const [member function]
    cls.add_method('GetRoute', 
                   'ns3::Ptr< ns3::Ipv4Route >', 
                   [], 
                   is_const=True)
    ## aodv-rtable.h (module 'aodv'): uint8_t ns3::aodv::RoutingTableEntry::GetRreqCnt() const [member function]
    cls.add_method('GetRreqCnt', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## aodv-rtable.h (module 'aodv'): uint32_t ns3::aodv::RoutingTableEntry::GetSeqNo() const [member function]
    cls.add_method('GetSeqNo', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## aodv-rtable.h (module 'aodv'): bool ns3::aodv::RoutingTableEntry::GetValidSeqNo() const [member function]
    cls.add_method('GetValidSeqNo', 
                   'bool', 
                   [], 
                   is_const=True)
    ## aodv-rtable.h (module 'aodv'): void ns3::aodv::RoutingTableEntry::IncrementRreqCnt() [member function]
    cls.add_method('IncrementRreqCnt', 
                   'void', 
                   [])
    ## aodv-rtable.h (module 'aodv'): bool ns3::aodv::RoutingTableEntry::InsertPrecursor(ns3::Ipv4Address id) [member function]
    cls.add_method('InsertPrecursor', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'id')])
    ## aodv-rtable.h (module 'aodv'): void ns3::aodv::RoutingTableEntry::Invalidate(ns3::Time badLinkLifetime) [member function]
    cls.add_method('Invalidate', 
                   'void', 
                   [param('ns3::Time', 'badLinkLifetime')])
    ## aodv-rtable.h (module 'aodv'): bool ns3::aodv::RoutingTableEntry::IsPrecursorListEmpty() const [member function]
    cls.add_method('IsPrecursorListEmpty', 
                   'bool', 
                   [], 
                   is_const=True)
    ## aodv-rtable.h (module 'aodv'): bool ns3::aodv::RoutingTableEntry::IsUnidirectional() const [member function]
    cls.add_method('IsUnidirectional', 
                   'bool', 
                   [], 
                   is_const=True)
    ## aodv-rtable.h (module 'aodv'): bool ns3::aodv::RoutingTableEntry::LookupPrecursor(ns3::Ipv4Address id) [member function]
    cls.add_method('LookupPrecursor', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'id')])
    ## aodv-rtable.h (module 'aodv'): void ns3::aodv::RoutingTableEntry::Print(ns3::Ptr<ns3::OutputStreamWrapper> stream) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('ns3::Ptr< ns3::OutputStreamWrapper >', 'stream')], 
                   is_const=True)
    ## aodv-rtable.h (module 'aodv'): void ns3::aodv::RoutingTableEntry::SetBalcklistTimeout(ns3::Time t) [member function]
    cls.add_method('SetBalcklistTimeout', 
                   'void', 
                   [param('ns3::Time', 't')])
    ## aodv-rtable.h (module 'aodv'): void ns3::aodv::RoutingTableEntry::SetFlag(ns3::aodv::RouteFlags flag) [member function]
    cls.add_method('SetFlag', 
                   'void', 
                   [param('ns3::aodv::RouteFlags', 'flag')])
    ## aodv-rtable.h (module 'aodv'): void ns3::aodv::RoutingTableEntry::SetHop(uint16_t hop) [member function]
    cls.add_method('SetHop', 
                   'void', 
                   [param('uint16_t', 'hop')])
    ## aodv-rtable.h (module 'aodv'): void ns3::aodv::RoutingTableEntry::SetInterface(ns3::Ipv4InterfaceAddress iface) [member function]
    cls.add_method('SetInterface', 
                   'void', 
                   [param('ns3::Ipv4InterfaceAddress', 'iface')])
    ## aodv-rtable.h (module 'aodv'): void ns3::aodv::RoutingTableEntry::SetLifeTime(ns3::Time lt) [member function]
    cls.add_method('SetLifeTime', 
                   'void', 
                   [param('ns3::Time', 'lt')])
    ## aodv-rtable.h (module 'aodv'): void ns3::aodv::RoutingTableEntry::SetNextHop(ns3::Ipv4Address nextHop) [member function]
    cls.add_method('SetNextHop', 
                   'void', 
                   [param('ns3::Ipv4Address', 'nextHop')])
    ## aodv-rtable.h (module 'aodv'): void ns3::aodv::RoutingTableEntry::SetOutputDevice(ns3::Ptr<ns3::NetDevice> dev) [member function]
    cls.add_method('SetOutputDevice', 
                   'void', 
                   [param('ns3::Ptr< ns3::NetDevice >', 'dev')])
    ## aodv-rtable.h (module 'aodv'): void ns3::aodv::RoutingTableEntry::SetRoute(ns3::Ptr<ns3::Ipv4Route> r) [member function]
    cls.add_method('SetRoute', 
                   'void', 
                   [param('ns3::Ptr< ns3::Ipv4Route >', 'r')])
    ## aodv-rtable.h (module 'aodv'): void ns3::aodv::RoutingTableEntry::SetRreqCnt(uint8_t n) [member function]
    cls.add_method('SetRreqCnt', 
                   'void', 
                   [param('uint8_t', 'n')])
    ## aodv-rtable.h (module 'aodv'): void ns3::aodv::RoutingTableEntry::SetSeqNo(uint32_t sn) [member function]
    cls.add_method('SetSeqNo', 
                   'void', 
                   [param('uint32_t', 'sn')])
    ## aodv-rtable.h (module 'aodv'): void ns3::aodv::RoutingTableEntry::SetUnidirectional(bool u) [member function]
    cls.add_method('SetUnidirectional', 
                   'void', 
                   [param('bool', 'u')])
    ## aodv-rtable.h (module 'aodv'): void ns3::aodv::RoutingTableEntry::SetValidSeqNo(bool s) [member function]
    cls.add_method('SetValidSeqNo', 
                   'void', 
                   [param('bool', 's')])
    ## aodv-rtable.h (module 'aodv'): ns3::aodv::RoutingTableEntry::m_ackTimer [variable]
    cls.add_instance_attribute('m_ackTimer', 'ns3::Timer', is_const=False)
    return

def register_Ns3AodvRrepAckHeader_methods(root_module, cls):
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    ## aodv-packet.h (module 'aodv'): ns3::aodv::RrepAckHeader::RrepAckHeader(ns3::aodv::RrepAckHeader const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::aodv::RrepAckHeader const &', 'arg0')])
    ## aodv-packet.h (module 'aodv'): ns3::aodv::RrepAckHeader::RrepAckHeader() [constructor]
    cls.add_constructor([])
    ## aodv-packet.h (module 'aodv'): uint32_t ns3::aodv::RrepAckHeader::Deserialize(ns3::Buffer::Iterator start) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_virtual=True)
    ## aodv-packet.h (module 'aodv'): ns3::TypeId ns3::aodv::RrepAckHeader::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## aodv-packet.h (module 'aodv'): uint32_t ns3::aodv::RrepAckHeader::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## aodv-packet.h (module 'aodv'): static ns3::TypeId ns3::aodv::RrepAckHeader::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## aodv-packet.h (module 'aodv'): void ns3::aodv::RrepAckHeader::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## aodv-packet.h (module 'aodv'): void ns3::aodv::RrepAckHeader::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True, is_virtual=True)
    return

def register_Ns3AodvRrepHeader_methods(root_module, cls):
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    ## aodv-packet.h (module 'aodv'): ns3::aodv::RrepHeader::RrepHeader(ns3::aodv::RrepHeader const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::aodv::RrepHeader const &', 'arg0')])
    ## aodv-packet.h (module 'aodv'): ns3::aodv::RrepHeader::RrepHeader(uint8_t prefixSize=0, uint8_t hopCount=0, ns3::Ipv4Address dst=ns3::Ipv4Address(), uint32_t dstSeqNo=0, ns3::Ipv4Address origin=ns3::Ipv4Address(), ns3::Time lifetime=ns3::MilliSeconds( )) [constructor]
    cls.add_constructor([param('uint8_t', 'prefixSize', default_value='0'), param('uint8_t', 'hopCount', default_value='0'), param('ns3::Ipv4Address', 'dst', default_value='ns3::Ipv4Address()'), param('uint32_t', 'dstSeqNo', default_value='0'), param('ns3::Ipv4Address', 'origin', default_value='ns3::Ipv4Address()'), param('ns3::Time', 'lifetime', default_value='ns3::MilliSeconds(0)')])
    ## aodv-packet.h (module 'aodv'): uint32_t ns3::aodv::RrepHeader::Deserialize(ns3::Buffer::Iterator start) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_virtual=True)
    ## aodv-packet.h (module 'aodv'): bool ns3::aodv::RrepHeader::GetAckRequired() const [member function]
    cls.add_method('GetAckRequired', 
                   'bool', 
                   [], 
                   is_const=True)
    ## aodv-packet.h (module 'aodv'): ns3::Ipv4Address ns3::aodv::RrepHeader::GetDst() const [member function]
    cls.add_method('GetDst', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## aodv-packet.h (module 'aodv'): uint32_t ns3::aodv::RrepHeader::GetDstSeqno() const [member function]
    cls.add_method('GetDstSeqno', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## aodv-packet.h (module 'aodv'): uint8_t ns3::aodv::RrepHeader::GetHopCount() const [member function]
    cls.add_method('GetHopCount', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## aodv-packet.h (module 'aodv'): ns3::TypeId ns3::aodv::RrepHeader::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## aodv-packet.h (module 'aodv'): ns3::Time ns3::aodv::RrepHeader::GetLifeTime() const [member function]
    cls.add_method('GetLifeTime', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## aodv-packet.h (module 'aodv'): ns3::Ipv4Address ns3::aodv::RrepHeader::GetOrigin() const [member function]
    cls.add_method('GetOrigin', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## aodv-packet.h (module 'aodv'): uint8_t ns3::aodv::RrepHeader::GetPrefixSize() const [member function]
    cls.add_method('GetPrefixSize', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## aodv-packet.h (module 'aodv'): uint32_t ns3::aodv::RrepHeader::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## aodv-packet.h (module 'aodv'): static ns3::TypeId ns3::aodv::RrepHeader::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## aodv-packet.h (module 'aodv'): void ns3::aodv::RrepHeader::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## aodv-packet.h (module 'aodv'): void ns3::aodv::RrepHeader::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True, is_virtual=True)
    ## aodv-packet.h (module 'aodv'): void ns3::aodv::RrepHeader::SetAckRequired(bool f) [member function]
    cls.add_method('SetAckRequired', 
                   'void', 
                   [param('bool', 'f')])
    ## aodv-packet.h (module 'aodv'): void ns3::aodv::RrepHeader::SetDst(ns3::Ipv4Address a) [member function]
    cls.add_method('SetDst', 
                   'void', 
                   [param('ns3::Ipv4Address', 'a')])
    ## aodv-packet.h (module 'aodv'): void ns3::aodv::RrepHeader::SetDstSeqno(uint32_t s) [member function]
    cls.add_method('SetDstSeqno', 
                   'void', 
                   [param('uint32_t', 's')])
    ## aodv-packet.h (module 'aodv'): void ns3::aodv::RrepHeader::SetHello(ns3::Ipv4Address src, uint32_t srcSeqNo, ns3::Time lifetime) [member function]
    cls.add_method('SetHello', 
                   'void', 
                   [param('ns3::Ipv4Address', 'src'), param('uint32_t', 'srcSeqNo'), param('ns3::Time', 'lifetime')])
    ## aodv-packet.h (module 'aodv'): void ns3::aodv::RrepHeader::SetHopCount(uint8_t count) [member function]
    cls.add_method('SetHopCount', 
                   'void', 
                   [param('uint8_t', 'count')])
    ## aodv-packet.h (module 'aodv'): void ns3::aodv::RrepHeader::SetLifeTime(ns3::Time t) [member function]
    cls.add_method('SetLifeTime', 
                   'void', 
                   [param('ns3::Time', 't')])
    ## aodv-packet.h (module 'aodv'): void ns3::aodv::RrepHeader::SetOrigin(ns3::Ipv4Address a) [member function]
    cls.add_method('SetOrigin', 
                   'void', 
                   [param('ns3::Ipv4Address', 'a')])
    ## aodv-packet.h (module 'aodv'): void ns3::aodv::RrepHeader::SetPrefixSize(uint8_t sz) [member function]
    cls.add_method('SetPrefixSize', 
                   'void', 
                   [param('uint8_t', 'sz')])
    return

def register_Ns3AodvRreqHeader_methods(root_module, cls):
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    ## aodv-packet.h (module 'aodv'): ns3::aodv::RreqHeader::RreqHeader(ns3::aodv::RreqHeader const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::aodv::RreqHeader const &', 'arg0')])
    ## aodv-packet.h (module 'aodv'): ns3::aodv::RreqHeader::RreqHeader(uint8_t flags=0, uint8_t reserved=0, uint8_t hopCount=0, uint32_t requestID=0, ns3::Ipv4Address dst=ns3::Ipv4Address(), uint32_t dstSeqNo=0, ns3::Ipv4Address origin=ns3::Ipv4Address(), uint32_t originSeqNo=0) [constructor]
    cls.add_constructor([param('uint8_t', 'flags', default_value='0'), param('uint8_t', 'reserved', default_value='0'), param('uint8_t', 'hopCount', default_value='0'), param('uint32_t', 'requestID', default_value='0'), param('ns3::Ipv4Address', 'dst', default_value='ns3::Ipv4Address()'), param('uint32_t', 'dstSeqNo', default_value='0'), param('ns3::Ipv4Address', 'origin', default_value='ns3::Ipv4Address()'), param('uint32_t', 'originSeqNo', default_value='0')])
    ## aodv-packet.h (module 'aodv'): uint32_t ns3::aodv::RreqHeader::Deserialize(ns3::Buffer::Iterator start) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_virtual=True)
    ## aodv-packet.h (module 'aodv'): bool ns3::aodv::RreqHeader::GetDestinationOnly() const [member function]
    cls.add_method('GetDestinationOnly', 
                   'bool', 
                   [], 
                   is_const=True)
    ## aodv-packet.h (module 'aodv'): ns3::Ipv4Address ns3::aodv::RreqHeader::GetDst() const [member function]
    cls.add_method('GetDst', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## aodv-packet.h (module 'aodv'): uint32_t ns3::aodv::RreqHeader::GetDstSeqno() const [member function]
    cls.add_method('GetDstSeqno', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## aodv-packet.h (module 'aodv'): bool ns3::aodv::RreqHeader::GetGratiousRrep() const [member function]
    cls.add_method('GetGratiousRrep', 
                   'bool', 
                   [], 
                   is_const=True)
    ## aodv-packet.h (module 'aodv'): uint8_t ns3::aodv::RreqHeader::GetHopCount() const [member function]
    cls.add_method('GetHopCount', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## aodv-packet.h (module 'aodv'): uint32_t ns3::aodv::RreqHeader::GetId() const [member function]
    cls.add_method('GetId', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## aodv-packet.h (module 'aodv'): ns3::TypeId ns3::aodv::RreqHeader::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## aodv-packet.h (module 'aodv'): ns3::Ipv4Address ns3::aodv::RreqHeader::GetOrigin() const [member function]
    cls.add_method('GetOrigin', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## aodv-packet.h (module 'aodv'): uint32_t ns3::aodv::RreqHeader::GetOriginSeqno() const [member function]
    cls.add_method('GetOriginSeqno', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## aodv-packet.h (module 'aodv'): uint32_t ns3::aodv::RreqHeader::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## aodv-packet.h (module 'aodv'): static ns3::TypeId ns3::aodv::RreqHeader::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## aodv-packet.h (module 'aodv'): bool ns3::aodv::RreqHeader::GetUnknownSeqno() const [member function]
    cls.add_method('GetUnknownSeqno', 
                   'bool', 
                   [], 
                   is_const=True)
    ## aodv-packet.h (module 'aodv'): void ns3::aodv::RreqHeader::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## aodv-packet.h (module 'aodv'): void ns3::aodv::RreqHeader::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True, is_virtual=True)
    ## aodv-packet.h (module 'aodv'): void ns3::aodv::RreqHeader::SetDestinationOnly(bool f) [member function]
    cls.add_method('SetDestinationOnly', 
                   'void', 
                   [param('bool', 'f')])
    ## aodv-packet.h (module 'aodv'): void ns3::aodv::RreqHeader::SetDst(ns3::Ipv4Address a) [member function]
    cls.add_method('SetDst', 
                   'void', 
                   [param('ns3::Ipv4Address', 'a')])
    ## aodv-packet.h (module 'aodv'): void ns3::aodv::RreqHeader::SetDstSeqno(uint32_t s) [member function]
    cls.add_method('SetDstSeqno', 
                   'void', 
                   [param('uint32_t', 's')])
    ## aodv-packet.h (module 'aodv'): void ns3::aodv::RreqHeader::SetGratiousRrep(bool f) [member function]
    cls.add_method('SetGratiousRrep', 
                   'void', 
                   [param('bool', 'f')])
    ## aodv-packet.h (module 'aodv'): void ns3::aodv::RreqHeader::SetHopCount(uint8_t count) [member function]
    cls.add_method('SetHopCount', 
                   'void', 
                   [param('uint8_t', 'count')])
    ## aodv-packet.h (module 'aodv'): void ns3::aodv::RreqHeader::SetId(uint32_t id) [member function]
    cls.add_method('SetId', 
                   'void', 
                   [param('uint32_t', 'id')])
    ## aodv-packet.h (module 'aodv'): void ns3::aodv::RreqHeader::SetOrigin(ns3::Ipv4Address a) [member function]
    cls.add_method('SetOrigin', 
                   'void', 
                   [param('ns3::Ipv4Address', 'a')])
    ## aodv-packet.h (module 'aodv'): void ns3::aodv::RreqHeader::SetOriginSeqno(uint32_t s) [member function]
    cls.add_method('SetOriginSeqno', 
                   'void', 
                   [param('uint32_t', 's')])
    ## aodv-packet.h (module 'aodv'): void ns3::aodv::RreqHeader::SetUnknownSeqno(bool f) [member function]
    cls.add_method('SetUnknownSeqno', 
                   'void', 
                   [param('bool', 'f')])
    return

def register_Ns3AodvTypeHeader_methods(root_module, cls):
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    ## aodv-packet.h (module 'aodv'): ns3::aodv::TypeHeader::TypeHeader(ns3::aodv::TypeHeader const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::aodv::TypeHeader const &', 'arg0')])
    ## aodv-packet.h (module 'aodv'): ns3::aodv::TypeHeader::TypeHeader(ns3::aodv::MessageType t) [constructor]
    cls.add_constructor([param('ns3::aodv::MessageType', 't')])
    ## aodv-packet.h (module 'aodv'): uint32_t ns3::aodv::TypeHeader::Deserialize(ns3::Buffer::Iterator start) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_virtual=True)
    ## aodv-packet.h (module 'aodv'): ns3::aodv::MessageType ns3::aodv::TypeHeader::Get() const [member function]
    cls.add_method('Get', 
                   'ns3::aodv::MessageType', 
                   [], 
                   is_const=True)
    ## aodv-packet.h (module 'aodv'): ns3::TypeId ns3::aodv::TypeHeader::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## aodv-packet.h (module 'aodv'): uint32_t ns3::aodv::TypeHeader::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## aodv-packet.h (module 'aodv'): static ns3::TypeId ns3::aodv::TypeHeader::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## aodv-packet.h (module 'aodv'): bool ns3::aodv::TypeHeader::IsValid() const [member function]
    cls.add_method('IsValid', 
                   'bool', 
                   [], 
                   is_const=True)
    ## aodv-packet.h (module 'aodv'): void ns3::aodv::TypeHeader::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## aodv-packet.h (module 'aodv'): void ns3::aodv::TypeHeader::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True, is_virtual=True)
    return

def register_Ns3DsdvDsdvHeader_methods(root_module, cls):
    cls.add_output_stream_operator()
    ## dsdv-packet.h (module 'dsdv'): ns3::dsdv::DsdvHeader::DsdvHeader(ns3::dsdv::DsdvHeader const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsdv::DsdvHeader const &', 'arg0')])
    ## dsdv-packet.h (module 'dsdv'): ns3::dsdv::DsdvHeader::DsdvHeader(ns3::Ipv4Address dst=ns3::Ipv4Address(), uint32_t hopcount=0, uint32_t dstSeqNo=0) [constructor]
    cls.add_constructor([param('ns3::Ipv4Address', 'dst', default_value='ns3::Ipv4Address()'), param('uint32_t', 'hopcount', default_value='0'), param('uint32_t', 'dstSeqNo', default_value='0')])
    ## dsdv-packet.h (module 'dsdv'): uint32_t ns3::dsdv::DsdvHeader::Deserialize(ns3::Buffer::Iterator start) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_virtual=True)
    ## dsdv-packet.h (module 'dsdv'): ns3::Ipv4Address ns3::dsdv::DsdvHeader::GetDst() const [member function]
    cls.add_method('GetDst', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## dsdv-packet.h (module 'dsdv'): uint32_t ns3::dsdv::DsdvHeader::GetDstSeqno() const [member function]
    cls.add_method('GetDstSeqno', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## dsdv-packet.h (module 'dsdv'): uint32_t ns3::dsdv::DsdvHeader::GetHopCount() const [member function]
    cls.add_method('GetHopCount', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## dsdv-packet.h (module 'dsdv'): ns3::TypeId ns3::dsdv::DsdvHeader::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsdv-packet.h (module 'dsdv'): uint32_t ns3::dsdv::DsdvHeader::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsdv-packet.h (module 'dsdv'): static ns3::TypeId ns3::dsdv::DsdvHeader::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## dsdv-packet.h (module 'dsdv'): void ns3::dsdv::DsdvHeader::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## dsdv-packet.h (module 'dsdv'): void ns3::dsdv::DsdvHeader::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True, is_virtual=True)
    ## dsdv-packet.h (module 'dsdv'): void ns3::dsdv::DsdvHeader::SetDst(ns3::Ipv4Address destination) [member function]
    cls.add_method('SetDst', 
                   'void', 
                   [param('ns3::Ipv4Address', 'destination')])
    ## dsdv-packet.h (module 'dsdv'): void ns3::dsdv::DsdvHeader::SetDstSeqno(uint32_t sequenceNumber) [member function]
    cls.add_method('SetDstSeqno', 
                   'void', 
                   [param('uint32_t', 'sequenceNumber')])
    ## dsdv-packet.h (module 'dsdv'): void ns3::dsdv::DsdvHeader::SetHopCount(uint32_t hopCount) [member function]
    cls.add_method('SetHopCount', 
                   'void', 
                   [param('uint32_t', 'hopCount')])
    return

def register_Ns3DsdvPacketQueue_methods(root_module, cls):
    ## dsdv-packet-queue.h (module 'dsdv'): ns3::dsdv::PacketQueue::PacketQueue(ns3::dsdv::PacketQueue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsdv::PacketQueue const &', 'arg0')])
    ## dsdv-packet-queue.h (module 'dsdv'): ns3::dsdv::PacketQueue::PacketQueue() [constructor]
    cls.add_constructor([])
    ## dsdv-packet-queue.h (module 'dsdv'): bool ns3::dsdv::PacketQueue::Dequeue(ns3::Ipv4Address dst, ns3::dsdv::QueueEntry & entry) [member function]
    cls.add_method('Dequeue', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'dst'), param('ns3::dsdv::QueueEntry &', 'entry')])
    ## dsdv-packet-queue.h (module 'dsdv'): void ns3::dsdv::PacketQueue::DropPacketWithDst(ns3::Ipv4Address dst) [member function]
    cls.add_method('DropPacketWithDst', 
                   'void', 
                   [param('ns3::Ipv4Address', 'dst')])
    ## dsdv-packet-queue.h (module 'dsdv'): bool ns3::dsdv::PacketQueue::Enqueue(ns3::dsdv::QueueEntry & entry) [member function]
    cls.add_method('Enqueue', 
                   'bool', 
                   [param('ns3::dsdv::QueueEntry &', 'entry')])
    ## dsdv-packet-queue.h (module 'dsdv'): bool ns3::dsdv::PacketQueue::Find(ns3::Ipv4Address dst) [member function]
    cls.add_method('Find', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'dst')])
    ## dsdv-packet-queue.h (module 'dsdv'): uint32_t ns3::dsdv::PacketQueue::GetCountForPacketsWithDst(ns3::Ipv4Address dst) [member function]
    cls.add_method('GetCountForPacketsWithDst', 
                   'uint32_t', 
                   [param('ns3::Ipv4Address', 'dst')])
    ## dsdv-packet-queue.h (module 'dsdv'): uint32_t ns3::dsdv::PacketQueue::GetMaxPacketsPerDst() const [member function]
    cls.add_method('GetMaxPacketsPerDst', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## dsdv-packet-queue.h (module 'dsdv'): uint32_t ns3::dsdv::PacketQueue::GetMaxQueueLen() const [member function]
    cls.add_method('GetMaxQueueLen', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## dsdv-packet-queue.h (module 'dsdv'): ns3::Time ns3::dsdv::PacketQueue::GetQueueTimeout() const [member function]
    cls.add_method('GetQueueTimeout', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## dsdv-packet-queue.h (module 'dsdv'): uint32_t ns3::dsdv::PacketQueue::GetSize() [member function]
    cls.add_method('GetSize', 
                   'uint32_t', 
                   [])
    ## dsdv-packet-queue.h (module 'dsdv'): void ns3::dsdv::PacketQueue::SetMaxPacketsPerDst(uint32_t len) [member function]
    cls.add_method('SetMaxPacketsPerDst', 
                   'void', 
                   [param('uint32_t', 'len')])
    ## dsdv-packet-queue.h (module 'dsdv'): void ns3::dsdv::PacketQueue::SetMaxQueueLen(uint32_t len) [member function]
    cls.add_method('SetMaxQueueLen', 
                   'void', 
                   [param('uint32_t', 'len')])
    ## dsdv-packet-queue.h (module 'dsdv'): void ns3::dsdv::PacketQueue::SetQueueTimeout(ns3::Time t) [member function]
    cls.add_method('SetQueueTimeout', 
                   'void', 
                   [param('ns3::Time', 't')])
    return

def register_Ns3DsdvQueueEntry_methods(root_module, cls):
    cls.add_binary_comparison_operator('==')
    ## dsdv-packet-queue.h (module 'dsdv'): ns3::dsdv::QueueEntry::QueueEntry(ns3::dsdv::QueueEntry const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsdv::QueueEntry const &', 'arg0')])
    ## dsdv-packet-queue.h (module 'dsdv'): ns3::dsdv::QueueEntry::QueueEntry(ns3::Ptr<ns3::Packet const> pa=0, ns3::Ipv4Header const & h=ns3::Ipv4Header(), ns3::Callback<void, ns3::Ptr<ns3::Ipv4Route>, ns3::Ptr<ns3::Packet const>, ns3::Ipv4Header const&, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ucb=ns3::Callback<void, ns3::Ptr<ns3::Ipv4Route>, ns3::Ptr<const ns3::Packet>, const ns3::Ipv4Header&, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty>(), ns3::Callback<void, ns3::Ptr<ns3::Packet const>, ns3::Ipv4Header const&, ns3::Socket::SocketErrno, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ecb=ns3::Callback<void, ns3::Ptr<const ns3::Packet>, const ns3::Ipv4Header&, ns3::Socket::SocketErrno, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty>()) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::Packet const >', 'pa', default_value='0'), param('ns3::Ipv4Header const &', 'h', default_value='ns3::Ipv4Header()'), param('ns3::Callback< void, ns3::Ptr< ns3::Ipv4Route >, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'ucb', default_value='ns3::Callback<void, ns3::Ptr<ns3::Ipv4Route>, ns3::Ptr<const ns3::Packet>, const ns3::Ipv4Header&, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty>()'), param('ns3::Callback< void, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, ns3::Socket::SocketErrno, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'ecb', default_value='ns3::Callback<void, ns3::Ptr<const ns3::Packet>, const ns3::Ipv4Header&, ns3::Socket::SocketErrno, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty>()')])
    ## dsdv-packet-queue.h (module 'dsdv'): ns3::Callback<void, ns3::Ptr<ns3::Packet const>, ns3::Ipv4Header const&, ns3::Socket::SocketErrno, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ns3::dsdv::QueueEntry::GetErrorCallback() const [member function]
    cls.add_method('GetErrorCallback', 
                   'ns3::Callback< void, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, ns3::Socket::SocketErrno, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 
                   [], 
                   is_const=True)
    ## dsdv-packet-queue.h (module 'dsdv'): ns3::Time ns3::dsdv::QueueEntry::GetExpireTime() const [member function]
    cls.add_method('GetExpireTime', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## dsdv-packet-queue.h (module 'dsdv'): ns3::Ipv4Header ns3::dsdv::QueueEntry::GetIpv4Header() const [member function]
    cls.add_method('GetIpv4Header', 
                   'ns3::Ipv4Header', 
                   [], 
                   is_const=True)
    ## dsdv-packet-queue.h (module 'dsdv'): ns3::Ptr<ns3::Packet const> ns3::dsdv::QueueEntry::GetPacket() const [member function]
    cls.add_method('GetPacket', 
                   'ns3::Ptr< ns3::Packet const >', 
                   [], 
                   is_const=True)
    ## dsdv-packet-queue.h (module 'dsdv'): ns3::Callback<void, ns3::Ptr<ns3::Ipv4Route>, ns3::Ptr<ns3::Packet const>, ns3::Ipv4Header const&, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ns3::dsdv::QueueEntry::GetUnicastForwardCallback() const [member function]
    cls.add_method('GetUnicastForwardCallback', 
                   'ns3::Callback< void, ns3::Ptr< ns3::Ipv4Route >, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 
                   [], 
                   is_const=True)
    ## dsdv-packet-queue.h (module 'dsdv'): void ns3::dsdv::QueueEntry::SetErrorCallback(ns3::Callback<void, ns3::Ptr<ns3::Packet const>, ns3::Ipv4Header const&, ns3::Socket::SocketErrno, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ecb) [member function]
    cls.add_method('SetErrorCallback', 
                   'void', 
                   [param('ns3::Callback< void, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, ns3::Socket::SocketErrno, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'ecb')])
    ## dsdv-packet-queue.h (module 'dsdv'): void ns3::dsdv::QueueEntry::SetExpireTime(ns3::Time exp) [member function]
    cls.add_method('SetExpireTime', 
                   'void', 
                   [param('ns3::Time', 'exp')])
    ## dsdv-packet-queue.h (module 'dsdv'): void ns3::dsdv::QueueEntry::SetIpv4Header(ns3::Ipv4Header h) [member function]
    cls.add_method('SetIpv4Header', 
                   'void', 
                   [param('ns3::Ipv4Header', 'h')])
    ## dsdv-packet-queue.h (module 'dsdv'): void ns3::dsdv::QueueEntry::SetPacket(ns3::Ptr<ns3::Packet const> p) [member function]
    cls.add_method('SetPacket', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet const >', 'p')])
    ## dsdv-packet-queue.h (module 'dsdv'): void ns3::dsdv::QueueEntry::SetUnicastForwardCallback(ns3::Callback<void, ns3::Ptr<ns3::Ipv4Route>, ns3::Ptr<ns3::Packet const>, ns3::Ipv4Header const&, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ucb) [member function]
    cls.add_method('SetUnicastForwardCallback', 
                   'void', 
                   [param('ns3::Callback< void, ns3::Ptr< ns3::Ipv4Route >, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'ucb')])
    return

def register_Ns3DsdvRoutingProtocol_methods(root_module, cls):
    ## dsdv-routing-protocol.h (module 'dsdv'): ns3::dsdv::RoutingProtocol::RoutingProtocol(ns3::dsdv::RoutingProtocol const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsdv::RoutingProtocol const &', 'arg0')])
    ## dsdv-routing-protocol.h (module 'dsdv'): ns3::dsdv::RoutingProtocol::RoutingProtocol() [constructor]
    cls.add_constructor([])
    ## dsdv-routing-protocol.h (module 'dsdv'): int64_t ns3::dsdv::RoutingProtocol::AssignStreams(int64_t stream) [member function]
    cls.add_method('AssignStreams', 
                   'int64_t', 
                   [param('int64_t', 'stream')])
    ## dsdv-routing-protocol.h (module 'dsdv'): void ns3::dsdv::RoutingProtocol::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   is_virtual=True)
    ## dsdv-routing-protocol.h (module 'dsdv'): bool ns3::dsdv::RoutingProtocol::GetEnableBufferFlag() const [member function]
    cls.add_method('GetEnableBufferFlag', 
                   'bool', 
                   [], 
                   is_const=True)
    ## dsdv-routing-protocol.h (module 'dsdv'): bool ns3::dsdv::RoutingProtocol::GetEnableRAFlag() const [member function]
    cls.add_method('GetEnableRAFlag', 
                   'bool', 
                   [], 
                   is_const=True)
    ## dsdv-routing-protocol.h (module 'dsdv'): static ns3::TypeId ns3::dsdv::RoutingProtocol::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## dsdv-routing-protocol.h (module 'dsdv'): bool ns3::dsdv::RoutingProtocol::GetWSTFlag() const [member function]
    cls.add_method('GetWSTFlag', 
                   'bool', 
                   [], 
                   is_const=True)
    ## dsdv-routing-protocol.h (module 'dsdv'): void ns3::dsdv::RoutingProtocol::NotifyAddAddress(uint32_t interface, ns3::Ipv4InterfaceAddress address) [member function]
    cls.add_method('NotifyAddAddress', 
                   'void', 
                   [param('uint32_t', 'interface'), param('ns3::Ipv4InterfaceAddress', 'address')], 
                   is_virtual=True)
    ## dsdv-routing-protocol.h (module 'dsdv'): void ns3::dsdv::RoutingProtocol::NotifyInterfaceDown(uint32_t interface) [member function]
    cls.add_method('NotifyInterfaceDown', 
                   'void', 
                   [param('uint32_t', 'interface')], 
                   is_virtual=True)
    ## dsdv-routing-protocol.h (module 'dsdv'): void ns3::dsdv::RoutingProtocol::NotifyInterfaceUp(uint32_t interface) [member function]
    cls.add_method('NotifyInterfaceUp', 
                   'void', 
                   [param('uint32_t', 'interface')], 
                   is_virtual=True)
    ## dsdv-routing-protocol.h (module 'dsdv'): void ns3::dsdv::RoutingProtocol::NotifyRemoveAddress(uint32_t interface, ns3::Ipv4InterfaceAddress address) [member function]
    cls.add_method('NotifyRemoveAddress', 
                   'void', 
                   [param('uint32_t', 'interface'), param('ns3::Ipv4InterfaceAddress', 'address')], 
                   is_virtual=True)
    ## dsdv-routing-protocol.h (module 'dsdv'): void ns3::dsdv::RoutingProtocol::PrintRoutingTable(ns3::Ptr<ns3::OutputStreamWrapper> stream) const [member function]
    cls.add_method('PrintRoutingTable', 
                   'void', 
                   [param('ns3::Ptr< ns3::OutputStreamWrapper >', 'stream')], 
                   is_const=True, is_virtual=True)
    ## dsdv-routing-protocol.h (module 'dsdv'): bool ns3::dsdv::RoutingProtocol::RouteInput(ns3::Ptr<ns3::Packet const> p, ns3::Ipv4Header const & header, ns3::Ptr<const ns3::NetDevice> idev, ns3::Callback<void, ns3::Ptr<ns3::Ipv4Route>, ns3::Ptr<ns3::Packet const>, ns3::Ipv4Header const&, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ucb, ns3::Callback<void,ns3::Ptr<ns3::Ipv4MulticastRoute>,ns3::Ptr<const ns3::Packet>,const ns3::Ipv4Header&,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty> mcb, ns3::Callback<void,ns3::Ptr<const ns3::Packet>,const ns3::Ipv4Header&,unsigned int,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty> lcb, ns3::Callback<void, ns3::Ptr<ns3::Packet const>, ns3::Ipv4Header const&, ns3::Socket::SocketErrno, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ecb) [member function]
    cls.add_method('RouteInput', 
                   'bool', 
                   [param('ns3::Ptr< ns3::Packet const >', 'p'), param('ns3::Ipv4Header const &', 'header'), param('ns3::Ptr< ns3::NetDevice const >', 'idev'), param('ns3::Callback< void, ns3::Ptr< ns3::Ipv4Route >, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'ucb'), param('ns3::Callback< void, ns3::Ptr< ns3::Ipv4MulticastRoute >, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'mcb'), param('ns3::Callback< void, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, unsigned int, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'lcb'), param('ns3::Callback< void, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, ns3::Socket::SocketErrno, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'ecb')], 
                   is_virtual=True)
    ## dsdv-routing-protocol.h (module 'dsdv'): ns3::Ptr<ns3::Ipv4Route> ns3::dsdv::RoutingProtocol::RouteOutput(ns3::Ptr<ns3::Packet> p, ns3::Ipv4Header const & header, ns3::Ptr<ns3::NetDevice> oif, ns3::Socket::SocketErrno & sockerr) [member function]
    cls.add_method('RouteOutput', 
                   'ns3::Ptr< ns3::Ipv4Route >', 
                   [param('ns3::Ptr< ns3::Packet >', 'p'), param('ns3::Ipv4Header const &', 'header'), param('ns3::Ptr< ns3::NetDevice >', 'oif'), param('ns3::Socket::SocketErrno &', 'sockerr')], 
                   is_virtual=True)
    ## dsdv-routing-protocol.h (module 'dsdv'): void ns3::dsdv::RoutingProtocol::SetEnableBufferFlag(bool f) [member function]
    cls.add_method('SetEnableBufferFlag', 
                   'void', 
                   [param('bool', 'f')])
    ## dsdv-routing-protocol.h (module 'dsdv'): void ns3::dsdv::RoutingProtocol::SetEnableRAFlag(bool f) [member function]
    cls.add_method('SetEnableRAFlag', 
                   'void', 
                   [param('bool', 'f')])
    ## dsdv-routing-protocol.h (module 'dsdv'): void ns3::dsdv::RoutingProtocol::SetIpv4(ns3::Ptr<ns3::Ipv4> ipv4) [member function]
    cls.add_method('SetIpv4', 
                   'void', 
                   [param('ns3::Ptr< ns3::Ipv4 >', 'ipv4')], 
                   is_virtual=True)
    ## dsdv-routing-protocol.h (module 'dsdv'): void ns3::dsdv::RoutingProtocol::SetWSTFlag(bool f) [member function]
    cls.add_method('SetWSTFlag', 
                   'void', 
                   [param('bool', 'f')])
    ## dsdv-routing-protocol.h (module 'dsdv'): ns3::dsdv::RoutingProtocol::DSDV_PORT [variable]
    cls.add_static_attribute('DSDV_PORT', 'uint32_t const', is_const=True)
    return

def register_Ns3DsdvRoutingTable_methods(root_module, cls):
    ## dsdv-rtable.h (module 'dsdv'): ns3::dsdv::RoutingTable::RoutingTable(ns3::dsdv::RoutingTable const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsdv::RoutingTable const &', 'arg0')])
    ## dsdv-rtable.h (module 'dsdv'): ns3::dsdv::RoutingTable::RoutingTable() [constructor]
    cls.add_constructor([])
    ## dsdv-rtable.h (module 'dsdv'): bool ns3::dsdv::RoutingTable::AddIpv4Event(ns3::Ipv4Address address, ns3::EventId id) [member function]
    cls.add_method('AddIpv4Event', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'address'), param('ns3::EventId', 'id')])
    ## dsdv-rtable.h (module 'dsdv'): bool ns3::dsdv::RoutingTable::AddRoute(ns3::dsdv::RoutingTableEntry & r) [member function]
    cls.add_method('AddRoute', 
                   'bool', 
                   [param('ns3::dsdv::RoutingTableEntry &', 'r')])
    ## dsdv-rtable.h (module 'dsdv'): bool ns3::dsdv::RoutingTable::AnyRunningEvent(ns3::Ipv4Address address) [member function]
    cls.add_method('AnyRunningEvent', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'address')])
    ## dsdv-rtable.h (module 'dsdv'): void ns3::dsdv::RoutingTable::Clear() [member function]
    cls.add_method('Clear', 
                   'void', 
                   [])
    ## dsdv-rtable.h (module 'dsdv'): void ns3::dsdv::RoutingTable::DeleteAllRoutesFromInterface(ns3::Ipv4InterfaceAddress iface) [member function]
    cls.add_method('DeleteAllRoutesFromInterface', 
                   'void', 
                   [param('ns3::Ipv4InterfaceAddress', 'iface')])
    ## dsdv-rtable.h (module 'dsdv'): bool ns3::dsdv::RoutingTable::DeleteIpv4Event(ns3::Ipv4Address address) [member function]
    cls.add_method('DeleteIpv4Event', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'address')])
    ## dsdv-rtable.h (module 'dsdv'): bool ns3::dsdv::RoutingTable::DeleteRoute(ns3::Ipv4Address dst) [member function]
    cls.add_method('DeleteRoute', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'dst')])
    ## dsdv-rtable.h (module 'dsdv'): bool ns3::dsdv::RoutingTable::ForceDeleteIpv4Event(ns3::Ipv4Address address) [member function]
    cls.add_method('ForceDeleteIpv4Event', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'address')])
    ## dsdv-rtable.h (module 'dsdv'): ns3::EventId ns3::dsdv::RoutingTable::GetEventId(ns3::Ipv4Address address) [member function]
    cls.add_method('GetEventId', 
                   'ns3::EventId', 
                   [param('ns3::Ipv4Address', 'address')])
    ## dsdv-rtable.h (module 'dsdv'): void ns3::dsdv::RoutingTable::GetListOfAllRoutes(std::map<ns3::Ipv4Address, ns3::dsdv::RoutingTableEntry, std::less<ns3::Ipv4Address>, std::allocator<std::pair<ns3::Ipv4Address const, ns3::dsdv::RoutingTableEntry> > > & allRoutes) [member function]
    cls.add_method('GetListOfAllRoutes', 
                   'void', 
                   [param('std::map< ns3::Ipv4Address, ns3::dsdv::RoutingTableEntry > &', 'allRoutes')])
    ## dsdv-rtable.h (module 'dsdv'): void ns3::dsdv::RoutingTable::GetListOfDestinationWithNextHop(ns3::Ipv4Address nxtHp, std::map<ns3::Ipv4Address, ns3::dsdv::RoutingTableEntry, std::less<ns3::Ipv4Address>, std::allocator<std::pair<ns3::Ipv4Address const, ns3::dsdv::RoutingTableEntry> > > & dstList) [member function]
    cls.add_method('GetListOfDestinationWithNextHop', 
                   'void', 
                   [param('ns3::Ipv4Address', 'nxtHp'), param('std::map< ns3::Ipv4Address, ns3::dsdv::RoutingTableEntry > &', 'dstList')])
    ## dsdv-rtable.h (module 'dsdv'): ns3::Time ns3::dsdv::RoutingTable::Getholddowntime() const [member function]
    cls.add_method('Getholddowntime', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## dsdv-rtable.h (module 'dsdv'): bool ns3::dsdv::RoutingTable::LookupRoute(ns3::Ipv4Address dst, ns3::dsdv::RoutingTableEntry & rt) [member function]
    cls.add_method('LookupRoute', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'dst'), param('ns3::dsdv::RoutingTableEntry &', 'rt')])
    ## dsdv-rtable.h (module 'dsdv'): bool ns3::dsdv::RoutingTable::LookupRoute(ns3::Ipv4Address id, ns3::dsdv::RoutingTableEntry & rt, bool forRouteInput) [member function]
    cls.add_method('LookupRoute', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'id'), param('ns3::dsdv::RoutingTableEntry &', 'rt'), param('bool', 'forRouteInput')])
    ## dsdv-rtable.h (module 'dsdv'): void ns3::dsdv::RoutingTable::Print(ns3::Ptr<ns3::OutputStreamWrapper> stream) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('ns3::Ptr< ns3::OutputStreamWrapper >', 'stream')], 
                   is_const=True)
    ## dsdv-rtable.h (module 'dsdv'): void ns3::dsdv::RoutingTable::Purge(std::map<ns3::Ipv4Address, ns3::dsdv::RoutingTableEntry, std::less<ns3::Ipv4Address>, std::allocator<std::pair<ns3::Ipv4Address const, ns3::dsdv::RoutingTableEntry> > > & removedAddresses) [member function]
    cls.add_method('Purge', 
                   'void', 
                   [param('std::map< ns3::Ipv4Address, ns3::dsdv::RoutingTableEntry > &', 'removedAddresses')])
    ## dsdv-rtable.h (module 'dsdv'): uint32_t ns3::dsdv::RoutingTable::RoutingTableSize() [member function]
    cls.add_method('RoutingTableSize', 
                   'uint32_t', 
                   [])
    ## dsdv-rtable.h (module 'dsdv'): void ns3::dsdv::RoutingTable::Setholddowntime(ns3::Time t) [member function]
    cls.add_method('Setholddowntime', 
                   'void', 
                   [param('ns3::Time', 't')])
    ## dsdv-rtable.h (module 'dsdv'): bool ns3::dsdv::RoutingTable::Update(ns3::dsdv::RoutingTableEntry & rt) [member function]
    cls.add_method('Update', 
                   'bool', 
                   [param('ns3::dsdv::RoutingTableEntry &', 'rt')])
    return

def register_Ns3DsdvRoutingTableEntry_methods(root_module, cls):
    ## dsdv-rtable.h (module 'dsdv'): ns3::dsdv::RoutingTableEntry::RoutingTableEntry(ns3::dsdv::RoutingTableEntry const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsdv::RoutingTableEntry const &', 'arg0')])
    ## dsdv-rtable.h (module 'dsdv'): ns3::dsdv::RoutingTableEntry::RoutingTableEntry(ns3::Ptr<ns3::NetDevice> dev=0, ns3::Ipv4Address dst=ns3::Ipv4Address(), u_int32_t m_seqNo=0, ns3::Ipv4InterfaceAddress iface=ns3::Ipv4InterfaceAddress(), u_int32_t hops=0, ns3::Ipv4Address nextHop=ns3::Ipv4Address(), ns3::Time lifetime=ns3::Simulator::Now( ), ns3::Time SettlingTime=ns3::Simulator::Now( ), bool changedEntries=false) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::NetDevice >', 'dev', default_value='0'), param('ns3::Ipv4Address', 'dst', default_value='ns3::Ipv4Address()'), param('u_int32_t', 'm_seqNo', default_value='0'), param('ns3::Ipv4InterfaceAddress', 'iface', default_value='ns3::Ipv4InterfaceAddress()'), param('u_int32_t', 'hops', default_value='0'), param('ns3::Ipv4Address', 'nextHop', default_value='ns3::Ipv4Address()'), param('ns3::Time', 'lifetime', default_value='ns3::Simulator::Now( )'), param('ns3::Time', 'SettlingTime', default_value='ns3::Simulator::Now( )'), param('bool', 'changedEntries', default_value='false')])
    ## dsdv-rtable.h (module 'dsdv'): ns3::Ipv4Address ns3::dsdv::RoutingTableEntry::GetDestination() const [member function]
    cls.add_method('GetDestination', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## dsdv-rtable.h (module 'dsdv'): bool ns3::dsdv::RoutingTableEntry::GetEntriesChanged() const [member function]
    cls.add_method('GetEntriesChanged', 
                   'bool', 
                   [], 
                   is_const=True)
    ## dsdv-rtable.h (module 'dsdv'): ns3::dsdv::RouteFlags ns3::dsdv::RoutingTableEntry::GetFlag() const [member function]
    cls.add_method('GetFlag', 
                   'ns3::dsdv::RouteFlags', 
                   [], 
                   is_const=True)
    ## dsdv-rtable.h (module 'dsdv'): uint32_t ns3::dsdv::RoutingTableEntry::GetHop() const [member function]
    cls.add_method('GetHop', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## dsdv-rtable.h (module 'dsdv'): ns3::Ipv4InterfaceAddress ns3::dsdv::RoutingTableEntry::GetInterface() const [member function]
    cls.add_method('GetInterface', 
                   'ns3::Ipv4InterfaceAddress', 
                   [], 
                   is_const=True)
    ## dsdv-rtable.h (module 'dsdv'): ns3::Time ns3::dsdv::RoutingTableEntry::GetLifeTime() const [member function]
    cls.add_method('GetLifeTime', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## dsdv-rtable.h (module 'dsdv'): ns3::Ipv4Address ns3::dsdv::RoutingTableEntry::GetNextHop() const [member function]
    cls.add_method('GetNextHop', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## dsdv-rtable.h (module 'dsdv'): ns3::Ptr<ns3::NetDevice> ns3::dsdv::RoutingTableEntry::GetOutputDevice() const [member function]
    cls.add_method('GetOutputDevice', 
                   'ns3::Ptr< ns3::NetDevice >', 
                   [], 
                   is_const=True)
    ## dsdv-rtable.h (module 'dsdv'): ns3::Ptr<ns3::Ipv4Route> ns3::dsdv::RoutingTableEntry::GetRoute() const [member function]
    cls.add_method('GetRoute', 
                   'ns3::Ptr< ns3::Ipv4Route >', 
                   [], 
                   is_const=True)
    ## dsdv-rtable.h (module 'dsdv'): uint32_t ns3::dsdv::RoutingTableEntry::GetSeqNo() const [member function]
    cls.add_method('GetSeqNo', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## dsdv-rtable.h (module 'dsdv'): ns3::Time ns3::dsdv::RoutingTableEntry::GetSettlingTime() const [member function]
    cls.add_method('GetSettlingTime', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## dsdv-rtable.h (module 'dsdv'): void ns3::dsdv::RoutingTableEntry::Print(ns3::Ptr<ns3::OutputStreamWrapper> stream) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('ns3::Ptr< ns3::OutputStreamWrapper >', 'stream')], 
                   is_const=True)
    ## dsdv-rtable.h (module 'dsdv'): void ns3::dsdv::RoutingTableEntry::SetEntriesChanged(bool entriesChanged) [member function]
    cls.add_method('SetEntriesChanged', 
                   'void', 
                   [param('bool', 'entriesChanged')])
    ## dsdv-rtable.h (module 'dsdv'): void ns3::dsdv::RoutingTableEntry::SetFlag(ns3::dsdv::RouteFlags flag) [member function]
    cls.add_method('SetFlag', 
                   'void', 
                   [param('ns3::dsdv::RouteFlags', 'flag')])
    ## dsdv-rtable.h (module 'dsdv'): void ns3::dsdv::RoutingTableEntry::SetHop(uint32_t hopCount) [member function]
    cls.add_method('SetHop', 
                   'void', 
                   [param('uint32_t', 'hopCount')])
    ## dsdv-rtable.h (module 'dsdv'): void ns3::dsdv::RoutingTableEntry::SetInterface(ns3::Ipv4InterfaceAddress iface) [member function]
    cls.add_method('SetInterface', 
                   'void', 
                   [param('ns3::Ipv4InterfaceAddress', 'iface')])
    ## dsdv-rtable.h (module 'dsdv'): void ns3::dsdv::RoutingTableEntry::SetLifeTime(ns3::Time lifeTime) [member function]
    cls.add_method('SetLifeTime', 
                   'void', 
                   [param('ns3::Time', 'lifeTime')])
    ## dsdv-rtable.h (module 'dsdv'): void ns3::dsdv::RoutingTableEntry::SetNextHop(ns3::Ipv4Address nextHop) [member function]
    cls.add_method('SetNextHop', 
                   'void', 
                   [param('ns3::Ipv4Address', 'nextHop')])
    ## dsdv-rtable.h (module 'dsdv'): void ns3::dsdv::RoutingTableEntry::SetOutputDevice(ns3::Ptr<ns3::NetDevice> device) [member function]
    cls.add_method('SetOutputDevice', 
                   'void', 
                   [param('ns3::Ptr< ns3::NetDevice >', 'device')])
    ## dsdv-rtable.h (module 'dsdv'): void ns3::dsdv::RoutingTableEntry::SetRoute(ns3::Ptr<ns3::Ipv4Route> route) [member function]
    cls.add_method('SetRoute', 
                   'void', 
                   [param('ns3::Ptr< ns3::Ipv4Route >', 'route')])
    ## dsdv-rtable.h (module 'dsdv'): void ns3::dsdv::RoutingTableEntry::SetSeqNo(uint32_t sequenceNumber) [member function]
    cls.add_method('SetSeqNo', 
                   'void', 
                   [param('uint32_t', 'sequenceNumber')])
    ## dsdv-rtable.h (module 'dsdv'): void ns3::dsdv::RoutingTableEntry::SetSettlingTime(ns3::Time settlingTime) [member function]
    cls.add_method('SetSettlingTime', 
                   'void', 
                   [param('ns3::Time', 'settlingTime')])
    return

def register_Ns3MbnDuplicatePacketDetection_methods(root_module, cls):
    ## mbn-aodv-dpd.h (module 'mbn-aodv'): ns3::mbn::DuplicatePacketDetection::DuplicatePacketDetection(ns3::mbn::DuplicatePacketDetection const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::mbn::DuplicatePacketDetection const &', 'arg0')])
    ## mbn-aodv-dpd.h (module 'mbn-aodv'): ns3::mbn::DuplicatePacketDetection::DuplicatePacketDetection(ns3::Time lifetime) [constructor]
    cls.add_constructor([param('ns3::Time', 'lifetime')])
    ## mbn-aodv-dpd.h (module 'mbn-aodv'): ns3::Time ns3::mbn::DuplicatePacketDetection::GetLifetime() const [member function]
    cls.add_method('GetLifetime', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## mbn-aodv-dpd.h (module 'mbn-aodv'): bool ns3::mbn::DuplicatePacketDetection::IsDuplicate(ns3::Ptr<ns3::Packet const> p, ns3::Ipv4Header const & header) [member function]
    cls.add_method('IsDuplicate', 
                   'bool', 
                   [param('ns3::Ptr< ns3::Packet const >', 'p'), param('ns3::Ipv4Header const &', 'header')])
    ## mbn-aodv-dpd.h (module 'mbn-aodv'): void ns3::mbn::DuplicatePacketDetection::SetLifetime(ns3::Time lifetime) [member function]
    cls.add_method('SetLifetime', 
                   'void', 
                   [param('ns3::Time', 'lifetime')])
    return

def register_Ns3MbnHelloHeader_methods(root_module, cls):
    cls.add_output_stream_operator()
    ## mbn-aodv-packet.h (module 'mbn-aodv'): ns3::mbn::HelloHeader::HelloHeader(ns3::mbn::HelloHeader const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::mbn::HelloHeader const &', 'arg0')])
    ## mbn-aodv-packet.h (module 'mbn-aodv'): ns3::mbn::HelloHeader::HelloHeader(uint16_t sequenceNumber=0, ns3::mbn::NodeStatus nodeStatus=::ns3::mbn::RN_NODE, ns3::mbn::BnBcn_Indicator bnBcnIndicator=::ns3::mbn::CONVERT_OTHER, ns3::Ipv4Address m_nodeIdentifier=ns3::Ipv4Address(), ns3::Ipv4Address m_associatedBnIdentifier=ns3::Ipv4Address(), ns3::mbn::WeightFunction weightFunction=::ns3::mbn::W_NODE_DEGREE, uint32_t weightValue=0, ns3::mbn::TwoHopBnNeighborSet tset=std::list<ns3::mbn::TwoHopBnNeighborTuple, std::allocator<ns3::mbn::TwoHopBnNeighborTuple> >()) [constructor]
    cls.add_constructor([param('uint16_t', 'sequenceNumber', default_value='0'), param('ns3::mbn::NodeStatus', 'nodeStatus', default_value='::ns3::mbn::RN_NODE'), param('ns3::mbn::BnBcn_Indicator', 'bnBcnIndicator', default_value='::ns3::mbn::CONVERT_OTHER'), param('ns3::Ipv4Address', 'm_nodeIdentifier', default_value='ns3::Ipv4Address()'), param('ns3::Ipv4Address', 'm_associatedBnIdentifier', default_value='ns3::Ipv4Address()'), param('ns3::mbn::WeightFunction', 'weightFunction', default_value='::ns3::mbn::W_NODE_DEGREE'), param('uint32_t', 'weightValue', default_value='0'), param('ns3::mbn::TwoHopBnNeighborSet', 'tset', default_value='std::list<ns3::mbn::TwoHopBnNeighborTuple, std::allocator<ns3::mbn::TwoHopBnNeighborTuple> >()')])
    ## mbn-aodv-packet.h (module 'mbn-aodv'): uint32_t ns3::mbn::HelloHeader::Deserialize(ns3::Buffer::Iterator start) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_virtual=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): ns3::Ipv4Address ns3::mbn::HelloHeader::GetAssociatedBnAddress() const [member function]
    cls.add_method('GetAssociatedBnAddress', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): ns3::mbn::BnBcn_Indicator ns3::mbn::HelloHeader::GetBnBcnIndicator() const [member function]
    cls.add_method('GetBnBcnIndicator', 
                   'ns3::mbn::BnBcn_Indicator', 
                   [], 
                   is_const=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): ns3::TypeId ns3::mbn::HelloHeader::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): uint8_t ns3::mbn::HelloHeader::GetListSize() const [member function]
    cls.add_method('GetListSize', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): uint16_t ns3::mbn::HelloHeader::GetMessageLength() const [member function]
    cls.add_method('GetMessageLength', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): uint16_t ns3::mbn::HelloHeader::GetMessageSequenceNumber() const [member function]
    cls.add_method('GetMessageSequenceNumber', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): ns3::mbn::NodeStatus ns3::mbn::HelloHeader::GetNodeStatus() const [member function]
    cls.add_method('GetNodeStatus', 
                   'ns3::mbn::NodeStatus', 
                   [], 
                   is_const=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): ns3::Ipv4Address ns3::mbn::HelloHeader::GetOriginatorAddress() const [member function]
    cls.add_method('GetOriginatorAddress', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): uint32_t ns3::mbn::HelloHeader::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): ns3::mbn::TwoHopBnNeighborSet ns3::mbn::HelloHeader::GetTwoHopNeighborSet() const [member function]
    cls.add_method('GetTwoHopNeighborSet', 
                   'ns3::mbn::TwoHopBnNeighborSet', 
                   [], 
                   is_const=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): static ns3::TypeId ns3::mbn::HelloHeader::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): uint32_t ns3::mbn::HelloHeader::GetWeightFunction() const [member function]
    cls.add_method('GetWeightFunction', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): uint16_t ns3::mbn::HelloHeader::GetWeightSize() const [member function]
    cls.add_method('GetWeightSize', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): uint32_t ns3::mbn::HelloHeader::GetWeightValue() const [member function]
    cls.add_method('GetWeightValue', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): void ns3::mbn::HelloHeader::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): void ns3::mbn::HelloHeader::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True, is_virtual=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): void ns3::mbn::HelloHeader::SetAssociatedBnAddress(ns3::Ipv4Address associatedBnAddress) [member function]
    cls.add_method('SetAssociatedBnAddress', 
                   'void', 
                   [param('ns3::Ipv4Address', 'associatedBnAddress')])
    ## mbn-aodv-packet.h (module 'mbn-aodv'): void ns3::mbn::HelloHeader::SetBnBcnIndicator(ns3::mbn::BnBcn_Indicator bnBcnIndicator) [member function]
    cls.add_method('SetBnBcnIndicator', 
                   'void', 
                   [param('ns3::mbn::BnBcn_Indicator', 'bnBcnIndicator')])
    ## mbn-aodv-packet.h (module 'mbn-aodv'): void ns3::mbn::HelloHeader::SetListSize(uint8_t listSize) [member function]
    cls.add_method('SetListSize', 
                   'void', 
                   [param('uint8_t', 'listSize')])
    ## mbn-aodv-packet.h (module 'mbn-aodv'): void ns3::mbn::HelloHeader::SetMessageLength(uint16_t length) [member function]
    cls.add_method('SetMessageLength', 
                   'void', 
                   [param('uint16_t', 'length')])
    ## mbn-aodv-packet.h (module 'mbn-aodv'): void ns3::mbn::HelloHeader::SetMessageSequenceNumber(uint16_t seqnum) [member function]
    cls.add_method('SetMessageSequenceNumber', 
                   'void', 
                   [param('uint16_t', 'seqnum')])
    ## mbn-aodv-packet.h (module 'mbn-aodv'): void ns3::mbn::HelloHeader::SetNodeStatus(ns3::mbn::NodeStatus nodeStatus) [member function]
    cls.add_method('SetNodeStatus', 
                   'void', 
                   [param('ns3::mbn::NodeStatus', 'nodeStatus')])
    ## mbn-aodv-packet.h (module 'mbn-aodv'): void ns3::mbn::HelloHeader::SetOriginatorAddress(ns3::Ipv4Address originatorAddress) [member function]
    cls.add_method('SetOriginatorAddress', 
                   'void', 
                   [param('ns3::Ipv4Address', 'originatorAddress')])
    ## mbn-aodv-packet.h (module 'mbn-aodv'): void ns3::mbn::HelloHeader::SetWeightFunction(ns3::mbn::WeightFunction weightFunction) [member function]
    cls.add_method('SetWeightFunction', 
                   'void', 
                   [param('ns3::mbn::WeightFunction', 'weightFunction')])
    ## mbn-aodv-packet.h (module 'mbn-aodv'): void ns3::mbn::HelloHeader::SetWeightSize(uint16_t weightSize) [member function]
    cls.add_method('SetWeightSize', 
                   'void', 
                   [param('uint16_t', 'weightSize')])
    ## mbn-aodv-packet.h (module 'mbn-aodv'): void ns3::mbn::HelloHeader::SetWeightValue(uint32_t weightValue) [member function]
    cls.add_method('SetWeightValue', 
                   'void', 
                   [param('uint32_t', 'weightValue')])
    ## mbn-aodv-packet.h (module 'mbn-aodv'): ns3::mbn::HelloHeader::m_TwoHopBnNeighbors [variable]
    cls.add_instance_attribute('m_TwoHopBnNeighbors', 'ns3::mbn::TwoHopBnNeighborSet', is_const=False)
    return

def register_Ns3MbnIdCache_methods(root_module, cls):
    ## mbn-aodv-id-cache.h (module 'mbn-aodv'): ns3::mbn::IdCache::IdCache(ns3::mbn::IdCache const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::mbn::IdCache const &', 'arg0')])
    ## mbn-aodv-id-cache.h (module 'mbn-aodv'): ns3::mbn::IdCache::IdCache(ns3::Time lifetime) [constructor]
    cls.add_constructor([param('ns3::Time', 'lifetime')])
    ## mbn-aodv-id-cache.h (module 'mbn-aodv'): ns3::Time ns3::mbn::IdCache::GetLifeTime() const [member function]
    cls.add_method('GetLifeTime', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## mbn-aodv-id-cache.h (module 'mbn-aodv'): uint32_t ns3::mbn::IdCache::GetSize() [member function]
    cls.add_method('GetSize', 
                   'uint32_t', 
                   [])
    ## mbn-aodv-id-cache.h (module 'mbn-aodv'): bool ns3::mbn::IdCache::IsDuplicate(ns3::Ipv4Address addr, uint32_t id) [member function]
    cls.add_method('IsDuplicate', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'addr'), param('uint32_t', 'id')])
    ## mbn-aodv-id-cache.h (module 'mbn-aodv'): void ns3::mbn::IdCache::Purge() [member function]
    cls.add_method('Purge', 
                   'void', 
                   [])
    ## mbn-aodv-id-cache.h (module 'mbn-aodv'): void ns3::mbn::IdCache::SetLifetime(ns3::Time lifetime) [member function]
    cls.add_method('SetLifetime', 
                   'void', 
                   [param('ns3::Time', 'lifetime')])
    return

def register_Ns3MbnNeighborPair_methods(root_module, cls):
    cls.add_binary_comparison_operator('<')
    cls.add_binary_comparison_operator('>')
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): ns3::mbn::NeighborPair::NeighborPair() [constructor]
    cls.add_constructor([])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): ns3::mbn::NeighborPair::NeighborPair(ns3::mbn::NeighborPair const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::mbn::NeighborPair const &', 'arg0')])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): ns3::mbn::NeighborPair::neighborFirstIfaceAddr [variable]
    cls.add_instance_attribute('neighborFirstIfaceAddr', 'ns3::Ipv4Address', is_const=False)
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): ns3::mbn::NeighborPair::neighborSecondIfaceAddr [variable]
    cls.add_instance_attribute('neighborSecondIfaceAddr', 'ns3::Ipv4Address', is_const=False)
    return

def register_Ns3MbnNeighborTriple_methods(root_module, cls):
    cls.add_binary_comparison_operator('<')
    cls.add_binary_comparison_operator('>')
    cls.add_output_stream_operator()
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): ns3::mbn::NeighborTriple::NeighborTriple() [constructor]
    cls.add_constructor([])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): ns3::mbn::NeighborTriple::NeighborTriple(ns3::mbn::NeighborTriple const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::mbn::NeighborTriple const &', 'arg0')])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): ns3::mbn::NeighborTriple::neighborCommonIfaceAddr [variable]
    cls.add_instance_attribute('neighborCommonIfaceAddr', 'ns3::Ipv4Address', is_const=False)
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): ns3::mbn::NeighborTriple::neighborOneIfaceAddr [variable]
    cls.add_instance_attribute('neighborOneIfaceAddr', 'ns3::Ipv4Address', is_const=False)
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): ns3::mbn::NeighborTriple::neighborTwoIfaceAddr [variable]
    cls.add_instance_attribute('neighborTwoIfaceAddr', 'ns3::Ipv4Address', is_const=False)
    return

def register_Ns3MbnNeighborTuple_methods(root_module, cls):
    cls.add_binary_comparison_operator('<')
    cls.add_binary_comparison_operator('>')
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): ns3::mbn::NeighborTuple::NeighborTuple(ns3::mbn::NeighborTuple const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::mbn::NeighborTuple const &', 'arg0')])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): ns3::mbn::NeighborTuple::NeighborTuple(ns3::Ipv4Address ip, ns3::Mac48Address mac, ns3::Time expire) [constructor]
    cls.add_constructor([param('ns3::Ipv4Address', 'ip'), param('ns3::Mac48Address', 'mac'), param('ns3::Time', 'expire')])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): ns3::mbn::NeighborTuple::NeighborTuple(ns3::Ipv4Address ip, ns3::Time expire) [constructor]
    cls.add_constructor([param('ns3::Ipv4Address', 'ip'), param('ns3::Time', 'expire')])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): ns3::mbn::NeighborTuple::close [variable]
    cls.add_instance_attribute('close', 'bool', is_const=False)
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): ns3::mbn::NeighborTuple::helloCounter [variable]
    cls.add_instance_attribute('helloCounter', 'uint16_t', is_const=False)
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): ns3::mbn::NeighborTuple::m_expireTime [variable]
    cls.add_instance_attribute('m_expireTime', 'ns3::Time', is_const=False)
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): ns3::mbn::NeighborTuple::m_hardwareAddress [variable]
    cls.add_instance_attribute('m_hardwareAddress', 'ns3::Mac48Address', is_const=False)
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): ns3::mbn::NeighborTuple::neighborAssociatedBN [variable]
    cls.add_instance_attribute('neighborAssociatedBN', 'ns3::Ipv4Address', is_const=False)
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): ns3::mbn::NeighborTuple::neighborBnBcnIndicator [variable]
    cls.add_instance_attribute('neighborBnBcnIndicator', 'ns3::mbn::BnBcn_Indicator', is_const=False)
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): ns3::mbn::NeighborTuple::neighborBnNeighbors [variable]
    cls.add_instance_attribute('neighborBnNeighbors', 'std::list< ns3::mbn::TwoHopBnNeighborTuple >', is_const=False)
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): ns3::mbn::NeighborTuple::neighborClient [variable]
    cls.add_instance_attribute('neighborClient', 'bool', is_const=False)
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): ns3::mbn::NeighborTuple::neighborIfaceAddr [variable]
    cls.add_instance_attribute('neighborIfaceAddr', 'ns3::Ipv4Address', is_const=False)
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): ns3::mbn::NeighborTuple::neighborNodeStatus [variable]
    cls.add_instance_attribute('neighborNodeStatus', 'ns3::mbn::NodeStatus', is_const=False)
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): ns3::mbn::NeighborTuple::neighborWeight [variable]
    cls.add_instance_attribute('neighborWeight', 'uint32_t', is_const=False)
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): ns3::mbn::NeighborTuple::sequenceNumber [variable]
    cls.add_instance_attribute('sequenceNumber', 'uint16_t', is_const=False)
    return

def register_Ns3MbnNeighbors_methods(root_module, cls):
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): ns3::mbn::Neighbors::Neighbors(ns3::mbn::Neighbors const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::mbn::Neighbors const &', 'arg0')])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): ns3::mbn::Neighbors::Neighbors(ns3::Time delay) [constructor]
    cls.add_constructor([param('ns3::Time', 'delay')])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): void ns3::mbn::Neighbors::AddArpCache(ns3::Ptr<ns3::ArpCache> arg0) [member function]
    cls.add_method('AddArpCache', 
                   'void', 
                   [param('ns3::Ptr< ns3::ArpCache >', 'arg0')])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): void ns3::mbn::Neighbors::AddHelloCounter(ns3::mbn::NeighborTuple * nt) [member function]
    cls.add_method('AddHelloCounter', 
                   'void', 
                   [param('ns3::mbn::NeighborTuple *', 'nt')])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): bool ns3::mbn::Neighbors::Are1HopNeighbors(ns3::Ipv4Address const & BNnode_v, ns3::Ipv4Address const & BNnode_w) [member function]
    cls.add_method('Are1HopNeighbors', 
                   'bool', 
                   [param('ns3::Ipv4Address const &', 'BNnode_v'), param('ns3::Ipv4Address const &', 'BNnode_w')])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): bool ns3::mbn::Neighbors::Are2HopNeighbors(ns3::Ipv4Address const & BNnode_v, ns3::Ipv4Address const & BNnode_w) [member function]
    cls.add_method('Are2HopNeighbors', 
                   'bool', 
                   [param('ns3::Ipv4Address const &', 'BNnode_v'), param('ns3::Ipv4Address const &', 'BNnode_w')])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): bool ns3::mbn::Neighbors::AreNeighbors(ns3::mbn::NeighborPair hop_bn, ns3::Ipv4Address neighbor) [member function]
    cls.add_method('AreNeighbors', 
                   'bool', 
                   [param('ns3::mbn::NeighborPair', 'hop_bn'), param('ns3::Ipv4Address', 'neighbor')])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): bool ns3::mbn::Neighbors::BCN2BNRule1() [member function]
    cls.add_method('BCN2BNRule1', 
                   'bool', 
                   [])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): bool ns3::mbn::Neighbors::BCN2BNRule2() [member function]
    cls.add_method('BCN2BNRule2', 
                   'bool', 
                   [])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): void ns3::mbn::Neighbors::Clear() [member function]
    cls.add_method('Clear', 
                   'void', 
                   [])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): void ns3::mbn::Neighbors::DelArpCache(ns3::Ptr<ns3::ArpCache> arg0) [member function]
    cls.add_method('DelArpCache', 
                   'void', 
                   [param('ns3::Ptr< ns3::ArpCache >', 'arg0')])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): void ns3::mbn::Neighbors::EraseAllTwoHopNeighborTuples(ns3::Ipv4Address const & twoHopNeighborAddress) [member function]
    cls.add_method('EraseAllTwoHopNeighborTuples', 
                   'void', 
                   [param('ns3::Ipv4Address const &', 'twoHopNeighborAddress')])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): void ns3::mbn::Neighbors::EraseNeighborTuple(ns3::mbn::NeighborTuple const & neighborTuple) [member function]
    cls.add_method('EraseNeighborTuple', 
                   'void', 
                   [param('ns3::mbn::NeighborTuple const &', 'neighborTuple')])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): void ns3::mbn::Neighbors::EraseNeighborTuple(ns3::Ipv4Address const & mainAddr) [member function]
    cls.add_method('EraseNeighborTuple', 
                   'void', 
                   [param('ns3::Ipv4Address const &', 'mainAddr')])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): void ns3::mbn::Neighbors::EraseTwoHopBnNeighborTuple(ns3::Ipv4Address const & neighbor, ns3::Ipv4Address const & twoHopNeighbor) [member function]
    cls.add_method('EraseTwoHopBnNeighborTuple', 
                   'void', 
                   [param('ns3::Ipv4Address const &', 'neighbor'), param('ns3::Ipv4Address const &', 'twoHopNeighbor')])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): ns3::mbn::NeighborTuple * ns3::mbn::Neighbors::FindNeighborTuple(ns3::Ipv4Address const & mainAddr) [member function]
    cls.add_method('FindNeighborTuple', 
                   'ns3::mbn::NeighborTuple *', 
                   [param('ns3::Ipv4Address const &', 'mainAddr')])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): ns3::mbn::NeighborTuple * ns3::mbn::Neighbors::FindNeighborTuple(ns3::Ipv4Address const & mainAddr, ns3::mbn::NodeStatus nodeStatus) [member function]
    cls.add_method('FindNeighborTuple', 
                   'ns3::mbn::NeighborTuple *', 
                   [param('ns3::Ipv4Address const &', 'mainAddr'), param('ns3::mbn::NodeStatus', 'nodeStatus')])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): ns3::mbn::TwoHopBnNeighborTuple * ns3::mbn::Neighbors::FindTwoHopBnNeighborTuple(ns3::Ipv4Address const & neighbor, ns3::Ipv4Address const & twoHopNeighbor) [member function]
    cls.add_method('FindTwoHopBnNeighborTuple', 
                   'ns3::mbn::TwoHopBnNeighborTuple *', 
                   [param('ns3::Ipv4Address const &', 'neighbor'), param('ns3::Ipv4Address const &', 'twoHopNeighbor')])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): ns3::mbn::TwoHopBnNeighborTuple * ns3::mbn::Neighbors::FindTwoHopBnNeighborTuple(ns3::Ipv4Address const & twoHopNeighbor) [member function]
    cls.add_method('FindTwoHopBnNeighborTuple', 
                   'ns3::mbn::TwoHopBnNeighborTuple *', 
                   [param('ns3::Ipv4Address const &', 'twoHopNeighbor')])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): uint32_t ns3::mbn::Neighbors::GetBCNNeighborhoodSize() [member function]
    cls.add_method('GetBCNNeighborhoodSize', 
                   'uint32_t', 
                   [])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): uint32_t ns3::mbn::Neighbors::GetBNNeighborhoodSize() [member function]
    cls.add_method('GetBNNeighborhoodSize', 
                   'uint32_t', 
                   [])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): ns3::mbn::NeighborTuple * ns3::mbn::Neighbors::GetBestNeighbor(ns3::mbn::NodeStatus nodeStatus) [member function]
    cls.add_method('GetBestNeighbor', 
                   'ns3::mbn::NeighborTuple *', 
                   [param('ns3::mbn::NodeStatus', 'nodeStatus')])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): ns3::mbn::TwoHopBnNeighborSet ns3::mbn::Neighbors::GetBnNeighbors() [member function]
    cls.add_method('GetBnNeighbors', 
                   'ns3::mbn::TwoHopBnNeighborSet', 
                   [])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): ns3::Callback<void, ns3::Ipv4Address, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ns3::mbn::Neighbors::GetCallback() const [member function]
    cls.add_method('GetCallback', 
                   'ns3::Callback< void, ns3::Ipv4Address, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 
                   [], 
                   is_const=True)
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): ns3::mbn::NeighborSet ns3::mbn::Neighbors::GetClients(ns3::mbn::NodeStatus nodeStatus) [member function]
    cls.add_method('GetClients', 
                   'ns3::mbn::NeighborSet', 
                   [param('ns3::mbn::NodeStatus', 'nodeStatus')])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): ns3::mbn::NeighborSet ns3::mbn::Neighbors::GetClients() [member function]
    cls.add_method('GetClients', 
                   'ns3::mbn::NeighborSet', 
                   [])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): ns3::mbn::AddressSet ns3::mbn::Neighbors::GetCommonBN(ns3::mbn::NeighborPair bn_pairs) [member function]
    cls.add_method('GetCommonBN', 
                   'ns3::mbn::AddressSet', 
                   [param('ns3::mbn::NeighborPair', 'bn_pairs')])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): ns3::Time ns3::mbn::Neighbors::GetExpireTime(ns3::Ipv4Address addr) [member function]
    cls.add_method('GetExpireTime', 
                   'ns3::Time', 
                   [param('ns3::Ipv4Address', 'addr')])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): uint32_t ns3::mbn::Neighbors::GetMinHello() [member function]
    cls.add_method('GetMinHello', 
                   'uint32_t', 
                   [])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): ns3::mbn::NeighborSet & ns3::mbn::Neighbors::GetNeighborList() [member function]
    cls.add_method('GetNeighborList', 
                   'ns3::mbn::NeighborSet &', 
                   [])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): uint32_t ns3::mbn::Neighbors::GetNeighborhoodSize() [member function]
    cls.add_method('GetNeighborhoodSize', 
                   'uint32_t', 
                   [])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): uint32_t ns3::mbn::Neighbors::GetNeighborhoodSize(ns3::mbn::NodeStatus nodeStatus) [member function]
    cls.add_method('GetNeighborhoodSize', 
                   'uint32_t', 
                   [param('ns3::mbn::NodeStatus', 'nodeStatus')])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): ns3::mbn::NeighborSet ns3::mbn::Neighbors::GetOneHopNeighbors(ns3::mbn::NodeStatus nodeStatus) [member function]
    cls.add_method('GetOneHopNeighbors', 
                   'ns3::mbn::NeighborSet', 
                   [param('ns3::mbn::NodeStatus', 'nodeStatus')])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): ns3::mbn::NeighborPairs ns3::mbn::Neighbors::GetOneHopPairs(ns3::mbn::NodeStatus set1, ns3::mbn::NodeStatus set2) [member function]
    cls.add_method('GetOneHopPairs', 
                   'ns3::mbn::NeighborPairs', 
                   [param('ns3::mbn::NodeStatus', 'set1'), param('ns3::mbn::NodeStatus', 'set2')])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): uint32_t ns3::mbn::Neighbors::GetRNNeighborhoodSize() [member function]
    cls.add_method('GetRNNeighborhoodSize', 
                   'uint32_t', 
                   [])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): ns3::mbn::AddressSet ns3::mbn::Neighbors::GetTwoHopNeighbors(ns3::Ipv4Address neighbor) [member function]
    cls.add_method('GetTwoHopNeighbors', 
                   'ns3::mbn::AddressSet', 
                   [param('ns3::Ipv4Address', 'neighbor')])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): ns3::Callback<void, ns3::WifiMacHeader const&, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ns3::mbn::Neighbors::GetTxErrorCallback() const [member function]
    cls.add_method('GetTxErrorCallback', 
                   'ns3::Callback< void, ns3::WifiMacHeader const &, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 
                   [], 
                   is_const=True)
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): bool ns3::mbn::Neighbors::HigherWeight(ns3::Ipv4Address neighbor) [member function]
    cls.add_method('HigherWeight', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'neighbor')])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): bool ns3::mbn::Neighbors::HigherWeight(ns3::mbn::NeighborTuple * node) [member function]
    cls.add_method('HigherWeight', 
                   'bool', 
                   [param('ns3::mbn::NeighborTuple *', 'node')])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): void ns3::mbn::Neighbors::InsertNeighborTuple(ns3::mbn::NeighborTuple const & tuple) [member function]
    cls.add_method('InsertNeighborTuple', 
                   'void', 
                   [param('ns3::mbn::NeighborTuple const &', 'tuple')])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): void ns3::mbn::Neighbors::InsertTwoHopNeighborTuple(ns3::Ipv4Address const oneHopNeighbor, ns3::mbn::TwoHopBnNeighborTuple const & twoHopNeighbor) [member function]
    cls.add_method('InsertTwoHopNeighborTuple', 
                   'void', 
                   [param('ns3::Ipv4Address const', 'oneHopNeighbor'), param('ns3::mbn::TwoHopBnNeighborTuple const &', 'twoHopNeighbor')])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): ns3::mbn::AddressSet ns3::mbn::Neighbors::Intersection(ns3::mbn::AddressSet set1, ns3::mbn::AddressSet set2) [member function]
    cls.add_method('Intersection', 
                   'ns3::mbn::AddressSet', 
                   [param('ns3::mbn::AddressSet', 'set1'), param('ns3::mbn::AddressSet', 'set2')])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): ns3::mbn::AddressSet ns3::mbn::Neighbors::Intersection(ns3::mbn::AddressSet set, ns3::Ipv4Address address) [member function]
    cls.add_method('Intersection', 
                   'ns3::mbn::AddressSet', 
                   [param('ns3::mbn::AddressSet', 'set'), param('ns3::Ipv4Address', 'address')])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): bool ns3::mbn::Neighbors::IsNeighbor(ns3::Ipv4Address addr) [member function]
    cls.add_method('IsNeighbor', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'addr')])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): void ns3::mbn::Neighbors::PrintAddressSet(ns3::mbn::AddressSet set) [member function]
    cls.add_method('PrintAddressSet', 
                   'void', 
                   [param('ns3::mbn::AddressSet', 'set')])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): void ns3::mbn::Neighbors::PrintLocalNeighborList() [member function]
    cls.add_method('PrintLocalNeighborList', 
                   'void', 
                   [])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): void ns3::mbn::Neighbors::PrintTwoHopNeighborList() [member function]
    cls.add_method('PrintTwoHopNeighborList', 
                   'void', 
                   [])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): void ns3::mbn::Neighbors::Purge() [member function]
    cls.add_method('Purge', 
                   'void', 
                   [])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): void ns3::mbn::Neighbors::PurgeHello() [member function]
    cls.add_method('PurgeHello', 
                   'void', 
                   [])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): void ns3::mbn::Neighbors::ResetHelloCounter(ns3::mbn::NeighborTuple * nt) [member function]
    cls.add_method('ResetHelloCounter', 
                   'void', 
                   [param('ns3::mbn::NeighborTuple *', 'nt')])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): void ns3::mbn::Neighbors::ResetHelloCounter() [member function]
    cls.add_method('ResetHelloCounter', 
                   'void', 
                   [])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): void ns3::mbn::Neighbors::ScheduleTimer() [member function]
    cls.add_method('ScheduleTimer', 
                   'void', 
                   [])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): void ns3::mbn::Neighbors::SetCallback(ns3::Callback<void, ns3::Ipv4Address, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> cb) [member function]
    cls.add_method('SetCallback', 
                   'void', 
                   [param('ns3::Callback< void, ns3::Ipv4Address, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'cb')])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): void ns3::mbn::Neighbors::SetMinHello(uint32_t minHello) [member function]
    cls.add_method('SetMinHello', 
                   'void', 
                   [param('uint32_t', 'minHello')])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): void ns3::mbn::Neighbors::Update(ns3::Ipv4Address addr, ns3::Time expire) [member function]
    cls.add_method('Update', 
                   'void', 
                   [param('ns3::Ipv4Address', 'addr'), param('ns3::Time', 'expire')])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): void ns3::mbn::Neighbors::UpdateNeighborTuple(ns3::mbn::HelloHeader * helloHeader, bool client) [member function]
    cls.add_method('UpdateNeighborTuple', 
                   'void', 
                   [param('ns3::mbn::HelloHeader *', 'helloHeader'), param('bool', 'client')])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): void ns3::mbn::Neighbors::UpdateTwoHopNeighborTuple(ns3::mbn::HelloHeader * helloHeader, ns3::Time newtTime) [member function]
    cls.add_method('UpdateTwoHopNeighborTuple', 
                   'void', 
                   [param('ns3::mbn::HelloHeader *', 'helloHeader'), param('ns3::Time', 'newtTime')])
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): static bool ns3::mbn::Neighbors::compare0IP(ns3::Ipv4Address const & a, ns3::Ipv4Address const & b) [member function]
    cls.add_method('compare0IP', 
                   'bool', 
                   [param('ns3::Ipv4Address const &', 'a'), param('ns3::Ipv4Address const &', 'b')], 
                   is_static=True)
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): static bool ns3::mbn::Neighbors::compare1IP(ns3::mbn::NeighborTuple const & a, ns3::mbn::NeighborTuple const & b) [member function]
    cls.add_method('compare1IP', 
                   'bool', 
                   [param('ns3::mbn::NeighborTuple const &', 'a'), param('ns3::mbn::NeighborTuple const &', 'b')], 
                   is_static=True)
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): static bool ns3::mbn::Neighbors::compare2IP(ns3::mbn::TwoHopBnNeighborTuple const & a, ns3::mbn::TwoHopBnNeighborTuple const & b) [member function]
    cls.add_method('compare2IP', 
                   'bool', 
                   [param('ns3::mbn::TwoHopBnNeighborTuple const &', 'a'), param('ns3::mbn::TwoHopBnNeighborTuple const &', 'b')], 
                   is_static=True)
    ## mbn-aodv-neighbor.h (module 'mbn-aodv'): ns3::mbn::Neighbors::localNeighborList [variable]
    cls.add_instance_attribute('localNeighborList', 'std::list< ns3::mbn::NeighborTuple >', is_const=False)
    return

def register_Ns3MbnQueueEntry_methods(root_module, cls):
    cls.add_binary_comparison_operator('==')
    ## mbn-aodv-rqueue.h (module 'mbn-aodv'): ns3::mbn::QueueEntry::QueueEntry(ns3::mbn::QueueEntry const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::mbn::QueueEntry const &', 'arg0')])
    ## mbn-aodv-rqueue.h (module 'mbn-aodv'): ns3::mbn::QueueEntry::QueueEntry(ns3::Ptr<ns3::Packet const> pa=0, ns3::Ipv4Header const & h=ns3::Ipv4Header(), ns3::Callback<void, ns3::Ptr<ns3::Ipv4Route>, ns3::Ptr<ns3::Packet const>, ns3::Ipv4Header const&, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ucb=ns3::Callback<void, ns3::Ptr<ns3::Ipv4Route>, ns3::Ptr<const ns3::Packet>, const ns3::Ipv4Header&, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty>(), ns3::Callback<void, ns3::Ptr<ns3::Packet const>, ns3::Ipv4Header const&, ns3::Socket::SocketErrno, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ecb=ns3::Callback<void, ns3::Ptr<const ns3::Packet>, const ns3::Ipv4Header&, ns3::Socket::SocketErrno, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty>(), ns3::Time exp=ns3::Simulator::Now( )) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::Packet const >', 'pa', default_value='0'), param('ns3::Ipv4Header const &', 'h', default_value='ns3::Ipv4Header()'), param('ns3::Callback< void, ns3::Ptr< ns3::Ipv4Route >, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'ucb', default_value='ns3::Callback<void, ns3::Ptr<ns3::Ipv4Route>, ns3::Ptr<const ns3::Packet>, const ns3::Ipv4Header&, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty>()'), param('ns3::Callback< void, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, ns3::Socket::SocketErrno, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'ecb', default_value='ns3::Callback<void, ns3::Ptr<const ns3::Packet>, const ns3::Ipv4Header&, ns3::Socket::SocketErrno, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty>()'), param('ns3::Time', 'exp', default_value='ns3::Simulator::Now( )')])
    ## mbn-aodv-rqueue.h (module 'mbn-aodv'): ns3::Callback<void, ns3::Ptr<ns3::Packet const>, ns3::Ipv4Header const&, ns3::Socket::SocketErrno, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ns3::mbn::QueueEntry::GetErrorCallback() const [member function]
    cls.add_method('GetErrorCallback', 
                   'ns3::Callback< void, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, ns3::Socket::SocketErrno, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 
                   [], 
                   is_const=True)
    ## mbn-aodv-rqueue.h (module 'mbn-aodv'): ns3::Time ns3::mbn::QueueEntry::GetExpireTime() const [member function]
    cls.add_method('GetExpireTime', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## mbn-aodv-rqueue.h (module 'mbn-aodv'): ns3::Ipv4Header ns3::mbn::QueueEntry::GetIpv4Header() const [member function]
    cls.add_method('GetIpv4Header', 
                   'ns3::Ipv4Header', 
                   [], 
                   is_const=True)
    ## mbn-aodv-rqueue.h (module 'mbn-aodv'): ns3::Ptr<ns3::Packet const> ns3::mbn::QueueEntry::GetPacket() const [member function]
    cls.add_method('GetPacket', 
                   'ns3::Ptr< ns3::Packet const >', 
                   [], 
                   is_const=True)
    ## mbn-aodv-rqueue.h (module 'mbn-aodv'): ns3::Callback<void, ns3::Ptr<ns3::Ipv4Route>, ns3::Ptr<ns3::Packet const>, ns3::Ipv4Header const&, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ns3::mbn::QueueEntry::GetUnicastForwardCallback() const [member function]
    cls.add_method('GetUnicastForwardCallback', 
                   'ns3::Callback< void, ns3::Ptr< ns3::Ipv4Route >, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 
                   [], 
                   is_const=True)
    ## mbn-aodv-rqueue.h (module 'mbn-aodv'): void ns3::mbn::QueueEntry::SetErrorCallback(ns3::Callback<void, ns3::Ptr<ns3::Packet const>, ns3::Ipv4Header const&, ns3::Socket::SocketErrno, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ecb) [member function]
    cls.add_method('SetErrorCallback', 
                   'void', 
                   [param('ns3::Callback< void, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, ns3::Socket::SocketErrno, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'ecb')])
    ## mbn-aodv-rqueue.h (module 'mbn-aodv'): void ns3::mbn::QueueEntry::SetExpireTime(ns3::Time exp) [member function]
    cls.add_method('SetExpireTime', 
                   'void', 
                   [param('ns3::Time', 'exp')])
    ## mbn-aodv-rqueue.h (module 'mbn-aodv'): void ns3::mbn::QueueEntry::SetIpv4Header(ns3::Ipv4Header h) [member function]
    cls.add_method('SetIpv4Header', 
                   'void', 
                   [param('ns3::Ipv4Header', 'h')])
    ## mbn-aodv-rqueue.h (module 'mbn-aodv'): void ns3::mbn::QueueEntry::SetPacket(ns3::Ptr<ns3::Packet const> p) [member function]
    cls.add_method('SetPacket', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet const >', 'p')])
    ## mbn-aodv-rqueue.h (module 'mbn-aodv'): void ns3::mbn::QueueEntry::SetUnicastForwardCallback(ns3::Callback<void, ns3::Ptr<ns3::Ipv4Route>, ns3::Ptr<ns3::Packet const>, ns3::Ipv4Header const&, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ucb) [member function]
    cls.add_method('SetUnicastForwardCallback', 
                   'void', 
                   [param('ns3::Callback< void, ns3::Ptr< ns3::Ipv4Route >, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'ucb')])
    return

def register_Ns3MbnRequestQueue_methods(root_module, cls):
    ## mbn-aodv-rqueue.h (module 'mbn-aodv'): ns3::mbn::RequestQueue::RequestQueue(ns3::mbn::RequestQueue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::mbn::RequestQueue const &', 'arg0')])
    ## mbn-aodv-rqueue.h (module 'mbn-aodv'): ns3::mbn::RequestQueue::RequestQueue(uint32_t maxLen, ns3::Time routeToQueueTimeout) [constructor]
    cls.add_constructor([param('uint32_t', 'maxLen'), param('ns3::Time', 'routeToQueueTimeout')])
    ## mbn-aodv-rqueue.h (module 'mbn-aodv'): bool ns3::mbn::RequestQueue::Dequeue(ns3::Ipv4Address dst, ns3::mbn::QueueEntry & entry) [member function]
    cls.add_method('Dequeue', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'dst'), param('ns3::mbn::QueueEntry &', 'entry')])
    ## mbn-aodv-rqueue.h (module 'mbn-aodv'): void ns3::mbn::RequestQueue::DropPacketWithDst(ns3::Ipv4Address dst) [member function]
    cls.add_method('DropPacketWithDst', 
                   'void', 
                   [param('ns3::Ipv4Address', 'dst')])
    ## mbn-aodv-rqueue.h (module 'mbn-aodv'): bool ns3::mbn::RequestQueue::Enqueue(ns3::mbn::QueueEntry & entry) [member function]
    cls.add_method('Enqueue', 
                   'bool', 
                   [param('ns3::mbn::QueueEntry &', 'entry')])
    ## mbn-aodv-rqueue.h (module 'mbn-aodv'): bool ns3::mbn::RequestQueue::Find(ns3::Ipv4Address dst) [member function]
    cls.add_method('Find', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'dst')])
    ## mbn-aodv-rqueue.h (module 'mbn-aodv'): uint32_t ns3::mbn::RequestQueue::GetMaxQueueLen() const [member function]
    cls.add_method('GetMaxQueueLen', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## mbn-aodv-rqueue.h (module 'mbn-aodv'): ns3::Time ns3::mbn::RequestQueue::GetQueueTimeout() const [member function]
    cls.add_method('GetQueueTimeout', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## mbn-aodv-rqueue.h (module 'mbn-aodv'): uint32_t ns3::mbn::RequestQueue::GetSize() [member function]
    cls.add_method('GetSize', 
                   'uint32_t', 
                   [])
    ## mbn-aodv-rqueue.h (module 'mbn-aodv'): void ns3::mbn::RequestQueue::SetMaxQueueLen(uint32_t len) [member function]
    cls.add_method('SetMaxQueueLen', 
                   'void', 
                   [param('uint32_t', 'len')])
    ## mbn-aodv-rqueue.h (module 'mbn-aodv'): void ns3::mbn::RequestQueue::SetQueueTimeout(ns3::Time t) [member function]
    cls.add_method('SetQueueTimeout', 
                   'void', 
                   [param('ns3::Time', 't')])
    return

def register_Ns3MbnRerrHeader_methods(root_module, cls):
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    ## mbn-aodv-packet.h (module 'mbn-aodv'): ns3::mbn::RerrHeader::RerrHeader(ns3::mbn::RerrHeader const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::mbn::RerrHeader const &', 'arg0')])
    ## mbn-aodv-packet.h (module 'mbn-aodv'): ns3::mbn::RerrHeader::RerrHeader() [constructor]
    cls.add_constructor([])
    ## mbn-aodv-packet.h (module 'mbn-aodv'): bool ns3::mbn::RerrHeader::AddUnDestination(ns3::Ipv4Address dst, uint32_t seqNo) [member function]
    cls.add_method('AddUnDestination', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'dst'), param('uint32_t', 'seqNo')])
    ## mbn-aodv-packet.h (module 'mbn-aodv'): void ns3::mbn::RerrHeader::Clear() [member function]
    cls.add_method('Clear', 
                   'void', 
                   [])
    ## mbn-aodv-packet.h (module 'mbn-aodv'): uint32_t ns3::mbn::RerrHeader::Deserialize(ns3::Buffer::Iterator start) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_virtual=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): uint8_t ns3::mbn::RerrHeader::GetDestCount() const [member function]
    cls.add_method('GetDestCount', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): ns3::TypeId ns3::mbn::RerrHeader::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): bool ns3::mbn::RerrHeader::GetNoDelete() const [member function]
    cls.add_method('GetNoDelete', 
                   'bool', 
                   [], 
                   is_const=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): uint32_t ns3::mbn::RerrHeader::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): static ns3::TypeId ns3::mbn::RerrHeader::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): void ns3::mbn::RerrHeader::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): bool ns3::mbn::RerrHeader::RemoveUnDestination(std::pair<ns3::Ipv4Address,unsigned int> & un) [member function]
    cls.add_method('RemoveUnDestination', 
                   'bool', 
                   [param('std::pair< ns3::Ipv4Address, unsigned int > &', 'un')])
    ## mbn-aodv-packet.h (module 'mbn-aodv'): void ns3::mbn::RerrHeader::Serialize(ns3::Buffer::Iterator i) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'i')], 
                   is_const=True, is_virtual=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): void ns3::mbn::RerrHeader::SetNoDelete(bool f) [member function]
    cls.add_method('SetNoDelete', 
                   'void', 
                   [param('bool', 'f')])
    return

def register_Ns3MbnRoutingProtocol_methods(root_module, cls):
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): ns3::mbn::RoutingProtocol::RoutingProtocol(ns3::mbn::RoutingProtocol const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::mbn::RoutingProtocol const &', 'arg0')])
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): ns3::mbn::RoutingProtocol::RoutingProtocol() [constructor]
    cls.add_constructor([])
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): bool ns3::mbn::RoutingProtocol::Are1HopNeighbors(ns3::Ipv4Address const & BNnode_v, ns3::Ipv4Address const & BNnode_w) [member function]
    cls.add_method('Are1HopNeighbors', 
                   'bool', 
                   [param('ns3::Ipv4Address const &', 'BNnode_v'), param('ns3::Ipv4Address const &', 'BNnode_w')])
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): bool ns3::mbn::RoutingProtocol::Are2HopNeighbors(ns3::Ipv4Address const & arg0, ns3::Ipv4Address const & arg1) [member function]
    cls.add_method('Are2HopNeighbors', 
                   'bool', 
                   [param('ns3::Ipv4Address const &', 'arg0'), param('ns3::Ipv4Address const &', 'arg1')])
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): void ns3::mbn::RoutingProtocol::AssociationAlgorithm() [member function]
    cls.add_method('AssociationAlgorithm', 
                   'void', 
                   [])
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): bool ns3::mbn::RoutingProtocol::BCN2BNRule2() [member function]
    cls.add_method('BCN2BNRule2', 
                   'bool', 
                   [])
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): bool ns3::mbn::RoutingProtocol::BCN2BN_ConversionAlgorithm() [member function]
    cls.add_method('BCN2BN_ConversionAlgorithm', 
                   'bool', 
                   [])
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): bool ns3::mbn::RoutingProtocol::BCN2BN_ConversionAlgorithm_1() [member function]
    cls.add_method('BCN2BN_ConversionAlgorithm_1', 
                   'bool', 
                   [])
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): bool ns3::mbn::RoutingProtocol::BCN2BN_ConversionAlgorithm_2() [member function]
    cls.add_method('BCN2BN_ConversionAlgorithm_2', 
                   'bool', 
                   [])
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): bool ns3::mbn::RoutingProtocol::BCN2BN_ConversionAlgorithm_3() [member function]
    cls.add_method('BCN2BN_ConversionAlgorithm_3', 
                   'bool', 
                   [])
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): bool ns3::mbn::RoutingProtocol::BN2BCN_ConversionAlgorithm() [member function]
    cls.add_method('BN2BCN_ConversionAlgorithm', 
                   'bool', 
                   [])
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): bool ns3::mbn::RoutingProtocol::BN2BCN_ConversionAlgorithm_1() [member function]
    cls.add_method('BN2BCN_ConversionAlgorithm_1', 
                   'bool', 
                   [])
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): bool ns3::mbn::RoutingProtocol::BN2BCN_ConversionAlgorithm_2() [member function]
    cls.add_method('BN2BCN_ConversionAlgorithm_2', 
                   'bool', 
                   [])
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): ns3::mbn::NeighborPairs ns3::mbn::RoutingProtocol::BN2BCN_ConversionAlgorithm_2a(ns3::mbn::NeighborPairs bn_pairs) [member function]
    cls.add_method('BN2BCN_ConversionAlgorithm_2a', 
                   'ns3::mbn::NeighborPairs', 
                   [param('ns3::mbn::NeighborPairs', 'bn_pairs')])
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): ns3::mbn::NeighborPairs ns3::mbn::RoutingProtocol::BN2BCN_ConversionAlgorithm_2b(ns3::mbn::NeighborPairs bn_pairs) [member function]
    cls.add_method('BN2BCN_ConversionAlgorithm_2b', 
                   'ns3::mbn::NeighborPairs', 
                   [param('ns3::mbn::NeighborPairs', 'bn_pairs')])
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): ns3::mbn::NeighborPairs ns3::mbn::RoutingProtocol::BN2BCN_ConversionAlgorithm_2c(ns3::mbn::NeighborPairs bn_pairs) [member function]
    cls.add_method('BN2BCN_ConversionAlgorithm_2c', 
                   'ns3::mbn::NeighborPairs', 
                   [param('ns3::mbn::NeighborPairs', 'bn_pairs')])
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): ns3::mbn::NeighborPairs ns3::mbn::RoutingProtocol::BN2BCN_ConversionAlgorithm_2d(ns3::mbn::NeighborPairs bn_pairs) [member function]
    cls.add_method('BN2BCN_ConversionAlgorithm_2d', 
                   'ns3::mbn::NeighborPairs', 
                   [param('ns3::mbn::NeighborPairs', 'bn_pairs')])
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): bool ns3::mbn::RoutingProtocol::BN2BCN_ConversionAlgorithm_3() [member function]
    cls.add_method('BN2BCN_ConversionAlgorithm_3', 
                   'bool', 
                   [])
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): ns3::mbn::NeighborPairs ns3::mbn::RoutingProtocol::BN2BCN_ConversionAlgorithm_3a(ns3::mbn::NeighborPairs pairs) [member function]
    cls.add_method('BN2BCN_ConversionAlgorithm_3a', 
                   'ns3::mbn::NeighborPairs', 
                   [param('ns3::mbn::NeighborPairs', 'pairs')])
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): ns3::mbn::NeighborPairs ns3::mbn::RoutingProtocol::BN2BCN_ConversionAlgorithm_3b(ns3::mbn::NeighborPairs pairs) [member function]
    cls.add_method('BN2BCN_ConversionAlgorithm_3b', 
                   'ns3::mbn::NeighborPairs', 
                   [param('ns3::mbn::NeighborPairs', 'pairs')])
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): ns3::mbn::NeighborPairs ns3::mbn::RoutingProtocol::BN2BCN_ConversionAlgorithm_3c(ns3::mbn::NeighborPairs pairs) [member function]
    cls.add_method('BN2BCN_ConversionAlgorithm_3c', 
                   'ns3::mbn::NeighborPairs', 
                   [param('ns3::mbn::NeighborPairs', 'pairs')])
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): void ns3::mbn::RoutingProtocol::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   is_virtual=True)
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): ns3::mbn::NeighborPairs ns3::mbn::RoutingProtocol::GetAllPairs(ns3::mbn::NeighborSet one, ns3::mbn::NeighborSet two) [member function]
    cls.add_method('GetAllPairs', 
                   'ns3::mbn::NeighborPairs', 
                   [param('ns3::mbn::NeighborSet', 'one'), param('ns3::mbn::NeighborSet', 'two')])
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): bool ns3::mbn::RoutingProtocol::GetBroadcastEnable() const [member function]
    cls.add_method('GetBroadcastEnable', 
                   'bool', 
                   [], 
                   is_const=True)
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): ns3::mbn::NeighborTriples ns3::mbn::RoutingProtocol::GetCommonBN(ns3::mbn::NeighborPair bn_pairs) [member function]
    cls.add_method('GetCommonBN', 
                   'ns3::mbn::NeighborTriples', 
                   [param('ns3::mbn::NeighborPair', 'bn_pairs')])
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): bool ns3::mbn::RoutingProtocol::GetDesinationOnlyFlag() const [member function]
    cls.add_method('GetDesinationOnlyFlag', 
                   'bool', 
                   [], 
                   is_const=True)
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): bool ns3::mbn::RoutingProtocol::GetGratuitousReplyFlag() const [member function]
    cls.add_method('GetGratuitousReplyFlag', 
                   'bool', 
                   [], 
                   is_const=True)
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): bool ns3::mbn::RoutingProtocol::GetHelloEnable() const [member function]
    cls.add_method('GetHelloEnable', 
                   'bool', 
                   [], 
                   is_const=True)
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): ns3::Ipv4Address ns3::mbn::RoutingProtocol::GetLocalAssociatedBN() const [member function]
    cls.add_method('GetLocalAssociatedBN', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): ns3::mbn::BnBcn_Indicator ns3::mbn::RoutingProtocol::GetLocalBnBcnIndicator() const [member function]
    cls.add_method('GetLocalBnBcnIndicator', 
                   'ns3::mbn::BnBcn_Indicator', 
                   [], 
                   is_const=True)
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): uint32_t ns3::mbn::RoutingProtocol::GetLocalCurrentBnNeighbors() const [member function]
    cls.add_method('GetLocalCurrentBnNeighbors', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): uint32_t ns3::mbn::RoutingProtocol::GetLocalLastBnNeighbors() const [member function]
    cls.add_method('GetLocalLastBnNeighbors', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): ns3::mbn::NodeStatus ns3::mbn::RoutingProtocol::GetLocalNodeStatus() const [member function]
    cls.add_method('GetLocalNodeStatus', 
                   'ns3::mbn::NodeStatus', 
                   [], 
                   is_const=True)
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): void ns3::mbn::RoutingProtocol::GetLocalState() [member function]
    cls.add_method('GetLocalState', 
                   'void', 
                   [])
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): uint32_t ns3::mbn::RoutingProtocol::GetLocalWeight() const [member function]
    cls.add_method('GetLocalWeight', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): ns3::mbn::WeightFunction ns3::mbn::RoutingProtocol::GetLocalWeightFunction() const [member function]
    cls.add_method('GetLocalWeightFunction', 
                   'ns3::mbn::WeightFunction', 
                   [], 
                   is_const=True)
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): uint32_t ns3::mbn::RoutingProtocol::GetMaxQueueLen() const [member function]
    cls.add_method('GetMaxQueueLen', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): ns3::Time ns3::mbn::RoutingProtocol::GetMaxQueueTime() const [member function]
    cls.add_method('GetMaxQueueTime', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): ns3::mbn::NeighborPairs ns3::mbn::RoutingProtocol::GetNotConnectedPairs(ns3::mbn::NeighborSet one, ns3::mbn::NeighborSet two) [member function]
    cls.add_method('GetNotConnectedPairs', 
                   'ns3::mbn::NeighborPairs', 
                   [param('ns3::mbn::NeighborSet', 'one'), param('ns3::mbn::NeighborSet', 'two')])
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): uint32_t ns3::mbn::RoutingProtocol::GetOneHopNeighborsSize(ns3::mbn::NodeStatus nodeStatus) [member function]
    cls.add_method('GetOneHopNeighborsSize', 
                   'uint32_t', 
                   [param('ns3::mbn::NodeStatus', 'nodeStatus')])
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): bool ns3::mbn::RoutingProtocol::GetRule1() const [member function]
    cls.add_method('GetRule1', 
                   'bool', 
                   [], 
                   is_const=True)
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): bool ns3::mbn::RoutingProtocol::GetRule2() const [member function]
    cls.add_method('GetRule2', 
                   'bool', 
                   [], 
                   is_const=True)
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): static ns3::TypeId ns3::mbn::RoutingProtocol::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): bool ns3::mbn::RoutingProtocol::HigherWeight(ns3::Ipv4Address neighbor) [member function]
    cls.add_method('HigherWeight', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'neighbor')])
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): bool ns3::mbn::RoutingProtocol::HigherWeight(ns3::mbn::NeighborTuple * node) [member function]
    cls.add_method('HigherWeight', 
                   'bool', 
                   [param('ns3::mbn::NeighborTuple *', 'node')])
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): bool ns3::mbn::RoutingProtocol::HigherWeight(ns3::mbn::TwoHopBnNeighborTuple * node2hop) [member function]
    cls.add_method('HigherWeight', 
                   'bool', 
                   [param('ns3::mbn::TwoHopBnNeighborTuple *', 'node2hop')])
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): void ns3::mbn::RoutingProtocol::NotifyAddAddress(uint32_t interface, ns3::Ipv4InterfaceAddress address) [member function]
    cls.add_method('NotifyAddAddress', 
                   'void', 
                   [param('uint32_t', 'interface'), param('ns3::Ipv4InterfaceAddress', 'address')], 
                   is_virtual=True)
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): void ns3::mbn::RoutingProtocol::NotifyInterfaceDown(uint32_t interface) [member function]
    cls.add_method('NotifyInterfaceDown', 
                   'void', 
                   [param('uint32_t', 'interface')], 
                   is_virtual=True)
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): void ns3::mbn::RoutingProtocol::NotifyInterfaceUp(uint32_t interface) [member function]
    cls.add_method('NotifyInterfaceUp', 
                   'void', 
                   [param('uint32_t', 'interface')], 
                   is_virtual=True)
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): void ns3::mbn::RoutingProtocol::NotifyRemoveAddress(uint32_t interface, ns3::Ipv4InterfaceAddress address) [member function]
    cls.add_method('NotifyRemoveAddress', 
                   'void', 
                   [param('uint32_t', 'interface'), param('ns3::Ipv4InterfaceAddress', 'address')], 
                   is_virtual=True)
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): void ns3::mbn::RoutingProtocol::PrintRoutingTable(ns3::Ptr<ns3::OutputStreamWrapper> stream) const [member function]
    cls.add_method('PrintRoutingTable', 
                   'void', 
                   [param('ns3::Ptr< ns3::OutputStreamWrapper >', 'stream')], 
                   is_const=True, is_virtual=True)
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): bool ns3::mbn::RoutingProtocol::RouteInput(ns3::Ptr<ns3::Packet const> p, ns3::Ipv4Header const & header, ns3::Ptr<const ns3::NetDevice> idev, ns3::Callback<void, ns3::Ptr<ns3::Ipv4Route>, ns3::Ptr<ns3::Packet const>, ns3::Ipv4Header const&, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ucb, ns3::Callback<void,ns3::Ptr<ns3::Ipv4MulticastRoute>,ns3::Ptr<const ns3::Packet>,const ns3::Ipv4Header&,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty> mcb, ns3::Callback<void,ns3::Ptr<const ns3::Packet>,const ns3::Ipv4Header&,unsigned int,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty> lcb, ns3::Callback<void, ns3::Ptr<ns3::Packet const>, ns3::Ipv4Header const&, ns3::Socket::SocketErrno, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ecb) [member function]
    cls.add_method('RouteInput', 
                   'bool', 
                   [param('ns3::Ptr< ns3::Packet const >', 'p'), param('ns3::Ipv4Header const &', 'header'), param('ns3::Ptr< ns3::NetDevice const >', 'idev'), param('ns3::Callback< void, ns3::Ptr< ns3::Ipv4Route >, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'ucb'), param('ns3::Callback< void, ns3::Ptr< ns3::Ipv4MulticastRoute >, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'mcb'), param('ns3::Callback< void, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, unsigned int, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'lcb'), param('ns3::Callback< void, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, ns3::Socket::SocketErrno, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'ecb')], 
                   is_virtual=True)
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): ns3::Ptr<ns3::Ipv4Route> ns3::mbn::RoutingProtocol::RouteOutput(ns3::Ptr<ns3::Packet> p, ns3::Ipv4Header const & header, ns3::Ptr<ns3::NetDevice> oif, ns3::Socket::SocketErrno & sockerr) [member function]
    cls.add_method('RouteOutput', 
                   'ns3::Ptr< ns3::Ipv4Route >', 
                   [param('ns3::Ptr< ns3::Packet >', 'p'), param('ns3::Ipv4Header const &', 'header'), param('ns3::Ptr< ns3::NetDevice >', 'oif'), param('ns3::Socket::SocketErrno &', 'sockerr')], 
                   is_virtual=True)
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): bool ns3::mbn::RoutingProtocol::Rule1Check(ns3::Ipv4Address const & BNnode_v, ns3::Ipv4Address const & BNnode_w) [member function]
    cls.add_method('Rule1Check', 
                   'bool', 
                   [param('ns3::Ipv4Address const &', 'BNnode_v'), param('ns3::Ipv4Address const &', 'BNnode_w')])
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): void ns3::mbn::RoutingProtocol::SetBroadcastEnable(bool f) [member function]
    cls.add_method('SetBroadcastEnable', 
                   'void', 
                   [param('bool', 'f')])
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): void ns3::mbn::RoutingProtocol::SetDesinationOnlyFlag(bool f) [member function]
    cls.add_method('SetDesinationOnlyFlag', 
                   'void', 
                   [param('bool', 'f')])
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): void ns3::mbn::RoutingProtocol::SetGratuitousReplyFlag(bool f) [member function]
    cls.add_method('SetGratuitousReplyFlag', 
                   'void', 
                   [param('bool', 'f')])
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): void ns3::mbn::RoutingProtocol::SetHelloEnable(bool f) [member function]
    cls.add_method('SetHelloEnable', 
                   'void', 
                   [param('bool', 'f')])
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): void ns3::mbn::RoutingProtocol::SetIpv4(ns3::Ptr<ns3::Ipv4> ipv4) [member function]
    cls.add_method('SetIpv4', 
                   'void', 
                   [param('ns3::Ptr< ns3::Ipv4 >', 'ipv4')], 
                   is_virtual=True)
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): void ns3::mbn::RoutingProtocol::SetLocalAssociatedBN(ns3::Ipv4Address const _localAssociatedBN) [member function]
    cls.add_method('SetLocalAssociatedBN', 
                   'void', 
                   [param('ns3::Ipv4Address const', '_localAssociatedBN')])
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): void ns3::mbn::RoutingProtocol::SetLocalBnBcnIndicator(ns3::mbn::BnBcn_Indicator _localBnBcnIndicator) [member function]
    cls.add_method('SetLocalBnBcnIndicator', 
                   'void', 
                   [param('ns3::mbn::BnBcn_Indicator', '_localBnBcnIndicator')])
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): void ns3::mbn::RoutingProtocol::SetLocalCurrentBnNeighbors(uint32_t _currentBnNodes) [member function]
    cls.add_method('SetLocalCurrentBnNeighbors', 
                   'void', 
                   [param('uint32_t', '_currentBnNodes')])
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): void ns3::mbn::RoutingProtocol::SetLocalLastBnNeighbors(uint32_t _lastBnNodes) [member function]
    cls.add_method('SetLocalLastBnNeighbors', 
                   'void', 
                   [param('uint32_t', '_lastBnNodes')])
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): void ns3::mbn::RoutingProtocol::SetLocalNodeStatus(ns3::mbn::NodeStatus _localNodeStatus) [member function]
    cls.add_method('SetLocalNodeStatus', 
                   'void', 
                   [param('ns3::mbn::NodeStatus', '_localNodeStatus')])
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): void ns3::mbn::RoutingProtocol::SetLocalWeight(uint32_t _localWeight) [member function]
    cls.add_method('SetLocalWeight', 
                   'void', 
                   [param('uint32_t', '_localWeight')])
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): void ns3::mbn::RoutingProtocol::SetLocalWeightFunction(ns3::mbn::WeightFunction _weightFunction) [member function]
    cls.add_method('SetLocalWeightFunction', 
                   'void', 
                   [param('ns3::mbn::WeightFunction', '_weightFunction')])
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): void ns3::mbn::RoutingProtocol::SetMaxQueueLen(uint32_t len) [member function]
    cls.add_method('SetMaxQueueLen', 
                   'void', 
                   [param('uint32_t', 'len')])
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): void ns3::mbn::RoutingProtocol::SetMaxQueueTime(ns3::Time t) [member function]
    cls.add_method('SetMaxQueueTime', 
                   'void', 
                   [param('ns3::Time', 't')])
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): void ns3::mbn::RoutingProtocol::SetRule1(bool f) [member function]
    cls.add_method('SetRule1', 
                   'void', 
                   [param('bool', 'f')])
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): void ns3::mbn::RoutingProtocol::SetRule2(bool f) [member function]
    cls.add_method('SetRule2', 
                   'void', 
                   [param('bool', 'f')])
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): void ns3::mbn::RoutingProtocol::UpdateLocalLastBnNeighbors() [member function]
    cls.add_method('UpdateLocalLastBnNeighbors', 
                   'void', 
                   [])
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): void ns3::mbn::RoutingProtocol::UpdateLocalWeight() [member function]
    cls.add_method('UpdateLocalWeight', 
                   'void', 
                   [])
    ## mbn-aodv-routing-protocol.h (module 'mbn-aodv'): ns3::mbn::RoutingProtocol::AODV_PORT [variable]
    cls.add_static_attribute('AODV_PORT', 'uint32_t const', is_const=True)
    return

def register_Ns3MbnRoutingTable_methods(root_module, cls):
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): ns3::mbn::RoutingTable::RoutingTable(ns3::mbn::RoutingTable const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::mbn::RoutingTable const &', 'arg0')])
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): ns3::mbn::RoutingTable::RoutingTable(ns3::Time t) [constructor]
    cls.add_constructor([param('ns3::Time', 't')])
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): bool ns3::mbn::RoutingTable::AddRoute(ns3::mbn::RoutingTableEntry & r) [member function]
    cls.add_method('AddRoute', 
                   'bool', 
                   [param('ns3::mbn::RoutingTableEntry &', 'r')])
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): void ns3::mbn::RoutingTable::Clear() [member function]
    cls.add_method('Clear', 
                   'void', 
                   [])
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): void ns3::mbn::RoutingTable::DeleteAllRoutesFromInterface(ns3::Ipv4InterfaceAddress iface) [member function]
    cls.add_method('DeleteAllRoutesFromInterface', 
                   'void', 
                   [param('ns3::Ipv4InterfaceAddress', 'iface')])
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): bool ns3::mbn::RoutingTable::DeleteRoute(ns3::Ipv4Address dst) [member function]
    cls.add_method('DeleteRoute', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'dst')])
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): ns3::Time ns3::mbn::RoutingTable::GetBadLinkLifetime() const [member function]
    cls.add_method('GetBadLinkLifetime', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): void ns3::mbn::RoutingTable::GetListOfDestinationWithNextHop(ns3::Ipv4Address nextHop, std::map<ns3::Ipv4Address, unsigned int, std::less<ns3::Ipv4Address>, std::allocator<std::pair<ns3::Ipv4Address const, unsigned int> > > & unreachable) [member function]
    cls.add_method('GetListOfDestinationWithNextHop', 
                   'void', 
                   [param('ns3::Ipv4Address', 'nextHop'), param('std::map< ns3::Ipv4Address, unsigned int > &', 'unreachable')])
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): void ns3::mbn::RoutingTable::InvalidateRoutesWithDst(std::map<ns3::Ipv4Address, unsigned int, std::less<ns3::Ipv4Address>, std::allocator<std::pair<ns3::Ipv4Address const, unsigned int> > > const & unreachable) [member function]
    cls.add_method('InvalidateRoutesWithDst', 
                   'void', 
                   [param('std::map< ns3::Ipv4Address, unsigned int > const &', 'unreachable')])
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): bool ns3::mbn::RoutingTable::LookupRoute(ns3::Ipv4Address dst, ns3::mbn::RoutingTableEntry & rt) [member function]
    cls.add_method('LookupRoute', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'dst'), param('ns3::mbn::RoutingTableEntry &', 'rt')])
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): bool ns3::mbn::RoutingTable::LookupValidRoute(ns3::Ipv4Address dst, ns3::mbn::RoutingTableEntry & rt) [member function]
    cls.add_method('LookupValidRoute', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'dst'), param('ns3::mbn::RoutingTableEntry &', 'rt')])
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): bool ns3::mbn::RoutingTable::MarkLinkAsUnidirectional(ns3::Ipv4Address neighbor, ns3::Time blacklistTimeout) [member function]
    cls.add_method('MarkLinkAsUnidirectional', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'neighbor'), param('ns3::Time', 'blacklistTimeout')])
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): void ns3::mbn::RoutingTable::Print(ns3::Ptr<ns3::OutputStreamWrapper> stream) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('ns3::Ptr< ns3::OutputStreamWrapper >', 'stream')], 
                   is_const=True)
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): void ns3::mbn::RoutingTable::Purge() [member function]
    cls.add_method('Purge', 
                   'void', 
                   [])
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): void ns3::mbn::RoutingTable::SetBadLinkLifetime(ns3::Time t) [member function]
    cls.add_method('SetBadLinkLifetime', 
                   'void', 
                   [param('ns3::Time', 't')])
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): bool ns3::mbn::RoutingTable::SetEntryState(ns3::Ipv4Address dst, ns3::mbn::RouteFlags state) [member function]
    cls.add_method('SetEntryState', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'dst'), param('ns3::mbn::RouteFlags', 'state')])
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): bool ns3::mbn::RoutingTable::Update(ns3::mbn::RoutingTableEntry & rt) [member function]
    cls.add_method('Update', 
                   'bool', 
                   [param('ns3::mbn::RoutingTableEntry &', 'rt')])
    return

def register_Ns3MbnRoutingTableEntry_methods(root_module, cls):
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): ns3::mbn::RoutingTableEntry::RoutingTableEntry(ns3::mbn::RoutingTableEntry const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::mbn::RoutingTableEntry const &', 'arg0')])
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): ns3::mbn::RoutingTableEntry::RoutingTableEntry(ns3::Ptr<ns3::NetDevice> dev=0, ns3::Ipv4Address dst=ns3::Ipv4Address(), bool vSeqNo=false, uint32_t m_seqNo=0, ns3::Ipv4InterfaceAddress iface=ns3::Ipv4InterfaceAddress(), uint16_t hops=0, ns3::Ipv4Address nextHop=ns3::Ipv4Address(), ns3::Time lifetime=ns3::Simulator::Now( )) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::NetDevice >', 'dev', default_value='0'), param('ns3::Ipv4Address', 'dst', default_value='ns3::Ipv4Address()'), param('bool', 'vSeqNo', default_value='false'), param('uint32_t', 'm_seqNo', default_value='0'), param('ns3::Ipv4InterfaceAddress', 'iface', default_value='ns3::Ipv4InterfaceAddress()'), param('uint16_t', 'hops', default_value='0'), param('ns3::Ipv4Address', 'nextHop', default_value='ns3::Ipv4Address()'), param('ns3::Time', 'lifetime', default_value='ns3::Simulator::Now( )')])
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): void ns3::mbn::RoutingTableEntry::DeleteAllPrecursors() [member function]
    cls.add_method('DeleteAllPrecursors', 
                   'void', 
                   [])
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): bool ns3::mbn::RoutingTableEntry::DeletePrecursor(ns3::Ipv4Address id) [member function]
    cls.add_method('DeletePrecursor', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'id')])
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): ns3::Time ns3::mbn::RoutingTableEntry::GetBlacklistTimeout() const [member function]
    cls.add_method('GetBlacklistTimeout', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): ns3::Ipv4Address ns3::mbn::RoutingTableEntry::GetDestination() const [member function]
    cls.add_method('GetDestination', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): ns3::mbn::RouteFlags ns3::mbn::RoutingTableEntry::GetFlag() const [member function]
    cls.add_method('GetFlag', 
                   'ns3::mbn::RouteFlags', 
                   [], 
                   is_const=True)
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): uint16_t ns3::mbn::RoutingTableEntry::GetHop() const [member function]
    cls.add_method('GetHop', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): ns3::Ipv4InterfaceAddress ns3::mbn::RoutingTableEntry::GetInterface() const [member function]
    cls.add_method('GetInterface', 
                   'ns3::Ipv4InterfaceAddress', 
                   [], 
                   is_const=True)
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): ns3::Time ns3::mbn::RoutingTableEntry::GetLifeTime() const [member function]
    cls.add_method('GetLifeTime', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): ns3::Ipv4Address ns3::mbn::RoutingTableEntry::GetNextHop() const [member function]
    cls.add_method('GetNextHop', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): ns3::Ptr<ns3::NetDevice> ns3::mbn::RoutingTableEntry::GetOutputDevice() const [member function]
    cls.add_method('GetOutputDevice', 
                   'ns3::Ptr< ns3::NetDevice >', 
                   [], 
                   is_const=True)
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): void ns3::mbn::RoutingTableEntry::GetPrecursors(std::vector<ns3::Ipv4Address, std::allocator<ns3::Ipv4Address> > & prec) const [member function]
    cls.add_method('GetPrecursors', 
                   'void', 
                   [param('std::vector< ns3::Ipv4Address > &', 'prec')], 
                   is_const=True)
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): ns3::Ptr<ns3::Ipv4Route> ns3::mbn::RoutingTableEntry::GetRoute() const [member function]
    cls.add_method('GetRoute', 
                   'ns3::Ptr< ns3::Ipv4Route >', 
                   [], 
                   is_const=True)
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): uint8_t ns3::mbn::RoutingTableEntry::GetRreqCnt() const [member function]
    cls.add_method('GetRreqCnt', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): uint32_t ns3::mbn::RoutingTableEntry::GetSeqNo() const [member function]
    cls.add_method('GetSeqNo', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): bool ns3::mbn::RoutingTableEntry::GetValidSeqNo() const [member function]
    cls.add_method('GetValidSeqNo', 
                   'bool', 
                   [], 
                   is_const=True)
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): void ns3::mbn::RoutingTableEntry::IncrementRreqCnt() [member function]
    cls.add_method('IncrementRreqCnt', 
                   'void', 
                   [])
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): bool ns3::mbn::RoutingTableEntry::InsertPrecursor(ns3::Ipv4Address id) [member function]
    cls.add_method('InsertPrecursor', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'id')])
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): void ns3::mbn::RoutingTableEntry::Invalidate(ns3::Time badLinkLifetime) [member function]
    cls.add_method('Invalidate', 
                   'void', 
                   [param('ns3::Time', 'badLinkLifetime')])
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): bool ns3::mbn::RoutingTableEntry::IsPrecursorListEmpty() const [member function]
    cls.add_method('IsPrecursorListEmpty', 
                   'bool', 
                   [], 
                   is_const=True)
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): bool ns3::mbn::RoutingTableEntry::IsUnidirectional() const [member function]
    cls.add_method('IsUnidirectional', 
                   'bool', 
                   [], 
                   is_const=True)
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): bool ns3::mbn::RoutingTableEntry::LookupPrecursor(ns3::Ipv4Address id) [member function]
    cls.add_method('LookupPrecursor', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'id')])
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): void ns3::mbn::RoutingTableEntry::Print(ns3::Ptr<ns3::OutputStreamWrapper> stream) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('ns3::Ptr< ns3::OutputStreamWrapper >', 'stream')], 
                   is_const=True)
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): void ns3::mbn::RoutingTableEntry::SetBalcklistTimeout(ns3::Time t) [member function]
    cls.add_method('SetBalcklistTimeout', 
                   'void', 
                   [param('ns3::Time', 't')])
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): void ns3::mbn::RoutingTableEntry::SetFlag(ns3::mbn::RouteFlags flag) [member function]
    cls.add_method('SetFlag', 
                   'void', 
                   [param('ns3::mbn::RouteFlags', 'flag')])
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): void ns3::mbn::RoutingTableEntry::SetHop(uint16_t hop) [member function]
    cls.add_method('SetHop', 
                   'void', 
                   [param('uint16_t', 'hop')])
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): void ns3::mbn::RoutingTableEntry::SetInterface(ns3::Ipv4InterfaceAddress iface) [member function]
    cls.add_method('SetInterface', 
                   'void', 
                   [param('ns3::Ipv4InterfaceAddress', 'iface')])
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): void ns3::mbn::RoutingTableEntry::SetLifeTime(ns3::Time lt) [member function]
    cls.add_method('SetLifeTime', 
                   'void', 
                   [param('ns3::Time', 'lt')])
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): void ns3::mbn::RoutingTableEntry::SetNextHop(ns3::Ipv4Address nextHop) [member function]
    cls.add_method('SetNextHop', 
                   'void', 
                   [param('ns3::Ipv4Address', 'nextHop')])
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): void ns3::mbn::RoutingTableEntry::SetOutputDevice(ns3::Ptr<ns3::NetDevice> dev) [member function]
    cls.add_method('SetOutputDevice', 
                   'void', 
                   [param('ns3::Ptr< ns3::NetDevice >', 'dev')])
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): void ns3::mbn::RoutingTableEntry::SetRoute(ns3::Ptr<ns3::Ipv4Route> r) [member function]
    cls.add_method('SetRoute', 
                   'void', 
                   [param('ns3::Ptr< ns3::Ipv4Route >', 'r')])
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): void ns3::mbn::RoutingTableEntry::SetRreqCnt(uint8_t n) [member function]
    cls.add_method('SetRreqCnt', 
                   'void', 
                   [param('uint8_t', 'n')])
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): void ns3::mbn::RoutingTableEntry::SetSeqNo(uint32_t sn) [member function]
    cls.add_method('SetSeqNo', 
                   'void', 
                   [param('uint32_t', 'sn')])
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): void ns3::mbn::RoutingTableEntry::SetUnidirectional(bool u) [member function]
    cls.add_method('SetUnidirectional', 
                   'void', 
                   [param('bool', 'u')])
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): void ns3::mbn::RoutingTableEntry::SetValidSeqNo(bool s) [member function]
    cls.add_method('SetValidSeqNo', 
                   'void', 
                   [param('bool', 's')])
    ## mbn-aodv-rtable.h (module 'mbn-aodv'): ns3::mbn::RoutingTableEntry::m_ackTimer [variable]
    cls.add_instance_attribute('m_ackTimer', 'ns3::Timer', is_const=False)
    return

def register_Ns3MbnRrepAckHeader_methods(root_module, cls):
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    ## mbn-aodv-packet.h (module 'mbn-aodv'): ns3::mbn::RrepAckHeader::RrepAckHeader(ns3::mbn::RrepAckHeader const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::mbn::RrepAckHeader const &', 'arg0')])
    ## mbn-aodv-packet.h (module 'mbn-aodv'): ns3::mbn::RrepAckHeader::RrepAckHeader() [constructor]
    cls.add_constructor([])
    ## mbn-aodv-packet.h (module 'mbn-aodv'): uint32_t ns3::mbn::RrepAckHeader::Deserialize(ns3::Buffer::Iterator start) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_virtual=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): ns3::TypeId ns3::mbn::RrepAckHeader::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): uint32_t ns3::mbn::RrepAckHeader::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): static ns3::TypeId ns3::mbn::RrepAckHeader::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): void ns3::mbn::RrepAckHeader::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): void ns3::mbn::RrepAckHeader::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True, is_virtual=True)
    return

def register_Ns3MbnRrepHeader_methods(root_module, cls):
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    ## mbn-aodv-packet.h (module 'mbn-aodv'): ns3::mbn::RrepHeader::RrepHeader(ns3::mbn::RrepHeader const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::mbn::RrepHeader const &', 'arg0')])
    ## mbn-aodv-packet.h (module 'mbn-aodv'): ns3::mbn::RrepHeader::RrepHeader(uint8_t prefixSize=0, uint8_t hopCount=0, ns3::Ipv4Address dst=ns3::Ipv4Address(), uint32_t dstSeqNo=0, ns3::Ipv4Address origin=ns3::Ipv4Address(), ns3::Time lifetime=ns3::MilliSeconds( )) [constructor]
    cls.add_constructor([param('uint8_t', 'prefixSize', default_value='0'), param('uint8_t', 'hopCount', default_value='0'), param('ns3::Ipv4Address', 'dst', default_value='ns3::Ipv4Address()'), param('uint32_t', 'dstSeqNo', default_value='0'), param('ns3::Ipv4Address', 'origin', default_value='ns3::Ipv4Address()'), param('ns3::Time', 'lifetime', default_value='ns3::MilliSeconds(0)')])
    ## mbn-aodv-packet.h (module 'mbn-aodv'): uint32_t ns3::mbn::RrepHeader::Deserialize(ns3::Buffer::Iterator start) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_virtual=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): bool ns3::mbn::RrepHeader::GetAckRequired() const [member function]
    cls.add_method('GetAckRequired', 
                   'bool', 
                   [], 
                   is_const=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): ns3::Ipv4Address ns3::mbn::RrepHeader::GetDst() const [member function]
    cls.add_method('GetDst', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): uint32_t ns3::mbn::RrepHeader::GetDstSeqno() const [member function]
    cls.add_method('GetDstSeqno', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): uint8_t ns3::mbn::RrepHeader::GetHopCount() const [member function]
    cls.add_method('GetHopCount', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): ns3::TypeId ns3::mbn::RrepHeader::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): ns3::Time ns3::mbn::RrepHeader::GetLifeTime() const [member function]
    cls.add_method('GetLifeTime', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): ns3::Ipv4Address ns3::mbn::RrepHeader::GetOrigin() const [member function]
    cls.add_method('GetOrigin', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): uint8_t ns3::mbn::RrepHeader::GetPrefixSize() const [member function]
    cls.add_method('GetPrefixSize', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): uint32_t ns3::mbn::RrepHeader::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): static ns3::TypeId ns3::mbn::RrepHeader::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): void ns3::mbn::RrepHeader::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): void ns3::mbn::RrepHeader::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True, is_virtual=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): void ns3::mbn::RrepHeader::SetAckRequired(bool f) [member function]
    cls.add_method('SetAckRequired', 
                   'void', 
                   [param('bool', 'f')])
    ## mbn-aodv-packet.h (module 'mbn-aodv'): void ns3::mbn::RrepHeader::SetDst(ns3::Ipv4Address a) [member function]
    cls.add_method('SetDst', 
                   'void', 
                   [param('ns3::Ipv4Address', 'a')])
    ## mbn-aodv-packet.h (module 'mbn-aodv'): void ns3::mbn::RrepHeader::SetDstSeqno(uint32_t s) [member function]
    cls.add_method('SetDstSeqno', 
                   'void', 
                   [param('uint32_t', 's')])
    ## mbn-aodv-packet.h (module 'mbn-aodv'): void ns3::mbn::RrepHeader::SetHello(ns3::Ipv4Address src, uint32_t srcSeqNo, ns3::Time lifetime) [member function]
    cls.add_method('SetHello', 
                   'void', 
                   [param('ns3::Ipv4Address', 'src'), param('uint32_t', 'srcSeqNo'), param('ns3::Time', 'lifetime')])
    ## mbn-aodv-packet.h (module 'mbn-aodv'): void ns3::mbn::RrepHeader::SetHopCount(uint8_t count) [member function]
    cls.add_method('SetHopCount', 
                   'void', 
                   [param('uint8_t', 'count')])
    ## mbn-aodv-packet.h (module 'mbn-aodv'): void ns3::mbn::RrepHeader::SetLifeTime(ns3::Time t) [member function]
    cls.add_method('SetLifeTime', 
                   'void', 
                   [param('ns3::Time', 't')])
    ## mbn-aodv-packet.h (module 'mbn-aodv'): void ns3::mbn::RrepHeader::SetOrigin(ns3::Ipv4Address a) [member function]
    cls.add_method('SetOrigin', 
                   'void', 
                   [param('ns3::Ipv4Address', 'a')])
    ## mbn-aodv-packet.h (module 'mbn-aodv'): void ns3::mbn::RrepHeader::SetPrefixSize(uint8_t sz) [member function]
    cls.add_method('SetPrefixSize', 
                   'void', 
                   [param('uint8_t', 'sz')])
    return

def register_Ns3MbnRreqHeader_methods(root_module, cls):
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    ## mbn-aodv-packet.h (module 'mbn-aodv'): ns3::mbn::RreqHeader::RreqHeader(ns3::mbn::RreqHeader const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::mbn::RreqHeader const &', 'arg0')])
    ## mbn-aodv-packet.h (module 'mbn-aodv'): ns3::mbn::RreqHeader::RreqHeader(uint8_t flags=0, uint8_t reserved=0, uint8_t hopCount=0, uint32_t requestID=0, ns3::Ipv4Address dst=ns3::Ipv4Address(), uint32_t dstSeqNo=0, ns3::Ipv4Address origin=ns3::Ipv4Address(), uint32_t originSeqNo=0) [constructor]
    cls.add_constructor([param('uint8_t', 'flags', default_value='0'), param('uint8_t', 'reserved', default_value='0'), param('uint8_t', 'hopCount', default_value='0'), param('uint32_t', 'requestID', default_value='0'), param('ns3::Ipv4Address', 'dst', default_value='ns3::Ipv4Address()'), param('uint32_t', 'dstSeqNo', default_value='0'), param('ns3::Ipv4Address', 'origin', default_value='ns3::Ipv4Address()'), param('uint32_t', 'originSeqNo', default_value='0')])
    ## mbn-aodv-packet.h (module 'mbn-aodv'): uint32_t ns3::mbn::RreqHeader::Deserialize(ns3::Buffer::Iterator start) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_virtual=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): bool ns3::mbn::RreqHeader::GetDestinationOnly() const [member function]
    cls.add_method('GetDestinationOnly', 
                   'bool', 
                   [], 
                   is_const=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): ns3::Ipv4Address ns3::mbn::RreqHeader::GetDst() const [member function]
    cls.add_method('GetDst', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): uint32_t ns3::mbn::RreqHeader::GetDstSeqno() const [member function]
    cls.add_method('GetDstSeqno', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): bool ns3::mbn::RreqHeader::GetGratiousRrep() const [member function]
    cls.add_method('GetGratiousRrep', 
                   'bool', 
                   [], 
                   is_const=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): uint8_t ns3::mbn::RreqHeader::GetHopCount() const [member function]
    cls.add_method('GetHopCount', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): uint32_t ns3::mbn::RreqHeader::GetId() const [member function]
    cls.add_method('GetId', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): ns3::TypeId ns3::mbn::RreqHeader::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): ns3::Ipv4Address ns3::mbn::RreqHeader::GetOrigin() const [member function]
    cls.add_method('GetOrigin', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): uint32_t ns3::mbn::RreqHeader::GetOriginSeqno() const [member function]
    cls.add_method('GetOriginSeqno', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): uint32_t ns3::mbn::RreqHeader::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): static ns3::TypeId ns3::mbn::RreqHeader::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): bool ns3::mbn::RreqHeader::GetUnknownSeqno() const [member function]
    cls.add_method('GetUnknownSeqno', 
                   'bool', 
                   [], 
                   is_const=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): void ns3::mbn::RreqHeader::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): void ns3::mbn::RreqHeader::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True, is_virtual=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): void ns3::mbn::RreqHeader::SetDestinationOnly(bool f) [member function]
    cls.add_method('SetDestinationOnly', 
                   'void', 
                   [param('bool', 'f')])
    ## mbn-aodv-packet.h (module 'mbn-aodv'): void ns3::mbn::RreqHeader::SetDst(ns3::Ipv4Address a) [member function]
    cls.add_method('SetDst', 
                   'void', 
                   [param('ns3::Ipv4Address', 'a')])
    ## mbn-aodv-packet.h (module 'mbn-aodv'): void ns3::mbn::RreqHeader::SetDstSeqno(uint32_t s) [member function]
    cls.add_method('SetDstSeqno', 
                   'void', 
                   [param('uint32_t', 's')])
    ## mbn-aodv-packet.h (module 'mbn-aodv'): void ns3::mbn::RreqHeader::SetGratiousRrep(bool f) [member function]
    cls.add_method('SetGratiousRrep', 
                   'void', 
                   [param('bool', 'f')])
    ## mbn-aodv-packet.h (module 'mbn-aodv'): void ns3::mbn::RreqHeader::SetHopCount(uint8_t count) [member function]
    cls.add_method('SetHopCount', 
                   'void', 
                   [param('uint8_t', 'count')])
    ## mbn-aodv-packet.h (module 'mbn-aodv'): void ns3::mbn::RreqHeader::SetId(uint32_t id) [member function]
    cls.add_method('SetId', 
                   'void', 
                   [param('uint32_t', 'id')])
    ## mbn-aodv-packet.h (module 'mbn-aodv'): void ns3::mbn::RreqHeader::SetOrigin(ns3::Ipv4Address a) [member function]
    cls.add_method('SetOrigin', 
                   'void', 
                   [param('ns3::Ipv4Address', 'a')])
    ## mbn-aodv-packet.h (module 'mbn-aodv'): void ns3::mbn::RreqHeader::SetOriginSeqno(uint32_t s) [member function]
    cls.add_method('SetOriginSeqno', 
                   'void', 
                   [param('uint32_t', 's')])
    ## mbn-aodv-packet.h (module 'mbn-aodv'): void ns3::mbn::RreqHeader::SetUnknownSeqno(bool f) [member function]
    cls.add_method('SetUnknownSeqno', 
                   'void', 
                   [param('bool', 'f')])
    return

def register_Ns3MbnTwoHopBnNeighborTuple_methods(root_module, cls):
    cls.add_binary_comparison_operator('<')
    cls.add_binary_comparison_operator('>')
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    ## mbn-aodv-common.h (module 'mbn-aodv'): ns3::mbn::TwoHopBnNeighborTuple::TwoHopBnNeighborTuple(ns3::mbn::TwoHopBnNeighborTuple const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::mbn::TwoHopBnNeighborTuple const &', 'arg0')])
    ## mbn-aodv-common.h (module 'mbn-aodv'): ns3::mbn::TwoHopBnNeighborTuple::TwoHopBnNeighborTuple(ns3::Ipv4Address addr, uint32_t weight, ns3::mbn::BnBcn_Indicator ind, ns3::Time time) [constructor]
    cls.add_constructor([param('ns3::Ipv4Address', 'addr'), param('uint32_t', 'weight'), param('ns3::mbn::BnBcn_Indicator', 'ind'), param('ns3::Time', 'time')])
    ## mbn-aodv-common.h (module 'mbn-aodv'): ns3::mbn::TwoHopBnNeighborTuple::TwoHopBnNeighborTuple(ns3::Ipv4Address addr, uint32_t weight, ns3::mbn::BnBcn_Indicator ind) [constructor]
    cls.add_constructor([param('ns3::Ipv4Address', 'addr'), param('uint32_t', 'weight'), param('ns3::mbn::BnBcn_Indicator', 'ind')])
    ## mbn-aodv-common.h (module 'mbn-aodv'): ns3::mbn::TwoHopBnNeighborTuple::TwoHopBnNeighborTuple() [constructor]
    cls.add_constructor([])
    ## mbn-aodv-common.h (module 'mbn-aodv'): ns3::mbn::TwoHopBnNeighborTuple::twoHopBnNeighborIfaceAddr [variable]
    cls.add_instance_attribute('twoHopBnNeighborIfaceAddr', 'ns3::Ipv4Address', is_const=False)
    ## mbn-aodv-common.h (module 'mbn-aodv'): ns3::mbn::TwoHopBnNeighborTuple::twoHopBnNeighborIndicator [variable]
    cls.add_instance_attribute('twoHopBnNeighborIndicator', 'ns3::mbn::BnBcn_Indicator', is_const=False)
    ## mbn-aodv-common.h (module 'mbn-aodv'): ns3::mbn::TwoHopBnNeighborTuple::twoHopBnNeighborTimeout [variable]
    cls.add_instance_attribute('twoHopBnNeighborTimeout', 'ns3::Time', is_const=False)
    ## mbn-aodv-common.h (module 'mbn-aodv'): ns3::mbn::TwoHopBnNeighborTuple::twoHopBnNeighborWeight [variable]
    cls.add_instance_attribute('twoHopBnNeighborWeight', 'uint32_t', is_const=False)
    return

def register_Ns3MbnTypeHeader_methods(root_module, cls):
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    ## mbn-aodv-packet.h (module 'mbn-aodv'): ns3::mbn::TypeHeader::TypeHeader(ns3::mbn::TypeHeader const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::mbn::TypeHeader const &', 'arg0')])
    ## mbn-aodv-packet.h (module 'mbn-aodv'): ns3::mbn::TypeHeader::TypeHeader(ns3::mbn::MessageType t) [constructor]
    cls.add_constructor([param('ns3::mbn::MessageType', 't')])
    ## mbn-aodv-packet.h (module 'mbn-aodv'): uint32_t ns3::mbn::TypeHeader::Deserialize(ns3::Buffer::Iterator start) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_virtual=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): ns3::mbn::MessageType ns3::mbn::TypeHeader::Get() const [member function]
    cls.add_method('Get', 
                   'ns3::mbn::MessageType', 
                   [], 
                   is_const=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): ns3::TypeId ns3::mbn::TypeHeader::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): uint32_t ns3::mbn::TypeHeader::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): static ns3::TypeId ns3::mbn::TypeHeader::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): bool ns3::mbn::TypeHeader::IsValid() const [member function]
    cls.add_method('IsValid', 
                   'bool', 
                   [], 
                   is_const=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): void ns3::mbn::TypeHeader::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## mbn-aodv-packet.h (module 'mbn-aodv'): void ns3::mbn::TypeHeader::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True, is_virtual=True)
    return

def register_Ns3OlsrAssociation_methods(root_module, cls):
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::Association::Association() [constructor]
    cls.add_constructor([])
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::Association::Association(ns3::olsr::Association const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::olsr::Association const &', 'arg0')])
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::Association::netmask [variable]
    cls.add_instance_attribute('netmask', 'ns3::Ipv4Mask', is_const=False)
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::Association::networkAddr [variable]
    cls.add_instance_attribute('networkAddr', 'ns3::Ipv4Address', is_const=False)
    return

def register_Ns3OlsrAssociationTuple_methods(root_module, cls):
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::AssociationTuple::AssociationTuple() [constructor]
    cls.add_constructor([])
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::AssociationTuple::AssociationTuple(ns3::olsr::AssociationTuple const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::olsr::AssociationTuple const &', 'arg0')])
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::AssociationTuple::expirationTime [variable]
    cls.add_instance_attribute('expirationTime', 'ns3::Time', is_const=False)
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::AssociationTuple::gatewayAddr [variable]
    cls.add_instance_attribute('gatewayAddr', 'ns3::Ipv4Address', is_const=False)
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::AssociationTuple::netmask [variable]
    cls.add_instance_attribute('netmask', 'ns3::Ipv4Mask', is_const=False)
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::AssociationTuple::networkAddr [variable]
    cls.add_instance_attribute('networkAddr', 'ns3::Ipv4Address', is_const=False)
    return

def register_Ns3OlsrDuplicateTuple_methods(root_module, cls):
    cls.add_binary_comparison_operator('==')
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::DuplicateTuple::DuplicateTuple() [constructor]
    cls.add_constructor([])
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::DuplicateTuple::DuplicateTuple(ns3::olsr::DuplicateTuple const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::olsr::DuplicateTuple const &', 'arg0')])
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::DuplicateTuple::address [variable]
    cls.add_instance_attribute('address', 'ns3::Ipv4Address', is_const=False)
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::DuplicateTuple::expirationTime [variable]
    cls.add_instance_attribute('expirationTime', 'ns3::Time', is_const=False)
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::DuplicateTuple::ifaceList [variable]
    cls.add_instance_attribute('ifaceList', 'std::vector< ns3::Ipv4Address >', is_const=False)
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::DuplicateTuple::retransmitted [variable]
    cls.add_instance_attribute('retransmitted', 'bool', is_const=False)
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::DuplicateTuple::sequenceNumber [variable]
    cls.add_instance_attribute('sequenceNumber', 'uint16_t', is_const=False)
    return

def register_Ns3OlsrIfaceAssocTuple_methods(root_module, cls):
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::IfaceAssocTuple::IfaceAssocTuple() [constructor]
    cls.add_constructor([])
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::IfaceAssocTuple::IfaceAssocTuple(ns3::olsr::IfaceAssocTuple const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::olsr::IfaceAssocTuple const &', 'arg0')])
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::IfaceAssocTuple::ifaceAddr [variable]
    cls.add_instance_attribute('ifaceAddr', 'ns3::Ipv4Address', is_const=False)
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::IfaceAssocTuple::mainAddr [variable]
    cls.add_instance_attribute('mainAddr', 'ns3::Ipv4Address', is_const=False)
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::IfaceAssocTuple::time [variable]
    cls.add_instance_attribute('time', 'ns3::Time', is_const=False)
    return

def register_Ns3OlsrLinkTuple_methods(root_module, cls):
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::LinkTuple::LinkTuple() [constructor]
    cls.add_constructor([])
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::LinkTuple::LinkTuple(ns3::olsr::LinkTuple const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::olsr::LinkTuple const &', 'arg0')])
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::LinkTuple::asymTime [variable]
    cls.add_instance_attribute('asymTime', 'ns3::Time', is_const=False)
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::LinkTuple::localIfaceAddr [variable]
    cls.add_instance_attribute('localIfaceAddr', 'ns3::Ipv4Address', is_const=False)
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::LinkTuple::neighborIfaceAddr [variable]
    cls.add_instance_attribute('neighborIfaceAddr', 'ns3::Ipv4Address', is_const=False)
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::LinkTuple::symTime [variable]
    cls.add_instance_attribute('symTime', 'ns3::Time', is_const=False)
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::LinkTuple::time [variable]
    cls.add_instance_attribute('time', 'ns3::Time', is_const=False)
    return

def register_Ns3OlsrMessageHeader_methods(root_module, cls):
    cls.add_output_stream_operator()
    ## olsr-header.h (module 'olsr'): ns3::olsr::MessageHeader::MessageHeader(ns3::olsr::MessageHeader const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::olsr::MessageHeader const &', 'arg0')])
    ## olsr-header.h (module 'olsr'): ns3::olsr::MessageHeader::MessageHeader() [constructor]
    cls.add_constructor([])
    ## olsr-header.h (module 'olsr'): uint32_t ns3::olsr::MessageHeader::Deserialize(ns3::Buffer::Iterator start) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_virtual=True)
    ## olsr-header.h (module 'olsr'): ns3::olsr::MessageHeader::Hello & ns3::olsr::MessageHeader::GetHello() [member function]
    cls.add_method('GetHello', 
                   'ns3::olsr::MessageHeader::Hello &', 
                   [])
    ## olsr-header.h (module 'olsr'): ns3::olsr::MessageHeader::Hello const & ns3::olsr::MessageHeader::GetHello() const [member function]
    cls.add_method('GetHello', 
                   'ns3::olsr::MessageHeader::Hello const &', 
                   [], 
                   is_const=True)
    ## olsr-header.h (module 'olsr'): ns3::olsr::MessageHeader::Hna & ns3::olsr::MessageHeader::GetHna() [member function]
    cls.add_method('GetHna', 
                   'ns3::olsr::MessageHeader::Hna &', 
                   [])
    ## olsr-header.h (module 'olsr'): ns3::olsr::MessageHeader::Hna const & ns3::olsr::MessageHeader::GetHna() const [member function]
    cls.add_method('GetHna', 
                   'ns3::olsr::MessageHeader::Hna const &', 
                   [], 
                   is_const=True)
    ## olsr-header.h (module 'olsr'): uint8_t ns3::olsr::MessageHeader::GetHopCount() const [member function]
    cls.add_method('GetHopCount', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## olsr-header.h (module 'olsr'): ns3::TypeId ns3::olsr::MessageHeader::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## olsr-header.h (module 'olsr'): uint16_t ns3::olsr::MessageHeader::GetMessageSequenceNumber() const [member function]
    cls.add_method('GetMessageSequenceNumber', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## olsr-header.h (module 'olsr'): ns3::olsr::MessageHeader::MessageType ns3::olsr::MessageHeader::GetMessageType() const [member function]
    cls.add_method('GetMessageType', 
                   'ns3::olsr::MessageHeader::MessageType', 
                   [], 
                   is_const=True)
    ## olsr-header.h (module 'olsr'): ns3::olsr::MessageHeader::Mid & ns3::olsr::MessageHeader::GetMid() [member function]
    cls.add_method('GetMid', 
                   'ns3::olsr::MessageHeader::Mid &', 
                   [])
    ## olsr-header.h (module 'olsr'): ns3::olsr::MessageHeader::Mid const & ns3::olsr::MessageHeader::GetMid() const [member function]
    cls.add_method('GetMid', 
                   'ns3::olsr::MessageHeader::Mid const &', 
                   [], 
                   is_const=True)
    ## olsr-header.h (module 'olsr'): ns3::Ipv4Address ns3::olsr::MessageHeader::GetOriginatorAddress() const [member function]
    cls.add_method('GetOriginatorAddress', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## olsr-header.h (module 'olsr'): uint32_t ns3::olsr::MessageHeader::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## olsr-header.h (module 'olsr'): ns3::olsr::MessageHeader::Tc & ns3::olsr::MessageHeader::GetTc() [member function]
    cls.add_method('GetTc', 
                   'ns3::olsr::MessageHeader::Tc &', 
                   [])
    ## olsr-header.h (module 'olsr'): ns3::olsr::MessageHeader::Tc const & ns3::olsr::MessageHeader::GetTc() const [member function]
    cls.add_method('GetTc', 
                   'ns3::olsr::MessageHeader::Tc const &', 
                   [], 
                   is_const=True)
    ## olsr-header.h (module 'olsr'): uint8_t ns3::olsr::MessageHeader::GetTimeToLive() const [member function]
    cls.add_method('GetTimeToLive', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## olsr-header.h (module 'olsr'): static ns3::TypeId ns3::olsr::MessageHeader::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## olsr-header.h (module 'olsr'): ns3::Time ns3::olsr::MessageHeader::GetVTime() const [member function]
    cls.add_method('GetVTime', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## olsr-header.h (module 'olsr'): void ns3::olsr::MessageHeader::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## olsr-header.h (module 'olsr'): void ns3::olsr::MessageHeader::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True, is_virtual=True)
    ## olsr-header.h (module 'olsr'): void ns3::olsr::MessageHeader::SetHopCount(uint8_t hopCount) [member function]
    cls.add_method('SetHopCount', 
                   'void', 
                   [param('uint8_t', 'hopCount')])
    ## olsr-header.h (module 'olsr'): void ns3::olsr::MessageHeader::SetMessageSequenceNumber(uint16_t messageSequenceNumber) [member function]
    cls.add_method('SetMessageSequenceNumber', 
                   'void', 
                   [param('uint16_t', 'messageSequenceNumber')])
    ## olsr-header.h (module 'olsr'): void ns3::olsr::MessageHeader::SetMessageType(ns3::olsr::MessageHeader::MessageType messageType) [member function]
    cls.add_method('SetMessageType', 
                   'void', 
                   [param('ns3::olsr::MessageHeader::MessageType', 'messageType')])
    ## olsr-header.h (module 'olsr'): void ns3::olsr::MessageHeader::SetOriginatorAddress(ns3::Ipv4Address originatorAddress) [member function]
    cls.add_method('SetOriginatorAddress', 
                   'void', 
                   [param('ns3::Ipv4Address', 'originatorAddress')])
    ## olsr-header.h (module 'olsr'): void ns3::olsr::MessageHeader::SetTimeToLive(uint8_t timeToLive) [member function]
    cls.add_method('SetTimeToLive', 
                   'void', 
                   [param('uint8_t', 'timeToLive')])
    ## olsr-header.h (module 'olsr'): void ns3::olsr::MessageHeader::SetVTime(ns3::Time time) [member function]
    cls.add_method('SetVTime', 
                   'void', 
                   [param('ns3::Time', 'time')])
    return

def register_Ns3OlsrMessageHeaderHello_methods(root_module, cls):
    ## olsr-header.h (module 'olsr'): ns3::olsr::MessageHeader::Hello::Hello() [constructor]
    cls.add_constructor([])
    ## olsr-header.h (module 'olsr'): ns3::olsr::MessageHeader::Hello::Hello(ns3::olsr::MessageHeader::Hello const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::olsr::MessageHeader::Hello const &', 'arg0')])
    ## olsr-header.h (module 'olsr'): uint32_t ns3::olsr::MessageHeader::Hello::Deserialize(ns3::Buffer::Iterator start, uint32_t messageSize) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start'), param('uint32_t', 'messageSize')])
    ## olsr-header.h (module 'olsr'): ns3::Time ns3::olsr::MessageHeader::Hello::GetHTime() const [member function]
    cls.add_method('GetHTime', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## olsr-header.h (module 'olsr'): uint32_t ns3::olsr::MessageHeader::Hello::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## olsr-header.h (module 'olsr'): void ns3::olsr::MessageHeader::Hello::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True)
    ## olsr-header.h (module 'olsr'): void ns3::olsr::MessageHeader::Hello::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True)
    ## olsr-header.h (module 'olsr'): void ns3::olsr::MessageHeader::Hello::SetHTime(ns3::Time time) [member function]
    cls.add_method('SetHTime', 
                   'void', 
                   [param('ns3::Time', 'time')])
    ## olsr-header.h (module 'olsr'): ns3::olsr::MessageHeader::Hello::hTime [variable]
    cls.add_instance_attribute('hTime', 'uint8_t', is_const=False)
    ## olsr-header.h (module 'olsr'): ns3::olsr::MessageHeader::Hello::linkMessages [variable]
    cls.add_instance_attribute('linkMessages', 'std::vector< ns3::olsr::MessageHeader::Hello::LinkMessage >', is_const=False)
    ## olsr-header.h (module 'olsr'): ns3::olsr::MessageHeader::Hello::willingness [variable]
    cls.add_instance_attribute('willingness', 'uint8_t', is_const=False)
    return

def register_Ns3OlsrMessageHeaderHelloLinkMessage_methods(root_module, cls):
    ## olsr-header.h (module 'olsr'): ns3::olsr::MessageHeader::Hello::LinkMessage::LinkMessage() [constructor]
    cls.add_constructor([])
    ## olsr-header.h (module 'olsr'): ns3::olsr::MessageHeader::Hello::LinkMessage::LinkMessage(ns3::olsr::MessageHeader::Hello::LinkMessage const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::olsr::MessageHeader::Hello::LinkMessage const &', 'arg0')])
    ## olsr-header.h (module 'olsr'): ns3::olsr::MessageHeader::Hello::LinkMessage::linkCode [variable]
    cls.add_instance_attribute('linkCode', 'uint8_t', is_const=False)
    ## olsr-header.h (module 'olsr'): ns3::olsr::MessageHeader::Hello::LinkMessage::neighborInterfaceAddresses [variable]
    cls.add_instance_attribute('neighborInterfaceAddresses', 'std::vector< ns3::Ipv4Address >', is_const=False)
    return

def register_Ns3OlsrMessageHeaderHna_methods(root_module, cls):
    ## olsr-header.h (module 'olsr'): ns3::olsr::MessageHeader::Hna::Hna() [constructor]
    cls.add_constructor([])
    ## olsr-header.h (module 'olsr'): ns3::olsr::MessageHeader::Hna::Hna(ns3::olsr::MessageHeader::Hna const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::olsr::MessageHeader::Hna const &', 'arg0')])
    ## olsr-header.h (module 'olsr'): uint32_t ns3::olsr::MessageHeader::Hna::Deserialize(ns3::Buffer::Iterator start, uint32_t messageSize) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start'), param('uint32_t', 'messageSize')])
    ## olsr-header.h (module 'olsr'): uint32_t ns3::olsr::MessageHeader::Hna::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## olsr-header.h (module 'olsr'): void ns3::olsr::MessageHeader::Hna::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True)
    ## olsr-header.h (module 'olsr'): void ns3::olsr::MessageHeader::Hna::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True)
    ## olsr-header.h (module 'olsr'): ns3::olsr::MessageHeader::Hna::associations [variable]
    cls.add_instance_attribute('associations', 'std::vector< ns3::olsr::MessageHeader::Hna::Association >', is_const=False)
    return

def register_Ns3OlsrMessageHeaderHnaAssociation_methods(root_module, cls):
    ## olsr-header.h (module 'olsr'): ns3::olsr::MessageHeader::Hna::Association::Association() [constructor]
    cls.add_constructor([])
    ## olsr-header.h (module 'olsr'): ns3::olsr::MessageHeader::Hna::Association::Association(ns3::olsr::MessageHeader::Hna::Association const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::olsr::MessageHeader::Hna::Association const &', 'arg0')])
    ## olsr-header.h (module 'olsr'): ns3::olsr::MessageHeader::Hna::Association::address [variable]
    cls.add_instance_attribute('address', 'ns3::Ipv4Address', is_const=False)
    ## olsr-header.h (module 'olsr'): ns3::olsr::MessageHeader::Hna::Association::mask [variable]
    cls.add_instance_attribute('mask', 'ns3::Ipv4Mask', is_const=False)
    return

def register_Ns3OlsrMessageHeaderMid_methods(root_module, cls):
    ## olsr-header.h (module 'olsr'): ns3::olsr::MessageHeader::Mid::Mid() [constructor]
    cls.add_constructor([])
    ## olsr-header.h (module 'olsr'): ns3::olsr::MessageHeader::Mid::Mid(ns3::olsr::MessageHeader::Mid const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::olsr::MessageHeader::Mid const &', 'arg0')])
    ## olsr-header.h (module 'olsr'): uint32_t ns3::olsr::MessageHeader::Mid::Deserialize(ns3::Buffer::Iterator start, uint32_t messageSize) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start'), param('uint32_t', 'messageSize')])
    ## olsr-header.h (module 'olsr'): uint32_t ns3::olsr::MessageHeader::Mid::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## olsr-header.h (module 'olsr'): void ns3::olsr::MessageHeader::Mid::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True)
    ## olsr-header.h (module 'olsr'): void ns3::olsr::MessageHeader::Mid::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True)
    ## olsr-header.h (module 'olsr'): ns3::olsr::MessageHeader::Mid::interfaceAddresses [variable]
    cls.add_instance_attribute('interfaceAddresses', 'std::vector< ns3::Ipv4Address >', is_const=False)
    return

def register_Ns3OlsrMessageHeaderTc_methods(root_module, cls):
    ## olsr-header.h (module 'olsr'): ns3::olsr::MessageHeader::Tc::Tc() [constructor]
    cls.add_constructor([])
    ## olsr-header.h (module 'olsr'): ns3::olsr::MessageHeader::Tc::Tc(ns3::olsr::MessageHeader::Tc const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::olsr::MessageHeader::Tc const &', 'arg0')])
    ## olsr-header.h (module 'olsr'): uint32_t ns3::olsr::MessageHeader::Tc::Deserialize(ns3::Buffer::Iterator start, uint32_t messageSize) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start'), param('uint32_t', 'messageSize')])
    ## olsr-header.h (module 'olsr'): uint32_t ns3::olsr::MessageHeader::Tc::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## olsr-header.h (module 'olsr'): void ns3::olsr::MessageHeader::Tc::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True)
    ## olsr-header.h (module 'olsr'): void ns3::olsr::MessageHeader::Tc::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True)
    ## olsr-header.h (module 'olsr'): ns3::olsr::MessageHeader::Tc::ansn [variable]
    cls.add_instance_attribute('ansn', 'uint16_t', is_const=False)
    ## olsr-header.h (module 'olsr'): ns3::olsr::MessageHeader::Tc::neighborAddresses [variable]
    cls.add_instance_attribute('neighborAddresses', 'std::vector< ns3::Ipv4Address >', is_const=False)
    return

def register_Ns3OlsrMprSelectorTuple_methods(root_module, cls):
    cls.add_binary_comparison_operator('==')
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::MprSelectorTuple::MprSelectorTuple() [constructor]
    cls.add_constructor([])
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::MprSelectorTuple::MprSelectorTuple(ns3::olsr::MprSelectorTuple const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::olsr::MprSelectorTuple const &', 'arg0')])
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::MprSelectorTuple::expirationTime [variable]
    cls.add_instance_attribute('expirationTime', 'ns3::Time', is_const=False)
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::MprSelectorTuple::mainAddr [variable]
    cls.add_instance_attribute('mainAddr', 'ns3::Ipv4Address', is_const=False)
    return

def register_Ns3OlsrNeighborTuple_methods(root_module, cls):
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::NeighborTuple::NeighborTuple() [constructor]
    cls.add_constructor([])
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::NeighborTuple::NeighborTuple(ns3::olsr::NeighborTuple const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::olsr::NeighborTuple const &', 'arg0')])
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::NeighborTuple::neighborMainAddr [variable]
    cls.add_instance_attribute('neighborMainAddr', 'ns3::Ipv4Address', is_const=False)
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::NeighborTuple::status [variable]
    cls.add_instance_attribute('status', 'ns3::olsr::NeighborTuple::Status', is_const=False)
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::NeighborTuple::willingness [variable]
    cls.add_instance_attribute('willingness', 'uint8_t', is_const=False)
    return

def register_Ns3OlsrPacketHeader_methods(root_module, cls):
    cls.add_output_stream_operator()
    ## olsr-header.h (module 'olsr'): ns3::olsr::PacketHeader::PacketHeader(ns3::olsr::PacketHeader const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::olsr::PacketHeader const &', 'arg0')])
    ## olsr-header.h (module 'olsr'): ns3::olsr::PacketHeader::PacketHeader() [constructor]
    cls.add_constructor([])
    ## olsr-header.h (module 'olsr'): uint32_t ns3::olsr::PacketHeader::Deserialize(ns3::Buffer::Iterator start) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_virtual=True)
    ## olsr-header.h (module 'olsr'): ns3::TypeId ns3::olsr::PacketHeader::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## olsr-header.h (module 'olsr'): uint16_t ns3::olsr::PacketHeader::GetPacketLength() const [member function]
    cls.add_method('GetPacketLength', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## olsr-header.h (module 'olsr'): uint16_t ns3::olsr::PacketHeader::GetPacketSequenceNumber() const [member function]
    cls.add_method('GetPacketSequenceNumber', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## olsr-header.h (module 'olsr'): uint32_t ns3::olsr::PacketHeader::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## olsr-header.h (module 'olsr'): static ns3::TypeId ns3::olsr::PacketHeader::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## olsr-header.h (module 'olsr'): void ns3::olsr::PacketHeader::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## olsr-header.h (module 'olsr'): void ns3::olsr::PacketHeader::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True, is_virtual=True)
    ## olsr-header.h (module 'olsr'): void ns3::olsr::PacketHeader::SetPacketLength(uint16_t length) [member function]
    cls.add_method('SetPacketLength', 
                   'void', 
                   [param('uint16_t', 'length')])
    ## olsr-header.h (module 'olsr'): void ns3::olsr::PacketHeader::SetPacketSequenceNumber(uint16_t seqnum) [member function]
    cls.add_method('SetPacketSequenceNumber', 
                   'void', 
                   [param('uint16_t', 'seqnum')])
    return

def register_Ns3OlsrRoutingProtocol_methods(root_module, cls):
    ## olsr-routing-protocol.h (module 'olsr'): ns3::olsr::RoutingProtocol::RoutingProtocol(ns3::olsr::RoutingProtocol const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::olsr::RoutingProtocol const &', 'arg0')])
    ## olsr-routing-protocol.h (module 'olsr'): ns3::olsr::RoutingProtocol::RoutingProtocol() [constructor]
    cls.add_constructor([])
    ## olsr-routing-protocol.h (module 'olsr'): void ns3::olsr::RoutingProtocol::AddHostNetworkAssociation(ns3::Ipv4Address networkAddr, ns3::Ipv4Mask netmask) [member function]
    cls.add_method('AddHostNetworkAssociation', 
                   'void', 
                   [param('ns3::Ipv4Address', 'networkAddr'), param('ns3::Ipv4Mask', 'netmask')])
    ## olsr-routing-protocol.h (module 'olsr'): int64_t ns3::olsr::RoutingProtocol::AssignStreams(int64_t stream) [member function]
    cls.add_method('AssignStreams', 
                   'int64_t', 
                   [param('int64_t', 'stream')])
    ## olsr-routing-protocol.h (module 'olsr'): void ns3::olsr::RoutingProtocol::Dump() [member function]
    cls.add_method('Dump', 
                   'void', 
                   [])
    ## olsr-routing-protocol.h (module 'olsr'): std::set<unsigned int, std::less<unsigned int>, std::allocator<unsigned int> > ns3::olsr::RoutingProtocol::GetInterfaceExclusions() const [member function]
    cls.add_method('GetInterfaceExclusions', 
                   'std::set< unsigned int >', 
                   [], 
                   is_const=True)
    ## olsr-routing-protocol.h (module 'olsr'): std::vector<ns3::olsr::RoutingTableEntry,std::allocator<ns3::olsr::RoutingTableEntry> > ns3::olsr::RoutingProtocol::GetRoutingTableEntries() const [member function]
    cls.add_method('GetRoutingTableEntries', 
                   'std::vector< ns3::olsr::RoutingTableEntry >', 
                   [], 
                   is_const=True)
    ## olsr-routing-protocol.h (module 'olsr'): static ns3::TypeId ns3::olsr::RoutingProtocol::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## olsr-routing-protocol.h (module 'olsr'): void ns3::olsr::RoutingProtocol::RemoveHostNetworkAssociation(ns3::Ipv4Address networkAddr, ns3::Ipv4Mask netmask) [member function]
    cls.add_method('RemoveHostNetworkAssociation', 
                   'void', 
                   [param('ns3::Ipv4Address', 'networkAddr'), param('ns3::Ipv4Mask', 'netmask')])
    ## olsr-routing-protocol.h (module 'olsr'): void ns3::olsr::RoutingProtocol::SetInterfaceExclusions(std::set<unsigned int, std::less<unsigned int>, std::allocator<unsigned int> > exceptions) [member function]
    cls.add_method('SetInterfaceExclusions', 
                   'void', 
                   [param('std::set< unsigned int >', 'exceptions')])
    ## olsr-routing-protocol.h (module 'olsr'): void ns3::olsr::RoutingProtocol::SetMainInterface(uint32_t interface) [member function]
    cls.add_method('SetMainInterface', 
                   'void', 
                   [param('uint32_t', 'interface')])
    ## olsr-routing-protocol.h (module 'olsr'): void ns3::olsr::RoutingProtocol::SetRoutingTableAssociation(ns3::Ptr<ns3::Ipv4StaticRouting> routingTable) [member function]
    cls.add_method('SetRoutingTableAssociation', 
                   'void', 
                   [param('ns3::Ptr< ns3::Ipv4StaticRouting >', 'routingTable')])
    ## olsr-routing-protocol.h (module 'olsr'): void ns3::olsr::RoutingProtocol::DoStart() [member function]
    cls.add_method('DoStart', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## olsr-routing-protocol.h (module 'olsr'): void ns3::olsr::RoutingProtocol::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='private', is_virtual=True)
    ## olsr-routing-protocol.h (module 'olsr'): void ns3::olsr::RoutingProtocol::NotifyAddAddress(uint32_t interface, ns3::Ipv4InterfaceAddress address) [member function]
    cls.add_method('NotifyAddAddress', 
                   'void', 
                   [param('uint32_t', 'interface'), param('ns3::Ipv4InterfaceAddress', 'address')], 
                   visibility='private', is_virtual=True)
    ## olsr-routing-protocol.h (module 'olsr'): void ns3::olsr::RoutingProtocol::NotifyInterfaceDown(uint32_t interface) [member function]
    cls.add_method('NotifyInterfaceDown', 
                   'void', 
                   [param('uint32_t', 'interface')], 
                   visibility='private', is_virtual=True)
    ## olsr-routing-protocol.h (module 'olsr'): void ns3::olsr::RoutingProtocol::NotifyInterfaceUp(uint32_t interface) [member function]
    cls.add_method('NotifyInterfaceUp', 
                   'void', 
                   [param('uint32_t', 'interface')], 
                   visibility='private', is_virtual=True)
    ## olsr-routing-protocol.h (module 'olsr'): void ns3::olsr::RoutingProtocol::NotifyRemoveAddress(uint32_t interface, ns3::Ipv4InterfaceAddress address) [member function]
    cls.add_method('NotifyRemoveAddress', 
                   'void', 
                   [param('uint32_t', 'interface'), param('ns3::Ipv4InterfaceAddress', 'address')], 
                   visibility='private', is_virtual=True)
    ## olsr-routing-protocol.h (module 'olsr'): void ns3::olsr::RoutingProtocol::PrintRoutingTable(ns3::Ptr<ns3::OutputStreamWrapper> stream) const [member function]
    cls.add_method('PrintRoutingTable', 
                   'void', 
                   [param('ns3::Ptr< ns3::OutputStreamWrapper >', 'stream')], 
                   is_const=True, visibility='private', is_virtual=True)
    ## olsr-routing-protocol.h (module 'olsr'): bool ns3::olsr::RoutingProtocol::RouteInput(ns3::Ptr<ns3::Packet const> p, ns3::Ipv4Header const & header, ns3::Ptr<const ns3::NetDevice> idev, ns3::Callback<void, ns3::Ptr<ns3::Ipv4Route>, ns3::Ptr<ns3::Packet const>, ns3::Ipv4Header const&, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ucb, ns3::Callback<void,ns3::Ptr<ns3::Ipv4MulticastRoute>,ns3::Ptr<const ns3::Packet>,const ns3::Ipv4Header&,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty> mcb, ns3::Callback<void,ns3::Ptr<const ns3::Packet>,const ns3::Ipv4Header&,unsigned int,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty> lcb, ns3::Callback<void, ns3::Ptr<ns3::Packet const>, ns3::Ipv4Header const&, ns3::Socket::SocketErrno, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ecb) [member function]
    cls.add_method('RouteInput', 
                   'bool', 
                   [param('ns3::Ptr< ns3::Packet const >', 'p'), param('ns3::Ipv4Header const &', 'header'), param('ns3::Ptr< ns3::NetDevice const >', 'idev'), param('ns3::Callback< void, ns3::Ptr< ns3::Ipv4Route >, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'ucb'), param('ns3::Callback< void, ns3::Ptr< ns3::Ipv4MulticastRoute >, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'mcb'), param('ns3::Callback< void, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, unsigned int, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'lcb'), param('ns3::Callback< void, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, ns3::Socket::SocketErrno, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'ecb')], 
                   visibility='private', is_virtual=True)
    ## olsr-routing-protocol.h (module 'olsr'): ns3::Ptr<ns3::Ipv4Route> ns3::olsr::RoutingProtocol::RouteOutput(ns3::Ptr<ns3::Packet> p, ns3::Ipv4Header const & header, ns3::Ptr<ns3::NetDevice> oif, ns3::Socket::SocketErrno & sockerr) [member function]
    cls.add_method('RouteOutput', 
                   'ns3::Ptr< ns3::Ipv4Route >', 
                   [param('ns3::Ptr< ns3::Packet >', 'p'), param('ns3::Ipv4Header const &', 'header'), param('ns3::Ptr< ns3::NetDevice >', 'oif'), param('ns3::Socket::SocketErrno &', 'sockerr')], 
                   visibility='private', is_virtual=True)
    ## olsr-routing-protocol.h (module 'olsr'): void ns3::olsr::RoutingProtocol::SetIpv4(ns3::Ptr<ns3::Ipv4> ipv4) [member function]
    cls.add_method('SetIpv4', 
                   'void', 
                   [param('ns3::Ptr< ns3::Ipv4 >', 'ipv4')], 
                   visibility='private', is_virtual=True)
    return

def register_Ns3OlsrRoutingTableEntry_methods(root_module, cls):
    ## olsr-routing-protocol.h (module 'olsr'): ns3::olsr::RoutingTableEntry::RoutingTableEntry(ns3::olsr::RoutingTableEntry const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::olsr::RoutingTableEntry const &', 'arg0')])
    ## olsr-routing-protocol.h (module 'olsr'): ns3::olsr::RoutingTableEntry::RoutingTableEntry() [constructor]
    cls.add_constructor([])
    ## olsr-routing-protocol.h (module 'olsr'): ns3::olsr::RoutingTableEntry::destAddr [variable]
    cls.add_instance_attribute('destAddr', 'ns3::Ipv4Address', is_const=False)
    ## olsr-routing-protocol.h (module 'olsr'): ns3::olsr::RoutingTableEntry::distance [variable]
    cls.add_instance_attribute('distance', 'uint32_t', is_const=False)
    ## olsr-routing-protocol.h (module 'olsr'): ns3::olsr::RoutingTableEntry::interface [variable]
    cls.add_instance_attribute('interface', 'uint32_t', is_const=False)
    ## olsr-routing-protocol.h (module 'olsr'): ns3::olsr::RoutingTableEntry::nextAddr [variable]
    cls.add_instance_attribute('nextAddr', 'ns3::Ipv4Address', is_const=False)
    return

def register_Ns3OlsrTopologyTuple_methods(root_module, cls):
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::TopologyTuple::TopologyTuple() [constructor]
    cls.add_constructor([])
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::TopologyTuple::TopologyTuple(ns3::olsr::TopologyTuple const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::olsr::TopologyTuple const &', 'arg0')])
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::TopologyTuple::destAddr [variable]
    cls.add_instance_attribute('destAddr', 'ns3::Ipv4Address', is_const=False)
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::TopologyTuple::expirationTime [variable]
    cls.add_instance_attribute('expirationTime', 'ns3::Time', is_const=False)
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::TopologyTuple::lastAddr [variable]
    cls.add_instance_attribute('lastAddr', 'ns3::Ipv4Address', is_const=False)
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::TopologyTuple::sequenceNumber [variable]
    cls.add_instance_attribute('sequenceNumber', 'uint16_t', is_const=False)
    return

def register_Ns3OlsrTwoHopNeighborTuple_methods(root_module, cls):
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::TwoHopNeighborTuple::TwoHopNeighborTuple() [constructor]
    cls.add_constructor([])
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::TwoHopNeighborTuple::TwoHopNeighborTuple(ns3::olsr::TwoHopNeighborTuple const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::olsr::TwoHopNeighborTuple const &', 'arg0')])
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::TwoHopNeighborTuple::expirationTime [variable]
    cls.add_instance_attribute('expirationTime', 'ns3::Time', is_const=False)
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::TwoHopNeighborTuple::neighborMainAddr [variable]
    cls.add_instance_attribute('neighborMainAddr', 'ns3::Ipv4Address', is_const=False)
    ## olsr-repositories.h (module 'olsr'): ns3::olsr::TwoHopNeighborTuple::twoHopNeighborAddr [variable]
    cls.add_instance_attribute('twoHopNeighborAddr', 'ns3::Ipv4Address', is_const=False)
    return

def register_Ns3PimdmAssertMetric_methods(root_module, cls):
    cls.add_binary_comparison_operator('>')
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::AssertMetric::AssertMetric(ns3::pimdm::AssertMetric const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::pimdm::AssertMetric const &', 'arg0')])
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::AssertMetric::AssertMetric() [constructor]
    cls.add_constructor([])
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::AssertMetric::AssertMetric(int m, int r, uint32_t ip) [constructor]
    cls.add_constructor([param('int', 'm'), param('int', 'r'), param('uint32_t', 'ip')])
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::AssertMetric::AssertMetric(int m, int r, ns3::Ipv4Address ip) [constructor]
    cls.add_constructor([param('int', 'm'), param('int', 'r'), param('ns3::Ipv4Address', 'ip')])
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::AssertMetric::IPAddress [variable]
    cls.add_instance_attribute('IPAddress', 'ns3::Ipv4Address', is_const=False)
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::AssertMetric::metricPreference [variable]
    cls.add_instance_attribute('metricPreference', 'uint32_t', is_const=False)
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::AssertMetric::routeMetric [variable]
    cls.add_instance_attribute('routeMetric', 'uint32_t', is_const=False)
    return

def register_Ns3PimdmIdTag_methods(root_module, cls):
    ## pimdm-routing.h (module 'pimdm'): ns3::pimdm::IdTag::IdTag(ns3::pimdm::IdTag const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::pimdm::IdTag const &', 'arg0')])
    ## pimdm-routing.h (module 'pimdm'): ns3::pimdm::IdTag::IdTag(uint32_t id=0) [constructor]
    cls.add_constructor([param('uint32_t', 'id', default_value='0')])
    ## pimdm-routing.h (module 'pimdm'): void ns3::pimdm::IdTag::Deserialize(ns3::TagBuffer i) [member function]
    cls.add_method('Deserialize', 
                   'void', 
                   [param('ns3::TagBuffer', 'i')], 
                   is_virtual=True)
    ## pimdm-routing.h (module 'pimdm'): ns3::TypeId ns3::pimdm::IdTag::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## pimdm-routing.h (module 'pimdm'): uint32_t ns3::pimdm::IdTag::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## pimdm-routing.h (module 'pimdm'): static ns3::TypeId ns3::pimdm::IdTag::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## pimdm-routing.h (module 'pimdm'): void ns3::pimdm::IdTag::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## pimdm-routing.h (module 'pimdm'): void ns3::pimdm::IdTag::Serialize(ns3::TagBuffer i) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::TagBuffer', 'i')], 
                   is_const=True, is_virtual=True)
    ## pimdm-routing.h (module 'pimdm'): ns3::pimdm::IdTag::m_id [variable]
    cls.add_instance_attribute('m_id', 'uint32_t', is_const=False)
    return

def register_Ns3PimdmMulticastEntry_methods(root_module, cls):
    ## pimdm-routing.h (module 'pimdm'): ns3::pimdm::MulticastEntry::MulticastEntry(ns3::pimdm::MulticastEntry const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::pimdm::MulticastEntry const &', 'arg0')])
    ## pimdm-routing.h (module 'pimdm'): ns3::pimdm::MulticastEntry::MulticastEntry() [constructor]
    cls.add_constructor([])
    ## pimdm-routing.h (module 'pimdm'): ns3::pimdm::MulticastEntry::interface [variable]
    cls.add_instance_attribute('interface', 'uint32_t', is_const=False)
    ## pimdm-routing.h (module 'pimdm'): ns3::pimdm::MulticastEntry::nextAddr [variable]
    cls.add_instance_attribute('nextAddr', 'ns3::Ipv4Address', is_const=False)
    ## pimdm-routing.h (module 'pimdm'): ns3::pimdm::MulticastEntry::sourceAddr [variable]
    cls.add_instance_attribute('sourceAddr', 'ns3::Ipv4Address', is_const=False)
    return

def register_Ns3PimdmMulticastRoutingProtocol_methods(root_module, cls):
    ## pimdm-routing.h (module 'pimdm'): ns3::pimdm::MulticastRoutingProtocol::MulticastRoutingProtocol(ns3::pimdm::MulticastRoutingProtocol const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::pimdm::MulticastRoutingProtocol const &', 'arg0')])
    ## pimdm-routing.h (module 'pimdm'): ns3::pimdm::MulticastRoutingProtocol::MulticastRoutingProtocol() [constructor]
    cls.add_constructor([])
    ## pimdm-routing.h (module 'pimdm'): std::set<unsigned int, std::less<unsigned int>, std::allocator<unsigned int> > ns3::pimdm::MulticastRoutingProtocol::GetInterfaceExclusions() const [member function]
    cls.add_method('GetInterfaceExclusions', 
                   'std::set< unsigned int >', 
                   [], 
                   is_const=True)
    ## pimdm-routing.h (module 'pimdm'): uint32_t ns3::pimdm::MulticastRoutingProtocol::GetMainInterface() [member function]
    cls.add_method('GetMainInterface', 
                   'uint32_t', 
                   [])
    ## pimdm-routing.h (module 'pimdm'): uint16_t ns3::pimdm::MulticastRoutingProtocol::GetRouteMetric(uint32_t interface, ns3::Ipv4Address source) [member function]
    cls.add_method('GetRouteMetric', 
                   'uint16_t', 
                   [param('uint32_t', 'interface'), param('ns3::Ipv4Address', 'source')])
    ## pimdm-routing.h (module 'pimdm'): std::vector<ns3::pimdm::RoutingMulticastTable,std::allocator<ns3::pimdm::RoutingMulticastTable> > ns3::pimdm::MulticastRoutingProtocol::GetRoutingTableEntries() const [member function]
    cls.add_method('GetRoutingTableEntries', 
                   'std::vector< ns3::pimdm::RoutingMulticastTable >', 
                   [], 
                   is_const=True)
    ## pimdm-routing.h (module 'pimdm'): static ns3::TypeId ns3::pimdm::MulticastRoutingProtocol::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## pimdm-routing.h (module 'pimdm'): void ns3::pimdm::MulticastRoutingProtocol::SetInterfaceExclusions(std::set<unsigned int, std::less<unsigned int>, std::allocator<unsigned int> > exceptions) [member function]
    cls.add_method('SetInterfaceExclusions', 
                   'void', 
                   [param('std::set< unsigned int >', 'exceptions')])
    ## pimdm-routing.h (module 'pimdm'): void ns3::pimdm::MulticastRoutingProtocol::UpdateMRIB() [member function]
    cls.add_method('UpdateMRIB', 
                   'void', 
                   [])
    ## pimdm-routing.h (module 'pimdm'): void ns3::pimdm::MulticastRoutingProtocol::registerMember(ns3::Ipv4Address source, ns3::Ipv4Address group, uint32_t interface) [member function]
    cls.add_method('registerMember', 
                   'void', 
                   [param('ns3::Ipv4Address', 'source'), param('ns3::Ipv4Address', 'group'), param('uint32_t', 'interface')])
    ## pimdm-routing.h (module 'pimdm'): void ns3::pimdm::MulticastRoutingProtocol::register_SG(std::string SG) [member function]
    cls.add_method('register_SG', 
                   'void', 
                   [param('std::string', 'SG')])
    ## pimdm-routing.h (module 'pimdm'): void ns3::pimdm::MulticastRoutingProtocol::unregisterMember(ns3::Ipv4Address source, ns3::Ipv4Address group, uint32_t interface) [member function]
    cls.add_method('unregisterMember', 
                   'void', 
                   [param('ns3::Ipv4Address', 'source'), param('ns3::Ipv4Address', 'group'), param('uint32_t', 'interface')])
    ## pimdm-routing.h (module 'pimdm'): void ns3::pimdm::MulticastRoutingProtocol::DoStart() [member function]
    cls.add_method('DoStart', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## pimdm-routing.h (module 'pimdm'): void ns3::pimdm::MulticastRoutingProtocol::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='private', is_virtual=True)
    ## pimdm-routing.h (module 'pimdm'): void ns3::pimdm::MulticastRoutingProtocol::NotifyAddAddress(uint32_t interface, ns3::Ipv4InterfaceAddress address) [member function]
    cls.add_method('NotifyAddAddress', 
                   'void', 
                   [param('uint32_t', 'interface'), param('ns3::Ipv4InterfaceAddress', 'address')], 
                   visibility='private', is_virtual=True)
    ## pimdm-routing.h (module 'pimdm'): void ns3::pimdm::MulticastRoutingProtocol::NotifyInterfaceDown(uint32_t interface) [member function]
    cls.add_method('NotifyInterfaceDown', 
                   'void', 
                   [param('uint32_t', 'interface')], 
                   visibility='private', is_virtual=True)
    ## pimdm-routing.h (module 'pimdm'): void ns3::pimdm::MulticastRoutingProtocol::NotifyInterfaceUp(uint32_t interface) [member function]
    cls.add_method('NotifyInterfaceUp', 
                   'void', 
                   [param('uint32_t', 'interface')], 
                   visibility='private', is_virtual=True)
    ## pimdm-routing.h (module 'pimdm'): void ns3::pimdm::MulticastRoutingProtocol::NotifyRemoveAddress(uint32_t interface, ns3::Ipv4InterfaceAddress address) [member function]
    cls.add_method('NotifyRemoveAddress', 
                   'void', 
                   [param('uint32_t', 'interface'), param('ns3::Ipv4InterfaceAddress', 'address')], 
                   visibility='private', is_virtual=True)
    ## pimdm-routing.h (module 'pimdm'): void ns3::pimdm::MulticastRoutingProtocol::PrintRoutingTable(ns3::Ptr<ns3::OutputStreamWrapper> stream) const [member function]
    cls.add_method('PrintRoutingTable', 
                   'void', 
                   [param('ns3::Ptr< ns3::OutputStreamWrapper >', 'stream')], 
                   is_const=True, visibility='private', is_virtual=True)
    ## pimdm-routing.h (module 'pimdm'): bool ns3::pimdm::MulticastRoutingProtocol::RouteInput(ns3::Ptr<ns3::Packet const> p, ns3::Ipv4Header const & header, ns3::Ptr<const ns3::NetDevice> idev, ns3::Callback<void, ns3::Ptr<ns3::Ipv4Route>, ns3::Ptr<ns3::Packet const>, ns3::Ipv4Header const&, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ucb, ns3::Callback<void,ns3::Ptr<ns3::Ipv4MulticastRoute>,ns3::Ptr<const ns3::Packet>,const ns3::Ipv4Header&,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty> mcb, ns3::Callback<void,ns3::Ptr<const ns3::Packet>,const ns3::Ipv4Header&,unsigned int,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty> lcb, ns3::Callback<void, ns3::Ptr<ns3::Packet const>, ns3::Ipv4Header const&, ns3::Socket::SocketErrno, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ecb) [member function]
    cls.add_method('RouteInput', 
                   'bool', 
                   [param('ns3::Ptr< ns3::Packet const >', 'p'), param('ns3::Ipv4Header const &', 'header'), param('ns3::Ptr< ns3::NetDevice const >', 'idev'), param('ns3::Callback< void, ns3::Ptr< ns3::Ipv4Route >, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'ucb'), param('ns3::Callback< void, ns3::Ptr< ns3::Ipv4MulticastRoute >, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'mcb'), param('ns3::Callback< void, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, unsigned int, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'lcb'), param('ns3::Callback< void, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, ns3::Socket::SocketErrno, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'ecb')], 
                   visibility='private', is_virtual=True)
    ## pimdm-routing.h (module 'pimdm'): ns3::Ptr<ns3::Ipv4Route> ns3::pimdm::MulticastRoutingProtocol::RouteOutput(ns3::Ptr<ns3::Packet> p, ns3::Ipv4Header const & header, ns3::Ptr<ns3::NetDevice> oif, ns3::Socket::SocketErrno & sockerr) [member function]
    cls.add_method('RouteOutput', 
                   'ns3::Ptr< ns3::Ipv4Route >', 
                   [param('ns3::Ptr< ns3::Packet >', 'p'), param('ns3::Ipv4Header const &', 'header'), param('ns3::Ptr< ns3::NetDevice >', 'oif'), param('ns3::Socket::SocketErrno &', 'sockerr')], 
                   visibility='private', is_virtual=True)
    ## pimdm-routing.h (module 'pimdm'): void ns3::pimdm::MulticastRoutingProtocol::SetIpv4(ns3::Ptr<ns3::Ipv4> ipv4) [member function]
    cls.add_method('SetIpv4', 
                   'void', 
                   [param('ns3::Ptr< ns3::Ipv4 >', 'ipv4')], 
                   visibility='private', is_virtual=True)
    return

def register_Ns3PimdmNeighborState_methods(root_module, cls):
    cls.add_binary_comparison_operator('<')
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::NeighborState::NeighborState(ns3::pimdm::NeighborState const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::pimdm::NeighborState const &', 'arg0')])
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::NeighborState::NeighborState(ns3::Ipv4Address neighbor, ns3::Ipv4Address rec) [constructor]
    cls.add_constructor([param('ns3::Ipv4Address', 'neighbor'), param('ns3::Ipv4Address', 'rec')])
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::NeighborState::neigborNLT [variable]
    cls.add_instance_attribute('neigborNLT', 'ns3::Timer', is_const=False)
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::NeighborState::neighborCreation [variable]
    cls.add_instance_attribute('neighborCreation', 'ns3::Time', is_const=False)
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::NeighborState::neighborGenerationID [variable]
    cls.add_instance_attribute('neighborGenerationID', 'uint32_t', is_const=False)
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::NeighborState::neighborGraftRetry [variable]
    cls.add_instance_attribute('neighborGraftRetry', 'uint8_t [ 2 ]', is_const=False)
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::NeighborState::neighborHoldTime [variable]
    cls.add_instance_attribute('neighborHoldTime', 'ns3::Time', is_const=False)
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::NeighborState::neighborIfaceAddr [variable]
    cls.add_instance_attribute('neighborIfaceAddr', 'ns3::Ipv4Address', is_const=False)
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::NeighborState::neighborInterval [variable]
    cls.add_instance_attribute('neighborInterval', 'uint8_t', is_const=False)
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::NeighborState::neighborOverrideInterval [variable]
    cls.add_instance_attribute('neighborOverrideInterval', 'ns3::Time', is_const=False)
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::NeighborState::neighborPropagationDelay [variable]
    cls.add_instance_attribute('neighborPropagationDelay', 'ns3::Time', is_const=False)
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::NeighborState::neighborRefresh [variable]
    cls.add_instance_attribute('neighborRefresh', 'ns3::Time', is_const=False)
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::NeighborState::neighborT [variable]
    cls.add_instance_attribute('neighborT', 'uint8_t', is_const=False)
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::NeighborState::neighborTimeout [variable]
    cls.add_instance_attribute('neighborTimeout', 'ns3::Time', is_const=False)
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::NeighborState::neighborTimeoutB [variable]
    cls.add_instance_attribute('neighborTimeoutB', 'bool', is_const=False)
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::NeighborState::neighborVersion [variable]
    cls.add_instance_attribute('neighborVersion', 'uint8_t', is_const=False)
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::NeighborState::receivingIfaceAddr [variable]
    cls.add_instance_attribute('receivingIfaceAddr', 'ns3::Ipv4Address', is_const=False)
    return

def register_Ns3PimdmNeighborhoodStatus_methods(root_module, cls):
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::NeighborhoodStatus::NeighborhoodStatus(ns3::pimdm::NeighborhoodStatus const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::pimdm::NeighborhoodStatus const &', 'arg0')])
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::NeighborhoodStatus::NeighborhoodStatus() [constructor]
    cls.add_constructor([])
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::NeighborhoodStatus::LANDelayEnabled [variable]
    cls.add_instance_attribute('LANDelayEnabled', 'bool', is_const=False)
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::NeighborhoodStatus::hello_timer [variable]
    cls.add_instance_attribute('hello_timer', 'ns3::Timer', is_const=False)
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::NeighborhoodStatus::neighbors [variable]
    cls.add_instance_attribute('neighbors', 'ns3::pimdm::NeighborList', is_const=False)
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::NeighborhoodStatus::overrideInterval [variable]
    cls.add_instance_attribute('overrideInterval', 'ns3::Time', is_const=False)
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::NeighborhoodStatus::propagationDelay [variable]
    cls.add_instance_attribute('propagationDelay', 'ns3::Time', is_const=False)
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::NeighborhoodStatus::pruneHoldtime [variable]
    cls.add_instance_attribute('pruneHoldtime', 'ns3::Time', is_const=False)
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::NeighborhoodStatus::stateRefreshCapable [variable]
    cls.add_instance_attribute('stateRefreshCapable', 'bool', is_const=False)
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::NeighborhoodStatus::stateRefreshInterval [variable]
    cls.add_instance_attribute('stateRefreshInterval', 'ns3::Time', is_const=False)
    return

def register_Ns3PimdmPIMHeader_methods(root_module, cls):
    cls.add_output_stream_operator()
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::PIMHeader(ns3::pimdm::PIMHeader const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::pimdm::PIMHeader const &', 'arg0')])
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::PIMHeader() [constructor]
    cls.add_constructor([])
    ## pimdm-packet.h (module 'pimdm'): uint32_t ns3::pimdm::PIMHeader::Deserialize(ns3::Buffer::Iterator start) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_virtual=True)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::AssertMessage & ns3::pimdm::PIMHeader::GetAssertMessage() [member function]
    cls.add_method('GetAssertMessage', 
                   'ns3::pimdm::PIMHeader::AssertMessage &', 
                   [])
    ## pimdm-packet.h (module 'pimdm'): uint16_t ns3::pimdm::PIMHeader::GetChecksum() const [member function]
    cls.add_method('GetChecksum', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::GraftAckMessage & ns3::pimdm::PIMHeader::GetGraftAckMessage() [member function]
    cls.add_method('GetGraftAckMessage', 
                   'ns3::pimdm::PIMHeader::GraftAckMessage &', 
                   [])
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::GraftMessage & ns3::pimdm::PIMHeader::GetGraftMessage() [member function]
    cls.add_method('GetGraftMessage', 
                   'ns3::pimdm::PIMHeader::GraftMessage &', 
                   [])
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::HelloMessage & ns3::pimdm::PIMHeader::GetHelloMessage() [member function]
    cls.add_method('GetHelloMessage', 
                   'ns3::pimdm::PIMHeader::HelloMessage &', 
                   [])
    ## pimdm-packet.h (module 'pimdm'): ns3::TypeId ns3::pimdm::PIMHeader::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::JoinPruneMessage & ns3::pimdm::PIMHeader::GetJoinPruneMessage() [member function]
    cls.add_method('GetJoinPruneMessage', 
                   'ns3::pimdm::PIMHeader::JoinPruneMessage &', 
                   [])
    ## pimdm-packet.h (module 'pimdm'): uint8_t ns3::pimdm::PIMHeader::GetReserved() const [member function]
    cls.add_method('GetReserved', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## pimdm-packet.h (module 'pimdm'): uint32_t ns3::pimdm::PIMHeader::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::StateRefreshMessage & ns3::pimdm::PIMHeader::GetStateRefreshMessage() [member function]
    cls.add_method('GetStateRefreshMessage', 
                   'ns3::pimdm::PIMHeader::StateRefreshMessage &', 
                   [])
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMType ns3::pimdm::PIMHeader::GetType() const [member function]
    cls.add_method('GetType', 
                   'ns3::pimdm::PIMType', 
                   [], 
                   is_const=True)
    ## pimdm-packet.h (module 'pimdm'): static ns3::TypeId ns3::pimdm::PIMHeader::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## pimdm-packet.h (module 'pimdm'): uint8_t ns3::pimdm::PIMHeader::GetVersion() const [member function]
    cls.add_method('GetVersion', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## pimdm-packet.h (module 'pimdm'): void ns3::pimdm::PIMHeader::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## pimdm-packet.h (module 'pimdm'): void ns3::pimdm::PIMHeader::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True, is_virtual=True)
    ## pimdm-packet.h (module 'pimdm'): void ns3::pimdm::PIMHeader::SetChecksum(uint8_t checksum) [member function]
    cls.add_method('SetChecksum', 
                   'void', 
                   [param('uint8_t', 'checksum')])
    ## pimdm-packet.h (module 'pimdm'): void ns3::pimdm::PIMHeader::SetReserved(uint8_t reserved) [member function]
    cls.add_method('SetReserved', 
                   'void', 
                   [param('uint8_t', 'reserved')])
    ## pimdm-packet.h (module 'pimdm'): void ns3::pimdm::PIMHeader::SetType(ns3::pimdm::PIMType type) [member function]
    cls.add_method('SetType', 
                   'void', 
                   [param('ns3::pimdm::PIMType', 'type')])
    ## pimdm-packet.h (module 'pimdm'): void ns3::pimdm::PIMHeader::SetVersion(uint8_t version) [member function]
    cls.add_method('SetVersion', 
                   'void', 
                   [param('uint8_t', 'version')])
    return

def register_Ns3PimdmPIMHeaderAssertMessage_methods(root_module, cls):
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::AssertMessage::AssertMessage() [constructor]
    cls.add_constructor([])
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::AssertMessage::AssertMessage(ns3::pimdm::PIMHeader::AssertMessage const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::pimdm::PIMHeader::AssertMessage const &', 'arg0')])
    ## pimdm-packet.h (module 'pimdm'): uint32_t ns3::pimdm::PIMHeader::AssertMessage::Deserialize(ns3::Buffer::Iterator start, uint32_t messageSize) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start'), param('uint32_t', 'messageSize')])
    ## pimdm-packet.h (module 'pimdm'): uint32_t ns3::pimdm::PIMHeader::AssertMessage::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## pimdm-packet.h (module 'pimdm'): void ns3::pimdm::PIMHeader::AssertMessage::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True)
    ## pimdm-packet.h (module 'pimdm'): void ns3::pimdm::PIMHeader::AssertMessage::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::AssertMessage::m_R [variable]
    cls.add_instance_attribute('m_R', 'uint8_t', is_const=False)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::AssertMessage::m_destination [variable]
    cls.add_instance_attribute('m_destination', 'ns3::Ipv4Address', is_const=False)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::AssertMessage::m_metric [variable]
    cls.add_instance_attribute('m_metric', 'uint32_t', is_const=False)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::AssertMessage::m_metricPreference [variable]
    cls.add_instance_attribute('m_metricPreference', 'uint32_t', is_const=False)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::AssertMessage::m_multicastGroupAddr [variable]
    cls.add_instance_attribute('m_multicastGroupAddr', 'ns3::pimdm::PIMHeader::EncodedGroup', is_const=False)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::AssertMessage::m_sourceAddr [variable]
    cls.add_instance_attribute('m_sourceAddr', 'ns3::pimdm::PIMHeader::EncodedUnicast', is_const=False)
    return

def register_Ns3PimdmPIMHeaderEncodedGroup_methods(root_module, cls):
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::EncodedGroup::EncodedGroup() [constructor]
    cls.add_constructor([])
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::EncodedGroup::EncodedGroup(ns3::pimdm::PIMHeader::EncodedGroup const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::pimdm::PIMHeader::EncodedGroup const &', 'arg0')])
    ## pimdm-packet.h (module 'pimdm'): uint32_t ns3::pimdm::PIMHeader::EncodedGroup::Deserialize(ns3::Buffer::Iterator start, uint32_t messageSize) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start'), param('uint32_t', 'messageSize')])
    ## pimdm-packet.h (module 'pimdm'): uint32_t ns3::pimdm::PIMHeader::EncodedGroup::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## pimdm-packet.h (module 'pimdm'): void ns3::pimdm::PIMHeader::EncodedGroup::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True)
    ## pimdm-packet.h (module 'pimdm'): void ns3::pimdm::PIMHeader::EncodedGroup::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::EncodedGroup::m_B [variable]
    cls.add_instance_attribute('m_B', 'uint8_t', is_const=False)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::EncodedGroup::m_Z [variable]
    cls.add_instance_attribute('m_Z', 'uint8_t', is_const=False)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::EncodedGroup::m_addressFamily [variable]
    cls.add_instance_attribute('m_addressFamily', 'uint8_t', is_const=False)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::EncodedGroup::m_encodingType [variable]
    cls.add_instance_attribute('m_encodingType', 'uint8_t', is_const=False)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::EncodedGroup::m_groupAddress [variable]
    cls.add_instance_attribute('m_groupAddress', 'ns3::Ipv4Address', is_const=False)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::EncodedGroup::m_maskLength [variable]
    cls.add_instance_attribute('m_maskLength', 'uint8_t', is_const=False)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::EncodedGroup::m_reserved [variable]
    cls.add_instance_attribute('m_reserved', 'uint8_t', is_const=False)
    return

def register_Ns3PimdmPIMHeaderEncodedSource_methods(root_module, cls):
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::EncodedSource::EncodedSource() [constructor]
    cls.add_constructor([])
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::EncodedSource::EncodedSource(ns3::pimdm::PIMHeader::EncodedSource const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::pimdm::PIMHeader::EncodedSource const &', 'arg0')])
    ## pimdm-packet.h (module 'pimdm'): uint32_t ns3::pimdm::PIMHeader::EncodedSource::Deserialize(ns3::Buffer::Iterator start, uint32_t messageSize) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start'), param('uint32_t', 'messageSize')])
    ## pimdm-packet.h (module 'pimdm'): uint32_t ns3::pimdm::PIMHeader::EncodedSource::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## pimdm-packet.h (module 'pimdm'): void ns3::pimdm::PIMHeader::EncodedSource::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True)
    ## pimdm-packet.h (module 'pimdm'): void ns3::pimdm::PIMHeader::EncodedSource::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::EncodedSource::m_R [variable]
    cls.add_instance_attribute('m_R', 'uint8_t', is_const=False)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::EncodedSource::m_S [variable]
    cls.add_instance_attribute('m_S', 'uint8_t', is_const=False)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::EncodedSource::m_W [variable]
    cls.add_instance_attribute('m_W', 'uint8_t', is_const=False)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::EncodedSource::m_addressFamily [variable]
    cls.add_instance_attribute('m_addressFamily', 'uint8_t', is_const=False)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::EncodedSource::m_encodingType [variable]
    cls.add_instance_attribute('m_encodingType', 'uint8_t', is_const=False)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::EncodedSource::m_maskLength [variable]
    cls.add_instance_attribute('m_maskLength', 'uint8_t', is_const=False)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::EncodedSource::m_reserved [variable]
    cls.add_instance_attribute('m_reserved', 'uint8_t', is_const=False)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::EncodedSource::m_sourceAddress [variable]
    cls.add_instance_attribute('m_sourceAddress', 'ns3::Ipv4Address', is_const=False)
    return

def register_Ns3PimdmPIMHeaderEncodedUnicast_methods(root_module, cls):
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::EncodedUnicast::EncodedUnicast() [constructor]
    cls.add_constructor([])
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::EncodedUnicast::EncodedUnicast(ns3::pimdm::PIMHeader::EncodedUnicast const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::pimdm::PIMHeader::EncodedUnicast const &', 'arg0')])
    ## pimdm-packet.h (module 'pimdm'): uint32_t ns3::pimdm::PIMHeader::EncodedUnicast::Deserialize(ns3::Buffer::Iterator start, uint32_t messageSize) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start'), param('uint32_t', 'messageSize')])
    ## pimdm-packet.h (module 'pimdm'): uint32_t ns3::pimdm::PIMHeader::EncodedUnicast::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## pimdm-packet.h (module 'pimdm'): void ns3::pimdm::PIMHeader::EncodedUnicast::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True)
    ## pimdm-packet.h (module 'pimdm'): void ns3::pimdm::PIMHeader::EncodedUnicast::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::EncodedUnicast::m_addressFamily [variable]
    cls.add_instance_attribute('m_addressFamily', 'uint8_t', is_const=False)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::EncodedUnicast::m_encodingType [variable]
    cls.add_instance_attribute('m_encodingType', 'uint8_t', is_const=False)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::EncodedUnicast::m_unicastAddress [variable]
    cls.add_instance_attribute('m_unicastAddress', 'ns3::Ipv4Address', is_const=False)
    return

def register_Ns3PimdmPIMHeaderGraftAckMessage_methods(root_module, cls):
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::GraftAckMessage::GraftAckMessage() [constructor]
    cls.add_constructor([])
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::GraftAckMessage::GraftAckMessage(ns3::pimdm::PIMHeader::GraftAckMessage const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::pimdm::PIMHeader::GraftAckMessage const &', 'arg0')])
    ## pimdm-packet.h (module 'pimdm'): uint32_t ns3::pimdm::PIMHeader::GraftAckMessage::Deserialize(ns3::Buffer::Iterator start, uint32_t messageSize) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start'), param('uint32_t', 'messageSize')])
    ## pimdm-packet.h (module 'pimdm'): uint32_t ns3::pimdm::PIMHeader::GraftAckMessage::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## pimdm-packet.h (module 'pimdm'): void ns3::pimdm::PIMHeader::GraftAckMessage::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True)
    ## pimdm-packet.h (module 'pimdm'): void ns3::pimdm::PIMHeader::GraftAckMessage::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::GraftAckMessage::m_joinPruneMessage [variable]
    cls.add_instance_attribute('m_joinPruneMessage', 'ns3::pimdm::PIMHeader::JoinPruneGraftMessage', is_const=False)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::GraftAckMessage::m_multicastGroups [variable]
    cls.add_instance_attribute('m_multicastGroups', 'std::vector< ns3::pimdm::PIMHeader::MulticastGroupEntry >', is_const=False)
    return

def register_Ns3PimdmPIMHeaderGraftMessage_methods(root_module, cls):
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::GraftMessage::GraftMessage() [constructor]
    cls.add_constructor([])
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::GraftMessage::GraftMessage(ns3::pimdm::PIMHeader::GraftMessage const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::pimdm::PIMHeader::GraftMessage const &', 'arg0')])
    ## pimdm-packet.h (module 'pimdm'): uint32_t ns3::pimdm::PIMHeader::GraftMessage::Deserialize(ns3::Buffer::Iterator start, uint32_t messageSize) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start'), param('uint32_t', 'messageSize')])
    ## pimdm-packet.h (module 'pimdm'): uint32_t ns3::pimdm::PIMHeader::GraftMessage::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## pimdm-packet.h (module 'pimdm'): void ns3::pimdm::PIMHeader::GraftMessage::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True)
    ## pimdm-packet.h (module 'pimdm'): void ns3::pimdm::PIMHeader::GraftMessage::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::GraftMessage::m_joinPruneMessage [variable]
    cls.add_instance_attribute('m_joinPruneMessage', 'ns3::pimdm::PIMHeader::JoinPruneGraftMessage', is_const=False)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::GraftMessage::m_multicastGroups [variable]
    cls.add_instance_attribute('m_multicastGroups', 'std::vector< ns3::pimdm::PIMHeader::MulticastGroupEntry >', is_const=False)
    return

def register_Ns3PimdmPIMHeaderHelloMessage_methods(root_module, cls):
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::HelloMessage::HelloMessage() [constructor]
    cls.add_constructor([])
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::HelloMessage::HelloMessage(ns3::pimdm::PIMHeader::HelloMessage const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::pimdm::PIMHeader::HelloMessage const &', 'arg0')])
    ## pimdm-packet.h (module 'pimdm'): uint32_t ns3::pimdm::PIMHeader::HelloMessage::Deserialize(ns3::Buffer::Iterator start, uint32_t messageSize) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start'), param('uint32_t', 'messageSize')])
    ## pimdm-packet.h (module 'pimdm'): uint32_t ns3::pimdm::PIMHeader::HelloMessage::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## pimdm-packet.h (module 'pimdm'): void ns3::pimdm::PIMHeader::HelloMessage::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True)
    ## pimdm-packet.h (module 'pimdm'): void ns3::pimdm::PIMHeader::HelloMessage::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::HelloMessage::m_destination [variable]
    cls.add_instance_attribute('m_destination', 'ns3::Ipv4Address', is_const=False)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::HelloMessage::m_optionList [variable]
    cls.add_instance_attribute('m_optionList', 'std::vector< ns3::pimdm::PIMHeader::HelloMessage::HelloEntry >', is_const=False)
    return

def register_Ns3PimdmPIMHeaderHelloMessageHelloEntry_methods(root_module, cls):
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::HelloMessage::HelloEntry() [constructor]
    cls.add_constructor([])
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::HelloMessage::HelloEntry(ns3::pimdm::PIMHeader::HelloMessage::HelloEntry const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::pimdm::PIMHeader::HelloMessage::HelloEntry const &', 'arg0')])
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::HelloMessage::HelloEntry::generationID [variable]
    cls.add_instance_attribute('generationID', 'ns3::pimdm::PIMHeader::HelloMessage::HelloEntry::GenerationID', is_const=False)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::HelloMessage::HelloEntry::holdTime [variable]
    cls.add_instance_attribute('holdTime', 'ns3::pimdm::PIMHeader::HelloMessage::HelloEntry::HoldTime', is_const=False)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::HelloMessage::HelloEntry::lanPruneDelay [variable]
    cls.add_instance_attribute('lanPruneDelay', 'ns3::pimdm::PIMHeader::HelloMessage::HelloEntry::LanPruneDelay', is_const=False)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::HelloMessage::HelloEntry::stateRefreshCapable [variable]
    cls.add_instance_attribute('stateRefreshCapable', 'ns3::pimdm::PIMHeader::HelloMessage::HelloEntry::StateRefreshCapable', is_const=False)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::HelloMessage::HelloEntry::HelloEntry() [constructor]
    cls.add_constructor([])
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::HelloMessage::HelloEntry::HelloEntry(ns3::pimdm::PIMHeader::HelloMessage::HelloEntry const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::pimdm::PIMHeader::HelloMessage::HelloEntry const &', 'arg0')])
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::HelloMessage::HelloEntry::m_optionLength [variable]
    cls.add_instance_attribute('m_optionLength', 'uint16_t', is_const=False)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::HelloMessage::HelloEntry::m_optionType [variable]
    cls.add_instance_attribute('m_optionType', 'ns3::pimdm::PIMHeader::HelloMessage::OptionType', is_const=False)
    return

def register_Ns3PimdmPIMHeaderHelloMessageHelloEntryGenerationID_methods(root_module, cls):
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::HelloMessage::HelloEntry::GenerationID::GenerationID() [constructor]
    cls.add_constructor([])
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::HelloMessage::HelloEntry::GenerationID::GenerationID(ns3::pimdm::PIMHeader::HelloMessage::HelloEntry::GenerationID const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::pimdm::PIMHeader::HelloMessage::HelloEntry::GenerationID const &', 'arg0')])
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::HelloMessage::HelloEntry::GenerationID::m_generatioID [variable]
    cls.add_instance_attribute('m_generatioID', 'uint32_t', is_const=False)
    return

def register_Ns3PimdmPIMHeaderHelloMessageHelloEntryHoldTime_methods(root_module, cls):
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::HelloMessage::HelloEntry::HoldTime::HoldTime() [constructor]
    cls.add_constructor([])
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::HelloMessage::HelloEntry::HoldTime::HoldTime(ns3::pimdm::PIMHeader::HelloMessage::HelloEntry::HoldTime const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::pimdm::PIMHeader::HelloMessage::HelloEntry::HoldTime const &', 'arg0')])
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::HelloMessage::HelloEntry::HoldTime::m_holdTime [variable]
    cls.add_instance_attribute('m_holdTime', 'ns3::Time', is_const=False)
    return

def register_Ns3PimdmPIMHeaderHelloMessageHelloEntryLanPruneDelay_methods(root_module, cls):
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::HelloMessage::HelloEntry::LanPruneDelay::LanPruneDelay() [constructor]
    cls.add_constructor([])
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::HelloMessage::HelloEntry::LanPruneDelay::LanPruneDelay(ns3::pimdm::PIMHeader::HelloMessage::HelloEntry::LanPruneDelay const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::pimdm::PIMHeader::HelloMessage::HelloEntry::LanPruneDelay const &', 'arg0')])
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::HelloMessage::HelloEntry::LanPruneDelay::m_T [variable]
    cls.add_instance_attribute('m_T', 'uint8_t', is_const=False)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::HelloMessage::HelloEntry::LanPruneDelay::m_overrideInterval [variable]
    cls.add_instance_attribute('m_overrideInterval', 'ns3::Time', is_const=False)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::HelloMessage::HelloEntry::LanPruneDelay::m_propagationDelay [variable]
    cls.add_instance_attribute('m_propagationDelay', 'ns3::Time', is_const=False)
    return

def register_Ns3PimdmPIMHeaderHelloMessageHelloEntryStateRefreshCapable_methods(root_module, cls):
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::HelloMessage::HelloEntry::StateRefreshCapable::StateRefreshCapable() [constructor]
    cls.add_constructor([])
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::HelloMessage::HelloEntry::StateRefreshCapable::StateRefreshCapable(ns3::pimdm::PIMHeader::HelloMessage::HelloEntry::StateRefreshCapable const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::pimdm::PIMHeader::HelloMessage::HelloEntry::StateRefreshCapable const &', 'arg0')])
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::HelloMessage::HelloEntry::StateRefreshCapable::m_interval [variable]
    cls.add_instance_attribute('m_interval', 'uint8_t', is_const=False)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::HelloMessage::HelloEntry::StateRefreshCapable::m_reserved [variable]
    cls.add_instance_attribute('m_reserved', 'uint16_t', is_const=False)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::HelloMessage::HelloEntry::StateRefreshCapable::m_version [variable]
    cls.add_instance_attribute('m_version', 'uint8_t', is_const=False)
    return

def register_Ns3PimdmPIMHeaderJoinPruneGraftMessage_methods(root_module, cls):
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::JoinPruneGraftMessage::JoinPruneGraftMessage() [constructor]
    cls.add_constructor([])
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::JoinPruneGraftMessage::JoinPruneGraftMessage(ns3::pimdm::PIMHeader::JoinPruneGraftMessage const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::pimdm::PIMHeader::JoinPruneGraftMessage const &', 'arg0')])
    ## pimdm-packet.h (module 'pimdm'): uint32_t ns3::pimdm::PIMHeader::JoinPruneGraftMessage::Deserialize(ns3::Buffer::Iterator start, uint32_t messageSize) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start'), param('uint32_t', 'messageSize')])
    ## pimdm-packet.h (module 'pimdm'): uint32_t ns3::pimdm::PIMHeader::JoinPruneGraftMessage::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## pimdm-packet.h (module 'pimdm'): void ns3::pimdm::PIMHeader::JoinPruneGraftMessage::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True)
    ## pimdm-packet.h (module 'pimdm'): void ns3::pimdm::PIMHeader::JoinPruneGraftMessage::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::JoinPruneGraftMessage::m_holdTime [variable]
    cls.add_instance_attribute('m_holdTime', 'ns3::Time', is_const=False)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::JoinPruneGraftMessage::m_numGroups [variable]
    cls.add_instance_attribute('m_numGroups', 'uint8_t', is_const=False)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::JoinPruneGraftMessage::m_reserved [variable]
    cls.add_instance_attribute('m_reserved', 'uint8_t', is_const=False)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::JoinPruneGraftMessage::m_upstreamNeighborAddr [variable]
    cls.add_instance_attribute('m_upstreamNeighborAddr', 'ns3::pimdm::PIMHeader::EncodedUnicast', is_const=False)
    return

def register_Ns3PimdmPIMHeaderJoinPruneMessage_methods(root_module, cls):
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::JoinPruneMessage::JoinPruneMessage() [constructor]
    cls.add_constructor([])
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::JoinPruneMessage::JoinPruneMessage(ns3::pimdm::PIMHeader::JoinPruneMessage const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::pimdm::PIMHeader::JoinPruneMessage const &', 'arg0')])
    ## pimdm-packet.h (module 'pimdm'): uint32_t ns3::pimdm::PIMHeader::JoinPruneMessage::Deserialize(ns3::Buffer::Iterator start, uint32_t messageSize) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start'), param('uint32_t', 'messageSize')])
    ## pimdm-packet.h (module 'pimdm'): uint32_t ns3::pimdm::PIMHeader::JoinPruneMessage::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## pimdm-packet.h (module 'pimdm'): void ns3::pimdm::PIMHeader::JoinPruneMessage::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True)
    ## pimdm-packet.h (module 'pimdm'): void ns3::pimdm::PIMHeader::JoinPruneMessage::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::JoinPruneMessage::m_joinPruneMessage [variable]
    cls.add_instance_attribute('m_joinPruneMessage', 'ns3::pimdm::PIMHeader::JoinPruneGraftMessage', is_const=False)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::JoinPruneMessage::m_multicastGroups [variable]
    cls.add_instance_attribute('m_multicastGroups', 'std::vector< ns3::pimdm::PIMHeader::MulticastGroupEntry >', is_const=False)
    return

def register_Ns3PimdmPIMHeaderMulticastGroupEntry_methods(root_module, cls):
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::MulticastGroupEntry::MulticastGroupEntry(ns3::pimdm::PIMHeader::MulticastGroupEntry const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::pimdm::PIMHeader::MulticastGroupEntry const &', 'arg0')])
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::MulticastGroupEntry::MulticastGroupEntry() [constructor]
    cls.add_constructor([])
    ## pimdm-packet.h (module 'pimdm'): uint32_t ns3::pimdm::PIMHeader::MulticastGroupEntry::Deserialize(ns3::Buffer::Iterator start, uint32_t messageSize) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start'), param('uint32_t', 'messageSize')])
    ## pimdm-packet.h (module 'pimdm'): uint32_t ns3::pimdm::PIMHeader::MulticastGroupEntry::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## pimdm-packet.h (module 'pimdm'): void ns3::pimdm::PIMHeader::MulticastGroupEntry::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True)
    ## pimdm-packet.h (module 'pimdm'): void ns3::pimdm::PIMHeader::MulticastGroupEntry::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::MulticastGroupEntry::m_joinedSourceAddrs [variable]
    cls.add_instance_attribute('m_joinedSourceAddrs', 'std::vector< ns3::pimdm::PIMHeader::EncodedSource >', is_const=False)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::MulticastGroupEntry::m_multicastGroupAddr [variable]
    cls.add_instance_attribute('m_multicastGroupAddr', 'ns3::pimdm::PIMHeader::EncodedGroup', is_const=False)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::MulticastGroupEntry::m_numberJoinedSources [variable]
    cls.add_instance_attribute('m_numberJoinedSources', 'uint16_t', is_const=False)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::MulticastGroupEntry::m_numberPrunedSources [variable]
    cls.add_instance_attribute('m_numberPrunedSources', 'uint16_t', is_const=False)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::MulticastGroupEntry::m_prunedSourceAddrs [variable]
    cls.add_instance_attribute('m_prunedSourceAddrs', 'std::vector< ns3::pimdm::PIMHeader::EncodedSource >', is_const=False)
    return

def register_Ns3PimdmPIMHeaderStateRefreshMessage_methods(root_module, cls):
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::StateRefreshMessage::StateRefreshMessage() [constructor]
    cls.add_constructor([])
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::StateRefreshMessage::StateRefreshMessage(ns3::pimdm::PIMHeader::StateRefreshMessage const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::pimdm::PIMHeader::StateRefreshMessage const &', 'arg0')])
    ## pimdm-packet.h (module 'pimdm'): uint32_t ns3::pimdm::PIMHeader::StateRefreshMessage::Deserialize(ns3::Buffer::Iterator start, uint32_t messageSize) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start'), param('uint32_t', 'messageSize')])
    ## pimdm-packet.h (module 'pimdm'): uint32_t ns3::pimdm::PIMHeader::StateRefreshMessage::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## pimdm-packet.h (module 'pimdm'): void ns3::pimdm::PIMHeader::StateRefreshMessage::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True)
    ## pimdm-packet.h (module 'pimdm'): void ns3::pimdm::PIMHeader::StateRefreshMessage::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::StateRefreshMessage::m_N [variable]
    cls.add_instance_attribute('m_N', 'uint8_t', is_const=False)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::StateRefreshMessage::m_O [variable]
    cls.add_instance_attribute('m_O', 'uint8_t', is_const=False)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::StateRefreshMessage::m_P [variable]
    cls.add_instance_attribute('m_P', 'uint8_t', is_const=False)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::StateRefreshMessage::m_R [variable]
    cls.add_instance_attribute('m_R', 'uint8_t', is_const=False)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::StateRefreshMessage::m_interval [variable]
    cls.add_instance_attribute('m_interval', 'uint8_t', is_const=False)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::StateRefreshMessage::m_maskLength [variable]
    cls.add_instance_attribute('m_maskLength', 'uint8_t', is_const=False)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::StateRefreshMessage::m_metric [variable]
    cls.add_instance_attribute('m_metric', 'uint32_t', is_const=False)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::StateRefreshMessage::m_metricPreference [variable]
    cls.add_instance_attribute('m_metricPreference', 'uint32_t', is_const=False)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::StateRefreshMessage::m_multicastGroupAddr [variable]
    cls.add_instance_attribute('m_multicastGroupAddr', 'ns3::pimdm::PIMHeader::EncodedGroup', is_const=False)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::StateRefreshMessage::m_originatorAddr [variable]
    cls.add_instance_attribute('m_originatorAddr', 'ns3::pimdm::PIMHeader::EncodedUnicast', is_const=False)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::StateRefreshMessage::m_reserved [variable]
    cls.add_instance_attribute('m_reserved', 'uint8_t', is_const=False)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::StateRefreshMessage::m_sourceAddr [variable]
    cls.add_instance_attribute('m_sourceAddr', 'ns3::pimdm::PIMHeader::EncodedUnicast', is_const=False)
    ## pimdm-packet.h (module 'pimdm'): ns3::pimdm::PIMHeader::StateRefreshMessage::m_ttl [variable]
    cls.add_instance_attribute('m_ttl', 'uint8_t', is_const=False)
    return

def register_Ns3PimdmRelayTag_methods(root_module, cls):
    ## pimdm-routing.h (module 'pimdm'): ns3::pimdm::RelayTag::RelayTag(ns3::pimdm::RelayTag const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::pimdm::RelayTag const &', 'arg0')])
    ## pimdm-routing.h (module 'pimdm'): ns3::pimdm::RelayTag::RelayTag(ns3::Ipv4Address sender=ns3::Ipv4Address::GetAny(), ns3::Ipv4Address receiver=ns3::Ipv4Address::GetAny()) [constructor]
    cls.add_constructor([param('ns3::Ipv4Address', 'sender', default_value='ns3::Ipv4Address::GetAny()'), param('ns3::Ipv4Address', 'receiver', default_value='ns3::Ipv4Address::GetAny()')])
    ## pimdm-routing.h (module 'pimdm'): void ns3::pimdm::RelayTag::Deserialize(ns3::TagBuffer i) [member function]
    cls.add_method('Deserialize', 
                   'void', 
                   [param('ns3::TagBuffer', 'i')], 
                   is_virtual=True)
    ## pimdm-routing.h (module 'pimdm'): ns3::TypeId ns3::pimdm::RelayTag::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## pimdm-routing.h (module 'pimdm'): uint32_t ns3::pimdm::RelayTag::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## pimdm-routing.h (module 'pimdm'): static ns3::TypeId ns3::pimdm::RelayTag::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## pimdm-routing.h (module 'pimdm'): void ns3::pimdm::RelayTag::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## pimdm-routing.h (module 'pimdm'): void ns3::pimdm::RelayTag::Serialize(ns3::TagBuffer i) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::TagBuffer', 'i')], 
                   is_const=True, is_virtual=True)
    ## pimdm-routing.h (module 'pimdm'): ns3::pimdm::RelayTag::m_receiver [variable]
    cls.add_instance_attribute('m_receiver', 'ns3::Ipv4Address', is_const=False)
    ## pimdm-routing.h (module 'pimdm'): ns3::pimdm::RelayTag::m_sender [variable]
    cls.add_instance_attribute('m_sender', 'ns3::Ipv4Address', is_const=False)
    return

def register_Ns3PimdmRoutingMulticastTable_methods(root_module, cls):
    ## pimdm-routing.h (module 'pimdm'): ns3::pimdm::RoutingMulticastTable::RoutingMulticastTable(ns3::pimdm::RoutingMulticastTable const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::pimdm::RoutingMulticastTable const &', 'arg0')])
    ## pimdm-routing.h (module 'pimdm'): ns3::pimdm::RoutingMulticastTable::RoutingMulticastTable() [constructor]
    cls.add_constructor([])
    ## pimdm-routing.h (module 'pimdm'): ns3::pimdm::RoutingMulticastTable::groupAddr [variable]
    cls.add_instance_attribute('groupAddr', 'ns3::Ipv4Address', is_const=False)
    ## pimdm-routing.h (module 'pimdm'): ns3::pimdm::RoutingMulticastTable::mgroup [variable]
    cls.add_instance_attribute('mgroup', 'std::map< ns3::Ipv4Address, ns3::pimdm::MulticastEntry >', is_const=False)
    return

def register_Ns3PimdmSourceGroupPair_methods(root_module, cls):
    cls.add_binary_comparison_operator('<')
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::SourceGroupPair::SourceGroupPair(ns3::pimdm::SourceGroupPair const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::pimdm::SourceGroupPair const &', 'arg0')])
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::SourceGroupPair::SourceGroupPair() [constructor]
    cls.add_constructor([])
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::SourceGroupPair::SourceGroupPair(ns3::Ipv4Address s, ns3::Ipv4Address g) [constructor]
    cls.add_constructor([param('ns3::Ipv4Address', 's'), param('ns3::Ipv4Address', 'g')])
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::SourceGroupPair::SourceGroupPair(ns3::Ipv4Address s, ns3::Ipv4Address g, ns3::Ipv4Address n) [constructor]
    cls.add_constructor([param('ns3::Ipv4Address', 's'), param('ns3::Ipv4Address', 'g'), param('ns3::Ipv4Address', 'n')])
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::SourceGroupPair::groupMulticastAddr [variable]
    cls.add_instance_attribute('groupMulticastAddr', 'ns3::Ipv4Address', is_const=False)
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::SourceGroupPair::nextMulticastAddr [variable]
    cls.add_instance_attribute('nextMulticastAddr', 'ns3::Ipv4Address', is_const=False)
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::SourceGroupPair::sourceMulticastAddr [variable]
    cls.add_instance_attribute('sourceMulticastAddr', 'ns3::Ipv4Address', is_const=False)
    return

def register_Ns3PimdmSourceGroupState_methods(root_module, cls):
    cls.add_binary_comparison_operator('==')
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::SourceGroupState::SourceGroupState(ns3::pimdm::SourceGroupState const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::pimdm::SourceGroupState const &', 'arg0')])
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::SourceGroupState::SourceGroupState(ns3::pimdm::SourceGroupPair sgp) [constructor]
    cls.add_constructor([param('ns3::pimdm::SourceGroupPair', 'sgp')])
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::SourceGroupState::AssertState [variable]
    cls.add_instance_attribute('AssertState', 'ns3::pimdm::AssertWinnerState', is_const=False)
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::SourceGroupState::AssertWinner [variable]
    cls.add_instance_attribute('AssertWinner', 'ns3::pimdm::AssertMetric', is_const=False)
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::SourceGroupState::LocalMembership [variable]
    cls.add_instance_attribute('LocalMembership', 'ns3::pimdm::LocalMembership', is_const=False)
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::SourceGroupState::PruneState [variable]
    cls.add_instance_attribute('PruneState', 'ns3::pimdm::PruneState', is_const=False)
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::SourceGroupState::SGAM [variable]
    cls.add_instance_attribute('SGAM', 'uint32_t', is_const=False)
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::SourceGroupState::SGPair [variable]
    cls.add_instance_attribute('SGPair', 'ns3::pimdm::SourceGroupPair', is_const=False)
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::SourceGroupState::SG_AT [variable]
    cls.add_instance_attribute('SG_AT', 'ns3::Timer', is_const=False)
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::SourceGroupState::SG_DATA_TTL [variable]
    cls.add_instance_attribute('SG_DATA_TTL', 'uint8_t', is_const=False)
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::SourceGroupState::SG_PLTD [variable]
    cls.add_instance_attribute('SG_PLTD', 'ns3::Timer', is_const=False)
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::SourceGroupState::SG_PPT [variable]
    cls.add_instance_attribute('SG_PPT', 'ns3::Timer', is_const=False)
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::SourceGroupState::SG_PT [variable]
    cls.add_instance_attribute('SG_PT', 'ns3::Timer', is_const=False)
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::SourceGroupState::SG_SR_TTL [variable]
    cls.add_instance_attribute('SG_SR_TTL', 'uint8_t', is_const=False)
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::SourceGroupState::lastStateRefresh [variable]
    cls.add_instance_attribute('lastStateRefresh', 'ns3::Time', is_const=False)
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::SourceGroupState::upstream [variable]
    cls.add_instance_attribute('upstream', 'ns3::pimdm::UpstreamState', is_const=False)
    return

def register_Ns3PimdmUpstreamState_methods(root_module, cls):
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::UpstreamState::UpstreamState(ns3::pimdm::UpstreamState const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::pimdm::UpstreamState const &', 'arg0')])
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::UpstreamState::UpstreamState() [constructor]
    cls.add_constructor([])
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::UpstreamState::UpstreamState(bool valid) [constructor]
    cls.add_constructor([param('bool', 'valid')])
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::UpstreamState::GraftPrune [variable]
    cls.add_instance_attribute('GraftPrune', 'ns3::pimdm::GraftPruneState', is_const=False)
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::UpstreamState::SG_GRT [variable]
    cls.add_instance_attribute('SG_GRT', 'ns3::Timer', is_const=False)
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::UpstreamState::SG_OT [variable]
    cls.add_instance_attribute('SG_OT', 'ns3::Timer', is_const=False)
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::UpstreamState::SG_PLT [variable]
    cls.add_instance_attribute('SG_PLT', 'ns3::Timer', is_const=False)
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::UpstreamState::SG_SAT [variable]
    cls.add_instance_attribute('SG_SAT', 'ns3::Timer', is_const=False)
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::UpstreamState::SG_SRT [variable]
    cls.add_instance_attribute('SG_SRT', 'ns3::Timer', is_const=False)
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::UpstreamState::origination [variable]
    cls.add_instance_attribute('origination', 'ns3::pimdm::Origination', is_const=False)
    ## pimdm-structure.h (module 'pimdm'): ns3::pimdm::UpstreamState::valid [variable]
    cls.add_instance_attribute('valid', 'bool', is_const=False)
    return

def register_functions(root_module):
    module = root_module
    register_functions_ns3_FatalImpl(module.get_submodule('FatalImpl'), root_module)
    register_functions_ns3_aodv(module.get_submodule('aodv'), root_module)
    register_functions_ns3_dsdv(module.get_submodule('dsdv'), root_module)
    register_functions_ns3_internal(module.get_submodule('internal'), root_module)
    register_functions_ns3_mbn(module.get_submodule('mbn'), root_module)
    register_functions_ns3_olsr(module.get_submodule('olsr'), root_module)
    register_functions_ns3_pimdm(module.get_submodule('pimdm'), root_module)
    return

def register_functions_ns3_FatalImpl(module, root_module):
    return

def register_functions_ns3_aodv(module, root_module):
    return

def register_functions_ns3_dsdv(module, root_module):
    return

def register_functions_ns3_internal(module, root_module):
    return

def register_functions_ns3_mbn(module, root_module):
    return

def register_functions_ns3_olsr(module, root_module):
    return

def register_functions_ns3_pimdm(module, root_module):
    return

def main():
    out = FileCodeSink(sys.stdout)
    root_module = module_init()
    register_types(root_module)
    register_methods(root_module)
    register_functions(root_module)
    root_module.generate(out)

if __name__ == '__main__':
    main()

