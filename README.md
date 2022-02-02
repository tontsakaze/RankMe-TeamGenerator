# RankMe Kento Edition + tontsakaze's Team Generator
Rankme plugin with team generator extension.<br>
Team generator uses RankMe's score database to generate balanced or fully random teams, and then changes players' team.<br>


## Install
1. Upload .smx, include and translation -files to your server
2. Plugin will automatically create a config file "cfg/sourcemod/kento_rankme.cfg"
3. If you want to use MySQL, change "rankme_mysql" to 1, and add the following to your databases.cfg -file:
```
"rankme" 
 {        
  "driver"    "mysql"        
  "host"      "your_host"        
  "database"  "your_database"
  "user"      "your_user"        
  "pass"      "your_pw"        
  //"timeout" "0"
  "port"      "3306" 
 }
```
4. If MySQL is not working for you, please check your SQL connection. Linux users should also make sure Sourcemod extension "dbi.mysql.ext" is running.


## Commands and Cvars
<details>
  <summary>New Commands</summary>

  ```
  // SERVER COMMANDS
  mp_genteams                             <0/1/2>     //TeamGen: Generates and moves players to new teams, 0=Random  1=Balanced  2=Extra balanced
  
  // ADMIN COMMANDS
  sm_genteams                             <0/1/2>     //TeamGen: Generates and moves players to new teams, 0=Random  1=Balanced  2=Extra balanced
  ```
</details>
<details>
  <summary>Old Commands</summary>

  ```
  //ADMIN COMMANDS
  sm_resetrank                                        //RankMe: Resets the rank of a player
  sm_rankme_remove_duplicate                          //RankMe: Removes the duplicated rows on the database
  sm_rankpurge                                        //RankMe: Purges from the rank players that didn't connected for X days
  sm_resetrank_all                                    //RankMe: Resets the rank of all players
  
  //PLAYER COMMANDS
  sm_session                                          //RankMe: Shows the stats of your current session
  sm_rank                                             //RankMe: Shows your rank
  sm_top                                              //RankMe: Shows the TOP
  sm_topweapon                                        //RankMe: Shows the TOP ordered by kills with a specific weapon
  sm_topacc                                           //RankMe: Shows the TOP ordered by accuracy
  sm_tophs                                            //RankMe: Shows the TOP ordered by HeadShots
  sm_toptime                                          //RankMe: Shows the TOP ordered by Connected Time
  sm_topkills                                         //RankMe: Shows the TOP ordered by kills
  sm_topdeaths                                        //RankMe: Shows the TOP ordered by deaths
  sm_hitboxme                                         //RankMe: Shows the HitBox stats
  sm_weaponme                                         //RankMe: Shows the kills with each weapon
  sm_resetmyrank                                      //RankMe: Resets your own rank
  sm_statsme                                          //RankMe: Shows your stats
  sm_next                                             //RankMe: Shows the next 9 players above you on the TOP
  sm_statsme2                                         //RankMe: Shows the stats from a player
  sm_rankme                                           //RankMe: Shows a menu with the basic commands
  sm_topassists                                       //RankMe: Shows the TOP ordered by Assists
  sm_toptk                                            //RankMe: Shows the TOP ordered by TKs
  sm_topmvp                                           //RankMe: Shows the TOP ordered by MVPs
  sm_topdamage                                        //RankMe: Shows the TOP ordered by damage
  sm_rankmechat                                       //Disable rankme chat messages
  sm_topkdr                                           //RankMe: Shows the TOP ordered by kdr
  sm_toppoints                                        //RankMe: Shows the TOP ordered by points
  sm_topfb                                            //RankMe: Shows the TOP ordered by first bloods
  sm_topns                                            //RankMe: Shows the TOP ordered by no scopes
  sm_topnsd                                           //RankMe: Shows the TOP ordered by no scope distance
  sm_topfk                                            //RankMe: Shows the TOP ordered by flashed kills
  sm_topthrusmoke                                     //RankMe: Shows the TOP ordered by killing through smokes
  sm_topwall                                          //RankMe: Shows the TOP ordered by wallbangs 
  ```
