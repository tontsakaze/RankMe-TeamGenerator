// = = = = = = = = = = = = = = = = = = = = =
// CODE BELOW IS ADDITION TO KENTO RANK-ME |
// PLUGIN AND REQUIRES THAT PLUGIN TO WORK |
// = = = = = = = = = = = = = = = = = = = = =

/*********************************************************
 * Switch clients teams, updates its model and respawns it
 * Code copied from AlliedMods.net forums
 *
 * @param client  The client index of the player
 * @param team    Team to be switched
 * @noreturn
 *********************************************************/
void SwitchPlayerTeam(int client, int team){
    if (GetClientTeam(client) == team)
        return;

    if (team > CS_TEAM_SPECTATOR) {
        CS_SwitchTeam(client, team);
        CS_UpdateClientModel(client);
        CS_RespawnPlayer(client);
    } else {
        ChangeClientTeam(client, team);
    }
}


/*********************************************************
 * Set players to new teams and announces the average and overall
 * score of the teams as well as the difference between them
 * Code by tontsakaze
 *
 * @param T1_clients The array of client indexes of the players in team 1
 * @param T1_scores  The array of players' scores in team 1
 * @param T2_clients The array of client indexes of the players in team 2
 * @param T2_scores  The array of players' scores in team 2
 * @noreturn
 *********************************************************/
void SetPlayersToNewRandomizedTeams(int[] T1_clients, int[] T1_scores, int[] T2_clients, int[] T2_scores ){
    int score01 = 0;
    int iTeam01 = 0;
    int score02 = 0;
    int iTeam02 = 0;
    
    for(int i=0; i<MaxClients; i++){
        if(T1_clients[i]>0 ){
            if( IsClientInGame(T1_clients[i]) && (!IsFakeClient(T1_clients[i]) || g_bRankBots) ){
                SwitchPlayerTeam(T1_clients[i], CS_TEAM_CT);
                score01 += T1_scores[i];
                iTeam01 += 1;
            }
        }
        if(T2_clients[i]>0 ){
            if( IsClientInGame(T2_clients[i]) && (!IsFakeClient(T2_clients[i]) || g_bRankBots) ){
                SwitchPlayerTeam(T2_clients[i], CS_TEAM_T);
                score02 += T2_scores[i];
                iTeam02 += 1;
            }
        }
    }
    
    // SHOW SCORE DIFFERENCES
    int avgTeam01 = (iTeam01 > 0) ? RoundToCeil(float(score01)/float(iTeam01)) : 0 ;
    int avgTeam02 = (iTeam02 > 0) ? RoundToCeil(float(score02)/float(iTeam02)) : 0 ;
    
    CPrintToChatAll("{blue}%t","GenTeam_ResultInfo","CTs", avgTeam01, score01);
    CPrintToChatAll("{red}%t","GenTeam_ResultInfo","Ts", avgTeam02, score02);
    CPrintToChatAll("{orange}%t","GenTeam_ResultInfo","DIFF", IntAbsCustom(avgTeam01-avgTeam02), IntAbsCustom(score01-score02) );
    
    /*for(int i=1; i<=MaxClients; i++){
        if (IsClientInGame(i) && GetClientTeam(i) != CS_TEAM_NONE) {
            //CPrintToChatAll("{blue}CTs | AVG: %i | OVERALL: %i", avgTeam01, score01);
            //CPrintToChat(i, "{blue}%T", "GenTeam_ResultInfo", i, "CTs", avgTeam01, score01);
            CPrintToChatAll("%t","GenTeam_ResultInfo","CTs", avgTeam01, score01);
            //CPrintToChatAll("{red}Ts | AVG: %i | OVERALL: %i", avgTeam02, score02);
            CPrintToChat(i, "{red}%T", "GenTeam_ResultInfo", i, "Ts", avgTeam02, score02);
            //CPrintToChatAll("{orange}DIFF | AVG: %i | OVERALL: %i", IntAbsCustom(avgTeam01-avgTeam02), IntAbsCustom(score01-score02) );
            CPrintToChat(i, "{orange}%T", "GenTeam_ResultInfo", i, "DIFF", IntAbsCustom(avgTeam01-avgTeam02), IntAbsCustom(score01-score02) );
        }
    }*/
    
    PrintToServer("CTs | AVG: %i | OVERALL: %i", avgTeam01, score01);
    PrintToServer("Ts | AVG: %i | OVERALL: %i", avgTeam02, score02);
    PrintToServer("DIFF | AVG: %i | OVERALL: %i", IntAbsCustom(avgTeam01-avgTeam02), IntAbsCustom(score01-score02) );

}


