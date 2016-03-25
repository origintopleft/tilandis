﻿using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using System.Threading.Tasks;
using Windows.ApplicationModel;
using Windows.ApplicationModel.Activation;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

namespace TilandisUWP
{
    /// <summary>
    /// Provides application-specific behavior to supplement the default Application class.
    /// </summary>
    sealed partial class App : Application {
        /// <summary>
        /// Configuration data.
        /// </summary>
        public static bool bool_darkUI { get; set; }
        public static string str_launchprotocol { get; set; }
        public static string str_controlprotocol { get; set; }

        // Internal use
        private static Windows.Storage.StorageFolder dir_appfolder = Windows.Storage.ApplicationData.Current.LocalFolder;

        /// <summary>
        /// Initializes the singleton application object.  This is the first line of authored code
        /// executed, and as such is the logical equivalent of main() or WinMain().
        /// </summary>
        public App()
        {
            // Note to people who actually read the source code: Yes, I know how suspicious this next line looks.
            // It came with the "blank UWP app" template.
            // At the moment, I'm pretty sure all this does is crash reports unless I explicitly configure
            // it to collect other stuff. Because how else would it know what to collect?
            // I have no interest in anything other than crash reports. I just figured I should lampshade this.
            Microsoft.ApplicationInsights.WindowsAppInitializer.InitializeAsync(
                Microsoft.ApplicationInsights.WindowsCollectors.Metadata |
                Microsoft.ApplicationInsights.WindowsCollectors.Session);
            this.InitializeComponent();
            this.Suspending += OnSuspending;

            // Load config
            Task.Run(() => LoadConfig());
        }

        private static async Task LoadConfig() {
            // load defaults first
            bool_darkUI = false;
            str_launchprotocol = "tilandis";
            str_controlprotocol = "tilectl";
            if (await dir_appfolder.TryGetItemAsync("config.cfg") != null) { // file exists
                // This will only set the config options that are different from defaults.
                Windows.Storage.StorageFile file_config = await dir_appfolder.GetFileAsync("config.cfg");
                IList<string> iter_config = await Windows.Storage.FileIO.ReadLinesAsync(file_config);
                foreach (string line in iter_config) {
                    string[] split = line.Split('=');
                    // an advantage of UWP is I don't have to worry about users mucking with the config files
                    // so i don't have to lowercase everything in code
                    if (split[0] == "darkui") {
                        if (split[1] == "true") { bool_darkUI = true; }
                        else { bool_darkUI = false; }
                    } else if (split[0] == "launch") {
                        str_launchprotocol = split[1];
                    } else if (split[0] == "ctl") {
                        str_controlprotocol = split[1];
                    }
                }
            }
        }

        /// <summary>
        /// Invoked when the application is launched normally by the end user.  Other entry points
        /// will be used such as when the application is launched to open a specific file.
        /// </summary>
        /// <param name="e">Details about the launch request and process.</param>
        protected override void OnLaunched(LaunchActivatedEventArgs e)
        {

#if DEBUG
            if (System.Diagnostics.Debugger.IsAttached)
            {
                this.DebugSettings.EnableFrameRateCounter = true;
            }
#endif

            Frame rootFrame = Window.Current.Content as Frame;

            // Do not repeat app initialization when the Window already has content,
            // just ensure that the window is active
            if (rootFrame == null)
            {
                // Create a Frame to act as the navigation context and navigate to the first page
                rootFrame = new Frame();

                rootFrame.NavigationFailed += OnNavigationFailed;

                if (e.PreviousExecutionState == ApplicationExecutionState.Terminated)
                {
                    //TODO: Load state from previously suspended application
                }

                // Place the frame in the current Window
                Window.Current.Content = rootFrame;
            }

            if (rootFrame.Content == null)
            {
                // When the navigation stack isn't restored navigate to the first page,
                // configuring the new page by passing required information as a navigation
                // parameter
                rootFrame.Navigate(typeof(MainPage), e.Arguments);
            }
            // Ensure the current window is active
            Window.Current.Activate();
        }

        /// <summary>
        /// Invoked when Navigation to a certain page fails
        /// </summary>
        /// <param name="sender">The Frame which failed navigation</param>
        /// <param name="e">Details about the navigation failure</param>
        void OnNavigationFailed(object sender, NavigationFailedEventArgs e)
        {
            throw new Exception("Failed to load Page " + e.SourcePageType.FullName);
        }

        /// <summary>
        /// Invoked when application execution is being suspended.  Application state is saved
        /// without knowing whether the application will be terminated or resumed with the contents
        /// of memory still intact.
        /// </summary>
        /// <param name="sender">The source of the suspend request.</param>
        /// <param name="e">Details about the suspend request.</param>
        private void OnSuspending(object sender, SuspendingEventArgs e)
        {
            var deferral = e.SuspendingOperation.GetDeferral();
            //TODO: Save application state and stop any background activity
            deferral.Complete();
        }
    }
}