"""Capture a reproducible, synthetic dashboard demonstration in Chromium.

Requires playwright and installed Chromium; outputs a silent MP4 via ffmpeg.
This captures the implemented browser dashboard, not the separate 3D app.
"""
import asyncio
import os
import subprocess
from pathlib import Path
from playwright.async_api import async_playwright

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / "spaceapps_2026" / "artifacts"

async def main():
    OUT.mkdir(parents=True, exist_ok=True)
    async with async_playwright() as p:
        browser = await p.chromium.launch(headless=True, args=["--no-sandbox"])
        page = await browser.new_page(viewport={"width": 1920, "height": 1080}, device_scale_factor=1)
        await page.goto((ROOT / "dashboard" / "index.html").as_uri())
        await page.wait_for_function("document.querySelector('#missionTime').textContent.includes('s')")
        states = []
        for i in range(21):
            await page.evaluate("""i => { frame = i; update(i); }""", i)
            await page.screenshot(path=str(OUT / f"frame_{i:03d}.png"), full_page=False)
            states.append(await page.locator("#healthState").inner_text())
        await browser.close()
    if not {"NOMINAL", "ATTENTION REQUIRED", "CRITICAL ALERT"}.issubset(set(states)):
        raise RuntimeError("Dashboard did not demonstrate all three software states")
    subprocess.run([
        "ffmpeg", "-hide_banner", "-loglevel", "error", "-y",
        "-framerate", "0.5", "-i", str(OUT / "frame_%03d.png"),
        "-c:v", "libx264", "-pix_fmt", "yuv420p",
        "-movflags", "+faststart", str(OUT / "dashboard_demo.mp4")
    ], check=True)
    if (OUT / "dashboard_demo.mp4").stat().st_size < 1024:
        raise RuntimeError("Demonstration video is empty")
    print("Browser demonstration rendered and all three states observed.")

if __name__ == "__main__":
    asyncio.run(main())
