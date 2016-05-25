//#ident "$Id: Pinball.h,v 1.16 2003/06/11 13:25:51 rzr Exp $"
#ifndef PINBALL_H
#define PINBALL_H

constexpr int PBL_NULL                  = 0x0;
constexpr int PBL_LOCK                  = 0x1;
constexpr int PBL_BALL                  = 0x2;
constexpr int PBL_WALLS                 = 0x20;
constexpr int PBL_WALLS_ONE             = 0x40;
constexpr int PBL_UNACTIVE_ARM          = 0x80;
constexpr int PBL_ACTIVE_ARM            = 0x100;

constexpr int PBL_BUMPER                = 0x400;
constexpr int PBL_TRAP_BOUNCE           = 0x800;
constexpr int PBL_GROUP1                = 0x1000;
constexpr int PBL_GROUP2                = 0x2000;
constexpr int PBL_GROUP3                = 0x4000;
constexpr int PBL_GROUP4                = 0x8000;
constexpr int PBL_TRAP                  = 0x10000;
constexpr int PBL_PLUNGER               = 0x20000;

constexpr int PBL_TYPE_ARMBEH           = 1;
constexpr int PBL_TYPE_BOUNCEBEH        = 2;
constexpr int PBL_TYPE_BUMPERBEH        = 3;
constexpr int PBL_TYPE_CAVEBEH          = 4;
constexpr int PBL_TYPE_EYEBEH           = 5;
constexpr int PBL_TYPE_LOCKBEH          = 6;
constexpr int PBL_TYPE_STATEBEH         = 7;
constexpr int PBL_TYPE_SWITCHBEH        = 8;
constexpr int PBL_TYPE_TRIGGERBEH       = 9;
constexpr int PBL_TYPE_SCRIPTBEH        = 10;
constexpr int PBL_TYPE_FAKEMODULEBEH    = 11;
constexpr int PBL_TYPE_PLUNGERBEH       = 12;

constexpr int PBL_SIG_NULL              = -1;

constexpr int PBL_SIG_RESET_ALL         = 666;
constexpr int PBL_SIG_TILT              = 667;
constexpr int PBL_SIG_GAME_OVER         = 668;
constexpr int PBL_SIG_GAME_START        = 669;
constexpr int PBL_SIG_GAME_PAUSE        = 670;
constexpr int PBL_SIG_TILT_WARNING      = 671;
constexpr int PBL_SIG_CLEAR_TEXT        = 672;

constexpr int PBL_SIG_LNUDGE            = 681;
constexpr int PBL_SIG_RNUDGE            = 682;
constexpr int PBL_SIG_BNUDGE            = 683;
constexpr int PBL_SIG_TNUDGE            = 684;
constexpr int PBL_SIG_LEFTARM_ON        = 691;
constexpr int PBL_SIG_RIGHTARM_ON       = 692;
//constexpr int PBL_SIG_MULTIBALL_OFF   = 771;

// constexpr int PBL_SIG__grp_type_act/un    (grp)(type)(0)(1=on,2=off)

constexpr int PBL_SIG_BALL_ON           = 3101;
constexpr int PBL_SIG_BALL_OFF          = 3102;
//constexpr int PBL_SIG_ALLBALLS_OFF     = 3109;

/*

constexpr int PBL_SIG_HIT_CAVE               = 1002;
constexpr int PBL_SIG_CAVE_OUT               = 1012;
constexpr int PBL_SIG_ACTIVATE_EXTRABALL     = 1003;
constexpr int PBL_SIG_JACKPOT                = 1004;
constexpr int PBL_SIG_NEW_TARGET             = 1060;
constexpr int PBL_SIG_TARGET_1               = 1005;
constexpr int PBL_SIG_TARGET_2               = 1006;

constexpr int PBL_SIG_LOCK_1                 = 2001;
constexpr int PBL_SIG_LOCK_2                 = 2002;
constexpr int PBL_SIG_ACTIVATE_LOCK          = 2010;
constexpr int PBL_SIG_RELEASE_LOCK           = 2020;
constexpr int PBL_SIG_NEW_LOCK               = 2666;

constexpr int PBL_SIG_LEFT_LOOP              = 3001;
constexpr int PBL_SIG_RIGHT_LOOP             = 3002;
constexpr int PBL_SIG_ACTIVATE_LEFT_LOOP     = 3011;
constexpr int PBL_SIG_ACTIVATE_RIGHT_LOOP    = 3012;

constexpr int PBL_SIG_ACTIVATE_BALL_1        = 4011;
constexpr int PBL_SIG_ACTIVATE_BALL_2        = 4012;
constexpr int PBL_SIG_ACTIVATE_BALL_3        = 4013;
constexpr int PBL_SIG_ACTIVATE_BALL_4        = 4014;
constexpr int PBL_SIG_BALL_1_DEAD            = 4021;
constexpr int PBL_SIG_BALL_2_DEAD            = 4022;
constexpr int PBL_SIG_BALL_3_DEAD            = 4023;
constexpr int PBL_SIG_BALL_4_DEAD            = 4024;
constexpr int PBL_SIG_MULTIBALL_DEAD         = 4666;

constexpr int PBL_SIG_MISSION_1              = 5001;
constexpr int PBL_SIG_MISSION_2              = 5002;

constexpr int PBL_LINUX_L_ON                 = 6001;

*/
#endif //PINBALL_H
