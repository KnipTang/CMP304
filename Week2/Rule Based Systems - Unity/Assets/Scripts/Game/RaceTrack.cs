using System.Collections;
using System.Collections.Generic;
using UnityEngine;


/**
 * RaceTrack manages the track the Legend Car can move along
 */
public class RaceTrack : MonoBehaviour
{
    //The different possible track tiles used in constructing a complete race track
    public enum TrackSectionType { VerticalNS, VerticalSN, HorizontalEW, HorizontalWE, CornerSE, CornerSW, CornerNW, CornerNE };

    private static float CARZ = -2f; // layout for the car postion

    public Grid groundGrid; // Grid the track will be positioned onto
    public GameObject trackSectionPrefab; // the prefab for each Track Section

    private List<TrackSection> raceTrack = new List<TrackSection>(); // list of all sections in the constrcted track
    private List<TrackData> trackInfo = new List<TrackData>(); // the data associated with each track, used for construction


    void Awake()
    {
        initTrackData();
     
    }
    void Start()
    {
        createTestTrack();
    }
    void Update()
    {
        
    }

    /**
     * getCarPosForTrackIndex will return the world position for a track index
     */
    public Vector3 getCarPosForTrackIndex(int trackIndex)
    {
        if (trackIndex < 0 || trackIndex >= raceTrack.Count)
        {
            Debug.LogWarning("WARNING: invalid track index: " + trackIndex);
            return Vector3.zero;
        }
        else
        {
           Vector3 trackPos = groundGrid.CellToWorld(trackInfo[trackIndex].gridPos);
           return new Vector3(trackPos.x, trackPos.y, CARZ);
        }

    }

    public TrackSectionType getCurrentTrackType(int trackIndex)
    {
        if (trackIndex < 0 || trackIndex >= trackInfo.Count)
        {
            Debug.LogWarning("WARNING: invalid track index: " + trackIndex);
            return 0;
        }

        return trackInfo[trackIndex].trackType;
    }

    /**
        * getNextCornerSpeed will return the next corner speed found from given start index
        */
    public int getNextCornerSpeed(int searchStart)
    {
        int nextCornerSpeed = 0;
        int nextCornerDistance = 0;

        (nextCornerDistance, nextCornerSpeed) = getNextCornerData(searchStart);
        return nextCornerDistance;
    }


    /**
     * getNextCornerSpeed will return the next corner speed and distance found from given start index
     */
    public (int, int) getNextCornerData(int searchStart)
    {
        int searchCount = 0;

        if(searchStart < 0 )
        {
            Debug.LogWarning("WARNING: invalid search start point in getNextCornerDist : " + searchStart);
            return (-1, -1);
        }
        else if(searchStart >= raceTrack.Count)
        {
            searchStart = searchStart % raceTrack.Count;// search should loop around to start 
        }

        int searchIndex = searchStart;
        do
        {
            if (raceTrack[searchIndex].isCorner())
            {
                return (searchCount, raceTrack[searchIndex].getCornerSpeed());
            }

            searchIndex = searchIndex + 1;
            if (searchIndex >= raceTrack.Count)
                searchIndex = 0;

            searchCount++;
        } while (searchCount < raceTrack.Count);

        Debug.LogWarning("WARNING: Cannot find next corner on track");
        return (-1, -1);
    }

    /**
     * getNextLegendLineDist will return the next legend line distance found from given start index
     */
    public int getNextLegendLineDist(int searchStart)
    {
        int searchCount = 0;

        if (searchStart < 0)
        {
            Debug.LogWarning("WARNING: invalid search start point in getNextLegendLineDist : " + searchStart);
            return -1;
        }
        else if (searchStart >= raceTrack.Count)
        { 
            searchStart = searchStart % raceTrack.Count;// search should loop around to start 
        }

        int searchIndex = searchStart;
        do
        {
            if (raceTrack[searchIndex].isLegendLine)
            {
                return searchCount;
            }

            searchIndex = searchIndex + 1;
            if (searchIndex >= raceTrack.Count)
                searchIndex = 0;

            searchCount++;
        } while (searchCount < raceTrack.Count);

        Debug.LogWarning("WARNING: Cannot find next legend line on track");
        return -1;
    }

    public int getTrackLength()
    {
        return raceTrack.Count;
    }

