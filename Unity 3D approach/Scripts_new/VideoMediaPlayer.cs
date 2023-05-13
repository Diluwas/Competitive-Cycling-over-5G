using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using RenderHeads.Media.AVProVideo;


public class VideoMediaPlayer : MonoBehaviour
{
    [SerializeField]
    private MediaPlayer mediaPlayer;
    [SerializeField]
    private mqttReceiver _eventSender;
    public string nameController = "Controller 1";
    private float playerSpeed = 1;
    private static bool functionExecuted = false;
    void Start(){
        _eventSender.OnMessageArrived += OnMessageArrivedHandler;
        Debug.Log("1: " + playerSpeed);
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
        _eventSender.OnMessageArrived += OnMessageArrivedHandler;
        functionExecuted = false;
    }
 
}
