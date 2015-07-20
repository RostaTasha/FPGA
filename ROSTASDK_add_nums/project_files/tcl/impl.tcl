###########################
#### Implement Modules ####
###########################
proc impl {impl} {
   global part
   global dcpLevel
   global verbose
   global implDir
   global xdcDir
   global dcpDir
   global modules
   global ooc_implementations 

   set top                 [get_attribute impl $impl top]
   set implXDC             [get_attribute impl $impl implXDC]
   set linkXDC             [get_attribute impl $impl linkXDC]
   set cores               [get_attribute impl $impl cores]
   set hd                  [get_attribute impl $impl hd.impl]
   set td                  [get_attribute impl $impl td.impl]
   set ic                  [get_attribute impl $impl ic.impl]
   set partitions          [get_attribute impl $impl partitions]
   set link                [get_attribute impl $impl link]
   set opt                 [get_attribute impl $impl opt]
   set opt.pre             [get_attribute impl $impl opt.pre]
   set opt_options         [get_attribute impl $impl opt_options]
   set opt_directive       [get_attribute impl $impl opt_directive]
   set place               [get_attribute impl $impl place]
   set place.pre           [get_attribute impl $impl place.pre]
   set place_options       [get_attribute impl $impl place_options]
   set place_directive     [get_attribute impl $impl place_directive]
   set phys                [get_attribute impl $impl phys]
   set phys.pre            [get_attribute impl $impl phys.pre]
   set phys_options        [get_attribute impl $impl phys_options]
   set phys_directive      [get_attribute impl $impl phys_directive]
   set route               [get_attribute impl $impl route]
   set route.pre           [get_attribute impl $impl route.pre]
   set route_options       [get_attribute impl $impl route_options]
   set route_directive     [get_attribute impl $impl route_directive]
   set bitstream           [get_attribute impl $impl bitstream]
   set bitstream.pre       [get_attribute impl $impl bitstream.pre]
   set bitstream_options   [get_attribute impl $impl bitstream_options]
   set bitstream_settings  [get_attribute impl $impl bitstream_settings]
   set drc.quiet           [get_attribute impl $impl drc.quiet]


   if {($hd && $td) || ($hd && $ic) || ($td && $ic)} {
      set errMsg "\nERROR: Implementation $impl has more than one of the following flow variables set to 1 \n\thd.impl\n\ttd.impl\n\tic.impl\nOnly one of these variables can be set true at one time. To run multiple flows, create separate implementation runs."
      error $errMsg
   }
   # Make the implementation directory if needed
   if {![file exists $implDir]} {
      command "file mkdir $implDir"
   }
   set resultDir "$implDir/$impl"
   set reportDir "$resultDir/reports"
   puts "\tWriting results to: $resultDir"
   puts "\tWriting reports to: $reportDir"

   ###########################################
   # Linking
   ###########################################
   if {$link} {
      command "file delete -force $resultDir"
      command "file mkdir $resultDir"
      command "file mkdir $reportDir"
   
      #Create in-memory project
      command "create_project -in_memory -part $part" "$resultDir/create_project.log"
   
      ###########################################
      # Define the top-level sources
      ###########################################
      #Determine state of Top (import or implement). 
      if {[llength $partitions]} {
         foreach partition $partitions {
            lassign $partition module cell state
            if {[string match $cell $top]} {
               if {[string match $state "implement"]} {
                  set topState "implement"
               } elseif {[string match $state "import"]} {
                  set topState "import"
               } else {
                  set errMsg "\nERROR: Invalid state $state in Partition settings for $module\($impl).\n"
                  error $errMsg
               }
            }
         }
      } else {
         set topState "implement"
      }

      if {[string match $topState "implement"]} {
         set topFile [get_module_file $top]
      } elseif {[string match $topState "import"]} {
         set topFile "$dcpDir/${top}_routed.dcp"
      }

      puts "\tAdding file $topFile for $top"
      if {[info exists topFile]} {
         command "add_files $topFile"
      } else {
         set errMsg "\nERROR: No module found with with attribute \"moduleName\" equal to $top, which is defined as \"top\" for implementation $impl."
         error $errMsg
      }
   
      #Read in top-level cores and XDC on if Top is being implemented
      if {[string match $topState "implement"]} { 
         #### Read in IP Netlists 
         if {[llength $cores] > 0} {
            add_cores $cores
         }

         #### Read in XDC file
         if {[llength $implXDC] > 0} {
            add_xdc $implXDC
         } else {
            puts "\tWARNING: No XDC file specified for $impl"
         }
      }
   
	  puts "Going to Use [get_param general.maxThreads] threads"
   
      ##############################################
      # Link the top-level design with black boxes 
      ##############################################
      set start_time [clock seconds]
time [clock seconds]
      puts "\t#HD: Running link_design for $top \[[clock format $start_time -format {%a %b %d %H:%M:%S %Y}]\]"
      command "link_design -mode default -part $part -top $top" "$resultDir/${top}_link_design.log"
      set end_time [clock seconds]
      log_time link_design $start_time $end_time 1
   
      ##############################################
      # Bring in OOC module check points
      ##############################################
      if {$hd && [llength $ooc_implementations] > 0} {
         get_ooc_results $ooc_implementations
      }

      if {$td} {
         #Turn phys_opt_design and route_design for TD run
         set phys  [set_attribute impl $impl phys  0]
         set route [set_attribute impl $impl route 0]

         command "puts \"\t#HD: Creating OOC constraints\""
         foreach ooc $ooc_implementations {
            #Set HD.PARTITION and create set_logic_* constraints
            set instName [get_attribute ooc $ooc inst]
            set hierInst [get_attribute ooc $ooc hierInst]
            command "set_property HD.PARTITION 1 \[get_cells $hierInst\]"
            set_partpin_range $hierInst
            create_set_logic $instName $hierInst $xdcDir
            create_ooc_clocks $instName $hierInst $xdcDir
         }
      }

      #If Partitions are defined, process accordingly
      foreach partition $partitions {
         lassign $partition module cell state
         set moduleName [get_attribute module $module moduleName]
         set name [lindex [split $cell "/"] end]
         if {![string match $moduleName $top]} {
            if {[string match $state "implement"]} {
               set partitionFile [get_module_file $module]
            } elseif {[string match $state "import"]} {
               set partitionFile "$dcpDir/${name}_route_design.dcp"
            } elseif {[string match $state "blackbox"]} {
               puts "\tInfo: Cell $cell will be implemented as a blackbox."
            } else {
               set errMsg "\nERROR: Invalid state \"$state\" in settings for $name\($impl)."
               append errMsg"Valid states are \"implement\", \"import\", or \"blackbox\".\n" 
               error $errMsg
            }

            if {[string match $state "blackbox"]} {
               puts "\tInserting LUT1 buffers on interface of $name"
               command "set_property HD.PARTITION 1 \[get_cells $cell]"
#               command "update_design -cells $cell -buffer_ports" "$resultDir/update_design_$name.log"
               ###To avoid errors in insert_proxy_flop, set param gui.enableFedEditing. 
#               puts "\tInserting FF buffers on interface of $name"
               insert_proxy_flop $cell
            } else {
               set fileSplit [split $partitionFile "."]
               set type [lindex $fileSplit end]
               if {[string match $type "dcp"]} {
                  set start_time [clock seconds]
                  puts "\tReading in checkpoint $partitionFile for $cell ($module) \[[clock format $start_time -format {%a %b %d %H:%M:%S %Y}]\]"
                  command "read_checkpoint -cell $cell $partitionFile -strict" "$resultDir/read_checkpoint_$name.log"
                  set end_time [clock seconds]
                  log_time read_checkpoint $start_time $end_time 0 "Resolve blacbox for $name"
               } elseif {[string match $type "edf"] || [string match $type "edn"]} {
                  set start_time [clock seconds]
                  puts "\tUpdating design with $partitionFile for $cell ($module) \[[clock format $start_time -format {%a %b %d %H:%M:%S %Y}]\]"
                  command "update_design -cells $cell -from_file $partitionFile" "$resultDir/update_design_$name.log"
                  set end_time [clock seconds]
                  log_time update_design $start_time $end_time 0 "Resolve blacbox for $name"
               } else {
                  set errMsg "\nERROR: Invalid file type \"$type\" for $partitionFile.\n"
                  error $errMsg
               }
            }

            if {[string match $state "import"]} {
               set start_time [clock seconds]
               puts "\tLocking $cell \[[clock format $start_time -format {%a %b %d %H:%M:%S %Y}]\]"
               command "lock_design -level routing $cell" "$resultDir/lock_design_$name.log"
               set end_time [clock seconds]
               log_time lock_design $start_time $end_time 0 "Lock imported Partition $name"
            }

            ##Mark module with HD.PARTITION if being implemented
            if {[string match $state "implement"]} {
               command "set_property HD.PARTITION 1 \[get_cells $cell]"
            }
         }
      }

      ##############################################
      # Read in any linkXDC files 
      ##############################################
      if {[llength $linkXDC] > 0} {
         readXDC $linkXDC
      }

      if {$dcpLevel > 0} {
         set start_time [clock seconds]
         command "write_checkpoint -force $resultDir/${top}_link_design.dcp" "$resultDir/temp.log"
         set end_time [clock seconds]
         log_time write_checkpoint $start_time $end_time 0 "Post link_design checkpoint"
      }
      puts "\t#HD: Completed link_design"
      puts "\t##########################\n"

      if {$verbose > 1} {
         set start_time [clock seconds]
         command "report_utilization -file $reportDir/${top}_utilization_link_design.rpt" "$resultDir/temp.log"
         set end_time [clock seconds]
         log_time report_utilization $start_time $end_time
      } 
      #Run methodology DRCs and catch any Critical Warnings or Error (module ruledeck quiet)
      set start_time [clock seconds]
      check_drc $top methodology_checks 1
      set end_time [clock seconds]
      log_time report_drc $start_time $end_time 0 "methodology checks"
      #Run timing DRCs and catch any Critical Warnings or Error (module ruledeck quiet)
      set start_time [clock seconds]
      check_drc $top timing_checks 1
      set end_time [clock seconds]
      log_time report_drc $start_time $end_time 0 "timing_checks"
   }
  

puts "Going to Use [get_param general.maxThreads] threads 2"
   
   
   ############################################################################################
   # Implementation steps: opt_design, place_design, phys_opt_design, route_design
   ############################################################################################
   set impl_start [clock seconds]
   if {$opt} {
      impl_step opt_design $top $opt_options $opt_directive ${opt.pre}
   }

   if {$place} {
      impl_step place_design $top $place_options $place_directive ${place.pre}

      #### If Top-Down, write out XDCs 
      if {$td} {
         puts "\n\tWriting instance level XDC files."
         foreach ooc $ooc_implementations {
            set instName [get_attribute ooc $ooc inst]
            set hierInst [get_attribute ooc $ooc hierInst]
            write_hd_xdc $instName $hierInst $xdcDir
         }
      }
   }

   if {$phys} {
      impl_step phys_opt_design $top $phys_options $phys_directive ${phys.pre}
   }

   if {$route} {
      impl_step route_design $top $route_options $route_directive ${route.pre}
 
      #Run report_timing_summary on final design
      set start_time [clock seconds]
      command "report_timing_summary -file $reportDir/${top}_timing_summary.rpt" "$resultDir/temp.log"
      set end_time [clock seconds]
      log_time report_timing $start_time $end_time 0 "Timing Summary"
   
      #Run a final DRC that catches any Critical Warnings (module ruledeck quiet)
      set start_time [clock seconds]
      check_drc $top bitstream_checks ${drc.quiet}
      set end_time [clock seconds]
      log_time report_drc $start_time $end_time 0 "bistream_checks"
   
   }
   
   if {![file exists $dcpDir]} {
      command "file mkdir $dcpDir"
   }   

   foreach partition $partitions {
      lassign $partition module cell state
      set moduleName [get_attribute module $module moduleName]
      set name [lindex [split $cell "/"] end]
      if {![string match $moduleName $top]} {
         set start_time [clock seconds]
         command "write_checkpoint -force -cell $cell $resultDir/${name}_route_design.dcp" "$resultDir/temp.log"
         set end_time [clock seconds]
         log_time write_checkpoint $start_time $end_time 0 "Write cell checkpoint for $name"
         command "file copy -force $resultDir/${name}_route_design.dcp $dcpDir"
         if {[string match $topState "implement"]} {
            set start_time [clock seconds]
            command "update_design -cell $cell -black_box" "$resultDir/carve_$name.log"
            set end_time [clock seconds]
            log_time update_design $start_time $end_time 0 "Carve out (blackbox) Partition $name"
         }
      }
   }

   if {[llength $partitions] && [string match $topState "implement"]} {
      set start_time [clock seconds]
      puts "\tLocking $top and exporting results \[[clock format $start_time -format {%a %b %d %H:%M:%S %Y}]\]"
      command "lock_design -level routing" "$resultDir/lock_design_$top.log"
      set end_time [clock seconds]
      log_time lock_design $start_time $end_time 0 "Lock placement and routing of $top"
      command "write_checkpoint -force $resultDir/${top}_routed.dcp" "$resultDir/temp.log"
      command "file copy -force $resultDir/${top}_routed.dcp $dcpDir"
   }

   if {$bitstream} {
      impl_step write_bitstream $top $bitstream_options none ${bitstream.pre} $bitstream_settings
   }
   
   set impl_end [clock seconds]
   log_time final $impl_start $impl_end 
   log_data $impl $top

   command "close_project"
   command "\n"
}
