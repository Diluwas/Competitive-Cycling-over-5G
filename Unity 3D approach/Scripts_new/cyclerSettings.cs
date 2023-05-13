using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class cyclerSettings : MonoBehaviour
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

        userName = UserName.text;

        //check for which protocol to use
        if(MQTT.isOn){
            isMQTT = true;
        }
        else{
            isMQTT = false;
        }

        if(UDP.isOn){
            isUDP = true;
        }
        else{
            isUDP = false;
        }
        
        if((isMQTT && isUDP) || !(isMQTT || isUDP) || UserName.text == ""){
            errorPopup.SetActive(true);
            return;
        }

        //check for local media server IP
        if(VideoServer.text != ""){
            videoServer = VideoServer.text;
        }
        else{
            videoServer = "http://192.168.1.102:8080/hls/bicycle.m3u8";
        }

        //GameServer name or IP
        if(GameServer.text != ""){
            gameServer = GameServer.text;
        }
        else{
            if(isMQTT){
                gameServer = "test.mosquitto.org";
            }
            else if(isUDP){
                gameServer = "http://192.168.1.102";
            }
        }

        Debug.Log("User name = " + userName);
        Debug.Log("is MQTT = " + isMQTT);
        Debug.Log("is UDP = " + isUDP);
        Debug.Log("video server = " + videoServer);
        Debug.Log("game server = " + gameServer);
    }
    
}