/*********************************************************
 * Generates 2 fully random teams from clients
 * Code by tontsakaze
 *
 * @param clintCount    Count of overall clients playing
 * @param allClients    The array of client indexes
 * @param allScores     The array of scores of clients
 * @param T1_clients    The array of size MaxClients, filled with client indexes
 * @param T1_scores     The array of size MaxClients, filled with client scores
 * @param T2_clients    The array of size MaxClients, filled with client indexes
 * @param T2_scores     The array of size MaxClients, filled with client scores
 * @return              Difference in score between teams as integer
 *********************************************************/
int GenTeamsRandomMode(int clientCount, int[] allClients, int[] allScores, int[] T1_clients, int[] T1_scores, int[] T2_clients, int[] T2_scores ){
    int side = 0;
        
    for( int i=0; i<clientCount; i++){
        if( GetRandomInt(0, 1)==0 ){
            if( side<1){
                T1_clients[i] = allClients[i];
                T1_scores[i] = allScores[i];
                side++;
            
            }else{
                T2_clients[i] = allClients[i];
                T2_scores[i] = allScores[i];
                side--;
            }
        
        }else{
            if( side>-1){
                T2_clients[i] = allClients[i];
                T2_scores[i] = allScores[i];
                side--;
            
            }else{
                T1_clients[i] = allClients[i];
                T1_scores[i] = allScores[i];
                side++;
            }
        }
    }
    
    // CALCULATE DIFFERENCE AND RETURN IT
    side = 0;
    for( int i=0; i<MaxClients; i++){
        side += T1_scores[i];
        side -= T2_scores[i];
    }
    
    return IntAbsCustom(side);
}


/*********************************************************
 * Sorts Clients-Scores array pair using insertion sort
 * putting the client with the highest score to first
 * Code by tontsakaze
 *
 * @param clients   The array of client indexes
 * @param scores    The array of client scores
 * @noreturn
 *********************************************************/
void SortClientScoresBestFirst(int[] clients, int[] scores){
    // USE INSERTION SORT -> BEST FOR SMALL ARRAYS
    int keyS, keyC, j;
    
    for( int i=1; i<MaxClients; i++){
        keyS = scores[i];
        keyC = clients[i];
        j = i - 1;
        
        while(j >=0 && scores[j] < keyS){
            scores[j+1] = scores[j];
            clients[j+1] = clients[j];
            j -= 1;
        }
        scores[j+1] = keyS;
        clients[j+1] = keyC;
    }
}


/*********************************************************
 * Used for giving clients info about 
 * beginning of the team generation
 * Code by tontsakaze
 *
 * @param mode   Integer which mode is used
 * @noreturn
 *********************************************************/
