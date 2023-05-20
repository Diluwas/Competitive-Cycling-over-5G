using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using RenderHeads.Media.AVProVideo;
using uPLibrary.Networking.M2Mqtt;
using uPLibrary.Networking.M2Mqtt.Messages;
using M2MqttUnity;
using UnityEngine.SceneManagement;

public class VideoMediaPlayer : MonoBehaviour
{
    [SerializeField]
    private MediaPlayer mediaPlayer;
    
    public string nameController = "Controller 1";
    private float playerSpeed = 1;
    private static bool functionExecuted = false;

    public M2MqttUnityClient mqtt_client;

    private int checkedForConnection = 0;
    public mqttReceiver _eventSender;

    public GameObject ConnectionPopUpError;
    void Start(){
        // Opening media URL via a Path
        mqtt_client.brokerAddress = UserSettings.GameServer;
        string videoPath = UserSettings.VideoServer;
        Debug.Log("videoPath : " + videoPath);
        bool isOpening = mediaPlayer.OpenMedia(new MediaPath(videoPath, MediaPathType.AbsolutePathOrURL), autoPlay:true);
        Debug.Log("isOpening: "+ isOpening);
        MediaHints hints = mediaPlayer.FallbackMediaHints;
        hints.stereoPacking = StereoPacking.TopBottom;
        mediaPlayer.FallbackMediaHints = hints;

        _eventSender.OnMessageArrived += OnMessageArrivedHandler;
        //Debug.Log("1: " + playerSpeed);
    }

    private void OnMessageArrivedHandler(string newMsg){

        if(newMsg != null && functionExecuted == false){
            playerSpeed = float.Parse(newMsg);
            float rate = mediaPlayer.PlaybackRate;
            mediaPlayer.PlaybackRate = 1 * playerSpeed;
            functionExecuted = true;
            return;
        }
        else{
            playerSpeed = 1;
            return;
        }
    }

    public void Update(){
        if(_eventSender.isConnected){
            ConnectionPopUpError.SetActive(false);
        }
        else{
            ConnectionPopUpError.SetActive(true);
        }
        _eventSender.OnMessageArrived += OnMessageArrivedHandler;
        functionExecuted = false;
    }

    public void returnToPreviousScene(){
         SceneManager.LoadScene("MenueScene");
    }
 
}
