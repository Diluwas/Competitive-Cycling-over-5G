using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using RenderHeads.Media.AVProVideo;
using UnityEngine.UI;

public class ChooseWinner : MonoBehaviour
{
    public MediaPlayer mediaPlayer;
    private float duration = 300000f;
    public GameObject ViewWinner;

    [SerializeField]
    private Text FirstName;
    [SerializeField]
    private Text SecondName;
    [SerializeField]
    private Text FirstDistance;
    [SerializeField]
    private Text SecondDistance;
    [SerializeField]
    private Text FirstTime;
    [SerializeField]
    private Text SecondTime;


    private void DisplayResult(string WinnerName, string LoserName, float WinnerDistance, float LoserDistance, float WinnerTime, float LoserTime){
        FirstName.text = WinnerName;
        SecondName.text = LoserName;
        FirstDistance.text = WinnerDistance.ToString();
        SecondDistance.text = LoserDistance.ToString();
        FirstTime.text = 0.ToString();
        SecondTime.text = (LoserTime - WinnerTime).ToString();
    }

    void Update(){
        if(Movement.Recieved_message_red_new > duration){
            mediaPlayer.Pause();
            ViewWinner.SetActive(true);
            DisplayResult(UserSettings.RivalUserName, UserSettings.UserName,1000, 1000, Movement.Recieved_message_red_new, Movement.Recieved_message_yellow_new);
        }
        if(Movement.Recieved_message_yellow_new > duration){
            mediaPlayer.Pause();
            ViewWinner.SetActive(true);
            DisplayResult(UserSettings.UserName, UserSettings.RivalUserName,1000, 1000, Movement.Recieved_message_yellow_new, Movement.Recieved_message_red_new);
        }
    }

}
