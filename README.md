```markdown
<!--
MIT License

Copyright (c) DrElliot

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
-->

# Unreal Engine 5 Multi-Window Plugin

The Unreal Engine 5 Multi-Window Plugin provides a convenient way to create and manage external Slate windows within your Unreal Engine projects. These windows can host custom user interfaces, enabling enhanced flexibility and interaction options.

![Multi Window Example](https://imgur.com/DCLo9Lx)
![Multi Window Example](https://imgur.com/btjW9MP)

## Features

- **External Slate Windows**: Create external windows with custom titles, sizes, and positions.
- **UMG Widget Support**: Host UMG widgets inside external windows for enhanced user interactions.
- **Dependency Types**: Tie windows to specific contexts such as the world or PIE (Play In Editor) sessions.
- **Sizing Rules**: Specify sizing rules and support for window maximize and minimize actions.
- **Shutdown Functionality**: Ability to shut down windows by title or object reference.

## Installation

To install the Multi-Window Plugin in your Unreal Engine project, follow these steps:

1. Download the plugin from the [GitHub repository](https://github.com/MrDrElliot/Multi-Window-Plugin).
2. Extract the plugin folder into the "Plugins" directory of your Unreal Engine project.
3. Enable the plugin in your project settings or by adding it to your project's `.uproject` file.

## Usage

### Creating Multi Windows

Use the provided function `CreateMultiWindow` to create new Multi Windows with custom configurations. Here's an example of how to use the function:

```cpp
UMW_Window* CreateMultiWindow(
    FName InTitle = "New Window",
    UUserWidget* Widget = nullptr,
    EMultiWidgetDependencyType DependencyType = EMultiWidgetDependencyType::World,
    FVector2D WindowPosition = FVector2D(0.0f, 0.0f),
    FVector2D WindowSize = FVector2D(800.0f, 600.0f),
    UObject* DependencyObject = nullptr,
    EBPSizingRule SizingRule = EBPSizingRule::UserSized,
    bool bSupportsMaximize = true,
    bool bSupportsMinimize = true
);
```

### Initialization and Shutdown

Initialize a Multi Window object using the `Init()` function. This sets up the window with the specified parameters and adds it to the Slate application. Call `Shutdown()` to clean up and remove the window.

### Shutting Down Windows

Users can shut down windows using the following functions:

- `ShutdownWindowByName`: Tries to find an active window by its title and shuts it down.
- `ShutdownWindowByObjectReference`: Directly shuts down a window by providing its object reference.

## Example

```cpp
// Create a new Multi Window
UMW_Window* MyWindow = CreateMultiWindow(
    "My Window", 
    MyUserWidget, 
    EMultiWidgetDependencyType::World,
    FVector2D(100.0f, 100.0f),
    FVector2D(600.0f, 400.0f),
    nullptr, /* Only required for Object dependency */
    EBPSizingRule::FixedSize,
    true,
    true
);


// Later, shutdown the window by title
UMultiWindowSubsystem::Get()->ShutdownWindowByName("My Window");
```

## License

This plugin is provided under the [MIT License](LICENSE). Feel free to use and modify it in your projects.

## Support

If you encounter any issues or have suggestions for improvements, please [submit an issue](https://github.com/MrDrElliot/Multi-Window-Plugin/issues) on GitHub.

---

**Note:** Replace `MrDrElliot/Multi-Window-Plugin` with the actual GitHub repository URL for the Multi-Window Plugin.
```
