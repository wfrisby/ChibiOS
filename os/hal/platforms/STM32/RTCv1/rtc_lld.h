/*
    ChibiOS/RT - Copyright (C) 2006,2007,2008,2009,2010,
                 2011 Giovanni Di Sirio.

    This file is part of ChibiOS/RT.

    ChibiOS/RT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    ChibiOS/RT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * @file    STM32/RTCv1/rtc_lld.h
 * @brief   STM32 RTC subsystem low level driver header.
 *
 * @addtogroup RTC
 * @{
 */

#ifndef _RTC_LLD_H_
#define _RTC_LLD_H_

#if HAL_USE_RTC || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/
/**
 * @brief   Switch to TRUE if you need callbacks from RTC. Switch to FALSE
 *          if you need only time keeping.
 * @note    Default is true.
 */
#if !defined(RTC_SUPPORTS_CALLBACKS) || defined(__DOXYGEN__)
#define RTC_SUPPORTS_CALLBACKS              TRUE
#endif

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

#if HAL_USE_RTC && !STM32_HAS_RTC
#error "RTC not present in the selected device"
#endif

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @brief Structure representing an RTC time value.
 */
typedef struct {
  /**
   * @brief Seconds sins UNIX epoch.
   */
  uint32_t tv_sec;
  /**
   * @brief Fractional part.
   */
  uint32_t tv_msec;
}RTCDateTime;


/**
 * @brief Structure representing an RTC driver.
 * @note  This driver is dummy when callbacks disabled.
 */
struct RTCDriver{
#if RTC_SUPPORTS_CALLBACKS
  /**
   * @brief Overflow callback. Set it to NULL if not used.
   */
  rtccb_t           overflow_cb;

  /**
   * @brief Every second callback. Set it to NULL if not used.
   */
  rtccb_t           second_cb;

  /**
   * @brief Alarm callback. Set it to NULL if not used.
   */
  rtccb_t           alarm_cb;
#endif /* RTC_SUPPORTS_CALLBACKS */
};

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

extern RTCDriver RTCD;


#ifdef __cplusplus
extern "C" {
#endif
  void rtc_lld_init(void);
  void rtc_lld_set_callback(RTCDriver *rtcp, rtccb_t overflow_cb,
                            rtccb_t second_cb, rtccb_t alarm_cb);

  void rtc_lld_set_time(RTCDateTime *timespec);
  void rtc_lld_get_time(RTCDateTime *timespec);

  void rtc_lld_get_alarm(RTCDateTime *timespec);
  void rtc_lld_set_alarm(RTCDateTime *timespec);
#ifdef __cplusplus
}
#endif


#endif /* HAL_USE_RTC */
#endif /* _RTC_LLD_H_ */

/** @} */