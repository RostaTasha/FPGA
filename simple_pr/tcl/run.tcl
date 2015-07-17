###############################################################
###   Main flow - Do Not Edit
###############################################################
#TODO: For now defing the script version here... find a better home like the README or design.tcl?
set scriptVer "2014.2"
set vivadoVer [version -short]
#Bypass version check if script version is not specified
if {[info exists scriptVer]} {
   if {![string match $scriptVer $vivadoVer]} {
#      set errMsg "ERROR: Specified script version $scriptVer does not match Vivado version $vivadoVer.\n"
      set errMsg "Critical Warning: Specified script version $scriptVer does not match Vivado version $vivadoVer.\n"
      append errMsg "Either change the version of scripts being used or run with the correct version of Vivado."
#      error $errMsg
      puts "$errMsg"
   }
}
set runLog "run"
set commandLog "command"
set criticalLog "critical"
set logs [list $runLog $commandLog $criticalLog]
foreach log $logs {
   if {[file exists ${log}.log]} {
      file copy -force $log.log ${log}_prev.log
   }
}
set rfh [open "$runLog.log" w]
set cfh [open "$commandLog.log" w]
set wfh [open "$criticalLog.log" w]

#### Set Tcl Params
if {[info exists tclParams] && [llength $tclParams] > 0} {
   set_parameters $tclParams
}

#### Run Synthesis on any modules requiring synthesis
if {[llength $modules] > 0} {
   foreach module $modules {
      if {[get_attribute module $module synth]} {
       puts $rfh "\n#HD: Running synthesis for block $module"
       command "puts \"#HD: Running synthesis for block $module\""
       synth $module
       puts "#HD: Synthesis of module $module complete\n"
    }
  }
}

#### Run Top-Down implementation before OOC
if {[llength $implementations] > 0} {
   foreach impl $implementations {
      if {[get_attribute impl $impl impl] && [get_attribute impl $impl td.impl]} {
         #Override directives if directive file is specified
         if {[info exists useDirectives]} {
            puts "#HD: Overriding directives for implementation $impl"
            set_directives impl $impl
         }
         puts $rfh "#HD: Running implementation $impl"
         command "puts \"#HD: Running implementation $impl\""
         impl $impl
         puts "#HD: Implementation $impl complete\n"
      }
   }
}
#### Run OOC Implementations
if {[llength $ooc_implementations] > 0} {
   foreach ooc_impl $ooc_implementations {
      if {[get_attribute ooc $ooc_impl impl]} {
         #Override directives if directive file is specified
         if {[info exists useDirectives]} {
            puts "#HD: Overriding directives for implementation $ooc_impl"
            set_directives ooc $ooc_impl
         }
         puts $rfh "#HD: Running ooc implementation $ooc_impl (OUT-OF-CONTEXT)"
         command "puts \"#HD: Running OOC implementation $ooc_impl (OUT-OF-CONTEXT)\""
         ooc_impl $ooc_impl
         puts "#HD: OOC implementation of $ooc_impl complete\n"
      }
   }
}

#### Run PR configurations
if {[llength $configurations] > 0} {
   sort_configurations
   foreach config $configurations {
      if {[get_attribute config $config impl]} {
         #Override directives if directive file is specified
         if {[info exists useDirectives]} {
            puts "#HD: Overriding directives for configuration $config"
            set_directives config $config
         }
         puts $rfh "#HD: Running PR implementation $config (Partial Reconfiguration)" 
         command "puts \"#HD: Running PR implementation $config (Partial Reconfiguration)\"" 
         pr_impl $config
         puts "#HD: PR implementation of $config complete\n"
      }
   }
}

#### Run Assembly and Flat implementations
if {[llength $implementations] > 0} {
   foreach impl $implementations {
      if {[get_attribute impl $impl impl] && ![get_attribute impl $impl td.impl]} {
         #Override directives if directive file is specified
         if {[info exists useDirectives]} {
            puts "#HD: Overriding directives for implementation $impl"
            set_directives impl $impl
         }
         puts $rfh "#HD: Running implementation $impl"
         command "puts \"#HD: Running implementation $impl\""
         impl $impl
         puts "#HD: Implementation $impl complete\n"
      }
   }
}

#### Run PR verify 
if {[llength $configurations] > 1} {
   set start_time [clock seconds]
   puts $rfh "\n#HD: Running pr_verify on all configurations with attribute \"verify\" set to \'1\'" 
   command "puts \"#HD: Running pr_verify on all configurations([llength $configurations])\""
   verify_configs $configurations
   set end_time [clock seconds]
   log_time pr_verify $start_time $end_time 1 "[llength $configurations] Configurations"
}

#### Genearte PR bitstreams 
if {[llength $configurations] > 0} {
   set start_time [clock seconds]
   puts $rfh "\n#HD: Running write_bitstream on all configurations with attribute \"bitstream\" set to \'1\'" 
   command "puts \"#HD: Running write_bitstream on all configurations([llength $configurations])\""
   generate_pr_bitstreams $configurations
   set end_time [clock seconds]
   log_time write_bitstream $start_time $end_time 1 "[llength $configurations] Configurations"

}

close $rfh
close $cfh
close $wfh
