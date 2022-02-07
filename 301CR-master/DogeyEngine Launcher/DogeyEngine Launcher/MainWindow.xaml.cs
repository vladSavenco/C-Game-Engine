using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

using System.Diagnostics;

namespace DogeyEngine_Launcher
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void Play_Click(object sender, RoutedEventArgs e)
        {
            Process.Start("301CR.exe");
        }

        private void Level_Edit_Click(object sender, RoutedEventArgs e)
        {
            Process.Start("LevelEditor.exe");
        }

        private void Mesh_Click(object sender, RoutedEventArgs e)
        {
            Process.Start("explorer.exe", @"Data\Meshes");
        }

        private void Texture_Click(object sender, RoutedEventArgs e)
        {
            Process.Start("explorer.exe", @"Data\Textures");
        }

        private void Music_Click(object sender, RoutedEventArgs e)
        {
            Process.Start("explorer.exe", @"Data\Music");
        }

        private void Sound_Click(object sender, RoutedEventArgs e)
        {
            Process.Start("explorer.exe", @"Data\Sounds");
        }
    }
}
