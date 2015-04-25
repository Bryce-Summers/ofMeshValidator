//
//  MeshValidator.cpp
//  ofApp
//
//  Created by Bryce Summers on 10/1/14.
//
//

#include "MeshValidator.h"


// Returns true iff the mesh contains two index defined traingles that intersect.
bool check_triangle_intersections(ofMesh &mesh)
{
    
    int len = mesh.getNumIndices();
    for(int i = 0; i < len; i += 3)
    {
        ofVec3f v1 = mesh.getVertex(mesh.getIndex(i));
        ofVec3f v2 = mesh.getVertex(mesh.getIndex(i + 1));
        ofVec3f v3 = mesh.getVertex(mesh.getIndex(i + 2));
        
        for(int j = 0; j < len; j += 3)
        {
            ofVec3f p1 = mesh.getVertex(mesh.getIndex(j));
            ofVec3f p2 = mesh.getVertex(mesh.getIndex(j + 1));
            ofVec3f p3 = mesh.getVertex(mesh.getIndex(j + 2));
            
            int b  = Intersecting(p1, p2, v1, v2, v3);
            int b2 = Intersecting(p2, p3, v1, v2, v3);
            int b3 = Intersecting(p3, p1, v1, v2, v3);
            
            if(b == 1 || b2 == 1 || b3 == 1)
            {
                return true;
            }
            
            if(point_triangle_intersection(v1, v2, v3, p1)||
               point_triangle_intersection(v1, v2, v3, p2)||
               point_triangle_intersection(v1, v2, v3, p3))
            {
                return true;
            }
            
            
        }
        
    }
    
    return false;
    
}


/* Check whether P and Q lie on the same side of line AB */
float Side(ofVec3f &p, ofVec3f &q, ofVec3f &a, ofVec3f b)
{
    float z1 = (b.x - a.x) * (p.y - a.y) - (p.x - a.x) * (b.y - a.y);
    float z2 = (b.x - a.x) * (q.y - a.y) - (q.x - a.x) * (b.y - a.y);
    return z1 * z2;
}

/* Check whether segment P0P1 intersects with triangle t0t1t2 */
int Intersecting(ofVec3f &p0, ofVec3f &p1, ofVec3f &t0, ofVec3f &t1, ofVec3f &t2)
{
    /* Check whether segment is outside one of the three half-planes
     * delimited by the triangle. */
    float f1 = Side(p0, t2, t0, t1), f2 = Side(p1, t2, t0, t1);
    float f3 = Side(p0, t0, t1, t2), f4 = Side(p1, t0, t1, t2);
    float f5 = Side(p0, t1, t2, t0), f6 = Side(p1, t1, t2, t0);
    /* Check whether triangle is totally inside one of the two half-planes
     * delimited by the segment. */
    float f7 = Side(t0, t1, p0, p1);
    float f8 = Side(t1, t2, p0, p1);
    
    /* If segment is strictly outside triangle, or triangle is strictly
     * apart from the line, we're not intersecting */
    if ((f1 < 0 && f2 < 0) || (f3 < 0 && f4 < 0) || (f5 < 0 && f6 < 0)
        || (f7 > 0 && f8 > 0))
        return 0;
    
    /* If segment is aligned with one of the edges, we're overlapping */
    if ((f1 == 0 && f2 == 0) || (f3 == 0 && f4 == 0) || (f5 == 0 && f6 == 0))
        return 2;
    
    /* If segment is outside but not strictly, or triangle is apart but
     * not strictly, we're touching */
    if ((f1 <= 0 && f2 <= 0) || (f3 <= 0 && f4 <= 0) || (f5 <= 0 && f6 <= 0)
        || (f7 >= 0 && f8 >= 0))
        return 2; // Touching.
    
    /* If both segment points are strictly inside the triangle, we
     * are not intersecting either */
    if (f1 > 0 && f2 > 0 && f3 > 0 && f4 > 0 && f5 > 0 && f6 > 0)
        return 0;
    
    /* Otherwise we're intersecting with at least one edge */
    return 1;
}

// Returns true iff the point is inside or on the exterior of the triangle and not equal to one of the triangle vertices.
bool point_triangle_intersection(ofVec3f &t1, ofVec3f &t2, ofVec3f &t3, ofVec3f &point)
{
    
    if(point == t1 || point == t2 || point == t3)
    {
        return false;
    }
    
    float c1, c2, c3;
    
    BarycentricCoords(t1, t2, t3, point, c1, c2, c3);
    
    if(0 < c1 && c1 < 1 &&
       0 < c2 && c2 < 1 &&
       0 < c3 && c3 < 1)
    {
        return true;
    }
}


void BarycentricCoords(const ofVec3f & vTriVtx1,
                       const ofVec3f & vTriVtx2,
                       const ofVec3f & vTriVtx3,
                       const ofVec3f & vVertex,
                       float & fBary1, float & fBary2, float & fBary3 )
{
    
    ofVec3f kV02 = vTriVtx1 - vTriVtx3;
    ofVec3f kV12 = vTriVtx2 - vTriVtx3;
    ofVec3f kPV2 = vVertex - vTriVtx3;
    
    float fM00 = kV02.dot(kV02);
    float fM01 = kV02.dot(kV12);
    float fM11 = kV12.dot(kV12);
    float fR0  = kV02.dot(kPV2);
    float fR1  = kV12.dot(kPV2);
    float fDet = fM00*fM11 - fM01*fM01;
    
    float fInvDet = ((float)1.0)/fDet;
    
    fBary1 = (fM11*fR0 - fM01*fR1)*fInvDet;
    fBary2 = (fM00*fR1 - fM01*fR0)*fInvDet;
    fBary3 = (float)1.0 - fBary1 - fBary2;
}
