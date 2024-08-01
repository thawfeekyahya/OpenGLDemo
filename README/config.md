# Open GL configuration for the current hardware can be eqnuired via *glGetIntegerv* function

There are multiple configure options are supported, these are quite often used

```
GL_MAX_COMBINED_TEXTURE_IMAGE_UINTS,
GL_MAX_CUBE_MAP_TEXTURE_SIZE,
GL_MAX_DRAW_BUFFERS,
GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,
GL_MAX_TEXTURE_IMAGES_UNITS,
GL_MAX_TEXTURE_SIZE,
GL_MAX_VARYING_FLOATS,
GL_MAX_VERTEX_ATTRIBS,
GL_MAX_VERTEX_TEXTURE_IMAGES_UNITS,
GL_MAX_VERTEX_UNIFORM_COMPONENTS,
GL_MAX_VIEWPORTS_DIMS,
GL_MAX_STEREO
```

### Example
```
int v = 0;
glGetIntegerv(GL_MAX_TEXTURE_SIZE,&v);
cout<<v;
```