    /**
     * initTrackData will populate the trackInfo object with data for a complete race circuit
     */
    void initTrackData()
    {
        // the below data will proudce a compelte race track
        trackInfo.Add(new TrackData(new Vector3Int(-6, -4), TrackSectionType.HorizontalWE, 0, false, true));
        trackInfo.Add(new TrackData(new Vector3Int(-5, -4), TrackSectionType.HorizontalWE));
        trackInfo.Add(new TrackData(new Vector3Int(-4, -4), TrackSectionType.HorizontalWE));
        trackInfo.Add(new TrackData(new Vector3Int(-3, -4), TrackSectionType.HorizontalWE));
        trackInfo.Add(new TrackData(new Vector3Int(-2, -4), TrackSectionType.HorizontalWE));
        trackInfo.Add(new TrackData(new Vector3Int(-1, -4), TrackSectionType.HorizontalWE));
        trackInfo.Add(new TrackData(new Vector3Int(0, -4), TrackSectionType.HorizontalWE));
        trackInfo.Add(new TrackData(new Vector3Int(1, -4), TrackSectionType.HorizontalWE));
        trackInfo.Add(new TrackData(new Vector3Int(2, -4), TrackSectionType.HorizontalWE, 0, true, false));
        trackInfo.Add(new TrackData(new Vector3Int(3, -4), TrackSectionType.HorizontalWE));
        trackInfo.Add(new TrackData(new Vector3Int(4, -4), TrackSectionType.HorizontalWE));
        trackInfo.Add(new TrackData(new Vector3Int(5, -4), TrackSectionType.HorizontalWE));
        trackInfo.Add(new TrackData(new Vector3Int(6, -4), TrackSectionType.HorizontalWE));
        trackInfo.Add(new TrackData(new Vector3Int(7, -4), TrackSectionType.CornerNW, 6, false, false));
        trackInfo.Add(new TrackData(new Vector3Int(7, -3), TrackSectionType.VerticalSN, 0, true, false));
        trackInfo.Add(new TrackData(new Vector3Int(7, -2), TrackSectionType.VerticalSN));
        trackInfo.Add(new TrackData(new Vector3Int(7, -1), TrackSectionType.CornerSW, 3, false, false));
        trackInfo.Add(new TrackData(new Vector3Int(6, -1), TrackSectionType.HorizontalEW));
        trackInfo.Add(new TrackData(new Vector3Int(5, -1), TrackSectionType.HorizontalEW));
        trackInfo.Add(new TrackData(new Vector3Int(4, -1), TrackSectionType.HorizontalEW, 0, true, false));
        trackInfo.Add(new TrackData(new Vector3Int(3, -1), TrackSectionType.HorizontalEW));
        trackInfo.Add(new TrackData(new Vector3Int(2, -1), TrackSectionType.HorizontalEW));
        trackInfo.Add(new TrackData(new Vector3Int(1, -1), TrackSectionType.HorizontalEW));
        trackInfo.Add(new TrackData(new Vector3Int(0, -1), TrackSectionType.CornerNE, 4, false, false));
        trackInfo.Add(new TrackData(new Vector3Int(0, 0), TrackSectionType.VerticalSN, 0));
        trackInfo.Add(new TrackData(new Vector3Int(0, 1), TrackSectionType.VerticalSN, 0, true, false));
        trackInfo.Add(new TrackData(new Vector3Int(0, 2), TrackSectionType.VerticalSN));
        trackInfo.Add(new TrackData(new Vector3Int(0, 3), TrackSectionType.VerticalSN));
        trackInfo.Add(new TrackData(new Vector3Int(0, 4), TrackSectionType.CornerSW, 4, false, false));
        trackInfo.Add(new TrackData(new Vector3Int(-1, 4), TrackSectionType.HorizontalEW));
        trackInfo.Add(new TrackData(new Vector3Int(-2, 4), TrackSectionType.HorizontalEW));
        trackInfo.Add(new TrackData(new Vector3Int(-3, 4), TrackSectionType.HorizontalEW, 0, true, false));
        trackInfo.Add(new TrackData(new Vector3Int(-4, 4), TrackSectionType.HorizontalEW));
        trackInfo.Add(new TrackData(new Vector3Int(-5, 4), TrackSectionType.HorizontalEW));
        trackInfo.Add(new TrackData(new Vector3Int(-6, 4), TrackSectionType.HorizontalEW));
        trackInfo.Add(new TrackData(new Vector3Int(-7, 4), TrackSectionType.HorizontalEW));
        trackInfo.Add(new TrackData(new Vector3Int(-8, 4), TrackSectionType.CornerSE, 5, false, false));
        trackInfo.Add(new TrackData(new Vector3Int(-8, 3), TrackSectionType.VerticalNS));
        trackInfo.Add(new TrackData(new Vector3Int(-8, 2), TrackSectionType.VerticalNS));
        trackInfo.Add(new TrackData(new Vector3Int(-8, 1), TrackSectionType.VerticalNS));
        trackInfo.Add(new TrackData(new Vector3Int(-8, 0), TrackSectionType.VerticalNS, 0, true, false));
        trackInfo.Add(new TrackData(new Vector3Int(-8, -1), TrackSectionType.VerticalNS));
        trackInfo.Add(new TrackData(new Vector3Int(-8, -2), TrackSectionType.VerticalNS));
        trackInfo.Add(new TrackData(new Vector3Int(-8, -3), TrackSectionType.VerticalNS));
        trackInfo.Add(new TrackData(new Vector3Int(-8, -4), TrackSectionType.CornerNE, 4, false, false));
        trackInfo.Add(new TrackData(new Vector3Int(-7, -4), TrackSectionType.HorizontalWE));
    }

    /**
     * createTestTrack will construct a race track using the trackSectionPrefab's and the data in the trackInfo object
     */
    void createTestTrack()
    {
        for (int i=0;i< trackInfo.Count;i++)
        {
            Vector3 pos = groundGrid.CellToWorld(trackInfo[i].gridPos); // conver the track index to a world position
            GameObject go = Instantiate(trackSectionPrefab, pos, Quaternion.identity); // Instantiate a trackSectionPrefab object in the scene at the desired position
            TrackSection ts = go.GetComponent<TrackSection>();
            ts.initTrackSection(trackInfo[i].trackType, trackInfo[i].legendLine, trackInfo[i].startLine); // initalise the TrackSection object
            if (ts.isCorner())
                ts.setCornerSpeed(trackInfo[i].cornerSpeed); 
            raceTrack.Add(ts); // add the TrackSection to the overall raceTrack

        }


    }

}
