using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UserSettings : MonoBehaviour
{
    private static string userName;
    private static bool isMQTT;
    private static bool isUDP;
    private static string gameServer;
    private static string videoServer;
    
    public static string UserName{
        set{
            userName = value;
        }
        get{
            return userName;
        }
    }

    public static bool IsMQTT{
        set{
            isMQTT =  value;
        }
        get{
            return isMQTT;
        }
    }

    public static bool IsUDP{
        set{
            isUDP = value;
        }
        get{
            return isUDP;
        }
    }

    public static string GameServer{
        set{
            gameServer = value;
        }
        get{
            return gameServer;
        }
    }

    public static string VideoServer{
        set{
            videoServer = value;
        }
        get{
            return videoServer;
        }
    }
}
