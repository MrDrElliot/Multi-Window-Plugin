# Unreal Engine 5 MultiWindow Plugin

The Unreal Engine 5 MultiWindow Plugin enables the creation of external Slate windows for use in both the editor and runtime environments. These windows can host custom user interface elements, providing flexibility and versatility in your Unreal Engine projects.

## Features

- Create external Slate windows with custom titles, sizes, and positions.
- Host UMG widgets inside external windows.
- Support for different dependency types, allowing windows to be tied to specific contexts such as the world or PIE (Play In Editor) sessions.
- Specify sizing rules and support for window maximize and minimize actions.

## Installation

To install the MultiWindow Plugin in your Unreal Engine project, follow these steps:

1. Download the plugin from the [GitHub repository](https://github.com/example/multiwindow-plugin).
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

## Example

```cpp
// Create a new Multi Window
UMW_Window* MyWindow = CreateMultiWindow(
    "My Window", 
    MyUserWidget, 
    EMultiWidgetDependencyType::World,
    FVector2D(100.0f, 100.0f),
    FVector2D(600.0f, 400.0f),
    MyWorld,
    EBPSizingRule::FixedSize,
    true,
    true
);

// Initialize the window
MyWindow->Init();

// Later, shutdown the window
MyWindow->Shutdown();
```

## License

This plugin is provided under the [MIT License](LICENSE). Feel free to use and modify it in your projects.

## Support

If you encounter any issues or have suggestions for improvements, please [submit an issue](https://github.com/example/multiwindow-plugin/issues) on GitHub.

---

**Note:** Replace `example/multiwindow-plugin` with the actual GitHub repository URL for the MultiWindow Plugin.