void PrintStartGenTeamInfo(int mode){
    if(mode==0){ 
        CPrintToChatAll("{orange}%t\n", "GenTeam_BeginGenMode0");
        PrintToServer("Team Gen: Begin generating teams using Random-mode..."); 
    
    }else if(mode==1){
        CPrintToChatAll("{orange}%t\n", "GenTeam_BeginGenMode1");
        PrintToServer("Team Gen: Begin generating teams using Balanced-mode..."); 

    }else if(mode==2){
        CPrintToChatAll("{orange}%t\n", "GenTeam_BeginGenMode2");
        PrintToServer("Team Gen: Begin generating teams using Extra Balanced-mode..."); 
    }

    /*for(int i=1; i<=MaxClients; i++){
        if (IsClientInGame(i) && GetClientTeam(i) != CS_TEAM_NONE) {
            if(mode==0){ 
                CPrintToChat(i, "{orange}%T", "GenTeam_BeginGenMode0", i); 
                PrintToServer("Team Gen: Begin generating teams using Random-mode..."); 
            }
            if(mode==1){ 
                CPrintToChat(i, "{orange}%T", "GenTeam_BeginGenMode1", i);
                PrintToServer("Team Gen: Begin generating teams using Balanced-mode...");
            }
            if(mode==2){ 
                CPrintToChat(i, "{orange}%T", "GenTeam_BeginGenMode2", i);
                PrintToServer("Team Gen: Begin generating teams using Extra Balanced-mode..."); 
            }
        }
    }*/
}


/*********************************************************
 * Beginning of team generation. Counts all clients, retrieves their
 * scores from the database and generates teams based on given type.
 * Code by tontsakaze
 *
 * @param type  0=Random, 1=Balanced(Heuristic), 2=More Balanced(iterative random)
 * @return false if not enough players, otherwise true
 *********************************************************/
bool RandomizeTeams(int type){
    int[] T1_clients = new int[MaxClients];
    int[] T1_scores = new int[MaxClients];
    int[] T2_clients = new int[MaxClients];
    int[] T2_scores = new int[MaxClients];
    
    int[] allClients = new int[MaxClients];
    int[] allScores = new int[MaxClients];
    
    for(int i=0; i<MaxClients; i++){
        allClients[i] = -1;
        T1_clients[i] = -1;
        T2_clients[i] = -1;
        
        allScores[i] = 0;
        T1_scores[i] = 0;
        T2_scores[i] = 0;
    }
    
    int clientCount = 0;
    for (int i = 1; i <= MaxClients; i++) {
        if (IsClientInGame(i) && (!IsFakeClient(i) || g_bRankBots) && GetClientTeam(i) != CS_TEAM_SPECTATOR && GetClientTeam(i) != CS_TEAM_NONE) {
            // CLIENT
            allClients[clientCount] = i;
            
            //SCORE
            //allScores[clientCount] = RankMe_GetPoints(i);
            int rounds = RankMe_GetOverallRounds(i)+1;
            int score = RankMe_GetPoints(i)-1000;
            if(score<0){
                allScores[clientCount] = 0;
            }else{
                allScores[clientCount] = RoundToCeil( (float(score)/rounds)*30 );
            }
            
            clientCount++;
        }
    }
    
    // IF NOT ATLEAST 2 PLAYERS, RETURN WITH ERROR MSG
    if( clientCount<2 ){ return false; }
    
    
    // TYPE 0 aka RANDOM
    if( type==0 )
    {
        GenTeamsRandomMode(clientCount, allClients, allScores, T1_clients, T1_scores, T2_clients, T2_scores );
    }
    
    
    // TYPE 1 aka HEURISTIC
    if( type==1 ){
        SortClientScoresBestFirst(allClients, allScores);
        int score01=0;
        int score02=0;
        int iTeam01=0;
        int iTeam02=0;
        
        for (int i = 0; i < MaxClients; i++) {
            if( allClients[i]>0 ){
                if( score01<=score02 && iTeam01<=iTeam02 ){
                    T1_clients[iTeam01] = allClients[i];
                    T1_scores[iTeam01] = allScores[i];
                    score01 += allScores[i];
                    iTeam01 += 1;
                
                }else if( iTeam02<=iTeam01 ){
                    T2_clients[iTeam02] = allClients[i];
                    T2_scores[iTeam02] = allScores[i];
                    score02 += allScores[i];
                    iTeam02 += 1;
                
                }else{
                    T1_clients[iTeam01] = allClients[i];
                    T1_scores[iTeam01] = allScores[i];
                    score01 += allScores[i];
                    iTeam01 += 1;
                }
            }
        }
    }
    
    // TYPE 2 aka ITERATIVE RANDOM
    if( type==2 ){
        int[] Best_clients01 = new int[MaxClients];
        int[] Best_scores01 = new int[MaxClients];
        int[] Best_clients02 = new int[MaxClients];
        int[] Best_scores02 = new int[MaxClients];
        int leastDiff = -1;
        
        for( int i=0; i<100; i++){
            for(int k=0; k<MaxClients; k++){
                T1_clients[k] = -1;
                T2_clients[k] = -1;
                T1_scores[k] = 0;
                T2_scores[k] = 0;
            }
        
            int j = GenTeamsRandomMode(clientCount, allClients, allScores, T1_clients, T1_scores, T2_clients, T2_scores );
            if( leastDiff<0 || j<leastDiff ){
                leastDiff = j;
                for(int k=0; k<MaxClients; k++){
                    Best_clients01[k] = T1_clients[k];
                    Best_clients02[k] = T2_clients[k];
                    Best_scores01[k] = T1_scores[k];
                    Best_scores02[k] = T2_scores[k];
                }
            }
        }
        
        for(int i=0; i<MaxClients; i++){
            T1_clients[i] = Best_clients01[i];
            T2_clients[i] = Best_clients02[i];
            T1_scores[i] = Best_scores01[i];
            T2_scores[i] = Best_scores02[i];
        }
    }
    
    
    CPrintToChatAll("{orange}...%t\n", "GenTeam_Complete");
    PrintToServer("...Complete!\n");
    
    /*for(int i=1; i<=MaxClients; i++){
        if (IsClientInGame(i) && GetClientTeam(i) != CS_TEAM_NONE) {
            CPrintToChat(i, "{orange}...%T\n", "GenTeam_Complete", i); 
            PrintToServer("...Complete!\n"); 
        }
    }*/
    
    SetPlayersToNewRandomizedTeams(T1_clients,T1_scores,T2_clients,T2_scores);
    
    
    return true;
}


