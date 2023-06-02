using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using RenderHeads.Media.AVProVideo;
using uPLibrary.Networking.M2Mqtt;
using uPLibrary.Networking.M2Mqtt.Messages;
using M2MqttUnity;
using UnityEngine.SceneManagement;
using System.Text;

public class VideoMediaPlayer : MonoBehaviour
{
    [SerializeField]
    private MediaPlayer mediaPlayer;
    
    public string nameController = "Controller 1";
    private float playerSpeed = 1;
    private static bool functionExecuted = false;

    public M2MqttUnityClient mqtt_client;

    public mqttReceiver _eventSender;

    private float maxPlayback = 3.0f;
    private float playbackSpeed = 0f;
    private MqttClient client;
    private string myTopic; //to recieve data from ESP32
    private string sendTopic; //for dulsara delay test purposes

    public GameObject ConnectionPopUpError;
    void Start(){
        // Opening media URL via a Path
        myTopic = "VRcycling/"+UserSettings.UserId+"/Speed";
        sendTopic = "VRcycling/test2";

        client = new MqttClient(UserSettings.GameServer); 
        client.MqttMsgPublishReceived += client_MqttMsgPublishReceived;
        string clientId = Guid.NewGuid().ToString();
        client.Connect(clientId);
        client.Subscribe(new string[] {myTopic}, new byte[] { MqttMsgBase.QOS_LEVEL_AT_MOST_ONCE });

        string videoPath = UserSettings.VideoServer;
        Debug.Log("videoPath : " + videoPath);
        bool isOpening = mediaPlayer.OpenMedia(new MediaPath(videoPath, MediaPathType.AbsolutePathOrURL), autoPlay:true);
        Debug.Log("isOpening: "+ isOpening);
        MediaHints hints = mediaPlayer.FallbackMediaHints;
        hints.stereoPacking = StereoPacking.TopBottom;
        mediaPlayer.FallbackMediaHints = hints;
        //Debug.Log("1: " + playerSpeed);
    }

    private void client_MqttMsgPublishReceived(object sender, MqttMsgPublishEventArgs e){
        string newMsg = Encoding.UTF8.GetString(e.Message);
        if(newMsg != null){
            playerSpeed = float.Parse(newMsg);
            //Debug.Log("player speed: "+ playerSpeed);
            if (playerSpeed > 12.5){
                playbackSpeed = maxPlayback;
            }
            else if(playerSpeed > 0.1){
                playbackSpeed = (float)((playerSpeed * maxPlayback)/12.5);
            }
            else{
                playbackSpeed = 0;
            }
            //float rate = mediaPlayer.PlaybackRate;
            
            //functionExecuted = true;
            //return;
            client.Publish(sendTopic, Encoding.UTF8.GetBytes(playerSpeed.ToString()), MqttMsgBase.QOS_LEVEL_AT_MOST_ONCE, false);
        }
        else{
            playbackSpeed = 1;
            Debug.Log("elplayer speed: "+ playbackSpeed);
            return;
        }
    }

    public void Update(){
        if(client.IsConnected){
            ConnectionPopUpError.SetActive(false);
        }
        else{
            ConnectionPopUpError.SetActive(true);
        }
        mediaPlayer.PlaybackRate = 1 * playbackSpeed;

        //functionExecuted = false;
    }

    public void returnToPreviousScene(){
         SceneManager.LoadScene("MenueScene");
    }
 
}
