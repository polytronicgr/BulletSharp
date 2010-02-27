﻿using BulletSharp;
using DemoFramework;
using SlimDX;
using SlimDX.Direct3D9;
using SlimDX.DirectInput;
using System;
using System.Drawing;
using System.Windows.Forms;

namespace CcdPhysicsDemo
{
    class CcdPhysicsDemo : Game
    {
        int Width = 1024, Height = 768;
        Color ambient = Color.Gray;
        Vector3 eye = new Vector3(0, 10, 40);
        bool DrawDebugLines = true;
        float FieldOfView = (float)Math.PI / 4;

        Matrix Projection;
        Input input;
        FreeLook freelook;
        FpsDisplay fps;
        Mesh box, cylinder, sphere, groundBox;
        Light light;
        Material activeMaterial, passiveMaterial, groundMaterial;
        
        Physics physics;
        PhysicsDebugDraw debugDraw;

        public SlimDX.Direct3D9.Device Device
        {
            get { return Device9; }
        }

        protected override void Dispose(bool disposing)
        {
            base.Dispose(disposing);
            if (disposing)
            {
                input.Dispose();
                box.Dispose();
                cylinder.Dispose();
                groundBox.Dispose();
                fps.Dispose();
            }
        }

        protected override void OnInitialize()
        {
            Form.ClientSize = new Size(Width, Height);
            Form.Text = "BulletSharp - Continuous Collision Detection Demo";

            DeviceSettings9 settings = new DeviceSettings9();
            settings.CreationFlags = CreateFlags.HardwareVertexProcessing;
            settings.Windowed = true;
            settings.MultisampleType = MultisampleType.FourSamples;
            try
            {
                InitializeDevice(settings);
            }
            catch
            {
                // Disable 4xAA if not supported
                settings.MultisampleType = MultisampleType.None;
                InitializeDevice(settings);
            }

            physics = new Physics();

            input = new Input(Form);
            freelook = new FreeLook();
            if (physics.DoBenchmarkPyramids)
                freelook.SetEyeTarget(new Vector3(40, 40, 40), Vector3.Zero);
            else
                freelook.SetEyeTarget(eye, Vector3.Zero);


            box = Mesh.CreateBox(Device, physics.Scaling, physics.Scaling, physics.Scaling);
            cylinder = Mesh.CreateCylinder(Device, physics.Scaling / 2, physics.Scaling /2, physics.Scaling, 16, 1);
            sphere = Mesh.CreateSphere(Device, 1.8f, 16, 16);
            groundBox = Mesh.CreateBox(Device, 400, 100, 400);

            light = new Light();
            light.Type = LightType.Point;
            light.Range = 400;
            light.Position = new Vector3(10, 25, 10);
            light.Falloff = 0.1f;
            light.Diffuse = Color.LemonChiffon;

            //light.Type = LightType.Directional;
            //light.Direction = new Vector3(-1, -1, -1);

            activeMaterial = new Material();
            activeMaterial.Diffuse = Color.Orange;
            activeMaterial.Ambient = ambient;

            passiveMaterial = new Material();
            passiveMaterial.Diffuse = Color.Red;
            passiveMaterial.Ambient = ambient;

            groundMaterial = new Material();
            groundMaterial.Diffuse = Color.Green;
            groundMaterial.Ambient = ambient;

            fps = new FpsDisplay(Device);
            fps.Text = "Move using mouse and WASD\r\n" +
                "F11 - Toggle fullscreen";

            debugDraw = new PhysicsDebugDraw(Device);
            physics.world.DebugDrawer = debugDraw;
            //debugDraw.SetDebugMode(DebugDrawModes.DrawWireframe);
        }

        protected override void OnResourceLoad()
        {
            input.OnResetDevice();

            Device.SetLight(0, light);
            Device.EnableLight(0, true);
            Device.SetRenderState(RenderState.Ambient, new Color4(0.5f, 0.5f, 0.5f).ToArgb());

            Projection = Matrix.PerspectiveFovLH(FieldOfView, AspectRatio, 0.1f, 150.0f);

            Device.SetTransform(TransformState.Projection, Projection);

            fps.OnResourceLoad();
        }

        protected override void OnResourceUnload()
        {
            fps.OnResourceUnload();
        }

        protected override void OnUpdate()
        {
             input.GetCurrentState();

            // Handle mouse events
            if (input.MousePoint != Point.Empty)
            {
                freelook.Update(FrameDelta, input);
                MouseUpdate(input, freelook.Eye, freelook.Target, FieldOfView, physics.world);
            }

            // Handle keyboard events
            if (input.KeyboardState != null)
            {
                // Exit
                if (input.KeyboardState.IsPressed(Key.Escape))
                    Quit();

                if (input.KeyboardDown.Contains(Key.F11))
                    ToggleFullScreen();
            }

            physics.Update(FrameDelta);
        }

        protected override void OnRender()
        {
            Device.Clear(ClearFlags.Target | ClearFlags.ZBuffer, Color.LightGray, 1.0f, 0);
            Device.BeginScene();

            Device.SetTransform(TransformState.View, freelook.View);

            int i;
            for (i = 0; i < physics.world.NumCollisionObjects; i++)
            {
                if (i == 0)
                {
                    Device.Material = groundMaterial;
                    Device.SetTransform(TransformState.World, Matrix.Translation(-Vector3.UnitY * 60));
                    groundBox.DrawSubset(0);
                    continue;
                }

                Matrix trans = Matrix.RotationX((float)Math.PI / 2);
                MotionState ms = null;
                
                CollisionObject colObj = physics.world.CollisionObjectArray[i];
                RigidBody body = RigidBody.Upcast(colObj);

                if (body != null)
                {
                    ms = body.MotionState;
                }

                if (body != null && ms != null)
                    trans *= ms.WorldTransform;
                else
                    trans *= colObj.WorldTransform;

                Device.SetTransform(TransformState.World, trans);

                if (colObj.ActivationState == ActivationState.ActiveTag)
                    Device.Material = activeMaterial;
                else
                    Device.Material = passiveMaterial;

                if (colObj.CollisionShape.ShapeType == BroadphaseNativeType.CylinderShape)
                    cylinder.DrawSubset(0);
                else if (colObj.CollisionShape.ShapeType == BroadphaseNativeType.BoxShape)
                    box.DrawSubset(0);
                else if (colObj.CollisionShape.ShapeType == BroadphaseNativeType.SphereShape)
                    sphere.DrawSubset(0);
            }

            if (DrawDebugLines)
            {
                Device.SetRenderState(RenderState.Lighting, false);
                Device.SetTransform(TransformState.World, Matrix.Identity);
                Device.VertexFormat = PositionColored.FVF;
                physics.world.DebugDrawWorld();
                Device.SetRenderState(RenderState.Lighting, true);
            }

            fps.OnRender(FramesPerSecond);

            Device.EndScene();
            Device.Present();
        }

        class PhysicsDebugDraw : DebugDraw
        {
            SlimDX.Direct3D9.Device device;

            public PhysicsDebugDraw(SlimDX.Direct3D9.Device device)
            {
                this.device = device;
            }

            public override void DrawLine(Vector3 from, Vector3 to, Color4 color)
            {
                PositionColored[] vertices = new PositionColored[2];
                vertices[0] = new PositionColored(from, color.ToArgb());
                vertices[1] = new PositionColored(to, color.ToArgb());
                device.DrawUserPrimitives(PrimitiveType.LineList, 1, vertices);
            }
        }
    }
}
