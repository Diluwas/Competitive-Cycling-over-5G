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

    public mqttReceiver _eventSender;

    private float maxPlayback = 3.0f;
    private float playbackSpeed = 1.0f;

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

        if(newMsg != null){
            playerSpeed = float.Parse(newMsg);
            Debug.Log("player speed: "+ playerSpeed);
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
        }
        else{
            playbackSpeed = 1;
            Debug.Log("elplayer speed: "+ playbackSpeed);
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
        mediaPlayer.PlaybackRate = 1 * playbackSpeed;
        //functionExecuted = false;
    }

    public void returnToPreviousScene(){
         SceneManager.LoadScene("MenueScene");
    }
 
}
