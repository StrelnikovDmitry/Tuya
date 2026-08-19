# tuya

<img src="gallery/icon.svg" width="310" height="200" />

tuya is a lightweight and minimalistic library for creating TUIs. It uses dirty-rectangles technology pared with reactive rendering model only for specific slices.

## Technology

Instead of rerendering the whole screen every time, tuya works only with the given zone expected to change.
Tuya offers fast and lightweight screen refreshing, but requires manual control over the program's active output zone.
