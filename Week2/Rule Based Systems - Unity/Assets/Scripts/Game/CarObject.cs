using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using static RaceTrack;

/**
 * CarObject is associated with the LegendCar prefact
 */
public class CarObject : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void turnCar(TrackSectionType trackSectionType)
    {

        this.transform.eulerAngles = new Vector3(  
            this.transform.eulerAngles.x,
            this.transform.eulerAngles.y + 0,
            getCarRotationForTrackType(trackSectionType)
         );

   
    }

    private float getCarRotationForTrackType(TrackSectionType trackSectionType)
    {
        if (trackSectionType == TrackSectionType.CornerSE)
            return 135f;
        else if (trackSectionType == TrackSectionType.CornerSW)
            return 45f;
        else if (trackSectionType == TrackSectionType.CornerNW)
            return -45f;
        else if (trackSectionType == TrackSectionType.CornerNE)
            return -135f;
        else if (trackSectionType == TrackSectionType.HorizontalWE)
            return -90f;
        else if (trackSectionType == TrackSectionType.HorizontalEW)
            return 90f;
        else if (trackSectionType == TrackSectionType.VerticalNS)
            return 180f;
        else
            return 0f;
    }
}