// ServerCommand
public Action CMD_MpGenTeams(int args){
    if (args < 1)
    {
        PrintToServer("Usage: sm_randomteams <0/1/2> || 0=Random, 1=Balanced, 2=Extra balanced");
        return Plugin_Handled;
    }
    
    char mode[5];
    GetCmdArg(1,mode,sizeof(mode));
    
    if(StringToInt(mode)==0 || StringToInt(mode)==1 || StringToInt(mode)==2 ){
        PrintStartGenTeamInfo(StringToInt(mode));
        
        bool bSuccess = RandomizeTeams(StringToInt(mode));
        if( !bSuccess ){ PrintToServer("Team Gen: Not enough players with score to generate teams!"); }
    }
    else{
        PrintToServer("Usage: sm_randomteams <0/1/2> || 0=Random, 1=Balanced, 2=Extra balanced");
    }
    
    return Plugin_Handled;
}


// Sourcemod AdminCommand
public Action CMD_SmGenTeams(int client, int args){
    if (args < 1)
    {
        return Plugin_Handled;
    }
    
    char mode[5];
    GetCmdArg(1,mode,sizeof(mode));
    
    if(StringToInt(mode)==0 || StringToInt(mode)==1 || StringToInt(mode)==2 ){
        PrintStartGenTeamInfo(StringToInt(mode));
    
        bool bSuccess = RandomizeTeams(StringToInt(mode));
        if( !bSuccess ){ CPrintToChat(client, "%T", "GenTeam_Fail", client); }
    }
    else{
        CPrintToChat(client, "%T", "GenTeam_HowToCommand", client);
    }
    
    return Plugin_Handled;
}














