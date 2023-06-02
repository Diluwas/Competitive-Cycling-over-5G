using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using uPLibrary.Networking.M2Mqtt;
using uPLibrary.Networking.M2Mqtt.Messages;
using System.Text;
using RenderHeads.Media.AVProVideo;
using UnityEngine.UI;

public class Movement : MonoBehaviour
{
    public Transform yellowCyclist;
    public Transform redCyclist;
    public float movementSpeed = 1f;
    private MqttClient client;

    private float speed = 0f;
    private float recieved_message_yellow = 0f;
    private float recieved_message_red = 0f;
    private static float recieved_message_yellow_new = 0f;
    private static float recieved_message_red_new = 0f;
    private float yellowMovement;
    public MediaPlayer mediaPlayer2;
    private double currentPosition;
    private int iteration = 0;
    private string myTimeStampTopic;
    private string rivalTimeStampTopic;
    public Text UserA;
    public Text UserB;

    void Start(){
        // create client instance 
        myTimeStampTopic = "VRcycling/"+UserSettings.UserId+"/Ts";
        rivalTimeStampTopic = "VRcycling/"+UserSettings.RivalUserId+"/Ts";

        client = new MqttClient(UserSettings.GameServer); 
 
        // register to message received 
        client.MqttMsgPublishReceived += client_MqttMsgPublishReceived; 
 
        string clientId = System.Guid.NewGuid().ToString(); 
        client.Connect(clientId); 
 
        // subscribe to the topic with QoS 2 
        client.Subscribe(new string[] { myTimeStampTopic }, new byte[] { MqttMsgBase.QOS_LEVEL_AT_MOST_ONCE });
        client.Subscribe(new string[] { rivalTimeStampTopic }, new byte[] { MqttMsgBase.QOS_LEVEL_AT_MOST_ONCE }); 
        UserA.text = UserSettings.UserId;
        UserB.text = UserSettings.RivalUserId;

    }

    public void client_MqttMsgPublishReceived(object sender, MqttMsgPublishEventArgs e){
        
        string topic_msg = e.Topic;
        if(topic_msg == myTimeStampTopic){
            recieved_message_yellow = float.Parse(Encoding.UTF8.GetString(e.Message));
            
        }
        if(topic_msg == rivalTimeStampTopic){
            recieved_message_red = float.Parse(Encoding.UTF8.GetString(e.Message));
        }

    }

    public static float Recieved_message_yellow_new{
        set{
            recieved_message_yellow_new = value;
        }
        get{
            return recieved_message_yellow_new;
        }
    }

    public static float Recieved_message_red_new{
        set{
            recieved_message_red_new = value;
        }
        get{
            return recieved_message_red_new;
        }
    }


    void Update(){
        
        if(iteration > 20){
            currentPosition = Math.Round(mediaPlayer2.Control.GetCurrentTime()*1000,2);
            client.Publish(myTimeStampTopic, Encoding.UTF8.GetBytes(currentPosition.ToString()), MqttMsgBase.QOS_LEVEL_AT_MOST_ONCE, false);
            iteration = 0;
        }
        

        if(recieved_message_yellow-recieved_message_yellow_new!=0){
            float dif_yellow = recieved_message_yellow-recieved_message_yellow_new;
            Debug.Log(recieved_message_yellow);
            float yellowMovement = dif_yellow*0.00002f;
            yellowCyclist.Translate(Vector3.right * yellowMovement);
    
            recieved_message_yellow_new = recieved_message_yellow;

        }


        if(recieved_message_red-recieved_message_red_new!=0){
            float dif_red = recieved_message_red-recieved_message_red_new;
            Debug.Log(recieved_message_red);
            float redMovement = dif_red*0.00002f;
            redCyclist.Translate(Vector3.right * redMovement);
    
            recieved_message_red_new = recieved_message_red;

        }
        Movement.recieved_message_red_new = recieved_message_red;
        Movement.recieved_message_yellow_new = recieved_message_yellow;

        iteration++;
        /*
        float horizontalInput = Input.GetAxis("Horizontal");
        float yellowMovementAmount = horizontalInput * movementSpeed * Time.deltaTime;

       // float yellowMovementAmount = client_MqttMsgPublishReceived(object sender, MqttMsgPublishEventArgs e);
        float redMovementAmount = 0f;
        if (Input.GetKey(KeyCode.B))
        {
            redMovementAmount = -movementSpeed * Time.deltaTime;
        }
        else if (Input.GetKey(KeyCode.N))
        {
            redMovementAmount = movementSpeed * Time.deltaTime;
        }
        redCyclist.Translate(Vector3.right * redMovementAmount);
        yellowCyclist.Translate(Vector3.right * yellowMovementAmount);

        Vector3 redScreenPos = Camera.main.WorldToScreenPoint(redCyclist.position);
        Vector3 yellowScreenPos = Camera.main.WorldToScreenPoint(yellowCyclist.position);
        */

    }
}
