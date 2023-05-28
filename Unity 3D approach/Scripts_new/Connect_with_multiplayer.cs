using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using UnityEngine;
using uPLibrary.Networking.M2Mqtt;
using uPLibrary.Networking.M2Mqtt.Messages;
using System.Diagnostics;
using UnityEngine.UI;


public class Connect_with_multiplayer : MonoBehaviour
{
    private string recieved_message;
    private MqttClient client;
    private int tries;
    private int packet_count = 11;

    private int x = 9999;
    private int y = 9999;
    private  Stopwatch stopwatch = new Stopwatch();
    public Text textField;
    private bool connected = false;
    private string myTopic = "VRcycling/Dilun";
    private string contenderTopic = "VRcycling/Sandeepa";
    private string synchronizationInTopic = "VRcycling/Synchin";
    private string synchronizationOutTopic = "VRcycling/Synchout";
    private bool ServerAccepted = false;
    public GameObject Timer;


    public void ConnectToBroker(){
        client = new MqttClient("test.mosquitto.org"); 
        client.MqttMsgPublishReceived += client_MqttMsgPublishReceived; 
        string clientId = Guid.NewGuid().ToString();
        client.Connect(clientId);
        client.Subscribe(new string[] {myTopic}, new byte[] { MqttMsgBase.QOS_LEVEL_AT_MOST_ONCE });
        client.Subscribe(new string[] {synchronizationOutTopic}, new byte[] { MqttMsgBase.QOS_LEVEL_AT_MOST_ONCE }); 
        StartUserConnectionCheck();
    }

    private void client_MqttMsgPublishReceived(object sender, MqttMsgPublishEventArgs e)
    {
        recieved_message = Encoding.UTF8.GetString(e.Message);
        stopwatch.Stop();
    }

    private void publishMessage(int message){
        stopwatch.Reset();
        client.Publish(contenderTopic, Encoding.UTF8.GetBytes(message.ToString()), MqttMsgBase.QOS_LEVEL_AT_MOST_ONCE, false);
        stopwatch.Start();
        UnityEngine.Debug.Log("Published message: " + message.ToString());
    }

    private void publishMessageToServer(int message){
        client.Publish(synchronizationInTopic, Encoding.UTF8.GetBytes(message.ToString()), MqttMsgBase.QOS_LEVEL_AT_MOST_ONCE, false);
        UnityEngine.Debug.Log("Published server message: " + message.ToString());
    }

    public void startCounter(){
        UnityEngine.Debug.Log("counter started");
        Timer.SetActive(true);
    }

    IEnumerator issueStartRequestToserver(){
        int messageToServer = 101101;
        stopwatch.Reset();
        publishMessageToServer(messageToServer);
        stopwatch.Start();
        while (true){
            if (Int32.TryParse(recieved_message, out y)){
                if(y == messageToServer){
                    UnityEngine.Debug.Log(y+ "    " + recieved_message);
                    ServerAccepted = true;
                    startCounter();
                    UnityEngine.Debug.Log("switching to counter");
                    
                }
            }
    
            if(stopwatch.ElapsedMilliseconds > 10000){
                stopwatch.Stop();
                ServerAccepted = false;
                UnityEngine.Debug.Log("Timeout");
                break;
            }
            yield return new WaitForSeconds(0.1f);
        }
        
    }

    IEnumerator VerifyConnection(){
        if(UserSettings.IsHost){
            tries = 1;
            textField.text = "Connecting";
            publishMessage(tries);

            while (tries != packet_count){  //should be edited this function for second user
                if (Int32.TryParse(recieved_message, out x)){
                    UnityEngine.Debug.Log(recieved_message);
                    if(x == tries){
                        UnityEngine.Debug.Log("Recieved message: " + x);
                        textField.text = textField.text + ".";
                        tries++;
                        if(tries < 11){
                            publishMessage(tries);
                        }   
                    }
                }
                if(stopwatch.ElapsedMilliseconds > 10000){
                    stopwatch.Stop();
                    break;
                }
                yield return new WaitForSeconds(0.1f);
            }

            if(tries == 11){
                UnityEngine.Debug.Log("Connection OK");
                textField.text = "Player connected";
                connected = true;
                if(connected == true){
                    StartCoroutine(issueStartRequestToserver());
                }  
            }
            else{
                UnityEngine.Debug.Log("Connection is not OK");
                textField.text = "Player not connected";
                connected = false;
            }
        }
        else if(UserSettings.IsClient){
            UnityEngine.Debug.Log("Switching to Client code");
            tries = 1;
            textField.text = "Connecting";
            while (tries != packet_count){
                if (Int32.TryParse(recieved_message, out x)){
                    if(x == tries){
                        UnityEngine.Debug.Log("Recieved message: " + x);
                        textField.text = textField.text + ".";
                        if(tries < 11){
                            publishMessage(tries);
                        }
                        tries++;
                    }
                }
                if(stopwatch.ElapsedMilliseconds > 10000){
                    stopwatch.Stop();
                    break;
                }
                yield return new WaitForSeconds(0.1f);
            }

            if(tries == 11){
                UnityEngine.Debug.Log("Connection OK");
                textField.text = "Player connected";
                connected = true;
                if(connected == true){
                    StartCoroutine(issueStartRequestToserver());
                }  
            }
            else{
                UnityEngine.Debug.Log("Connection is not OK");
                textField.text = "Player not connected";
                connected = false;
            }
        }
    }

    

    public void StartUserConnectionCheck(){
        StartCoroutine(VerifyConnection());
    }
}
