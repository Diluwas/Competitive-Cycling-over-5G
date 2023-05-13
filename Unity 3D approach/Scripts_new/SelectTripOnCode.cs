using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class SelectTripOnCode : MonoBehaviour
{
    public void openTripScene(){
        SceneManager.LoadScene("VideoPlayer");
    }
}
