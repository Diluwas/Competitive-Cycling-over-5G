using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ExitApplication : MonoBehaviour
{
    public void exit_application(){
        Application.Quit();
        Debug.Log("Exit from application");
    }
}
