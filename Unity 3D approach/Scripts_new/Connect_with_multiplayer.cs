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
    private string recieved_topic;
    private MqttClient client;
    private int tries;
    private int packet_count = 11;

    private int x = 9999;
    private int y = 9999;
    private int z = 9999;
    private  Stopwatch stopwatch = new Stopwatch();
    public Text textField;
    private bool connected = false;
    private string myTopic;       //Subscribes to my topic to recieve message from second user
    private string contenderTopic;   //publishes message to second user
    private string synchronizationOutTopic; //publishes messsage to server 
    private string synchronizationInTopic;    //recieve message from server
    private bool ServerAccepted = false;
    public GameObject Timer;
    private int serverPollAtempts = 1;
    private int serverPollAtemptsCounter = 5;


    public void ConnectToBroker(){
        myTopic = "VRcycling/"+UserSettings.UserId+"/PlayerSynch";
        contenderTopic = "VRcycling/"+UserSettings.RivalUserId+"/PlayerSynch";
        synchronizationOutTopic = "VRcycling/"+UserSettings.UserId+"/ServerSynch";
        synchronizationInTopic = "VRcycling/"+UserSettings.UserId+"/Server";
        
        UnityEngine.Debug.Log(myTopic);
        UnityEngine.Debug.Log(contenderTopic);
        UnityEngine.Debug.Log(synchronizationOutTopic);
        UnityEngine.Debug.Log(synchronizationInTopic);

        client = new MqttClient(UserSettings.GameServer); 
        client.MqttMsgPublishReceived += client_MqttMsgPublishReceived; 
        string clientId = Guid.NewGuid().ToString();
        client.Connect(clientId);
        client.Subscribe(new string[] {myTopic}, new byte[] { MqttMsgBase.QOS_LEVEL_AT_MOST_ONCE });
        client.Subscribe(new string[] {synchronizationInTopic}, new byte[] { MqttMsgBase.QOS_LEVEL_AT_MOST_ONCE });
        StartUserConnectionCheck();
    }

    private void client_MqttMsgPublishReceived(object sender, MqttMsgPublishEventArgs e)
    {
        recieved_message = Encoding.UTF8.GetString(e.Message);
        recieved_topic = e.Topic;
        UnityEngine.Debug.Log("recieved_message: "+recieved_message+"\nrecieved_topic"+recieved_topic);
        stopwatch.Stop();
    }

    private void publishMessage(int message){
        stopwatch.Reset();
        client.Publish(contenderTopic, Encoding.UTF8.GetBytes(message.ToString()), MqttMsgBase.QOS_LEVEL_AT_MOST_ONCE, false);
        stopwatch.Start();
        UnityEngine.Debug.Log("Published message: " + message.ToString());
    }

    private void publishMessageToServer(int message){
        client.Publish(synchronizationOutTopic, Encoding.UTF8.GetBytes(message.ToString()), MqttMsgBase.QOS_LEVEL_AT_MOST_ONCE, false);
        UnityEngine.Debug.Log("Published server message: " + message.ToString());
    }

    public void startCounter(){
        UnityEngine.Debug.Log("counter started");
        Timer.SetActive(true);
    }

    IEnumerator issueStartRequestToserver(){
        int pollingMessage = 10101;
        stopwatch.Reset();
        publishMessageToServer(pollingMessage);
        stopwatch.Start();
        while (serverPollAtempts != serverPollAtemptsCounter){
            if (Int32.TryParse(recieved_message, out y)){
                if(y == serverPollAtempts){
                    if(serverPollAtempts < 4){
                        publishMessageToServer(serverPollAtempts);
                        serverPollAtempts++;
                    }
                }
                else if(y == 10101){
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
