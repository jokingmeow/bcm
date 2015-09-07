/*
 * $Id: blackbird_service.c 1.13 Broadcom SDK $
 *
 * $Copyright: Copyright 2012 Broadcom Corporation.
 * This program is the proprietary software of Broadcom Corporation
 * and/or its licensors, and may only be used, duplicated, modified
 * or distributed pursuant to the terms and conditions of a separate,
 * written license agreement executed between you and Broadcom
 * (an "Authorized License").  Except as set forth in an Authorized
 * License, Broadcom grants no license (express or implied), right
 * to use, or waiver of any kind with respect to the Software, and
 * Broadcom expressly reserves all rights in and to the Software
 * and all intellectual property rights therein.  IF YOU HAVE
 * NO AUTHORIZED LICENSE, THEN YOU HAVE NO RIGHT TO USE THIS SOFTWARE
 * IN ANY WAY, AND SHOULD IMMEDIATELY NOTIFY BROADCOM AND DISCONTINUE
 * ALL USE OF THE SOFTWARE.  
 *  
 * Except as expressly set forth in the Authorized License,
 *  
 * 1.     This program, including its structure, sequence and organization,
 * constitutes the valuable trade secrets of Broadcom, and you shall use
 * all reasonable efforts to protect the confidentiality thereof,
 * and to use this information only in connection with your use of
 * Broadcom integrated circuit products.
 *  
 * 2.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS
 * PROVIDED "AS IS" AND WITH ALL FAULTS AND BROADCOM MAKES NO PROMISES,
 * REPRESENTATIONS OR WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY,
 * OR OTHERWISE, WITH RESPECT TO THE SOFTWARE.  BROADCOM SPECIFICALLY
 * DISCLAIMS ANY AND ALL IMPLIED WARRANTIES OF TITLE, MERCHANTABILITY,
 * NONINFRINGEMENT, FITNESS FOR A PARTICULAR PURPOSE, LACK OF VIRUSES,
 * ACCURACY OR COMPLETENESS, QUIET ENJOYMENT, QUIET POSSESSION OR
 * CORRESPONDENCE TO DESCRIPTION. YOU ASSUME THE ENTIRE RISK ARISING
 * OUT OF USE OR PERFORMANCE OF THE SOFTWARE.
 * 
 * 3.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT SHALL
 * BROADCOM OR ITS LICENSORS BE LIABLE FOR (i) CONSEQUENTIAL,
 * INCIDENTAL, SPECIAL, INDIRECT, OR EXEMPLARY DAMAGES WHATSOEVER
 * ARISING OUT OF OR IN ANY WAY RELATING TO YOUR USE OF OR INABILITY
 * TO USE THE SOFTWARE EVEN IF BROADCOM HAS BEEN ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES; OR (ii) ANY AMOUNT IN EXCESS OF
 * THE AMOUNT ACTUALLY PAID FOR THE SOFTWARE ITSELF OR USD 1.00,
 * WHICHEVER IS GREATER. THESE LIMITATIONS SHALL APPLY NOTWITHSTANDING
 * ANY FAILURE OF ESSENTIAL PURPOSE OF ANY LIMITED REMEDY.$
 */
 

#include <shared/types.h>
#include <soc/error.h>
#include <soc/drv_if.h>
#include <soc/robo/blackbird_service.h>
#include <soc/robo/gex_service.h>