</details>
<details>
  <summary>Old Cvars</summary>

  ```
  rankme_enabled                            "1"       //Is RankMe enabled? 1 = true 0 = false"
  rankme_rankbots                           "0"       //Rank bots? 1 = true 0 = false"
  rankme_autopurge                          "0"       //Auto-Purge inactive players? X = Days  0 = Off"
  rankme_points_bomb_defused_team           "2"       //How many points CTs got for defusing the C4?"
  rankme_points_bomb_defused_player         "2"       //How many points the CT who defused got additional?"
  rankme_points_bomb_planted_team           "2"       //How many points TRs got for planting the C4?"
  rankme_points_bomb_planted_player         "2"       //How many points the TR who planted got additional?
  rankme_points_bomb_exploded_team          "2"       //How many points TRs got for exploding the C4?
  rankme_points_bomb_exploded_player        "2"       //How many points the TR who planted got additional?
  rankme_points_hostage_rescued_team        "2"       //How many points CTs got for rescuing the hostage?
  rankme_points_hostage_rescued_player      "2"       //How many points the CT who rescued got additional?
  rankme_points_hs                          "1"       //How many additional points a player got for a HeadShot?
  rankme_points_kill_ct                     "2"       //How many points a CT got for killing?
  rankme_points_kill_tr                     "2"       //How many points a TR got for killing?
  rankme_points_kill_bonus_ct               "1"       //How many points a CT got for killing additional by the diffrence of points?
  rankme_points_kill_bonus_tr               "1"       //How many points a TR got for killing additional by the diffrence of points?
  rankme_points_kill_bonus_dif_ct           "100"     //How many points of diffrence is needed for a CT to got the bonus?
  rankme_points_kill_bonus_dif_tr           "100"     //How many points of diffrence is needed for a TR to got the bonus?
  rankme_points_ct_round_win                "0"       //How many points CT got for winning the round?
  rankme_points_tr_round_win                "0"       //How many points TR got for winning the round?
  rankme_points_ct_round_lose               "0"       //How many points CT lost for losing the round?
  rankme_points_tr_round_lose               "0"       //How many points TR lost for losing the round?
  rankme_points_knife_multiplier            "2.0"     //Multiplier of points by knife
  rankme_points_taser_multiplier            "2.0"     //Multiplier of points by taser
  rankme_points_start                       "1000"    //Starting points
  rankme_minimal_kills                      "0"       //Minimal kills for entering the rank
  rankme_percent_points_lose                "1.0"     //Multiplier of losing points. (WARNING: MAKE SURE TO INPUT IT AS FLOAT) 1.0 equals lose same amount as won by the killer, 0.0 equals no lose
  rankme_points_lose_round_ceil             "1"       //If the points is f1oat, round it to next the highest or lowest? 1 = highest 0 = lowest
  rankme_changes_chat                       "1"       //Show points changes on chat? 1 = true 0 = false
  rankme_show_rank_all                      "0"       //When rank command is used, show for all the rank of the player? 1 = true 0 = false
  rankme_rank_all_timer                     "30.0"    //Cooldown timer to prevent rank command spam. 0.0 = disabled
  rankme_show_bots_on_rank                  "0"       //Show bots on rank/top/etc? 1 = true 0 = false
  rankme_resetownrank                       "0"       //Allow player to reset his own rank? 1 = true 0 = false
  rankme_minimumplayers                     "2"       //Minimum players to start giving points
  rankme_vip_enabled                        "0"       //Show AS_ maps statiscs (VIP mod) on statsme and session?
  rankme_points_vip_escaped_team            "2"       //How many points CTs got helping the VIP to escaping?
  rankme_points_vip_escaped_player          "2"       //How many points the VIP got for escaping?
  rankme_points_vip_killed_team             "2"       //How many points TRs got for killing the VIP?
  rankme_points_vip_killed_player           "2"       //How many points the TR who killed the VIP got additional?
  rankme_points_lose_tk                     "0"       //How many points a player lose for Team Killing?
  rankme_points_lose_suicide                "0"       //How many points a player lose for Suiciding?
  rankme_rank_by                            "0"       //Rank players by? 0 = STEAM:ID 1 = Name 2 = IP
  rankme_ffa                                "0"       //Free-For-All (FFA) mode? 1 = true 0 = false
  rankme_mysql                              "0"       //Using MySQL? 1 = true 0 = false (SQLite)
  rankme_dump_db                            "0"       //Dump the Database to SQL file? (required to be 1 if using the web interface and SQLite, case MySQL, it won't be dumped) 1 = true 0 = false
  rankme_gather_stats                       "1"       //Gather Statistics (a.k.a count points)? (turning this off won't disallow to see the stats already gathered) 1 = true 0 = false
  rankme_days_to_not_show_on_rank           "0"       //Days inactive to not be shown on rank? X = days 0 = off
  rankme_rank_mode                          "1"       //Rank by what? 1 = by points 2 = by KDR
  rankme_sql_table                          "rankme"  //The name of the table that will be used. (Max: 100)
  rankme_chat_triggers                      "1"       //Enable (non-command) chat triggers. (e.g: rank, statsme, top) Recommended to be set to 0 when running with EventScripts for avoiding double responses. 1 = true 0 = false
  rankme_points_mvp_ct                      "1"       //How many points a CT got for being the MVP?
  rankme_points_mvp_tr                      "1"       //How many points a TR got for being the MVP?
  rankme_points_bomb_pickup                 "0"       //How many points a player gets for picking up the bomb?
  rankme_points_bomb_dropped                "0"       //How many points a player loess for dropping the bomb?
  rankme_points_assiist_kill                "1"       //How many points a player gets for assist kill?
  ankme_points_match_win                    "2"       //How many points a player win for winning the match?
  rankme_points_match_lose                  "2"       //How many points a player loess for losing the match?
  rankme_points_match_draw                  "0"       //How many points a player win when match draw?"
  rankme_announcer_player_connect           "1"       //Announce when a player connect with position and points?
  rankme_announcer_player_connect_chat      "1"       //Announce when a player connect at chat?
  rankme_announcer_player_connect_hint      "0"       //Announce when a player connect at hintbox?
  rankme_announcer_player_disconnect        "1"       //Announce when a player disconnect with position and points?
  rankme_announcer_top_player_connect       "1"       //Announce when a top player connect?
  rankme_announcer_top_pos_player_connect   "10"      //Max position to announce that a top player connect?
  rankme_announcer_top_player_connect_chat  "1"       //Announce when a top player connect at chat?
  rankme_announcer_top_player_connect_hint  "0"       //Announce when a top player connect at hintbox?
  rankme_gather_stats_warmup                "1"       //Gather Statistics In Warmup?
  rankme_points_min_enabled                 "1"       // Is minimum points enabled? 1 = true 0 = false
  rankme_points_min                         "0"       // Minimum points
  rankme_rank_cache                         "1"       //Get player rank via cache, auto build cache on every OnMapStart.
  rankme_points_ns                          "1"       //How many additional points a player got for a no scope kill?
  rankme_points_ns_allsnipers               "0"       //0: ssg08 and awp only, 1: ssg08, awp, g3sg1, scar20
  rankme_points_fb                          "1"       //How many additional points a player got for a First Blood?
  rankme_points_blind                       "1"       // How many additional points a player got for a flashed kill?
  rankme_points_smoke                       "1"       // How many additional points a player got for killing through smoke?
  rankme_points_lose_atk                    "1"       // How many points a player lose for Assist Team Killing?
  rankme_points_assiist_flash               "1"       // How many points a player gets for assist flash kill?
  rankme_points_lose_atf                    "1"       // How many points a lose for team assist flash kill?
  rankme_points_wall                        "1"       // How many additional points a player got for wallbang? 
  ```
