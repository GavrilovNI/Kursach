﻿#pragma checksum "..\..\..\WindowMNIST_Digits.xaml" "{ff1816ec-aa5e-4d10-87f7-6f4963833460}" "FA688171EDB3C5598882A15CC147D05146F164E7"
//------------------------------------------------------------------------------
// <auto-generated>
//     Этот код создан программой.
//     Исполняемая версия:4.0.30319.42000
//
//     Изменения в этом файле могут привести к неправильной работе и будут потеряны в случае
//     повторной генерации кода.
// </auto-generated>
//------------------------------------------------------------------------------

using NNDataFiller;
using System;
using System.Diagnostics;
using System.Windows;
using System.Windows.Automation;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Controls.Ribbon;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Ink;
using System.Windows.Input;
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Media.Effects;
using System.Windows.Media.Imaging;
using System.Windows.Media.Media3D;
using System.Windows.Media.TextFormatting;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Shell;


namespace NNDataFiller {
    
    
    /// <summary>
    /// WindowMNIST_Digits
    /// </summary>
    public partial class WindowMNIST_Digits : System.Windows.Window, System.Windows.Markup.IComponentConnector {
        
        
        #line 10 "..\..\..\WindowMNIST_Digits.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Image image;
        
        #line default
        #line hidden
        
        
        #line 12 "..\..\..\WindowMNIST_Digits.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Label label_Digit;
        
        #line default
        #line hidden
        
        
        #line 13 "..\..\..\WindowMNIST_Digits.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button btn_Next;
        
        #line default
        #line hidden
        
        
        #line 16 "..\..\..\WindowMNIST_Digits.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Label label_Count;
        
        #line default
        #line hidden
        
        
        #line 19 "..\..\..\WindowMNIST_Digits.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Label label_Num;
        
        #line default
        #line hidden
        
        
        #line 21 "..\..\..\WindowMNIST_Digits.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button btn_Load;
        
        #line default
        #line hidden
        
        
        #line 22 "..\..\..\WindowMNIST_Digits.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button btn_Save;
        
        #line default
        #line hidden
        
        
        #line 25 "..\..\..\WindowMNIST_Digits.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.TextBox textBox_maxCount;
        
        #line default
        #line hidden
        
        private bool _contentLoaded;
        
        /// <summary>
        /// InitializeComponent
        /// </summary>
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [System.CodeDom.Compiler.GeneratedCodeAttribute("PresentationBuildTasks", "5.0.1.0")]
        public void InitializeComponent() {
            if (_contentLoaded) {
                return;
            }
            _contentLoaded = true;
            System.Uri resourceLocater = new System.Uri("/NNDataFiller;component/windowmnist_digits.xaml", System.UriKind.Relative);
            
            #line 1 "..\..\..\WindowMNIST_Digits.xaml"
            System.Windows.Application.LoadComponent(this, resourceLocater);
            
            #line default
            #line hidden
        }
        
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [System.CodeDom.Compiler.GeneratedCodeAttribute("PresentationBuildTasks", "5.0.1.0")]
        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Never)]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Design", "CA1033:InterfaceMethodsShouldBeCallableByChildTypes")]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Maintainability", "CA1502:AvoidExcessiveComplexity")]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1800:DoNotCastUnnecessarily")]
        void System.Windows.Markup.IComponentConnector.Connect(int connectionId, object target) {
            switch (connectionId)
            {
            case 1:
            this.image = ((System.Windows.Controls.Image)(target));
            return;
            case 2:
            this.label_Digit = ((System.Windows.Controls.Label)(target));
            return;
            case 3:
            this.btn_Next = ((System.Windows.Controls.Button)(target));
            
            #line 13 "..\..\..\WindowMNIST_Digits.xaml"
            this.btn_Next.Click += new System.Windows.RoutedEventHandler(this.btn_next_click);
            
            #line default
            #line hidden
            return;
            case 4:
            this.label_Count = ((System.Windows.Controls.Label)(target));
            return;
            case 5:
            this.label_Num = ((System.Windows.Controls.Label)(target));
            return;
            case 6:
            this.btn_Load = ((System.Windows.Controls.Button)(target));
            
            #line 21 "..\..\..\WindowMNIST_Digits.xaml"
            this.btn_Load.Click += new System.Windows.RoutedEventHandler(this.btn_load_click);
            
            #line default
            #line hidden
            return;
            case 7:
            this.btn_Save = ((System.Windows.Controls.Button)(target));
            
            #line 22 "..\..\..\WindowMNIST_Digits.xaml"
            this.btn_Save.Click += new System.Windows.RoutedEventHandler(this.btn_save_click);
            
            #line default
            #line hidden
            return;
            case 8:
            this.textBox_maxCount = ((System.Windows.Controls.TextBox)(target));
            
            #line 25 "..\..\..\WindowMNIST_Digits.xaml"
            this.textBox_maxCount.PreviewTextInput += new System.Windows.Input.TextCompositionEventHandler(this.AllowOnlyUInt);
            
            #line default
            #line hidden
            
            #line 25 "..\..\..\WindowMNIST_Digits.xaml"
            this.textBox_maxCount.AddHandler(System.Windows.DataObject.PastingEvent, new System.Windows.DataObjectPastingEventHandler(this.AllowOnlyUInt));
            
            #line default
            #line hidden
            return;
            }
            this._contentLoaded = true;
        }
    }
}