drv_if_t drv_blackbird_services = {
/* reg_read                     */ drv_reg_read,
/* reg_write                    */ drv_reg_write,
/* reg_length_get               */ drv_reg_length_get,
/* reg_addr                     */ drv_reg_addr,
/* reg_field_set                */ drv_reg_field_set,
/* reg_field_get                */ drv_reg_field_get,
/* mem_length_get               */ drv_gex_mem_length_get,
/* mem_width_get                */ drv_gex_mem_width_get,
/* mem_read                     */ drv_gex_mem_read,
/* mem_write                    */ drv_gex_mem_write,
/* mem_field_get                */ drv_gex_mem_field_get,
/* mem_field_set                */ drv_gex_mem_field_set,
/* mem_clear                    */ drv_gex_mem_clear,
/* mem_search                   */ drv_gex_mem_search,
/* mem_insert                   */ drv_gex_mem_insert,
/* mem_delete                   */ drv_gex_mem_delete,
/* mem_cache_get                */ drv_mem_cache_get,
/* mem_cache_set                */ drv_mem_cache_set,
/* mem_move                     */ NULL,
/* mem_fill                     */ NULL,
/* counter_thread_set           */ drv_counter_thread_set,
/* counter_set                  */ drv_counter_set,
/* counter_get                  */ drv_counter_get,
/* counter_reset                */ drv_counter_reset,
/* vlan_mode_set                */ drv_vlan_mode_set,
/* vlan_mode_get                */ drv_vlan_mode_get,
/* port_vlan_pvid_set           */ drv_port_vlan_pvid_set,
/* port_vlan_pvid_get           */ drv_port_vlan_pvid_get,
/* port_vlan_set                */ drv_gex_port_vlan_set,
/* port_vlan_get                */ drv_gex_port_vlan_get,
/* vlan_prop_set                */ drv_gex_vlan_prop_set,
/* vlan_prop_get                */ drv_gex_vlan_prop_get,
/* vlan_prop_port_enable_set    */ drv_gex_vlan_prop_port_enable_set,
/* vlan_prop_port_enable_get    */ drv_gex_vlan_prop_port_enable_get,
/* vlan_vt_set                  */ NULL,
/* vlan_vt_get                  */ NULL,
/* vlan_vt_add                  */ NULL,
/* vlan_vt_delete               */ NULL,
/* vlan_vt_delete_all           */ NULL,
/* trunk_set                    */ drv_gex_trunk_set,
/* trunk_get                    */ drv_gex_trunk_get,
/* trunk_hash_field_add         */ drv_gex_trunk_hash_field_add,
/* trunk_hash_field_remove      */ drv_gex_trunk_hash_field_remove,
/* queue_mode_set               */ drv_gex_queue_mode_set,
/* queue_mode_get               */ drv_gex_queue_mode_get,
/* queue_count_set              */ drv_gex_queue_count_set,
/* queue_count_get              */ drv_gex_queue_count_get,
/* queue_WRR_weight_set         */ drv_gex_queue_WRR_weight_set,
/* queue_WRR_weight_get         */ drv_gex_queue_WRR_weight_get,
/* queue_prio_set               */ drv_gex_queue_prio_set,
/* queue_prio_get               */ drv_gex_queue_prio_get,
/* queue_tos_set                */ NULL,
/* queue_tos_get                */ NULL,
/* queue_dfsv_set               */ drv_gex_queue_dfsv_set,
/* queue_dfsv_get               */ drv_gex_queue_dfsv_get,
/* queue_mapping_type_set       */ drv_gex_queue_mapping_type_set,
/* queue_mapping_type_get       */ drv_gex_queue_mapping_type_get,
/* age_timer_set                */ drv_age_timer_set,
/* age_timer_get                */ drv_age_timer_get,
/* mac_set                      */ drv_gex_mac_set,
/* mac_get                      */ drv_gex_mac_get,
/* mirror_set                   */ drv_gex_mirror_set,
/* mirror_get                   */ drv_gex_mirror_get,
/* port_oper_mode_set           */ drv_port_oper_mode_set,
/* port_oper_mode_get           */ drv_port_oper_mode_get,
/* port_set                     */ drv_gex_port_set,
/* port_get                     */ drv_gex_port_get,
/* port_advertise_set           */ drv_port_advertise_set,
/* port_advertise_get           */ drv_port_advertise_get,
/* port_status_get              */ drv_gex_port_status_get,
/* port_sw_mac_update           */ drv_port_sw_mac_update,
/* port_pri_mapop_set           */ drv_blackbird_port_pri_mapop_set,
/* port_pri_mapop_get           */ drv_blackbird_port_pri_mapop_get,
/* port_bitmap_get              */ drv_port_bitmap_get,
/* port_cross_connect_set       */ NULL,
/* port_cross_connect_get       */ NULL,
/* security_set                 */ drv_gex_security_set,
/* security_get                 */ drv_gex_security_get,
/* security_egress_set          */ drv_gex_security_egress_set,
/* security_egress_get          */ drv_gex_security_egress_get,
/* security_eap_control_set     */ NULL,
/* security_eap_control_get     */ NULL,
/* mstp_config_set              */ drv_mstp_config_set,
/* mstp_config_get              */ drv_mstp_config_get,
/* mstp_port_set                */ drv_gex_mstp_port_set,
/* mstp_port_get                */ drv_gex_mstp_port_get,
/* trap_set                     */ drv_gex_trap_set,
/* trap_get                     */ drv_gex_trap_get,
/* snoop_set                    */ drv_gex_snoop_set,
/* snoop_get                    */ drv_gex_snoop_get,
/* rate_config_set              */ drv_gex_rate_config_set,
/* rate_config_get              */ drv_gex_rate_config_get,
/* rate_set                     */ drv_gex_rate_set,
/* rate_get                     */ drv_gex_rate_get,
/* storm_control_enable_set     */ drv_gex_storm_control_enable_set,
/* storm_control_enable_get     */ drv_gex_storm_control_enable_get,
/* storm_control_set            */ drv_gex_storm_control_set,
/* storm_control_get            */ drv_gex_storm_control_get,
/* dev_prop_get                 */ drv_blackbird_dev_prop_get,
/* dev_prop_set                 */ drv_blackbird_dev_prop_set,
/* mcast_init                   */ drv_mcast_init,
/* mcast_to_marl                */ drv_mcast_to_marl,
/* mcast_from_marl              */ drv_mcast_from_marl,
/* mcast_bmp_get                */ drv_gex_mcast_bmp_get,
/* mcast_bmp_set                */ drv_gex_mcast_bmp_set,
/* arl_table_process            */ drv_arl_table_process,
/* arl_sync                     */ drv_arl_sync,
/* arl_learn_enable_set         */ drv_gex_arl_learn_enable_set,
/* arl_learn_enable_get         */ drv_gex_arl_learn_enable_get,
/* queue_port_prio_to_queue_set */ drv_gex_queue_port_prio_to_queue_set,
/* queue_port_prio_to_queue_get */ drv_gex_queue_port_prio_to_queue_get,
/* queue_port_dfsv_set          */ drv_gex_queue_port_dfsv_set,
/* queue_port_dfsv_get          */ drv_gex_queue_port_dfsv_get,
/* queue_prio_remap_set         */ drv_gex_queue_prio_remap_set,
/* queue_prio_remap_get         */ drv_gex_queue_prio_remap_get,
/* queue_dfsv_remap_set         */ drv_gex_queue_dfsv_remap_set,
/* queue_dfsv_remap_get         */ drv_gex_queue_dfsv_remap_get,
/* queue_dfsv_unmap_set         */ NULL,
/* queue_dfsv_unmap_get         */ NULL,
/* queue_rx_reason_set          */ drv_gex_queue_rx_reason_set,
/* queue_rx_reason_get          */ drv_gex_queue_rx_reason_get,
/* queue_port_txq_pause_set     */ NULL,
/* queue_port_txq_pause_get     */ NULL,
/* queue_qos_control_set        */ NULL,
/* queue_qos_control_get        */ NULL,
/* cfp_init             		    */ NULL,
/* cfp_action_get       		    */ NULL,
/* cfp_action_set       		    */ NULL,
/* cfp_control_get      		    */ NULL,
/* cfp_control_set      		    */ NULL,
/* cfp_entry_read       		    */ NULL,
/* cfp_entry_search     		    */ NULL,
/* cfp_entry_write      		    */ NULL,
/* cfp_field_get        		    */ NULL,
/* cfp_field_set        		    */ NULL,
/* cfp_meter_rate_transform     */ NULL,
/* cfp_meter_get        		    */ NULL,
/* cfp_meter_set        		    */ NULL,
/* cfp_qset_get         		    */ NULL,
/* cfp_qset_set         		    */ NULL,
/* cfp_slice_id_select  		    */ NULL,
/* cfp_slice_to_qset    		    */ NULL,
/* cfp_stat_get         		    */ NULL,
/* cfp_stat_set         		    */ NULL,
/* cfp_udf_get          		    */ NULL,
/* cfp_udf_set          		    */ NULL,
/* cfp_ranger           		    */ NULL,
/* cfp_range_set        		    */ NULL,
/* cfp_range_get        		    */ NULL,
/* cfp_sub_qual_by_udf  		    */ NULL,
/* eav_control_set                  */ drv_gex_eav_control_set,
/* eav_control_get                  */ drv_gex_eav_control_get,
/* eav_enable_set                   */ drv_gex_eav_enable_set,
/* eav_enable_get                   */ drv_gex_eav_enable_get,
/* eav_link_status_set              */ drv_gex_eav_link_status_set,
/* eav_link_status_get              */ drv_gex_eav_link_status_get,
/* eav_egress_timestamp_get     */ drv_gex_eav_egress_timestamp_get,
/* eav_time_sync_set                */ drv_gex_eav_time_sync_set,
/* eav_time_sync_get                */ drv_gex_eav_time_sync_get,
/* eav_queue_control_set            */ drv_gex_eav_queue_control_set,
/* eav_queue_control_get        */ drv_gex_eav_queue_control_get,
/* eav_time_sync_mac_set        */ drv_gex_eav_time_sync_mac_set,
/* eav_time_sync_mac_get        */ drv_gex_eav_time_sync_mac_get,
/* timesync_config_set          */ NULL,
/* timesync_config_get          */ NULL,
/* control_timesync_set         */ NULL,
/* control_timesync_get         */ NULL,
/* dos_enable_set               */ drv_gex_dos_enable_set,
/* dos_enable_get               */ drv_gex_dos_enable_get,
/* dos_event_bitmap_get         */ NULL,
/* vm_init                      */ NULL,
/* vm_deinit 	                  */ NULL,
/* vm_field_get                 */ NULL,
/* vm_field_set                 */ NULL,
/* vm_action_get                */ NULL,
/* vm_action_set                */ NULL,
/* vm_entry_read                */ NULL,
/* vm_entry_write               */ NULL,
/* vm_qset_get                  */ NULL,
/* vm_qset_set                  */ NULL,
/* vm_format_id_select          */ NULL,
/* vm_slice_to_qset             */ NULL,
/* vm_range_set                 */ NULL,
/* vm_flow_alloc                */ NULL,
/* vm_flow_free                 */ NULL,
/* vm_ranger_inc                */ NULL,
/* vm_ranger_dec                */ NULL,
/* vm_ranger_count_get          */ NULL,
/* mcrep_vpgrp_vport_config_set */ NULL,
/* mcrep_vpgrp_vport_config_get */ NULL,
/* mcrep_vport_config_set 	    */ NULL, 
/* mcrep_vport_config_get 	    */ NULL, 
/* mcrep_vport_vid_search 	    */ NULL,
/* dev_control_set                  */ drv_dev_control_set,
/* dev_control_get                  */ drv_dev_control_get,
/* arl_learn_count_set  	    */ NULL,
/* arl_learn_count_get          */ NULL,
/* fp_init                      */ NULL,
/* fp_deinit                    */ NULL,
/* fp_qual_value_set            */ NULL,
/* fp_qual_value_get            */ NULL,
/* fp_udf_value_set             */ NULL,
/* fp_udf_value_get             */ NULL,
/* fp_entry_mem_control         */ NULL,
/* fp_entry_tcam_control        */ NULL,
/* fp_action_conflict           */ NULL,
/* fp_action_support_check      */ NULL,
/* fp_action_add                */ NULL,
/* fp_action_remove             */ NULL,
/* fp_selcode_mode_get          */ NULL,
/* fp_selcode_to_qset           */ NULL,
/* fp_qualify_support           */ NULL,
/* fp_id_control                */ NULL,
/* fp_tcam_parity_check         */ NULL,
/* fp_policer_control           */ NULL,
/* fp_stat_support_check        */ NULL,
/* fp_stat_type_get             */ NULL,
/* port_block_get               */ NULL,
/* port_block_set               */ NULL,
/* led_func_get                 */ drv_led_func_get,
/* led_func_set                 */ drv_led_func_set,
/* led_funcgrp_select_get       */ drv_led_funcgrp_select_get,
/* led_funcgrp_select_set       */ drv_led_funcgrp_select_set,
/* led_mode_get                 */ drv_led_mode_get,
/* led_mode_set                 */ drv_led_mode_set,
/* igmp_mld_snoop_mode_get      */ drv_gex_igmp_mld_snoop_mode_get,
/* igmp_mld_snoop_mode_set      */ drv_gex_igmp_mld_snoop_mode_set,
/* wred_init                    */ NULL,
/* wred_config_create           */ NULL,
/* wred_config_set              */ NULL,
/* wred_config_get              */ NULL,
/* wred_config_destroy          */ NULL,
/* wred_map_attach              */ NULL,
/* wred_map_deattach            */ NULL,
/* wred_map_get                 */ NULL,
/* wred_control_set             */ NULL,
/* wred_control_get             */ NULL,
/* wred_counter_enable_set      */ NULL,
/* wred_counter_enable_get      */ NULL,
/* wred_counter_set             */ NULL,
/* wred_counter_get             */ NULL,
};                              
