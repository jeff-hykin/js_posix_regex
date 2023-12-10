import { Module } from "./hello.min.js"

export const rexMatch = (regex, string)=> {
    return JSON.parse(
        Module.ccall("getCapturedGroups", "string", ["string", "string"], [ regex, string ])
    )
}