</details>


## Original Plugins
[benscobie's RankMe](https://github.com/benscobie/sourcemod-rankme)<br>

[RankMe Kento Edition](https://github.com/rogeraabbccdd/Kento-Rankme)<br>
[Forum Thread](https://forums.alliedmods.net/showthread.php?p=2467665)<br>


## Credits
[lok1](https://forums.alliedmods.net/showthread.php?t=155621) - Developed the original RankMe plugin that this plugin is based on<br>
[benscobie](https://github.com/benscobie/sourcemod-rankme) - This plugin is improved from his version<br>
[pracc](http://hlmod.ru/resources/cs-go-rankme-web.132) - Code of kill assist is edited from his rankme<br>
[TR1D](https://github.com/TR1D) - Thanks for his Russian translation<br>
[shanapu](https://github.com/shanapu) - Thanks for his German translation<br>
[2389736818](https://github.com/2389736818) - Thanks for his Simplified Chinese translation<br>
[Kxnrl](https://github.com/Kxnrl) - Thanks for his rankme cache<br>
[CrazyHackGUT](https://github.com/CrazyHackGUT) - Thanks for his optimization<br>
[paulocrash](https://github.com/paulocrash) - Thanks for his Português-BR translation<br>
[axyxx](https://github.com/awyxx) - Thanks for his Portuguese translation<br>
[tontsakaze](https://github.com/tontsakaze) - Creator of team generator code and Finnish translation<br>
