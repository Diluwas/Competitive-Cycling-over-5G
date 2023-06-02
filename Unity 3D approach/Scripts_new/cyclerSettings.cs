using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class cyclerSettings :MonoBehaviour
{
    private string userName;
    private bool isMQTT;
    private bool isUDP;
    private bool isHost;
    private bool isClient;
    private string gameServer;
    private string videoServer;

    public Toggle MQTT;
    public Toggle UDP;
    public Toggle Host;
    public Toggle Client;
    public InputField UserName;
    public InputField GameServer;
    public InputField VideoServer;
    public GameObject errorPopup;
    public void updateCyclerSettings(){

        UserSettings.UserName = UserName.text;

        //check for which protocol to use
        if(MQTT.isOn){
            isMQTT = true;
            UserSettings.IsMQTT = true;
        }
        else{
            isMQTT = false;
            UserSettings.IsMQTT = false;
        }

        if(UDP.isOn){
            isUDP = true;
            UserSettings.IsUDP = true;
        }
        else{
            isUDP = false;
            UserSettings.IsUDP = false;
        }

        if(Host.isOn){
            isHost = true;
            UserSettings.IsHost = true;
            UserSettings.UserId = "UserA";
            UserSettings.RivalUserId = "UserB";
        }
        else{
            isHost = false;
            UserSettings.IsHost = false;
        }

        if(Client.isOn){
            isClient = true;
            UserSettings.IsClient = true;
            UserSettings.UserId = "UserB";
            UserSettings.RivalUserId = "UserA";
        }
        else{
            isClient = false;
            UserSettings.IsClient = false;
        }

        
        if((isMQTT && isUDP) || !(isMQTT || isUDP) || (isHost && isClient) || !(isHost || isClient) || UserName.text == ""){
            errorPopup.SetActive(true);
            return;
        }

        //check for local media server IP
        if(VideoServer.text != ""){
            videoServer = VideoServer.text;
            videoServer = "http://"+videoServer+":8080/trip1/1080P.m3u8";
            UserSettings.VideoServer = videoServer;
        }
        else{
            videoServer = "http://192.168.8.130:8080/trip2/bicycle.m3u8";
            UserSettings.VideoServer = videoServer;   
        }

        //GameServer name or IP
        if(GameServer.text != ""){
            gameServer = GameServer.text;
            UserSettings.GameServer = gameServer;
        }
        else{
            if(isMQTT){
                gameServer = "test.mosquitto.org";
                UserSettings.GameServer = gameServer;
            }
            else if(isUDP){
                gameServer = "http://192.168.1.102";
                UserSettings.GameServer = gameServer;
            }
        }

        Debug.Log("isMQTT: "+UserSettings.IsMQTT+"\nisUDP: "+UserSettings.IsUDP+"\nUsername: "+UserSettings.UserName
        +"\nRival Username: "+UserSettings.RivalUserName +"\nUser id: "+UserSettings.UserId
        +"\nRival id: "+UserSettings.RivalUserId+"\nVideo server IP: "+UserSettings.VideoServer+"\nGame server: "+UserSettings.GameServer+"\nisHost: "+
        UserSettings.IsHost+"\nisClient: "+UserSettings.IsClient);
    }
}
