[TOC]

# RT: The Next Week
Citing: 
[_Ray Tracing: The Next Week_](https://raytracing.github.io/books/RayTracingTheNextWeek.html)

## Note

### 3 Bounding Volume Hierarchies (BVH)

#### The Key Idea

```c++
if (ray hits bounding object)
    return whether ray hits bounded objects
else
    return false
```

#### Hierarchies of Bounding Volumes

```c++
if (hits purple)
    hit0 = hits blue enclosed objects
    hit1 = hits red enclosed objects
    if (hit0 or hit1)
        return true and info of closer hit
return false
```

#### Axis-Aligned Bounding Boxes (AABBs)

A ray bounding volume intersection needs to be fast, and bounding volumes need to be pretty compact. In practice for most models, axis-aligned boxes work better than the alternatives.

The key observation to turn that 1D math into a hit test is that for a hit, the 𝑡-intervals need to overlap. For example, in 2D the green and blue overlapping only happens if there is a hit.

The following pseudocode determines whether the 𝑡 intervals in the slab overlap:
```c++
compute (tx0, tx1)
compute (ty0, ty1)
return overlap?( (tx0, tx1), (ty0, ty1))
```

That is awesomely simple, and the fact that the 3D version also works is why people love the slab method:

![](https://raytracing.github.io/images/fig-2.04-ray-slab-interval.jpg)

```c++
compute (tx0, tx1)
compute (ty0, ty1)
compute (tz0, tz1)
return overlap?( (tx0, tx1), (ty0, ty1), (tz0, tz1))
```

The boolean overlap that also computes the overlap interval (𝑓,𝐹) of intervals (𝑑,𝐷) and (𝑒,𝐸) would be:
```c++
bool overlap(d, D, e, E, f, F){
    f = max(d, e);
    F = min(D, E);
    return (f < F);
}
```

### 4. Solid Textures

