using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class TripSelector : MonoBehaviour
{
    public void OpenTrip()
    {
        SceneManager.LoadScene("Trip01");
    }
}

