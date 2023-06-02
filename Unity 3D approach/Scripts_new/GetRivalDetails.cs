using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class GetRivalDetails : MonoBehaviour
{
    public InputField RivaluserNameInput; 

    public void updateRivalsDetails(){
        UserSettings.RivalUserName = RivaluserNameInput.text;

        Debug.Log("isMQTT: "+UserSettings.IsMQTT+"\nisUDP: "+UserSettings.IsUDP+"\nUsername: "+UserSettings.UserName
        +"\nRival Username: "+UserSettings.RivalUserName +"\nUser id: "+UserSettings.UserId
        +"\nRival id: "+UserSettings.RivalUserId+"\nVideo server IP: "+UserSettings.VideoServer+"\nGame server: "+UserSettings.GameServer+"\nisHost: "+
        UserSettings.IsHost+"\nisClient: "+UserSettings.IsClient);
    }
}
