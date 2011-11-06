## -*- Mode: python; py-indent-offset: 4; indent-tabs-mode: nil; coding: utf-8; -*-

def build(bld):
    module = bld.create_ns3_module('pimdm', ['internet', 'point-to-point', 'wifi', 'mobility', 'applications', 'csma',  'virtual-net-device', 'aodv', 'mbn-aodv', 'olsr'])
    module.includes = '.'
    module.source = [
        'model/pimdm-packet.cc',
        'model/pimdm-routing.cc',
        'helper/pimdm-helper.cc',
        ]
        
    headers = bld.new_task_gen(features=['ns3header'])
    headers.module = 'pimdm'
    headers.source = [
        'model/pimdm-common.h',
        'model/pimdm-packet.h',
        'model/pimdm-structure.h',
        'model/pimdm-routing.h',
        'helper/pimdm-helper.h',
    ]
               
    module_test = bld.create_ns3_module_test_library('pimdm')
    module_test.source = [
          'test/pim-header-test-suite.cc',
          ]
    
    if bld.env['ENABLE_EXAMPLES']:
        bld.add_subdirs('examples')
        
#    bld.ns3_python_bindings()
