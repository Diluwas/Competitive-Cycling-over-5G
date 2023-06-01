using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class Timer : MonoBehaviour
{
    // Start is called before the first frame update
    float countdown = 10;
    public Text timerTime;
    public GameObject gameTimer;
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if(countdown > 0){
            countdown-=Time.deltaTime;
        }
        double timenow = System.Math.Round(countdown, 0);
        timerTime.text = timenow.ToString();
        Debug.Log(timenow);
        if(timenow == 0){
            Debug.Log("start now");
            gameTimer.SetActive(false);
            SceneManager.LoadScene("VideoPlayer");
            return;
        }
    }
}
