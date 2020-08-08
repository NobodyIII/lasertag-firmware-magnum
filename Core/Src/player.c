/*
 * player.c
 *
 *  Created on: Apr 23, 2020
 *      Author: blarson
 */

#include <string.h>

#include "audio.h"
#include "player.h"
#include "rgb.h"

#define FLASH_BRIGHTNESS 4
#define FLASH_DURATION 200
#define FLASH_DELAY 100
#define FLASH_REPEATS 3

player_state_t player_state;

/* only set by beacon/init */
static int num_teams;
static int friendly_fire;
static int max_hp;
static int revive_delay;

static int player_id;
static int team_id;

static int hp;
static int revives;
static int revive_timer;

static int killed_by[MAX_PLAYERS];

//TODO: finish flash code
static int flash_repeats = 0;
static int flash_timer = 0;
static int flash_color = 0;
static int flash_status = 0;


static void flash_toggle()
{
  /* toggle status */
  flash_status = !flash_status;

  /* handle new status */
  if (flash_status) {
    /* on */
    rgb_output(flash_color, FLASH_BRIGHTNESS);
    flash_timer = FLASH_DURATION;
  } else {
    /* off */
    rgb_output(RGB_COLOR_BLACK, 0);

    /* determine whether to keep flashing */
    if (--flash_repeats)
      flash_timer = FLASH_DELAY;
    else
      flash_timer = 0;
  }
}

static void flash_team(int team)
{
  /* flash own colors if killed by environment */
  if (team == 0)
    team = team_id;

  /* flash team color */

  flash_color = (rgb_color_ref_t)team_id;
  flash_repeats = FLASH_REPEATS;
  flash_toggle();
}

static void player_die(int killer)
{
//  /* verify player isn't unconfigured or already dead */
//  if (player_state != PLAYER_UNCONFIGURED && player_state != PLAYER_DEAD) {
  /* record death */
  killed_by[killer]++;

  /* make death sound */
  audio_play(SOUND_DEAD, 1);

  /* set state to dead */
  player_state = PLAYER_DEAD;
  revive_timer = revive_delay * 1000;
//  }
}

static void player_alive()
{
  /* reset hp */
  hp = max_hp;
  /* set state to alive */
  player_state = PLAYER_ALIVE;

  /* flash player's team */
  flash_team(team_id);

  /* make revive sound */
  audio_play(SOUND_REVIVE, 1);
}

static void player_begin()
{
  /* reset variables */
  memset(killed_by, 0, sizeof(killed_by));
  /* begin game */
  player_alive();
}

void player_set_num_teams(int teams, int enable_friendly_fire)
{
  num_teams = teams;
  friendly_fire = enable_friendly_fire;
  /* ensure current team is within valid range */
  if (team_id > num_teams)
    team_id = 0;
}

void player_set_max_hp(int hitpoints)
{
  max_hp = hitpoints;
  hp = max_hp;
}

void player_set_lives(int lives)
{
  /* beacons may set player lives to zero so one player can donate his life to another player */
  if (lives == 0) {
    player_die(0);
  } else {
    revives = lives - 1;
  }
}

void player_set_revive_delay(int seconds)
{
  revive_delay = seconds;
}

void player_set_id(int id)
{
  player_id = id;
}

int player_get_id()
{
  return player_id;
}

static void player_setup_test()
{
  player_set_max_hp(1);
  player_set_lives(5);
  player_set_revive_delay(5);
  player_set_num_teams(4, 0);
  player_set_id(1);
  player_team_select();
//  player_begin();
}

void player_reset()
{
  player_state = PLAYER_UNCONFIGURED;
  /* use test setup until we have beacons */
  player_setup_test();
}

void player_init()
{
  player_reset();
}

void player_shot(int shooter, int team, int damage)
{
  if ((shooter == player_id)
   || (!friendly_fire && (team == team_id))
   || (player_state != PLAYER_ALIVE))
    return;

  /* flash shooter's team color */
  flash_team(team);

  /* take damage */
  hp -= damage;
  if (hp <= 0) {
      /* player killed by shooter */
      player_die(shooter);
  } else {
      //TODO: (advanced play) not dead yet - gain temporary invulnerability
  }
}

void player_team_select(void)
{
//  audio_play(SOUND_GAME_OVER, 1);
//  rgb_output(RGB_COLOR_YELLOW, 1);
  /* only do something if player is unconfigured */
  //TODO: uncomment unconfigured check
  if (player_state == PLAYER_UNCONFIGURED) {
      /* team 0 is reserved for environment, so player teams range from 1 to num_teams */
      team_id = team_id % num_teams + 1;
      flash_team(team_id);
  }
}

void player_tick()
{
  //TODO: fill for basic play

  /* handle flashing */
  if (flash_timer) {
    if (--flash_timer == 0)
      flash_toggle();
  }

  if (revive_timer) {
    if (--revive_timer == 0) {
      /* revive if we can; otherwise indicate player is permanently dead */
      if (revives > 0) {
	  player_alive();
	  revives--;
      } else {
	  audio_play(SOUND_GAME_OVER, 1);
      }
    }
  }
}

int player_can_shoot()
{
  //TODO: remove unconfigured option
  return player_state == PLAYER_ALIVE || player_state == PLAYER_UNCONFIGURED;
}

uint32_t player_fire()
{
  //TODO: use mother beacon instead
  /* lock in config & begin game */
  if (player_state == PLAYER_UNCONFIGURED)
    player_begin();

  //TODO: generate actual firing packet
  return team_id;
}
