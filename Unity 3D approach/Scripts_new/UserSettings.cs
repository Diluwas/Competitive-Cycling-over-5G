using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UserSettings : MonoBehaviour
{
    private static string userName;
    private static bool isMQTT;
    private static bool isUDP;
    private static bool isHost;
    private static bool isClient;
    private static string gameServer;
    private static string videoServer;
    private static string rivalUserName;
    private static string userId;
    private static string rivalUserId;
    
    public static string UserName{
        set{
            userName = value;
        }
        get{
            return userName;
        }
    }

    public static string UserId{
        set{
            userId = value;
        }
        get{
            return userId;
        }
    }

    public static string RivalUserId{
        set{
            rivalUserId = value;
        }
        get{
            return rivalUserId;
        }
    }

    public static string RivalUserName{
        set{
            rivalUserName = value;
        }
        get{
            return rivalUserName;
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

    public static bool IsHost{
        set{
            isHost =  value;
        }
        get{
            return isHost;
        }
    }

    public static bool IsClient{
        set{
            isClient = value;
        }
        get{
            return isClient;
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
