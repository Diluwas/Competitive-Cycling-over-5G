using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class SettingSelector : MonoBehaviour
{
    public void OpenScene()
    {
        SceneManager.LoadScene("Settings");
    }
}
