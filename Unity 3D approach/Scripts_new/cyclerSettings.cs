using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class cyclerSettings :MonoBehaviour
{
    private string userName;
    private bool isMQTT;
    private bool isUDP;
    private string gameServer;
    private string videoServer;

    public Toggle MQTT;
    public Toggle UDP;
    public InputField UserName;
    public InputField GameServer;
    public InputField VideoServer;
    public GameObject errorPopup;
    public void updateCyclerSettings(){

        userName = "ABC";
        //userName = UserName.text;
        UserSettings.UserName = userName;

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
        
        if((isMQTT && isUDP) || !(isMQTT || isUDP)){     //if((isMQTT && isUDP) || !(isMQTT || isUDP) || UserName.text == ""){
            errorPopup.SetActive(true);
            return;
        }

        //check for local media server IP
        if(VideoServer.text != ""){
            videoServer = VideoServer.text;
            videoServer = "http://"+videoServer+":8080/hls/bicycle.m3u8";
            UserSettings.VideoServer = videoServer;
        }
        else{
            videoServer = "http://192.168.1.102:8080/hls/bicycle.m3u8";//http://192.168.8.130:8080/hls/bicycle.m3u8
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
        +"\nVideo server IP: "+UserSettings.VideoServer+"\nGame server: "+UserSettings.GameServer);
    }
}
